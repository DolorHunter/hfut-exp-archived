`include "PC.v"
`include "CU.v"
`include "ALU.v"
`include "RegFiles.v"
`include "InsMem.v"

module CPU(
    input wire clk,
    input wire rst
);

    wire [6:0] PC_pc;
    wire CU_wr_en;
    wire CU_m_wr_en;
    wire [6:0] CU_alu_op;
    wire [2:0] ALU_out;
    wire [2:0] RegFiles_reg_data1;
    wire [2:0] RegFiles_reg_data2;
    wire [15:0] InsMem_Ins;
    wire [2:0] Memory_rd_data;

    PC u_PC(
        .clk(clk),
        .rst(rst),
        .pc(PC_pc)
    );
    
    InsMem u_InsMen(
        .addr(PC_pc),
        .ins(InsMem_Ins)
    );

    CU u_CU(
        .ins(PC_pc),
        .alu_out(ALU_out),
        .wr_en(CU_wr_en),
        .m_wr_en(CU_m_wr_en),
        .alu_op(CU_alu_op)
    );

    ALU u_ALU(
        .clk(clk),
        .r_in1(RegFiles_reg_data1), .r_in2(RegFiles_reg_data2),
        .m_in(Memory_rd_data),
        .alu_op(CU_alu_op),
        .out(ALU_out)
    );

    RegFiles u_RegFiles(
        .clk(clk),
        .wr_en(CU_wr_en),
        .rd_reg1(InsMem_Ins[5:3]), .rd_reg2(InsMem_Ins[5:3]),  // .rd_reg1(InsMem_Ins[8:6]) cause error on my pc
        .wr_reg(InsMem_Ins[2:0]),
        .wr_data(ALU_out),
        .reg_data1(RegFiles_reg_data1), .reg_data2(RegFiles_reg_data2)
    );

    Memory u_Memory(
        .clk(clk),
        .m_wr_en(CU_m_wr_en),
        .addr(InsMem_Ins[8:6]),
        .wr_data(ALU_out),
        .rd_data(Memory_rd_data)
    );

endmodule
