module CU(
    input wire [7:0] ins,
    output reg wr_en,
    output reg [7:0] alu_op
);

    always@(*) begin
        // ins as alu_op
        alu_op <= ins;
        case(ins)
            8'b00000000: wr_en <= 1'b1;  // Add
            default: wr_en <= 1'bx;
        endcase
    end

endmodule
