/* -*- c++ -*- */
/* 
 * Copyright 2016 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_SPECTRUM_SENSOR_BINAGGR_IMPL_H
#define INCLUDED_SPECTRUM_SENSOR_BINAGGR_IMPL_H

#include <spectrum_sensor/binAggr.h>
#include <spectrum_sensor/binAggr_block_ctrl.hpp>
#include <ettus/rfnoc_block_impl.h>

namespace gr {
  namespace spectrum_sensor {

    class binAggr_impl : public binAggr, public gr::ettus::rfnoc_block_impl
    {
     private:
      // Nothing to declare in this block.

     public:
      binAggr_impl(
        const int fft_size,
        const int nbr_bins,
        const int samp_rate,
        const int center_freq,
        const int bandwidth,
        const int channel_bw,
	std::vector<unsigned int> output_bin_index,

        const gr::ettus::device3::sptr &dev,
        //const ::uhd::stream_args_t &tx_stream_args,
        //const ::uhd::stream_args_t &rx_stream_args,
        const int block_select,
        const int device_select
      );
      ~binAggr_impl();

      void set_bin_index(const int fft_size, const int nbr_bins, const int samp_rate, const int center_freq, const int bandwidth, const int channel_bw, std::vector<unsigned int> output_bin_index);

    };

  } // namespace spectrum_sensor
} // namespace gr

#endif /* INCLUDED_SPECTRUM_SENSOR_BINAGGR_IMPL_H */

