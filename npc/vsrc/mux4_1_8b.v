module mux4_1_8b(a,s,y);
    input [7:0] a [3:0];
    input [1:0] s;
    output  [7:0] y;

    MuxKey #(4, 2, 8) i0 (y, s, {
    2'b00, a[0],
    2'b01, a[1],
    2'b10, a[2],
    2'b11, a[3]
    });
endmodule
