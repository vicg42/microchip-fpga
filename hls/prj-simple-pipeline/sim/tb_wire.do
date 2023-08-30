#-----------------------------------------------------------------------
# Author : Viktor Golovachenko
#-----------------------------------------------------------------------
file delete -force -- work

vlib work

vlog ../hls_output/rtl/hls_hls_main.v
vlog ./tb_wire.sv

vsim -t 1ps -lib work cosim_tb

do tb_wire_wave.do
view wave
view structure
view signals
#run 320000ns
run 10000ns

#quit -force
