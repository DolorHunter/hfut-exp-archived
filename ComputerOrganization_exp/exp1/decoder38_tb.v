module decoder38_tb;

  reg Ip2,Ip1,Ip0;
  reg EN;
  wire Op0,Op1,Op2,Op3,Op4,Op5,Op6,Op7;

  decoder38 d38(EN,Ip2,Ip1,Ip0,Op0,Op1,Op2,Op3,Op4,Op5,Op6,Op7);

  initial
    begin
      #0 EN = 0; Ip2 = 1; Ip1 = 1; Ip0 = 1;
      #5 EN = 1; Ip2 = 0; Ip1 = 0; Ip0 = 1;
      #5 EN = 1; Ip2 = 0; Ip1 = 1; Ip0 = 0;
      #5 EN = 1; Ip2 = 0; Ip1 = 1; Ip0 = 1;
      #5 EN = 1; Ip2 = 1; Ip1 = 0; Ip0 = 0;
      #5 EN = 1; Ip2 = 1; Ip1 = 0; Ip0 = 1;
      #5 EN = 1; Ip2 = 1; Ip1 = 1; Ip0 = 0;
      #5 EN = 1; Ip2 = 1; Ip1 = 1; Ip0 = 1;
      #5 $stop;
  end

endmodule