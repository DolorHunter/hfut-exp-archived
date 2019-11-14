module CU(
    input wire [6:0] ins,
    input wire [2:0] alu_out,
    output reg wr_en,
    output reg m_wr_en,
    output reg [6:0] alu_op
);

    always@(*) begin
        alu_op <= ins;  // Default
        if(ins == 7'b0000100)  // STP
            $stop;
        if(ins == 7'b0001000)  // JMP
            alu_op <= alu_out;      
        if(ins == 7'b0001001 && alu_out>=3'b100)  // BAN
            alu_op <= alu_out;

        case(ins)
            7'b0000000: begin wr_en <= 1'b1; m_wr_en <= 1'b0; end  // CLA
            7'b0000001: begin wr_en <= 1'b1; m_wr_en <= 1'b0; end  // COM
            7'b0000010: begin wr_en <= 1'b1; m_wr_en <= 1'b0; end  // SHR
            7'b0000011: begin wr_en <= 1'b1; m_wr_en <= 1'b0; end  // CSL
            7'b0000100: begin wr_en <= 1'b0; m_wr_en <= 1'b0; end  // STP
            7'b0000101: begin wr_en <= 1'b1; m_wr_en <= 1'b0; end  // ADD
            7'b0000110: begin wr_en <= 1'b0; m_wr_en <= 1'b1; end  // STA
            7'b0000111: begin wr_en <= 1'b1; m_wr_en <= 1'b0; end  // LDA
            7'b0001000: begin wr_en <= 1'b0; m_wr_en <= 1'b0; end  // JMP
            7'b0001001: begin wr_en <= 1'b0; m_wr_en <= 1'b0; end  // BAN
            default: wr_en <= 1'bx;
        endcase

    end

endmodule
