//--------------------------------------------------------------------------------
//-- Company:     	 National Institute of Standards and Technology (NIST)
//-- Operating Unit: Communications Technology Laboratory (CTL)
//-- Division:    	 Wireless Networks Division (WND)
//-- Group:       	 Spectum Sharing Group
//-- Engineer:    	 El Ouni, Naceur A
//-- 
//-- Create Date:    15:37:58 12/02/2015
//-- Design Name:    RFNOC Bin Aggregator Block 
//-- Module Name: 	 Bin Aggregator - Behavioral
//-- Project Name:	 FPGA-Accelerated Spectrum Sensing (LTE band Monitoring)
//-- Target Devices: Ettus Research RFNoC-Enabled USRPs
//-- Tool versions:	 Xilinx Vivado 2015.2
//--
//-- Description: 
//--              Receives a stream of N FFT bin energies, 
//--              group them in OUTPUT_VLEN bins (50 bins default each representing one Ressource Block) 
//-- Dependencies: 
//--              none
//-- Revision: 
//--      Revision 0.01 - File Created
//--      Revision 0.03 - 
//--      Revision 0.10 - Tested, debugged 
//--                             
//-- Additional Comments: 
//----------------------------------------------------------------------------------

module binAggr
    #(parameter SR_INPUT_VLEN=0,
      parameter SR_OUTPUT_VLEN=0)
   (input clk, input reset,
    input [31:0] i_tdata, input i_tlast, input i_tvalid, output i_tready,
    input [SR_INPUT_VLEN-1:0] m_axis_bin_index_tdata, input m_axis_bin_index_tlast,
    input m_axis_bin_index_tvalid, input m_axis_bin_index_tready,
    output [31:0] o_tdata, output o_tlast, output o_tvalid, input o_tready);

   reg [31:0] out;

  genvar _k;
   generate
	 for (_k=0; _k<SR_INPUT_VLEN; _k=_k+1)
	 always @(posedge clk)
  	 begin
	    if (i_tvalid & i_tready & i_tlast & ((m_axis_bin_index_tdata[_k] > 0) && (m_axis_bin_index_tdata[_k] <= SR_OUTPUT_VLEN)))  
        	  begin
		      out[SR_OUTPUT_VLEN + m_axis_bin_index_tdata[_k] - 1] <= out[SR_OUTPUT_VLEN + m_axis_bin_index_tdata[_k] - 1] + i_tdata[SR_INPUT_VLEN + _k];
		  end
	 end
   endgenerate
 
 
   assign o_tdata = out; //FIXME 

   assign i_tready = o_tready;
   assign o_tvalid = i_tvalid;
   assign o_tlast  = i_tlast;
   
endmodule // binAggr
