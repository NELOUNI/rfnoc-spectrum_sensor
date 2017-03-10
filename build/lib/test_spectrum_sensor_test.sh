#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/raid/nae/gnuradio_RFNOC/src/rfnoc-spectrum_sensor/lib
export PATH=/raid/nae/gnuradio_RFNOC/src/rfnoc-spectrum_sensor/build/lib:$PATH
export LD_LIBRARY_PATH=/raid/nae/gnuradio_RFNOC/src/rfnoc-spectrum_sensor/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$PYTHONPATH
test-spectrum_sensor 
