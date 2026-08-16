module top (
    input clk,
    input rst,
    //指令读取接口
    output [31:0] pc_state,     
    input [31:0] instruction,      
    //数据访存接口
    output [31:0] m_addr,
    input [31:0] m_rdata,
    output [31:0] m_wdata,
    output m_ren,
    output m_wen,
    output [1:0] m_size
);

    wire [6:0] opcode;
    wire [2:0] funct3;
    wire [6:0] funct7;
    wire [4:0] rd, rs1, rs2;
    wire [31:0] imm;
    wire [31:0] rdata1, rdata2;
    wire [31:0] alu_result;
    wire jump_en;
    wire [31:0] wdata;
    wire wen;

    IFU ifu (clk, rst, jump_en, alu_result, pc_state);
    IDU idu(instruction, opcode, rd,  rs1, rs2, funct3, funct7, imm);
    EXU exu(opcode, funct3, funct7, rdata1, rdata2,  imm, jump_en, alu_result);
    LSU lsu(opcode, funct3, alu_result, rdata2, m_addr, m_wdata, m_ren, m_wen, m_size);
    WBU wbu(opcode, funct3, funct7, alu_result, pc_state, m_rdata, wdata, wen);

    GPR gpr (clk, rst, rs1, rs2, rdata1, rdata2, rd, wdata, wen);

endmodule
