module PC(
    input wire clk,
    input rst,
    output reg [7:0] pc
);

    // pc as addr of operator
    always@(posedge clk) begin
        if(rst == 1'b1)
            pc <= 8'd0;
        else
            pc <= pc + 1;
    end

endmodule
