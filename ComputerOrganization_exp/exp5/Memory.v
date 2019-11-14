module Memory(
	input wire clk,
	input wire m_wr_en,
    input wire [2:0] addr,
	input wire [2:0] wr_data,
	output reg [2:0] rd_data
);

	reg [2:0] Memorys [0:1]; // 2 mem(1rd & 1wr)

	// Import data to memory from the file
	initial $readmemb("memorys_data.dat",Memorys);

	always@(posedge clk) begin
		if(m_wr_en == 1'b1)
			Memorys[addr] <= wr_data;
		// Always reading memory
		rd_data <= Memorys[addr];
		#20 $display("Memorys: %b\t%b",Memorys[0],Memorys[1]);
	end

endmodule
