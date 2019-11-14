module InsMem(
    input wire [7:0] addr,
    output reg [15:0] ins
);

    always@(*) begin
        // addr as operator
        // data_addr: 000(rd_addr1) 001(rd_addr2) 010(wr_addr)
        // ins = [operator + data_addr]
        ins <= addr*128 + 16'b00000000000001010;
    end

endmodule
