module DataMemory(
    input wire clk,
    input wire WE, // Write Enable(0 WE, 1 Read Enable)
    input wire [15:0] address,
    input wire [15:0] write_data,
    output reg [15:0] read_data
);

    reg [15:0] Memory[1023:0]; // 1024 byte of 16-bit memory

    integer i;

    initial begin
        read_data <= 0;
        for(i=0;i<1024;i=i+1) Memory[i] = i;
    end

    always@(posedge clk) begin
        if(WE == 1'b0)
            Memory[address] <= write_data;
        else
            read_data <= Memory[address];
    end

endmodule
