`timescale 1 ns / 1 ns
module hls_main_top_tb ();
localparam NUM_CALLS = 16800;
localparam AXI_VERBOSE_LEVEL = 0;

localparam INPUT_FIFO_STALL_PROB = 0;
localparam OUTPUT_FIFO_STALL_PROB = 0;
localparam MAX_STALL_CYCLES = 5;


integer output_ports_finished = 0;
//integer mismatches = 0;

reg clk;
initial clk = 0;
always @(clk) clk <= #10 ~clk;

wire finish;
reg ready;
reg DUT_ready;

// start.
reg start = 0;
// reset.
reg reset = 1;
reg ready_TO_DUT_DS = 0;
wire all_init;
integer calls_started = 0;
initial begin
    repeat (10) @(negedge clk);
    reset = 0;
    @(posedge clk);
    ready_TO_DUT_DS = 1;
    while(calls_started < NUM_CALLS) begin
        wait(all_init == 0)
        start = 1;
        while (1)
            @ (posedge clk)
                if (DUT_ready) begin
                    start = 0;
                    calls_started = calls_started + 1;
                    break;
                end
    end
end

reg accel_start;
reg accel_ready;
reg accel_finish;
assign accel_start = start;
assign accel_ready = ready;
assign accel_finish = finish;


integer cycle_count = 0;
always @ (posedge clk) begin
    if (reset)
        cycle_count <= 0;
    else if (!all_init)
        cycle_count <= cycle_count + 1;
end

wire axis_i_tready;
reg axis_i_tvalid;
reg [15:0] axis_i_tdata;
reg [0:0] axis_i_tlast;
reg [1:0] axis_i_tuser;

wire axis_o_tready;
wire axis_o_tvalid;
wire [15:0] axis_o_tdata;
wire [0:0] axis_o_tlast;
wire [1:0] axis_o_tuser;

assign axis_o_tready = 1'b1;

parameter AXI_SLAVE_ADDR_WIDTH = 32;
parameter AXI_SLAVE_DATA_WIDTH = 64;

// 64-bit AXI4 Slave interface
// address read channel
reg [31:0] s_araddr = 0;
reg [7:0] s_arlen = 0;
wire s_arready;
reg s_arvalid = 0;

// address write channel
reg [31:0] s_awaddr = 0;
wire s_awready;
reg s_awvalid = 0;
reg [7:0] s_awlen = 0;

// response channel
wire [1:0] s_bresp;
reg s_bready = 0;
wire s_bvalid;

// read data channel
wire [63:0] s_rdata;
wire s_rlast;
wire [1:0] s_rresp;
reg s_rready = 0;
wire s_rvalid;

// write data channel
reg [63:0] s_wdata = 0;
reg s_wlast = 0;
reg [7:0] s_wstrb = 8'hFF;
wire s_wready;
reg s_wvalid = 0;

task automatic axi_slave_write;
  input [AXI_SLAVE_ADDR_WIDTH - 1 : 0] addr;
  input [AXI_SLAVE_DATA_WIDTH - 1 : 0] data;
  begin
    $display("AXI4 Slave write addr=%d data=0x%x", addr, data);

    // $display("Waiting for ififo_tlast");
    // wait(axis_i_tlast == 1);
    // $display("run AXI4 Slave write");

    $display("Waiting for s_wready");

    s_awaddr = addr;
    s_awvalid = 1;
    s_awlen = 0;

    s_wdata = data;
    s_wvalid = 1;
    s_wlast = 1;
    s_bready = 1;

    while (1) begin
        @(posedge clk) begin
            if (s_awready) begin
                s_awvalid = 0;
                // $display("Received s_awready");
            end
            if (s_wready) begin
                s_wvalid = 0;
                // $display("Received s_wready");
            end
        end
        if (~s_awvalid & ~s_wvalid)
            break;
    end

    s_wlast = 0;

    // The start signal assertion and the wait of s_bvalid should happen in
    // parallel otherwise we may miss the s_bvalid pulse.
    fork
    //   begin
    //     // start signal for the rest of the testbench
    //     start = 1;
    //     @(posedge clk) #1 start = 0;
    //   end

      begin
        // $display("Waiting for s_bresp");
        wait(s_bvalid);
        // $display("Received s_bresp: %b", s_bresp);
      end
    join

  end
endtask

task automatic axi_slave_read;
  input [AXI_SLAVE_ADDR_WIDTH - 1 : 0] addr;
  output [AXI_SLAVE_DATA_WIDTH - 1 : 0] data;
  begin
//    $display("Waiting for s_arready");

    s_araddr = addr;
    s_arvalid = 1;
    s_arlen = 0;
    s_rready = 0;

    while (1) begin
        @(posedge clk) begin
            if (s_arready) begin
                s_arvalid = 0;
//                $display("Received s_arready");
                break;
            end
        end
    end

    s_rready = 1;
//    $display("Waiting for s_rvalid");
    while (1) begin
        @(posedge clk) begin
            if (s_rvalid) begin
                s_rready = 0;
                data = s_rdata;
//                $display("Received s_rvalid");
                break;
            end
        end
    end
//    $display("AXI4 Slave read addr=%d data=0x%x", addr, data);
  end
endtask


initial begin : axi_slave
    reg [AXI_SLAVE_DATA_WIDTH-1:0] wdata;
    reg [AXI_SLAVE_DATA_WIDTH-1:0] rdata;
    reg [AXI_SLAVE_ADDR_WIDTH-1:0] addr;

    wait(~reset);
    wait(DUT_ready == 1);

    #1000;
    addr = 0;
    wdata = 64'd8;
    axi_slave_write(addr, wdata);

    #1000;
    addr = 0;
    wdata = 64'd10;
    axi_slave_write(addr, wdata);

    #2000;
    addr = 0;
    wdata = 64'h10000;
    axi_slave_write(addr, wdata);

end

hls_main_top DUT_hls_main_top (
    .clk( clk ),
    .reset( reset ),
    .start( start ),
    .ready( DUT_ready ),
    .finish( finish ),

    .axi_s_aw_addr  (s_awaddr ), //(0),    //in
    .axi_s_aw_len   (s_awlen  ), //(0),    //in
    .axi_s_aw_ready (s_awready), //(),     //out
    .axi_s_aw_valid (s_awvalid), //(1'b0), //in

    .axi_s_w_data   (s_wdata ), //(0), //in
    .axi_s_w_strb   (s_wstrb ), //(0), //in
    .axi_s_w_last   (s_wlast ), //(0), //in
    .axi_s_w_ready  (s_wready), //(),  //out
    .axi_s_w_valid  (s_wvalid), //(0), //in

    .axi_s_b_resp       (s_bresp ), //(),     //out
    .axi_s_b_resp_ready (s_bready), //(1'b1), //in
    .axi_s_b_resp_valid (s_bvalid), //(),     //out

    .axi_s_ar_addr  (s_araddr ), //(0), //in
    .axi_s_ar_len   (s_arlen  ), //(0), //in
    .axi_s_ar_ready (s_arready), //() , //out
    .axi_s_ar_valid (s_arvalid), //(0), //in

    .axi_s_r_data  (s_rdata ), //(),     //out
    .axi_s_r_ready (s_rready), //(1'b1), //in
    .axi_s_r_valid (s_rvalid), //(),     //out
    .axi_s_r_resp  (s_rresp ), //(),     //out
    .axi_s_r_last  (s_rlast ), //(),     //out

    // Input FIFO argument: ififo_tdata
    .ififo_ready( axis_i_tready), //out
    .ififo_valid( axis_i_tvalid), //in
    .ififo_tdata( axis_i_tdata ), //in
    .ififo_tlast( axis_i_tlast ), //in
    .ififo_tuser( axis_i_tuser ), //in

    // Output FIFO argument: ofifo_tdata
    .ofifo_ready( axis_o_tready), //in
    .ofifo_valid( axis_o_tvalid), //out
    .ofifo_tdata( axis_o_tdata ), //out
    .ofifo_tlast( axis_o_tlast ), //out
    .ofifo_tuser( axis_o_tuser )  //out
);


initial begin : ififo
    integer transfers;
    integer i;
    integer calls;
    reg [15:0] in;
    calls = 0;
    axis_i_tvalid = 0;
    axis_i_tuser = 0;
    axis_i_tlast = 0;
    in = 0;
    transfers = 100;

    while(calls < NUM_CALLS) begin
        // if (calls < 100)
        //     $display("Initializing input FIFO contents ififo_tdata at cycle = %d", cycle_count);

        for (i = 0; i < transfers; i = i + 1) begin
            do @(posedge clk); while (!axis_i_tready);
            axis_i_tvalid = 1;
            axis_i_tdata = in;
            if (i==0) begin
                axis_i_tuser = 1;
            end else begin
                axis_i_tuser = 0;
            end
            if (i == (transfers-1)) begin
                axis_i_tlast = 1;
            end
            in = in + 1;
            #1;
        end

        @(posedge clk);
        axis_i_tvalid = 0;
        axis_i_tlast = 0;
        axis_i_tdata = in;
        #1;

        calls = calls + 1;
    end
    axis_i_tvalid = 0;
end


assign all_init = 0;

reg finished;

initial begin : finish_condition
    integer finish_count;
    finished = 0;
    finish_count = 0;
    while (finish_count < NUM_CALLS) begin
        if (finish) begin
            finish_count = finish_count + 1;
            // if ((finish_count < 100) || (finish_count >= 100 && finish_count % 100 == 0))
            //     $display("%d / %d function calls completed.", finish_count, NUM_CALLS);
            // if (finish_count == 100)
            //     $display("\n### Suppressing repeated log messages after 100-th calls. ###\n\n");
        end
        // wait(all_init == 0);
        @(posedge clk);
    end
    // while (!all_done) begin
    //     @(posedge clk);
    // end
    $display("Number of calls: %d", NUM_CALLS);
    $display("Cycle latency: %d", cycle_count);
    finished = 1;
end

endmodule


module cosim_tb();
initial $display("Running SW/HW co-simulation...");
    reg clk;
    initial clk = 0;
    always @(clk) clk <= #10 ~clk;

    hls_main_top_tb hls_main_top_tb_inst();

    initial begin : finish_condition
        while (!(hls_main_top_tb_inst.finished)) begin
            @(posedge clk);
        end
        $finish;
end
endmodule
