library verilog;
use verilog.vl_types.all;
entity decoder38 is
    port(
        EN              : in     vl_logic;
        Ip2             : in     vl_logic;
        Ip1             : in     vl_logic;
        Ip0             : in     vl_logic;
        Op0             : out    vl_logic;
        Op1             : out    vl_logic;
        Op2             : out    vl_logic;
        Op3             : out    vl_logic;
        Op4             : out    vl_logic;
        Op5             : out    vl_logic;
        Op6             : out    vl_logic;
        Op7             : out    vl_logic
    );
end decoder38;
