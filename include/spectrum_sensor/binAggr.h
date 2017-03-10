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


#ifndef INCLUDED_SPECTRUM_SENSOR_BINAGGR_H
#define INCLUDED_SPECTRUM_SENSOR_BINAGGR_H

#include <spectrum_sensor/api.h>
#include <ettus/device3.h>
#include <ettus/rfnoc_block.h>
#include <uhd/stream.hpp>

namespace gr {
  namespace spectrum_sensor {

    /*!
     * \brief <+description of block+>
     * \ingroup spectrum_sensor
     *
     */
    class SPECTRUM_SENSOR_API binAggr : virtual public gr::ettus::rfnoc_block
    {
     public:
      typedef boost::shared_ptr<binAggr> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of spectrum_sensor::binAggr.
       *
       * To avoid accidental use of raw pointers, spectrum_sensor::binAggr's
       * constructor is in a private implementation
       * class. spectrum_sensor::binAggr::make is the public interface for
       * creating new instances.
       */
      static sptr make(
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
          const int block_select=-1,
          const int device_select=-1
      );

      //! Update the bin_indeces vactor
      virtual void set_bin_index(const int fft_size, const int nbr_bins, const int samp_rate, const int center_freq, const int bandwidth, const int channel_bw, std::vector<unsigned int> output_bin_index) = 0;
    };
  } // namespace spectrum_sensor
} // namespace gr

#endif /* INCLUDED_SPECTRUM_SENSOR_BINAGGR_H */

