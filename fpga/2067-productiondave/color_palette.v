`default_nettype none

// a color palette for mapping the TI99 colors to a 12-bit RGB dac

module color_palette (
    input wire [3:0]   color,
    output reg [11:0]  rgb
    );

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

    assign rgb = palette[color];
endmodule

