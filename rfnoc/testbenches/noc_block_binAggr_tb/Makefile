

# Copyright 2016 Ettus Research


#-------------------------------------------------
# Top-of-Makefile
#-------------------------------------------------
# Define BASE_DIR to point to the "top" dir
#/users/nae/gnuradio_RFNOC/src/uhd-fpga = ~/gnuradio_RFNOC/src/uhd-fpga
BASE_DIR = /users/nae/gnuradio_RFNOC/src/uhd-fpga/usrp3/top
#BASE_DIR = $(/users/nae/gnuradio_RFNOC/src/uhd-fpga)/usrp3/top
# Include viv_sim_preample after defining BASE_DIR
$(info BASE_DIR is $(BASE_DIR))
include $(BASE_DIR)/../tools/make/viv_sim_preamble.mak

#-------------------------------------------------
# Testbench Specific
#-------------------------------------------------
# Define only one toplevel module
SIM_TOP = noc_block_binAggr_tb

# Add test bench, user design under test, and
# additional user created files
SIM_SRCS = \
$(abspath noc_block_binAggr_tb.sv) \
$(abspath ../../fpga-src/noc_block_binAggr.v)

MODELSIM_USER_DO =

#-------------------------------------------------
# Bottom-of-Makefile
#-------------------------------------------------
# Include all simulator specific makefiles here
# Each should define a unique target to simulate
# e.g. xsim, vsim, etc and a common "clean" target
include $(BASE_DIR)/../tools/make/viv_simulator.mak
#$(info ########### Line 37 from ../rfnoc/testbenches/noc_block_binAggr_tb/Makefile  ###########)
