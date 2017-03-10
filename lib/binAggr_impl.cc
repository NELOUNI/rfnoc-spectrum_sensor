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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "binAggr_impl.h"
namespace gr {
  namespace spectrum_sensor {

    binAggr::sptr
    binAggr::make(
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
    )
    {
      return gnuradio::get_initial_sptr(
        new binAggr_impl(
		fft_size, 
		nbr_bins, 
		samp_rate, 
		center_freq, 
		bandwidth, 
		channel_bw, 
		output_bin_index,
		dev, 
		//tx_stream_args, 
		//rx_stream_args, 
		block_select, 
		device_select
        )
      );
    }

    /*
     * The private constructor
     */
    binAggr_impl::binAggr_impl(
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
    )
      : gr::ettus::rfnoc_block("binAggr"),
        gr::ettus::rfnoc_block_impl(
            dev,
            gr::ettus::rfnoc_block_impl::make_block_id("binAggr",  block_select, device_select),
            //tx_stream_args, rx_stream_args
            ::uhd::stream_args_t("fc32", "sc16"),
            ::uhd::stream_args_t("fc32", "sc16")
            )

    {
	set_bin_index(fft_size, nbr_bins, samp_rate, center_freq, bandwidth, channel_bw, output_bin_index); //FIXME does this need to be back
    }

    /*
     * Our virtual destructor.
     */
    binAggr_impl::~binAggr_impl()
    {
    }

   void binAggr_impl::set_bin_index(const int fft_size, const int nbr_bins, const int samp_rate, const int center_freq, const int bandwidth, const int channel_bw, std::vector<unsigned int> output_bin_index)
    {
      get_block_ctrl_throw< ::uhd::rfnoc::binAggr_block_ctrl >()->set_bin_index(fft_size, nbr_bins, samp_rate, center_freq, bandwidth, channel_bw, output_bin_index);
    }


  } /* namespace spectrum_sensor */
} /* namespace gr */

