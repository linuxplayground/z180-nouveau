// vim: set ft=verilog ts=4 sw=4 ai et:

module vdp (
    input wire          clk,
    input wire          reset,
    output wire[0:11]   rgb,
    output wire         hs,
    output wire         vs,

    output wire [9:0] name_raddr,
    input wire [7:0] name_rdata,

    output wire [10:0] pattern_raddr,
    input wire [7:0] pattern_rdata,

    output wire [9:0] colour_raddr,
    input wire [7:0] colour_rdata,

    input wire [3:0] border_colour_in
);

    localparam HLB  = 10'd64;      // horizontal left border here to use below
    localparam VTB  = 10'd48;      // vertical top border here to use below

    wire pxclk;

    //pll pll (
    //    .clock_in(clk),
    //    .clock_out(pxclk)
    //);
    assign pxclk = clk;

    wire border;
    wire vid;
    wire [9:0] col;
    wire [9:0] row;
    wire vga_hsync;
    wire vga_vsync;

    vgasync #(.HLB(HLB), .VTB(VTB)) vgasync (
        .clk(pxclk),
        .reset(~reset),
        .hsync(vga_hsync),
        .vsync(vga_vsync),
        .bdr_active(border),
        .vid_active(vid),
        .col(col),
        .row(row)
    );
    wire vdp_hsync, vdp_vsync;

    tile tile (
        .pxclk(pxclk),
        .reset(~reset),
        .hsync_in(vga_hsync),
        .hsync_out(vdp_hsync),
        .vsync_in(vga_vsync),
        .vsync_out(vdp_vsync),
        .active_in(vid),
        .border_in(border),
        .col_in(col-HLB),
        .row_in(row-VTB),
        .name_raddr(name_raddr),
        .name_rdata(name_rdata),
        .pattern_raddr(pattern_raddr),
        .pattern_rdata(pattern_rdata),
        .colour_raddr(colour_raddr),
        .colour_rdata(colour_rdata),
        .border_colour_in(border_colour_in),
        .rgb(rgb)
    );
    assign hs = ~vdp_hsync;
    assign vs = ~vdp_vsync;
endmodule
