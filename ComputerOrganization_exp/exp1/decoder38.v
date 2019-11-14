module decoder38(
  input EN,
  input Ip2,Ip1,Ip0,
  output reg Op0,Op1,Op2,Op3,Op4,Op5,Op6,Op7
);

  always@* begin
      Op0 = 0;
      Op1 = 0;
      Op2 = 0;
      Op3 = 0;
      Op4 = 0;
      Op5 = 0;
      Op6 = 0;
      Op7 = 0;
    if (EN==1'b1) begin
      case ({Ip2,Ip1,Ip0})
        3'b000: Op0 = 1;
        3'b001: Op1 = 1;
        3'b010: Op2 = 1;
        3'b011: Op3 = 1;
        3'b100: Op4 = 1;
        3'b101: Op5 = 1;
        3'b110: Op6 = 1;
        3'b111: Op7 = 1;
        default: begin
          Op0 = 0;
          Op1 = 0;
          Op2 = 0;
          Op3 = 0;
          Op4 = 0;
          Op5 = 0;
          Op6 = 0;
          Op7 = 0;
        end
      endcase
    end
  end

endmodule
