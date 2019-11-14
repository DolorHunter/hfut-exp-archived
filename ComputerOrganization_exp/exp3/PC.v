module PC(
    input wire clk,
    input wire reset,
    output reg [7:0] counter
);

    always@(posedge clk) begin
    if(reset == 1'b1)
        counter <= 8'd0;
    else
        counter <= counter + 8'd1;
    end

endmodule
