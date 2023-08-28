onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -group /cosim_tb -radix unsigned /cosim_tb/clk
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/output_ports_finished
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/clk
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/finish
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/ready
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_ready
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/start
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/reset
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/ready_TO_DUT_DS
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/all_init
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/calls_started
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/accel_start
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/accel_ready
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/accel_finish
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/cycle_count
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/ififo_ctrl_ready_FROM_DUT_US
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/ififo_ctrl_valid_TO_DUT_US
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/ififo_ctrl_tdata_data_TO_DUT_US
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/ififo_ctrl_tlast_data_TO_DUT_US
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/ififo_ctrl_tuser_data_TO_DUT_US
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/ififo_ready_FROM_DUT_US
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/ififo_valid_TO_DUT_US
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/ififo_tdata_data_TO_DUT_US
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/ififo_tlast_data_TO_DUT_US
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/ififo_tuser_data_TO_DUT_US
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/ofifo_valid_FROM_DUT_DS
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/ofifo_ready_TO_DUT_DS
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/ofifo_tdata_data_FROM_DUT_DS
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/ofifo_tlast_data_FROM_DUT_DS
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/ofifo_tuser_data_FROM_DUT_DS
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/ififo_ctrl_tdata_data_transfer_handshake
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/ififo_ctrl_tlast_data_transfer_handshake
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/ififo_ctrl_tuser_data_transfer_handshake
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/ififo_tdata_data_transfer_handshake
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/ififo_tlast_data_transfer_handshake
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/ififo_tuser_data_transfer_handshake
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/ofifo_tdata_done
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/ofifo_tlast_done
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/ofifo_tuser_done
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/all_done
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/finished
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/clk
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/reset
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/start
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ready
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/finish
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ififo_ctrl_tdata
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ififo_ctrl_ready
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ififo_ctrl_valid
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ififo_ctrl_tlast
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ififo_ctrl_tuser
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ififo_tdata
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ififo_ready
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ififo_valid
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ififo_tlast
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ififo_tuser
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ofifo_tdata
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ofifo_ready
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ofifo_valid
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ofifo_tlast
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ofifo_tuser
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst_clk
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst_reset
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst_start
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst_ready
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst_finish
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst_ififo_ctrl_tdata
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst_ififo_ctrl_ready
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst_ififo_ctrl_valid
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst_ififo_ctrl_tlast
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst_ififo_ctrl_tuser
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst_ififo_tdata
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst_ififo_ready
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst_ififo_valid
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst_ififo_tlast
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst_ififo_tuser
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst_ofifo_tdata
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst_ofifo_ready
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst_ofifo_valid
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst_ofifo_tlast
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst_ofifo_tuser
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst_finish_reg
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/clk
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/reset
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/start
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ready
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/finish
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ififo_ctrl_tdata
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ififo_ctrl_ready
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ififo_ctrl_valid
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ififo_ctrl_tlast
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ififo_ctrl_tuser
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ififo_tdata
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ififo_ready
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ififo_valid
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ififo_tlast
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ififo_tuser
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ofifo_tdata
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ofifo_ready
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ofifo_valid
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ofifo_tlast
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ofifo_tuser
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_entry_0
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_entry_NotCondition
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_entry_1
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_entry_bit_select2
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_entry_bit_select1
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_entry_3
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_entry_NotCondition2
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_entry_exitMask_F3
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_entry_tobool
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_entry_bit_concat3
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_entry_s_or10
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_entry_not_s_or10
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_entry_select12
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_entry_select9
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_entry_select
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_entry_4
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_entry_NotCondition5
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_entry_5
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_entry_6
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_entry_7
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_entry_exitMask_T13
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_entry_tobool_not
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_entry_NotCondition14
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_entry_exitMask_F15
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_entry_bit_concat
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_entry_8
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_entry_bit_select
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_entry_9
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_valid_bit_0
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_state_stall_0
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_state_enable_0
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_valid_bit_1
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_state_stall_1
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_state_enable_1
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_II_counter
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_entry_select_reg_stage1
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_entry_5_reg_stage1
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_entry_6_reg_stage1
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_entry_7_reg_stage1
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_entry_exitMask_T13_reg_stage1
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_entry_exitMask_F15_reg_stage1
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ififo_ctrl_tdata_consumed_valid
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ififo_ctrl_tdata_consumed_data
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ififo_ctrl_tdata_consumed_taken
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ififo_ctrl_tlast_consumed_valid
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ififo_ctrl_tlast_consumed_taken
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ififo_ctrl_tuser_consumed_valid
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ififo_ctrl_tuser_consumed_data
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ififo_ctrl_tuser_consumed_taken
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_entry_bit_concat3_bit_select_operand_0
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ififo_tdata_consumed_valid
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ififo_tdata_consumed_data
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ififo_tdata_consumed_taken
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ififo_tlast_consumed_valid
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ififo_tlast_consumed_data
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ififo_tlast_consumed_taken
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ififo_tuser_consumed_valid
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ififo_tuser_consumed_data
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ififo_tuser_consumed_taken
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ofifo_tdata_hls_main_state_1_not_accessed_due_to_stall_a
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ofifo_tdata_hls_main_state_1_stalln_reg
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ofifo_tdata_hls_main_state_1_enable_cond_a
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ofifo_tlast_hls_main_state_1_not_accessed_due_to_stall_a
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ofifo_tlast_hls_main_state_1_stalln_reg
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ofifo_tlast_hls_main_state_1_enable_cond_a
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ofifo_tuser_hls_main_state_1_not_accessed_due_to_stall_a
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ofifo_tuser_hls_main_state_1_stalln_reg
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/ofifo_tuser_hls_main_state_1_enable_cond_a
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/hls_main_entry_bit_concat_bit_select_operand_0
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/legup_mult_unsigned_16_16_1_0_clock
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/legup_mult_unsigned_16_16_1_0_aclr
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/legup_mult_unsigned_16_16_1_0_clken
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/legup_mult_unsigned_16_16_1_0_dataa
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/legup_mult_unsigned_16_16_1_0_datab
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/legup_mult_unsigned_16_16_1_0_result
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/legup_mult_hls_main_entry_8_out_actual
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/legup_mult_hls_main_entry_8_out
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/legup_mult_hls_main_entry_8_en
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/legup_mult_hls_main_entry_8_en_pipeline_cond
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/legup_mult_unsigned_16_16_1_0 -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/legup_mult_unsigned_16_16_1_0/clock
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/legup_mult_unsigned_16_16_1_0 -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/legup_mult_unsigned_16_16_1_0/aclr
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/legup_mult_unsigned_16_16_1_0 -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/legup_mult_unsigned_16_16_1_0/clken
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/legup_mult_unsigned_16_16_1_0 -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/legup_mult_unsigned_16_16_1_0/dataa
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/legup_mult_unsigned_16_16_1_0 -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/legup_mult_unsigned_16_16_1_0/datab
add wave -noupdate -group /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/legup_mult_unsigned_16_16_1_0 -radix unsigned /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/hls_main_inst/legup_mult_unsigned_16_16_1_0/result
add wave -noupdate -radix hexadecimal /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ififo_ctrl_tdata
add wave -noupdate /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ififo_ctrl_ready
add wave -noupdate /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ififo_ctrl_valid
add wave -noupdate /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ififo_ctrl_tlast
add wave -noupdate /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ififo_ctrl_tuser
add wave -noupdate -radix hexadecimal /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ififo_tdata
add wave -noupdate /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ififo_ready
add wave -noupdate /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ififo_valid
add wave -noupdate /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ififo_tlast
add wave -noupdate /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ififo_tuser
add wave -noupdate -radix hexadecimal /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ofifo_tdata
add wave -noupdate /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ofifo_ready
add wave -noupdate /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ofifo_valid
add wave -noupdate /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ofifo_tlast
add wave -noupdate /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ofifo_tuser
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {0 ns} 0}
quietly wave cursor active 0
configure wave -namecolwidth 300
configure wave -valuecolwidth 100
configure wave -justifyvalue left
configure wave -signalnamewidth 1
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
WaveRestoreZoom {0 ns} {353105 ns}
