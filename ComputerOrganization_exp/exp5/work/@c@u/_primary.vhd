library verilog;
use verilog.vl_types.all;
entity CU is
    port(
        ins             : in     vl_logic_vector(6 downto 0);
        alu_out         : in     vl_logic_vector(2 downto 0);
        wr_en           : out    vl_logic;
        m_wr_en         : out    vl_logic;
        alu_op          : out    vl_logic_vector(6 downto 0)
    );
end CU;
