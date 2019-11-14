module ALU(
    input wire clk,
    input wire [2:0] r_in1,r_in2,
    input wire [2:0] m_in,
    input wire [6:0] alu_op,
    output reg [2:0] out
);

    always@(posedge clk) begin
        // Define ALU operations
        case(alu_op)
            7'b0000000: out <= 0;                     // CLA
            7'b0000001: out <= ~r_in1;                // COM
            7'b0000010: out <= r_in1 >> 1;            // SHR
            7'b0000011: out <= {r_in1[1:0],r_in1[2]}; // CSL
            7'b0000101: out <= r_in1 + r_in2;         // ADD
            7'b0000110: out <= r_in1;                 // STA
            7'b0000111: out <= m_in;                  // LDA
            7'b0001000: out <= r_in1;                 // JMP
            7'b0001001: out <= r_in1;                 // BAN
            default: out <= 7'bx;
        endcase
    end

endmodule
