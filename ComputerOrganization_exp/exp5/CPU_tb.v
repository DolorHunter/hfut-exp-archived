`include "CPU.v"
module CPU_tb;

    reg clk;
    reg rst;

    initial begin
        clk = 1'b0;
        forever #10 clk = ~clk;
    end

    initial begin
        #0 rst = 1'b1;
        #20 rst = 1'b0;

        #200 $stop;
    end

    CPU u_cpu(
        .clk(clk),
        .rst(rst)
    );

endmodule
