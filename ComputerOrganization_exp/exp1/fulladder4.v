module fulladder4(
    input[3:0] in1,in2,
    input cin,
    output[3:0] out,
    output cout
);
    
    assign {cout,out} = in1 + in2 + cin;
    
endmodule
