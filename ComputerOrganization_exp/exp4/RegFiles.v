module RegFiles(
    input wire clk,
    input wire wr_en,
    input wire [0:2]rd_reg1,rd_reg2,
    input wire [0:2] wr_reg,  // wr into port2(10) so it needs 2-bit
    input wire [2:0] wr_data,
    output reg [2:0] reg_data1,reg_data2
);

    reg [2:0] registers [0:2];  // 3 register(2rd & 1wr)

    // Import data to registerfiles from the file
    initial $readmemb("regfiles_data.dat",registers);

    always@(negedge clk) begin
        // Always reading registers
        reg_data1 <= registers[rd_reg1];
        reg_data2 <= registers[rd_reg2];
        #10 $display("%d\t%d\t%d\n",registers[0],registers[1],registers[2]);
        if(wr_en == 1'b1)
            registers[wr_reg] <= wr_data;
    end

endmodule
