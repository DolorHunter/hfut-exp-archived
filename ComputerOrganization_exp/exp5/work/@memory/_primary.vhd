library verilog;
use verilog.vl_types.all;
entity Memory is
    port(
        clk             : in     vl_logic;
        m_wr_en         : in     vl_logic;
        addr            : in     vl_logic_vector(2 downto 0);
        wr_data         : in     vl_logic_vector(2 downto 0);
        rd_data         : out    vl_logic_vector(2 downto 0)
    );
end Memory;
