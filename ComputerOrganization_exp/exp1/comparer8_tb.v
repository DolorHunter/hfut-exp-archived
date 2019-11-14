module comparer8_tb;

  reg [7:0] in1, in2;
  wire out;

  comparer8 cmp8(in1,in2,out);

  initial
    begin
      #0 in1 = 8'b00000000; in2 = 8'b00000000;
      #5 in1 = 8'b00001000; in2 = 8'b00000111;
      #5 in1 = 8'b01001000; in2 = 8'b01001001;
      #5 in1 = 8'b01011000; in2 = 8'b01011001;
      #5 in1 = 8'b11111111; in2 = 8'b11111110;
      #5 $stop;  
    end

endmodule
