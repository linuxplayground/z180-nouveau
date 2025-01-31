// vim: set ft=verilog ts=4 sw=4 ai et:
module top (
    input wire          hwclk,
    input wire          reset,
    output wire[0:11]   rgb,
    output wire         hs,
    output wire         vs
);

vdp vdp (
        .clk(hwclk),
        .reset(reset),
        .rgb(rgb),
        .hs(hs),
        .vs(vs)
);

endmodule
