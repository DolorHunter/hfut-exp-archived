module RegisterFile_tb;

    reg EN;
    reg WR;
    reg [15:0] data;
    reg RD1,RD2;
    reg [1:0] select;
    wire [15:0] AX,BX,CX,DX,SP,BP,DI,SI;
    wire [15:0] ans;

    RegisterFile registerfile(EN,WR,data,RD1,RD2,select,AX,BX,CX,DX,SP,BP,DI,SI,ans);

    initial
        begin
            #0 EN=0; WR=1; data=16'b1111111111111111; select=2'b00;
            #5 EN=1; WR=1; data=16'b0000000000001111; select=2'b00;
            #5 EN=1; WR=1; data=16'b0000000011111111; select=2'b01;
            #5 EN=1; WR=1; data=16'b0000111111111111; select=2'b10;
            #5 EN=1; WR=1; data=16'b1111111111111111; select=2'b11;
            #0 WR=0; data=16'd0;
            #5 EN=1; RD1=1; select=2'b00;
            #5 EN=1; RD1=1; select=2'b01;
            #5 EN=1; RD1=1; select=2'b10;
            #5 EN=1; RD1=1; select=2'b11;
            #0 RD1=0;
            #5 EN=1; RD2=1; select=2'b00;
            #5 EN=1; RD2=1; select=2'b01;
            #5 EN=1; RD2=1; select=2'b10;
            #5 EN=1; RD2=1; select=2'b11;
            #10 $stop;
        end

endmodule
