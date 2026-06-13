module GPR (
    input clk,
    input rst,
    input [1:0] raddr1,
    input [1:0] raddr2,
    output [7:0] rdata1,
    output [7:0] rdata2,
    input [1:0] waddr,
    input [7:0] wdata,
    input wen
);

    wire [3:0] reg_sel, reg_wen;
    wire [7:0] reg_q [3:0];

    decoder2_4 dec1 (waddr, reg_sel);

    assign reg_wen = {4{wen}} & reg_sel;
    
    Reg_8b reg0 (clk, rst, wdata, reg_q[0], reg_wen[0]);
    Reg_8b reg1 (clk, rst, wdata, reg_q[1], reg_wen[1]);
    Reg_8b reg2 (clk, rst, wdata, reg_q[2], reg_wen[2]);
    Reg_8b reg3 (clk, rst, wdata, reg_q[3], reg_wen[3]);

    mux4_1_8b mux1 (reg_q, raddr1, rdata1);
    mux4_1_8b mux2 (reg_q, raddr2, rdata2);

endmodule
            
