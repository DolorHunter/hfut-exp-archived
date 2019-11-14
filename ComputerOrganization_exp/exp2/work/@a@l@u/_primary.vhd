library verilog;
use verilog.vl_types.all;
entity ALU is
    port(
        EN              : in     vl_logic;
        \select\        : in     vl_logic_vector(2 downto 0);
        src1            : in     vl_logic_vector(15 downto 0);
        src2            : in     vl_logic_vector(15 downto 0);
        ans             : out    vl_logic_vector(15 downto 0)
    );
end ALU;
