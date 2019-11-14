module PC_tb;

    reg clk;
    reg reset;
    wire [7:0] counter;
    
    PC pc(clk,reset,counter);

    integer i;

    initial begin 
        clk=0;
        forever #5 clk=~clk;
    end
    
    initial begin
        reset=1;
        #20;
        reset=0;
    end

endmodule
 