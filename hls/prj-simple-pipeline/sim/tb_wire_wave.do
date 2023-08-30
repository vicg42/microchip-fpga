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
add wave -noupdate -radix hexadecimal /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/bypass
add wave -noupdate -radix hexadecimal /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ctrl1
add wave -noupdate -radix hexadecimal /cosim_tb/hls_main_top_tb_inst/DUT_hls_main_top/ctrl2
add wave -noupdate -divider AXI
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
