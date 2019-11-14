module ALU_tb;
    reg EN;
    reg [2:0] select;
    reg [15:0] src1,src2;
    wire [15:0] ans;

    ALU alu(EN,select,src1,src2,ans);

    initial
        begin
            #0  EN=0; select=3'b000; src1=16'b1111000011110000;
            #10 EN=1; select=3'b000; src1=16'b1111000011110000; src2=16'b1111000011110000;
            #10 EN=1; select=3'b001; src1=16'b1111000011110000; src2=16'b0000111100001111;
            #10 EN=1; select=3'b010; src1=16'b1111000011110000; src2=16'b0000111100001111;
            #10 EN=1; select=3'b011; src1=16'b1111000011110000; src2=16'd1;
            #10 EN=1; select=3'b100; src1=16'b1111000011110000; src2=16'd1;
            #10 EN=1; select=3'b101; src1=16'b1111000011110000; src2=16'b1111000011110000;
            #10 EN=1; select=3'b110; src1=16'b1111000011110000; src2=16'b1111000011110000;
            #10 EN=1; select=3'b111;
            #10 $stop;
        end

endmodule