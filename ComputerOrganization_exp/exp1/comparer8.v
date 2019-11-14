module comparer8(
    input [7:0] in1, in2,
    output reg out
);
    always@* begin
        if(in1 > in2) out = 1'b1;
        else out = 1'b0;
    end

endmodule
