module fulladder4_tb;
  
  reg [3:0] in1, in2;
  reg cin;
  wire [3:0] out;
  wire cout;

  fulladder4 fa4(in1, in2, cin, out, cout);
  
  initial
    begin
      #0 in1 = 4'b0000; in2 = 4'b0000; cin = 1'b0;
      #5 in1 = 4'b0010; in2 = 4'b0000; cin = 1'b1;
      #5 in1 = 4'b0010; in2 = 4'b0010; cin = 1'b0;
      #5 in1 = 4'b1011; in2 = 4'b0010; cin = 1'b1;
      #5 in1 = 4'b0101; in2 = 4'b0011; cin = 1'b0;
      #5 in1 = 4'b0111; in2 = 4'b0111; cin = 1'b1;
      #5 in1 = 4'b1001; in2 = 4'b0111; cin = 1'b0;
      #5 in1 = 4'b1001; in2 = 4'b1001; cin = 1'b1;
      #5 in1 = 4'b1011; in2 = 4'b1011; cin = 1'b0;
      #5 in1 = 4'b1111; in2 = 4'b1111; cin = 1'b1;
      #5 $stop;
    end
  
endmodule
