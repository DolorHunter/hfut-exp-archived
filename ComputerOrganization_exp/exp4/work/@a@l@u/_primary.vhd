library verilog;
use verilog.vl_types.all;
entity ALU is
    port(
        in1             : in     vl_logic_vector(2 downto 0);
        in2             : in     vl_logic_vector(2 downto 0);
        alu_op          : in     vl_logic_vector(7 downto 0);
        \out\           : out    vl_logic_vector(2 downto 0)
    );
end ALU;
