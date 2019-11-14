library verilog;
use verilog.vl_types.all;
entity CPU is
    port(
        clk             : in     vl_logic;
        rst             : in     vl_logic
    );
end CPU;
