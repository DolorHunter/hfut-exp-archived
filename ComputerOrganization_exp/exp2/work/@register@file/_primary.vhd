library verilog;
use verilog.vl_types.all;
entity RegisterFile is
    port(
        EN              : in     vl_logic;
        WR              : in     vl_logic;
        data            : in     vl_logic_vector(15 downto 0);
        RD1             : in     vl_logic;
        RD2             : in     vl_logic;
        \select\        : in     vl_logic_vector(1 downto 0);
        AX              : out    vl_logic_vector(15 downto 0);
        BX              : out    vl_logic_vector(15 downto 0);
        CX              : out    vl_logic_vector(15 downto 0);
        DX              : out    vl_logic_vector(15 downto 0);
        SP              : out    vl_logic_vector(15 downto 0);
        BP              : out    vl_logic_vector(15 downto 0);
        DI              : out    vl_logic_vector(15 downto 0);
        SI              : out    vl_logic_vector(15 downto 0);
        ans             : out    vl_logic_vector(15 downto 0)
    );
end RegisterFile;
