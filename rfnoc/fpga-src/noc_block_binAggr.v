
//
// Copyright 2015 Ettus Research
//
//--------------------------------------------------------------------------------
//-- Company:            National Institute of Standards and Technology (NIST)
//-- Operating Unit: Communications Technology Laboratory (CTL)
//-- Division:           Wireless Networks Division (WND)
//-- Group:              Spectum Sharing Group
//-- Engineer:           El Ouni, Naceur A
//--
//-- Create Date:    15:37:58 12/02/2015
//-- Design Name:    RFNOC Bin Aggregator Block
//-- Module Name:        Bin Aggregator NOC Block
//-- Project Name:       FPGA-Accelerated Spectrum Sensing (LTE band Monitoring)
//-- Target Devices: Ettus Research RFNoC-Enabled USRPs
//-- Tool versions:      Xilinx Vivado 2015.2
//--
//-- Description:
//--              Receives a stream of N INPUT_VLEN bin energies,
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

module noc_block_binAggr #(
  parameter NOC_ID = 64'hB17A_0000_0000_0000,
  parameter STR_SINK_FIFOSIZE = 11)
(
  input bus_clk, input bus_rst,
  input ce_clk, input ce_rst,
  input  [63:0] i_tdata, input  i_tlast, input  i_tvalid, output i_tready,
  output [63:0] o_tdata, output o_tlast, output o_tvalid, input  o_tready,
  output [63:0] debug
);

  ////////////////////////////////////////////////////////////
  //
  // RFNoC Shell
  //
  ////////////////////////////////////////////////////////////
  wire [31:0] set_data;
  wire [7:0]  set_addr;
  wire        set_stb;
  reg  [63:0] rb_data;
  wire [7:0]  rb_addr;

  wire [63:0] cmdout_tdata, ackin_tdata;
  wire        cmdout_tlast, cmdout_tvalid, cmdout_tready, ackin_tlast, ackin_tvalid, ackin_tready;

  wire [63:0] str_sink_tdata, str_src_tdata;
  wire        str_sink_tlast, str_sink_tvalid, str_sink_tready, str_src_tlast, str_src_tvalid, str_src_tready;

  wire [15:0] src_sid;
  wire [15:0] next_dst_sid, resp_out_dst_sid;
  wire [15:0] resp_in_dst_sid;

  wire        clear_tx_seqnum;

  noc_shell #(
    .NOC_ID(NOC_ID),
    .STR_SINK_FIFOSIZE(STR_SINK_FIFOSIZE))
  noc_shell (
    .bus_clk(bus_clk), .bus_rst(bus_rst),
    .i_tdata(i_tdata), .i_tlast(i_tlast), .i_tvalid(i_tvalid), .i_tready(i_tready),
    .o_tdata(o_tdata), .o_tlast(o_tlast), .o_tvalid(o_tvalid), .o_tready(o_tready),
    // Computer Engine Clock Domain
    .clk(ce_clk), .reset(ce_rst),
    // Control Sink
    .set_data(set_data), .set_addr(set_addr), .set_stb(set_stb),
    .rb_stb(1'b1), .rb_data(rb_data), .rb_addr(rb_addr),
    // Control Source
    .cmdout_tdata(cmdout_tdata), .cmdout_tlast(cmdout_tlast), .cmdout_tvalid(cmdout_tvalid), .cmdout_tready(cmdout_tready),
    .ackin_tdata(ackin_tdata), .ackin_tlast(ackin_tlast), .ackin_tvalid(ackin_tvalid), .ackin_tready(ackin_tready),
    // Stream Sink
    .str_sink_tdata(str_sink_tdata), .str_sink_tlast(str_sink_tlast), .str_sink_tvalid(str_sink_tvalid), .str_sink_tready(str_sink_tready),
    // Stream Source
    .str_src_tdata(str_src_tdata), .str_src_tlast(str_src_tlast), .str_src_tvalid(str_src_tvalid), .str_src_tready(str_src_tready),
    // Stream IDs set by host
    .src_sid(src_sid),                   // SID of this block
    .next_dst_sid(next_dst_sid),         // Next destination SID
    .resp_in_dst_sid(resp_in_dst_sid),   // Response destination SID for input stream responses / errors
    .resp_out_dst_sid(resp_out_dst_sid), // Response destination SID for output stream responses / errors
    // Misc
    .vita_time('d0), .clear_tx_seqnum(clear_tx_seqnum),
    .debug(debug));

  ////////////////////////////////////////////////////////////
  //
  // AXI Wrapper
  // Convert RFNoC Shell interface into AXI stream interface
  //
  ////////////////////////////////////////////////////////////

  localparam NUM_AXI_CONFIG_BUS = 1;

  wire [31:0] m_axis_data_tdata;
  wire        m_axis_data_tlast;
  wire        m_axis_data_tvalid;
  wire        m_axis_data_tready;

  wire [31:0] s_axis_data_tdata;
  wire        s_axis_data_tlast;
  wire        s_axis_data_tvalid;
  wire        s_axis_data_tready;

  wire [SR_INPUT_VLEN-1:0] m_axis_config_tdata;
  wire        m_axis_config_tvalid;
  wire        m_axis_config_tready;


  localparam AXI_WRAPPER_BASE    = 128;
  localparam SR_AXI_CONFIG_BASE  = AXI_WRAPPER_BASE + 1;


  axi_wrapper #(
    .SIMPLE_MODE(1),
    .SR_AXI_CONFIG_BASE(SR_AXI_CONFIG_BASE),
    .NUM_AXI_CONFIG_BUS(NUM_AXI_CONFIG_BUS))
  axi_wrapper (
    .clk(ce_clk), .reset(ce_rst),
    .clear_tx_seqnum(clear_tx_seqnum),
    .next_dst(next_dst_sid),
    .set_stb(set_stb), .set_addr(set_addr), .set_data(set_data),
    .i_tdata(str_sink_tdata), .i_tlast(str_sink_tlast), .i_tvalid(str_sink_tvalid), .i_tready(str_sink_tready),
    .o_tdata(str_src_tdata), .o_tlast(str_src_tlast), .o_tvalid(str_src_tvalid), .o_tready(str_src_tready),
    .m_axis_data_tdata(m_axis_data_tdata),
    .m_axis_data_tlast(m_axis_data_tlast),
    .m_axis_data_tvalid(m_axis_data_tvalid),
    .m_axis_data_tready(m_axis_data_tready),
    .m_axis_data_tuser(),
    .s_axis_data_tdata(s_axis_data_tdata),
    .s_axis_data_tlast(s_axis_data_tlast),
    .s_axis_data_tvalid(s_axis_data_tvalid),
    .s_axis_data_tready(s_axis_data_tready),
    .s_axis_data_tuser(),
    .m_axis_config_tdata(m_axis_config_tdata),
    .m_axis_config_tlast(m_axis_config_tlast),
    .m_axis_config_tvalid(m_axis_config_tvalid),
    .m_axis_config_tready(m_axis_config_tready),
    .m_axis_pkt_len_tdata(),
    .m_axis_pkt_len_tvalid(),
    .m_axis_pkt_len_tready());

  ////////////////////////////////////////////////////////////
  //
  // User code
  //
  ////////////////////////////////////////////////////////////
  // NoC Shell registers 0 - 127,
  // User register address space starts at 128
  localparam SR_USER_REG_BASE = 128;

  // Control Source Unused
  assign cmdout_tdata  = 64'd0;
  assign cmdout_tlast  = 1'b0;
  assign cmdout_tvalid = 1'b0;
  assign ackin_tready  = 1'b1;

  // Settings registers
  //
  // - The settings register bus is a simple strobed interface.
  // - Transactions include both a write and a readback.
  // - The write occurs when set_stb is asserted.
  //   The settings register with the address matching set_addr will
  //   be loaded with the data on set_data.
  // - Readback occurs when rb_stb is asserted. The read back strobe
  //   must assert at least one clock cycle after set_stb asserts /
  //   rb_stb is ignored if asserted on the same clock cycle of set_stb.
  //   Example valid and invalid timing:
  //              __    __    __    __
  //   clk     __|  |__|  |__|  |__|  |__
  //               _____
  //   set_stb ___|     |________________
  //                     _____
  //   rb_stb  _________|     |__________     (Valid)
  //                           _____
  //   rb_stb  _______________|     |____     (Valid)
  //           __________________________
  //   rb_stb                                 (Valid if readback data is a constant)
  //               _____
  //   rb_stb  ___|     |________________     (Invalid / ignored, same cycle as set_stb)
  //

  //localparam [7:0] SR_TEST_REG_0 = SR_USER_REG_BASE;
  //localparam [7:0] SR_TEST_REG_1 = SR_USER_REG_BASE + 8'd1;

  localparam SR_INPUT_VLEN   = 131; // Note: AXI config bus in AXI wrapper uses 129 & 130
  localparam SR_OUTPUT_VLEN  = 132;
  localparam RB_INPUT_VLEN   = 0; // Note: AXI config bus in AXI wrapper uses 129 & 130
  localparam RB_OUTPUT_VLEN  = 0;
  
  localparam INPUT_VLEN  = 1024;
  localparam OUTPUT_VLEN = 50;

  //wire [31:0] test_reg_0;
  //setting_reg #(
  //  .my_addr(SR_TEST_REG_0), .awidth(8), .width(32))
  //sr_test_reg_0 (
  //  .clk(ce_clk), .rst(ce_rst),
  //  .strobe(set_stb), .addr(set_addr), .in(set_data), .out(test_reg_0), .changed());

  //wire [31:0] test_reg_1;
  //setting_reg #(
  //  .my_addr(SR_TEST_REG_1), .awidth(8), .width(32))
  //sr_test_reg_1 (
  //  .clk(ce_clk), .rst(ce_rst),
  //  .strobe(set_stb), .addr(set_addr), .in(set_data), .out(test_reg_1), .changed());

  // Readback registers
  // rb_stb set to 1'b1 on NoC Shell
  always @(posedge ce_clk) begin
    case(rb_addr)
      //8'd0 : rb_data <= {32'd0, };
      //8'd1 : rb_data <= {32'd0, test_reg_1};
      RB_INPUT_VLEN  : rb_data <= {INPUT_VLEN};
      RB_OUTPUT_VLEN : rb_data <= {OUTPUT_VLEN};
      default : rb_data <= 64'h0BADC0DE0BADC0DE;
    endcase
  end

     binAggr #(
        .SR_INPUT_VLEN(INPUT_VLEN),
        .SR_OUTPUT_VLEN(OUTPUT_VLEN))
     inst_binAggr (
        .clk(ce_clk), .reset(ce_rst), //.clear(1'b0),
        .m_axis_bin_index_tdata(m_axis_config_tdata[SR_INPUT_VLEN-1:0]), //have to be 32 or 64 max len ??
        .m_axis_bin_index_tlast(m_axis_config_tlast),
        .m_axis_bin_index_tvalid(m_axis_config_tvalid),
        .m_axis_bin_index_tready(m_axis_config_tready),

        .i_tdata(m_axis_data_tdata),
        .i_tlast(m_axis_data_tlast),
        .i_tvalid(m_axis_data_tvalid),
        .i_tready(m_axis_data_tready),
        .o_tdata(s_axis_data_tdata),
        .o_tlast(s_axis_data_tlast),
        .o_tvalid(s_axis_data_tvalid),
        .o_tready(s_axis_data_tready));

endmodule 

