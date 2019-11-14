library verilog;
use verilog.vl_types.all;
entity RegFiles is
    port(
        clk             : in     vl_logic;
        wr_en           : in     vl_logic;
        rd_reg1         : in     vl_logic_vector(0 to 2);
        rd_reg2         : in     vl_logic_vector(0 to 2);
        wr_reg          : in     vl_logic_vector(0 to 2);
        wr_data         : in     vl_logic_vector(2 downto 0);
        reg_data1       : out    vl_logic_vector(2 downto 0);
        reg_data2       : out    vl_logic_vector(2 downto 0)
    );
end RegFiles;
