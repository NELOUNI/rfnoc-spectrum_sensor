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


#include <spectrum_sensor/binAggr_block_ctrl.hpp>
#include <uhd/convert.hpp>
#include <uhd/utils/msg.hpp>
#include <vector>
#include <iostream>

using namespace uhd::rfnoc;

class binAggr_block_ctrl_impl : public binAggr_block_ctrl
{
public:
    UHD_RFNOC_BLOCK_CONSTRUCTOR(binAggr_block_ctrl),
        _item_type("sc16")
    {
        //std::vector<unsigned int> output_bin_index(get_arg<int>("fft_size")/*1024*/);
	//for (unsigned i=0; i<get_arg<int>("fft_size"); i++) output_bin_index[i]=0;

        //_set_default_bin_index(get_arg<int>("fft_size")/*1024*/,get_arg<int>("nbr_bins")/*50*/,get_arg<int>("samp_rate")/*20e6*/,get_arg<int>("center_freq")/*709e6*/,get_arg<int>("bandwidth")/*10e6*/,get_arg<int>("channel_bw")/*180e3*/, output_bin_index);
        //_set_default_bin_index(unsigned int(1024),unsigned int(50),int(20000000),int(709000000),int(10000000),int(180000), output_bin_index);
     }

    void set_bin_index(const unsigned int fft_size, const unsigned int nbr_bins, const int samp_rate, const int center_freq, const int bandwidth, const int channel_bw, std::vector<unsigned int> output_bin_index)
    {
	UHD_RFNOC_BLOCK_TRACE() << "binAggr_block::set_bin_index()" << std::endl;
	float start_freq = center_freq - bandwidth / 2.0;
        float stop_freq = start_freq + bandwidth;
	sr_write(SR_INPUT_VLEN, fft_size);	
	sr_write(SR_OUTPUT_VLEN, nbr_bins);	
	std::cout << "samp_rate = " << samp_rate << std::endl;
	std::cout << "nbr_bins = " << nbr_bins << std::endl;
	std::cout << "bandwidth = " << bandwidth << std::endl;
	std::cout << "fft_size = " << fft_size << std::endl;
        float hz_per_bin = samp_rate / fft_size;

	std::cout << "hz_per_bin = " << hz_per_bin << std::endl;
	std::cout << "center_freq = " << center_freq << std::endl;
	std::cout << "channel_bw = " << channel_bw << std::endl;
	std::cout << "start_freq = " << start_freq  << std::endl;
	std::cout << "stop_freq = " << stop_freq  << std::endl;

        for (int j=0; j < int(fft_size); j++)
                {
        	  float fj = center_freq + hz_per_bin * (j - int(fft_size / 2) - (int(fft_size) % 2));
		  std::cout << "fj[" << j << "] = "<< fj << std::endl;
            	  if ((fj >= start_freq) && (fj < stop_freq))
                        {
                 	 //boost::uint32_t channel_num = (floor((fj - start_freq) / channel_bw)) + 1;
                 	 unsigned int channel_num = (floor((fj - start_freq) / channel_bw)) + 1;
			 std::cout << " channel_num " << channel_num << std::endl;
                 	 output_bin_index[j] = channel_num;
        		 //// Write bin indeces via the BIN_INDEX bus
        		 std::cout << "output_bin_index[" << j << "] = " <<  output_bin_index[j] << std::endl; 
        		 sr_write(AXIS_BIN_INDEX, boost::uint32_t(output_bin_index[j]));
                        }
                }
      	// Assert tlast when sending the last index
      	sr_write(AXIS_BIN_INDEX_TLAST, boost::uint32_t(output_bin_index[fft_size-1]));
      	// Send the configuration word to replace the existing indeces with the new ones.
      	// Note: This configuration bus does not require tlast
      	sr_write(AXIS_BIN_AGGR_CONFIG, 0);
    }

private:
    const std::string  		_item_type;
    //void _set_default_bin_index(unsigned int fft_size, unsigned int nbr_bins, int samp_rate, int center_freq, int bandwidth, int channel_bw, std::vector<unsigned int> output_bin_index) {
    //    set_bin_index(fft_size, nbr_bins, samp_rate, center_freq, bandwidth, channel_bw, output_bin_index);
    //}
};
UHD_RFNOC_BLOCK_REGISTER(binAggr_block_ctrl, "binAggr");
