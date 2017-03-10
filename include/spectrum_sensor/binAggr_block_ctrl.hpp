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


#ifndef INCLUDED_LIBUHD_RFNOC_SPECTRUM_SENSOR_BINAGGR_HPP
#define INCLUDED_LIBUHD_RFNOC_SPECTRUM_SENSOR_BINAGGR_HPP

#include <uhd/rfnoc/source_block_ctrl_base.hpp>
#include <uhd/rfnoc/sink_block_ctrl_base.hpp>

namespace uhd {
    namespace rfnoc {

/*! \brief Block controller for the standard copy RFNoC block.
 *
 */
class UHD_API binAggr_block_ctrl : public source_block_ctrl_base, public sink_block_ctrl_base
{
public:

    UHD_RFNOC_BLOCK_OBJECT(binAggr_block_ctrl)

    static const boost::uint32_t RB_INPUT_VLEN   = 0;
    static const boost::uint32_t RB_OUTPUT_VLEN  = 0;

    static const boost::uint32_t SR_INPUT_VLEN    = 131;
    static const boost::uint32_t SR_OUTPUT_VLEN   = 132;

    static const boost::uint32_t AXIS_BIN_INDEX             = AXIS_CONFIG_BUS+0; // 2*0+0
    static const boost::uint32_t AXIS_BIN_INDEX_TLAST       = AXIS_CONFIG_BUS+1; // 2*0+1
    static const boost::uint32_t AXIS_BIN_AGGR_CONFIG       = AXIS_CONFIG_BUS+2; // 2*1+0
    static const boost::uint32_t AXIS_BIN_AGGR_CONFIG_TLAST = AXIS_CONFIG_BUS+3; // 2*1+1

    virtual void set_bin_index(const unsigned int fft_size, const unsigned int nbr_bins, const int samp_rate, const int center_freq, const int bandwidth, const int channel_bw, std::vector <unsigned int> output_bin_index) = 0;
    //virtual void set_bin_index() = 0;

    /*!
     * Your block configuration here
    */
}; /* class binAggr_block_ctrl*/

}} /* namespace uhd::rfnoc */

#endif /* INCLUDED_LIBUHD_RFNOC_SPECTRUM_SENSOR_BINAGGR_BLOCK_CTRL_HPP */
