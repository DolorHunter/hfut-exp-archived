module ALU(
    input wire [2:0] in1,in2,
    input wire [7:0] alu_op,
    output reg [2:0] out
);

    always@(*) begin
        // Define ALU operations
        case(alu_op)
            8'b00000000: out <= in1 + in2; // Add
            default: out <= 8'bx;
        endcase
    end

endmodule
