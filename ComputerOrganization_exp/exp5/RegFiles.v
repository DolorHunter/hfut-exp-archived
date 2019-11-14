module RegFiles(
    input wire clk,
    input wire wr_en,
    input wire [2:0] rd_reg1,rd_reg2,
    input wire [2:0] wr_reg,  // wr into port2(10) so it needs 2-bit
    input wire [2:0] wr_data,
    output reg [2:0] reg_data1,reg_data2
);

    reg [2:0] registers [0:2];  // 3 register(2rd & 1wr)

    // Import data to registerfiles from the file
    initial $readmemb("regfiles_data.dat",registers);

    always@(posedge clk) begin
        if(wr_en == 1'b1)
            registers[wr_reg] <= wr_data;
        // Always reading registers
        reg_data1 <= registers[rd_reg1];
        reg_data2 <= registers[rd_reg2];
        #20 $display("RegFiles: %b\t%b\t%b",registers[0],registers[1],registers[2]);
    end

endmodule
