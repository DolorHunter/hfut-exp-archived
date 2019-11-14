module InsMem(
    input wire [6:0] addr,
    output reg [15:0] ins
);

    always@(*) begin
        // addr as swich for operator
        // data_addr: 000(reg_addr0), 001(reg_addr1)), 010(reg_addr2)
        // ins = [operator + data_addr]
        case(addr)
            7'b0000000: ins <= addr*256 + 16'b0000000000001010;  // CLA: 
            7'b0000001: ins <= addr*256 + 16'b0000000000001010;  // COM
            7'b0000010: ins <= addr*256 + 16'b0000000000001010;  // SHR
            7'b0000011: ins <= addr*256 + 16'b0000000000001010;  // CSL
            7'b0000100: ins <= addr*256 + 16'b0000000000001010;  // STP
            7'b0000101: ins <= addr*256 + 16'b0000000000001010;  // ADD
            7'b0000110: ins <= addr*256 + 16'b0000000000001010;  // STA
            7'b0000111: ins <= addr*256 + 16'b0000000000001010;  // LDA
            7'b0001000: ins <= addr*256 + 16'b0000000000001010;  // JMP
            7'b0001001: ins <= addr*256 + 16'b0000000000001010;  // BAN
            default: ins <= 16'bx;
        endcase
    end

endmodule
