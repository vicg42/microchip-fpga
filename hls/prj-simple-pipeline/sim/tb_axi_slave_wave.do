onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/clk
add wave -noupdate /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/reset
add wave -noupdate /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/start
add wave -noupdate /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ready
add wave -noupdate /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/finish
add wave -noupdate -divider IN-FIFO
add wave -noupdate -radix hexadecimal /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ififo_tdata
add wave -noupdate /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ififo_ready
add wave -noupdate /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ififo_valid
add wave -noupdate {/cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ififo_tuser[0]}
add wave -noupdate /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ififo_tlast
add wave -noupdate -divider OUT-FIFO
add wave -noupdate -radix hexadecimal /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ofifo_tdata
add wave -noupdate /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ofifo_ready
add wave -noupdate /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ofifo_valid
add wave -noupdate {/cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ofifo_tuser[0]}
add wave -noupdate /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ofifo_tlast
add wave -noupdate -divider AXI-REGs
add wave -noupdate -radix hexadecimal /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/AxiRegs_status_inst/register
add wave -noupdate -radix hexadecimal /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/AxiRegs_bypass_inst/register
add wave -noupdate -radix hexadecimal /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/AxiRegs_ctrl1_inst/register
add wave -noupdate -radix hexadecimal /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/AxiRegs_ctrl2_inst/register
add wave -noupdate -divider AXI
add wave -noupdate -radix hexadecimal /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/axi_s_aw_addr
add wave -noupdate -radix hexadecimal /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/axi_s_aw_ready
add wave -noupdate -radix hexadecimal /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/axi_s_aw_valid
add wave -noupdate -radix hexadecimal /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/axi_s_aw_burst
add wave -noupdate -radix hexadecimal /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/axi_s_aw_size
add wave -noupdate -radix hexadecimal /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/axi_s_aw_len
add wave -noupdate -radix hexadecimal /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/axi_s_w_data
add wave -noupdate -radix hexadecimal /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/axi_s_w_ready
add wave -noupdate -radix hexadecimal /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/axi_s_w_valid
add wave -noupdate -radix hexadecimal /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/axi_s_w_strb
add wave -noupdate -radix hexadecimal /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/axi_s_w_last
add wave -noupdate -radix hexadecimal /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/axi_s_b_resp
add wave -noupdate -radix hexadecimal /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/axi_s_b_resp_ready
add wave -noupdate -radix hexadecimal /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/axi_s_b_resp_valid
add wave -noupdate -radix hexadecimal /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/axi_s_ar_addr
add wave -noupdate -radix hexadecimal /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/axi_s_ar_ready
add wave -noupdate -radix hexadecimal /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/axi_s_ar_valid
add wave -noupdate -radix hexadecimal /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/axi_s_ar_burst
add wave -noupdate -radix hexadecimal /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/axi_s_ar_size
add wave -noupdate -radix hexadecimal /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/axi_s_ar_len
add wave -noupdate -radix hexadecimal /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/axi_s_r_data
add wave -noupdate -radix hexadecimal /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/axi_s_r_ready
add wave -noupdate -radix hexadecimal /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/axi_s_r_valid
add wave -noupdate -radix hexadecimal /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/axi_s_r_resp
add wave -noupdate -radix hexadecimal /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/axi_s_r_last
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {8284 ps} 0}
quietly wave cursor active 1
configure wave -namecolwidth 418
configure wave -valuecolwidth 100
configure wave -justifyvalue left
configure wave -signalnamewidth 0
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 10000
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits ns
update
WaveRestoreZoom {0 ps} {10500 ns}
