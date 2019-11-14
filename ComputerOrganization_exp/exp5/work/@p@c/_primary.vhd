library verilog;
use verilog.vl_types.all;
entity PC is
    port(
        clk             : in     vl_logic;
        rst             : in     vl_logic;
        pc              : out    vl_logic_vector(6 downto 0)
    );
end PC;
