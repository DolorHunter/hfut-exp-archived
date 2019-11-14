module PC(
    input wire clk,
    input wire rst,
    output reg [6:0] pc
);

    // pc as addr of operator
    always@(posedge clk) begin
        if(rst == 1'b1)
            pc <= 7'd0;
        else
            pc <= pc + 1;
    end

endmodule
