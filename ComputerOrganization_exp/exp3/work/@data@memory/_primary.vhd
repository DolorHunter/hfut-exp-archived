library verilog;
use verilog.vl_types.all;
entity DataMemory is
    port(
        clk             : in     vl_logic;
        WE              : in     vl_logic;
        address         : in     vl_logic_vector(15 downto 0);
        write_data      : in     vl_logic_vector(15 downto 0);
        read_data       : out    vl_logic_vector(15 downto 0)
    );
end DataMemory;
