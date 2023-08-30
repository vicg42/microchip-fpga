1. #pragma HLS interface argument(Regs) type(axi_target) num_elements(2)
```
    void hls_main(hls::FIFO< axis_t > &ififo, hls::FIFO< axis_t > &ofifo, AxiRegs_st *Regs) {
    #pragma HLS function top
    #pragma HLS function pipeline
    #pragma HLS interface argument(Regs) type(axi_target) num_elements(2)

    }
``
!!!!!!!Не разлаживате!!!!!!!!!!!!!!!!!
shls rtl_synth

TCL script complete: "hls_main_top_syn.tcl"
TCL script had errors: "hls_main_top_syn.tcl"
exit status=9
exit status=9
Save changes for project:
/home/v.halavachenka/work/vicg42-github/microchip-fpga/hls/prj-simple-pipeline/hls_output/synthesis/hls/synthesis/hls_main_top_syn.prj
batch mode default:no
License checkin: synplifypro_actel
Error:  Synthesis failed.
Error:  The command 'run_tool' failed.
Error:  Failure when executing Tcl script. [ Line 54 ]
Error:  The Execute Script command failed.
The hls project was closed.


1. hls_main(hls::FIFO< axis_t > &ififo, hls::FIFO< axis_t > &ofifo, AxiRegs_st *Regs)



#--------------------------------------------------------
# AXI_slave + register synhronization (internal user regs as internal variables) + modelsim works incorrect
#--------------------------------------------------------
==================================================================
=====  Summary Report for RTL Simulation and FPGA Synthesis  =====
==================================================================

Project name: hls
FPGA Vendor: MICROSEMI
Device Family: PolarFire
Device: MPF300TS-1FCG1152I

Table of Contents
  1. Simulation Result
  2. Timing Result of HLS-generated IP Core
  3. Resource Usage of HLS-generated IP Core


====== 1. Simulation Result ======

Number of calls: 16,800
Cycle latency: 151,200
SW/HW co-simulation: PASS

====== 2. Timing Result of HLS-generated IP Core (top-level module: hls_main_top) ======

N/A. Please run 'Synthesize Hardware to FPGA' to obtain the timing result.

====== 3. Resource Usage of HLS-generated IP Core (top-level module: hls_main_top) ======

+--------------------------+----------------+--------+------------+
| Resource Type            | Used           | Total  | Percentage |
+--------------------------+----------------+--------+------------+
| Fabric + Interface 4LUT* | 424 + 36 = 460 | 299544 | 0.15       |
| Fabric + Interface DFF*  | 237 + 36 = 273 | 299544 | 0.09       |
| I/O Register             | 0              | 1536   | 0.00       |
| User I/O                 | 0              | 512    | 0.00       |
| uSRAM                    | 0              | 2772   | 0.00       |
| LSRAM                    | 0              | 952    | 0.00       |
| Math                     | 1              | 924    | 0.11       |
+--------------------------+----------------+--------+------------+

* Interface 4LUTs and DFFs are occupied due to the uses of LSRAM, Math, and uSRAM.
  Number of interface 4LUTs/DFFs = (36 * #.LSRAM) + (36 * #.Math) + (12 * #.uSRAM) = (36 * 0) + (36 * 1) + (12 * 0) = 36.

====== 4. Memory Usage ======

+------------------------------------------------------------------------------------------------------------------+
| Local Memories                                                                                                   |
+-----------------------------+-----------------------+----------+-------------+------------+-------+--------------+
| Name                        | Accessing Function(s) | Type     | Size [Bits] | Data Width | Depth | Read Latency |
+-----------------------------+-----------------------+----------+-------------+------------+-------+--------------+
| axi_s_read_burst_len_minus1 | AxiRegs_read          | Register | 8           | 8          | 1     | 0            |
| axi_s_read_count            | AxiRegs_read          | Register | 8           | 8          | 1     | 0            |
| axi_s_read_state            | AxiRegs_read          | Register | 1           | 1          | 1     | 0            |
| axi_s_read_word_addr        | AxiRegs_read          | Register | 32          | 32         | 1     | 0            |
| axi_s_write_count           | AxiRegs_write         | Register | 8           | 8          | 1     | 0            |
| axi_s_write_state           | AxiRegs_write         | Register | 1           | 1          | 1     | 0            |
| axi_s_write_word_addr       | AxiRegs_write         | Register | 32          | 32         | 1     | 0            |
+-----------------------------+-----------------------+----------+-------------+------------+-------+--------------+

+-------------------------+
| Local Constant Memories |
+-------------------------+
| None                    |
+-------------------------+

+--------------------------------------------------------------------------------------------------------------------------+
| Shared Local Memories                                                                                                    |
+----------------+--------------------------------------------+----------+-------------+------------+-------+--------------+
| Name           | Accessing Function(s)                      | Type     | Size [Bits] | Data Width | Depth | Read Latency |
+----------------+--------------------------------------------+----------+-------------+------------+-------+--------------+
| AxiRegs_bypass | AxiRegs_read, AxiRegs_write, hls_main_orig | Register | 16          | 16         | 1     | 0            |
| AxiRegs_ctrl   | AxiRegs_read, AxiRegs_write                | Register | 1           | 1          | 1     | 0            |
| AxiRegs_ctrl1  | AxiRegs_read, AxiRegs_write, hls_main_orig | Register | 16          | 16         | 1     | 0            |
| AxiRegs_ctrl2  | AxiRegs_read, AxiRegs_write, hls_main_orig | Register | 16          | 16         | 1     | 0            |
| AxiRegs_status | AxiRegs_read, AxiRegs_write, hls_main_orig | Register | 16          | 16         | 1     | 0            |
+----------------+--------------------------------------------+----------+-------------+------------+-------+--------------+

+------------------+
| Aliased Memories |
+------------------+
| None             |
+------------------+







#--------------------------------------------------------
# AXI SLAVE + register synhronization (internal user regs as global variables)
#--------------------------------------------------------

==================================================================
=====  Summary Report for RTL Simulation and FPGA Synthesis  =====
==================================================================

Project name: hls
FPGA Vendor: MICROSEMI
Device Family: PolarFire
Device: MPF300TS-1FCG1152I

Table of Contents
  1. Simulation Result
  2. Timing Result of HLS-generated IP Core
  3. Resource Usage of HLS-generated IP Core


====== 1. Simulation Result ======

Number of calls: 16,800
Cycle latency: 151,200
SW/HW co-simulation: PASS

====== 2. Timing Result of HLS-generated IP Core (top-level module: hls_main_top) ======

N/A. Please run 'Synthesize Hardware to FPGA' to obtain the timing result.

====== 3. Resource Usage of HLS-generated IP Core (top-level module: hls_main_top) ======

+--------------------------+----------------+--------+------------+
| Resource Type            | Used           | Total  | Percentage |
+--------------------------+----------------+--------+------------+
| Fabric + Interface 4LUT* | 442 + 36 = 478 | 299544 | 0.16       |
| Fabric + Interface DFF*  | 272 + 36 = 308 | 299544 | 0.10       |
| I/O Register             | 0              | 1536   | 0.00       |
| User I/O                 | 0              | 512    | 0.00       |
| uSRAM                    | 0              | 2772   | 0.00       |
| LSRAM                    | 0              | 952    | 0.00       |
| Math                     | 1              | 924    | 0.11       |
+--------------------------+----------------+--------+------------+

* Interface 4LUTs and DFFs are occupied due to the uses of LSRAM, Math, and uSRAM.
  Number of interface 4LUTs/DFFs = (36 * #.LSRAM) + (36 * #.Math) + (12 * #.uSRAM) = (36 * 0) + (36 * 1) + (12 * 0) = 36.

  ====== 4. Memory Usage ======

+------------------------------------------------------------------------------------------------------------------+
| Local Memories                                                                                                   |
+-----------------------------+-----------------------+----------+-------------+------------+-------+--------------+
| Name                        | Accessing Function(s) | Type     | Size [Bits] | Data Width | Depth | Read Latency |
+-----------------------------+-----------------------+----------+-------------+------------+-------+--------------+
| axi_s_read_burst_len_minus1 | AxiRegs_read          | Register | 8           | 8          | 1     | 0            |
| axi_s_read_count            | AxiRegs_read          | Register | 8           | 8          | 1     | 0            |
| axi_s_read_state            | AxiRegs_read          | Register | 1           | 1          | 1     | 0            |
| axi_s_read_word_addr        | AxiRegs_read          | Register | 32          | 32         | 1     | 0            |
| axi_s_write_count           | AxiRegs_write         | Register | 8           | 8          | 1     | 0            |
| axi_s_write_state           | AxiRegs_write         | Register | 1           | 1          | 1     | 0            |
| axi_s_write_word_addr       | AxiRegs_write         | Register | 32          | 32         | 1     | 0            |
| regA                        | hls_main_orig         | Register | 16          | 16         | 1     | 0            |
| regB                        | hls_main_orig         | Register | 16          | 16         | 1     | 0            |
| regC                        | hls_main_orig         | Register | 8           | 8          | 1     | 0            |
+-----------------------------+-----------------------+----------+-------------+------------+-------+--------------+

+-------------------------+
| Local Constant Memories |
+-------------------------+
| None                    |
+-------------------------+

+--------------------------------------------------------------------------------------------------------------------------+
| Shared Local Memories                                                                                                    |
+----------------+--------------------------------------------+----------+-------------+------------+-------+--------------+
| Name           | Accessing Function(s)                      | Type     | Size [Bits] | Data Width | Depth | Read Latency |
+----------------+--------------------------------------------+----------+-------------+------------+-------+--------------+
| AxiRegs_bypass | AxiRegs_read, AxiRegs_write, hls_main_orig | Register | 16          | 16         | 1     | 0            |
| AxiRegs_ctrl   | AxiRegs_read, AxiRegs_write                | Register | 1           | 1          | 1     | 0            |
| AxiRegs_ctrl1  | AxiRegs_read, AxiRegs_write, hls_main_orig | Register | 16          | 16         | 1     | 0            |
| AxiRegs_ctrl2  | AxiRegs_read, AxiRegs_write, hls_main_orig | Register | 16          | 16         | 1     | 0            |
| AxiRegs_status | AxiRegs_read, AxiRegs_write, hls_main_orig | Register | 16          | 16         | 1     | 0            |
+----------------+--------------------------------------------+----------+-------------+------------+-------+--------------+

+------------------+
| Aliased Memories |
+------------------+
| None             |
+------------------+