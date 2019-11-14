module RegisterFile(
    input wire EN,
    input wire WR,
    input wire [15:0] data,
    input wire RD1, RD2,
    input wire [1:0] select,
    output reg [15:0] AX,BX,CX,DX,SP,BP,DI,SI,
    output reg [15:0] ans
);

    always@(*)
    begin
        if(EN == 1'b1)
        begin
            if(WR == 1'b1)
            begin
                case(select)
                2'b00: AX <= data;
                2'b01: BX <= data;
                2'b10: CX <= data;
                2'b11: DX <= data;
                endcase

            end

            if(RD1 == 1'b1)
            begin
                case(select)
                2'b00: ans <= AX;
                2'b01: ans <= BX;
                2'b10: ans <= CX;
                2'b11: ans <= DX;
                endcase
            end

            if(RD2 == 1'b1)
            begin
                case(select)
                2'b00: ans <= SP;
                2'b01: ans <= BP;
                2'b10: ans <= DI;
                2'b11: ans <= SI;
                endcase
            end        
        end
    end

endmodule
