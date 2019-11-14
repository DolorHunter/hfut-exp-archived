library verilog;
use verilog.vl_types.all;
entity mux41 is
    port(
        in1             : in     vl_logic_vector(3 downto 0);
        in2             : in     vl_logic_vector(3 downto 0);
        in3             : in     vl_logic_vector(3 downto 0);
        in4             : in     vl_logic_vector(3 downto 0);
        \select\        : in     vl_logic_vector(1 downto 0);
        \out\           : out    vl_logic_vector(3 downto 0)
    );
end mux41;
