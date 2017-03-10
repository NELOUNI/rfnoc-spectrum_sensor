/* -*- c++ -*- */

#define SPECTRUM_SENSOR_API
#define ETTUS_API

%include "gnuradio.i"/*			*/// the common stuff

//load generated python docstrings
%include "spectrum_sensor_swig_doc.i"
//Header from gr-ettus
%include "ettus/device3.h"
%include "ettus/rfnoc_block.h"
%include "ettus/rfnoc_block_impl.h"

%{
#include "ettus/device3.h"
#include "ettus/rfnoc_block_impl.h"
#include "spectrum_sensor/binAggr.h"
%}

%include "spectrum_sensor/binAggr.h"
GR_SWIG_BLOCK_MAGIC2(spectrum_sensor, binAggr);
