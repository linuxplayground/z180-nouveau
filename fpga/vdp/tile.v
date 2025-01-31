// vim: set ft=verilog ts=4 sw=4 ai et:

module tile (
    input wire          pxclk,
    input wire          reset,
    input wire          hsync_in,
    input wire          vsync_in,
    input wire          active_in,
    input wire          border_in,

    input wire [9:0]    col_in,     // pixel position
    input wire [9:0]    row_in,     // pixel position

    output wire         hsync_out,
    output wire         vsync_out,
    output wire         active_out,
    output wire         border_out,

    output wire [9:0]   name_raddr,
    input  wire [7:0]   name_rdata,
    output wire [10:0]  pattern_raddr,
    input  wire [7:0]   pattern_rdata,
    output wire [9:0]   colour_raddr,
    input  wire [7:0]   colour_rdata,

    output wire [11:0]  rgb
    );

    wire [4:0] CCCCC;   // the tile column in the name plane
    wire [2:0] ccc;     // the pixel column in the pattern plane
    wire [4:0] RRRRR;   // the tile row in the name plane
    wire [2:0] rrr;     // the pixel row in the pattern plane

    assign {CCCCC,ccc} = col_in[8:1];
    assign {RRRRR,rrr} = row_in[8:1];

    assign name_raddr = {RRRRR,CCCCC};
    //assign colour_raddr = {RRRRR,CCCCC};
    assign colour_raddr = name_rdata;
    assign pattern_raddr = {name_rdata,rrr};

    // colours
    reg [11:0] palette[0:15];
    initial begin
        palette[0] =  12'h000;    // trasnparent
        palette[1] =  12'h000;    // black
        palette[2] =  12'h2C3;    // medium green
        palette[3] =  12'h5D6;    // light green
        palette[4] =  12'h54F;    // dark blue
        palette[5] =  12'h76F;    // light blue
        palette[6] =  12'hD54;    // dark red
        palette[7] =  12'h4EF;    // cyan
        palette[8] =  12'hF54;    // medium red
        palette[9] =  12'hF76;    // light red
        palette[10] = 12'hDC3;    // dark yellow
        palette[11] = 12'hED6;    // light yellow
        palette[12] = 12'h2B2;    // dark green
        palette[13] = 12'hC5C;    // magenta
        palette[14] = 12'hCCC;    // grey
        palette[15] = 12'hFFF;    // white
    end

    // pipeline
    reg [4:0] hsync_reg, hsync_next;
    reg [4:0] vsync_reg, vsync_next;
    reg [4:0] active_reg, active_next;
    reg [4:0] border_reg, border_next;
    reg [7:0] px_reg, px_next;
    reg [3:0] colour_reg, colour_next;
    reg [7:0] ctc_reg, ctc_next;

    reg [3:0] border_colour = 10;

    always @(posedge pxclk) begin
        if (reset) begin
            colour_reg <= 0;
            ctc_reg <= 0;
            px_reg <= 0;
            active_reg <= 0;
            border_reg <= 0;
            hsync_reg <= 0;
            vsync_reg <= 0;
        end else begin
            colour_reg <= colour_next;
            ctc_reg <= ctc_next;
            px_reg <= px_next;
            active_reg <= active_next;
            border_reg <= border_next;
            hsync_reg <= hsync_next;
            vsync_reg <= vsync_next;
        end
    end

    always @(*) begin
        colour_next = 0;
        // advance the pipeline (shifting left)
        active_next = {active_reg, active_in};
        border_next = {border_reg, border_in};
        hsync_next  = {hsync_reg, hsync_in};
        vsync_next  = {vsync_reg, vsync_in};
        px_next     = px_reg;
        ctc_next    = ctc_reg;

        if (col_in[0] == 0)
            px_next = {px_reg, 1'b0};   // shift left every other px clock

        if (ccc == 1) begin
            px_next = pattern_rdata;
            ctc_next = colour_rdata;
        end

        if (active_reg[2] && col_in < 32*8*2+3 && row_in < 24*8*2)
            colour_next = px_reg[7] ? ctc_reg[7:4] : ctc_reg[3:0];

        if (border_reg[2])
            colour_next = border_colour;
    end

    assign hsync_out   = hsync_reg[3];
    assign vsync_out   = vsync_reg[3];
    assign active_out  = active_reg[3];

    assign rgb = palette[colour_reg];
endmodule
