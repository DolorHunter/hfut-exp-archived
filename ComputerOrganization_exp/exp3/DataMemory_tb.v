module DataMemory_tb;

    reg clk;
    reg WE;
    reg [15:0] address;
    reg [15:0] write_data;
    wire [15:0] read_data;

    DataMemory dm(clk,WE,address,write_data,read_data);
    
    initial begin
        clk = 0;
        forever #5 clk = ~clk;
    end

    initial begin
        #0 WE = 1'b1; address = 16'd0;
        #5 WE = 1'b0;
        #5 address = 16'b0000000000000000; write_data = 16'd1;
        #5 address = 16'b0000000000000001; write_data = 16'd2;
        #5 address = 16'b0000000000000010; write_data = 16'd3;
        #5 address = 16'b0000000000000011; write_data = 16'd4;
        #5 address = 16'b0000000000000100; write_data = 16'd5;

        #5 WE = 1'b1;
        #5 address = 16'b0000000000000000;
        #5 address = 16'b0000000000000001;
        #5 address = 16'b0000000000000010;
        #5 address = 16'b0000000000000011;
        #5 address = 16'b0000000000000100;
        #10 $stop;
    end

endmodule
