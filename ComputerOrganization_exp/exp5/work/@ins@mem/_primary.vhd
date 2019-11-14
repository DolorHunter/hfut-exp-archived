library verilog;
use verilog.vl_types.all;
entity InsMem is
    port(
        addr            : in     vl_logic_vector(6 downto 0);
        ins             : out    vl_logic_vector(15 downto 0)
    );
end InsMem;
