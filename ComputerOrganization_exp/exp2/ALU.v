module ALU(
    input wire EN,
    input wire [2:0] select,
    input wire [15:0] src1,src2,
    output reg [15:0] ans
);

    always@(*)
    begin
        if(EN == 1'b1)
        begin
            case(select)
            3'b000: ans <= ~src1; // not16
            3'b001: ans <= src1 & src2; // and16
            3'b010: ans <= src1 | src2; // or16
            3'b011: ans <= src1 << src2; // shiftleft16
            3'b100: ans <= src1 >> src2; // shiftright16
            3'b101: ans <= src1 + src2; // fulladder16
            3'b110: ans <= src1 - src2; // fullsubtrater16
            default: $display("[ERROR]select=%b",select);
            endcase
        end
    end

endmodule
