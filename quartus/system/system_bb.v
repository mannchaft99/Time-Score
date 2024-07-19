
module system (
	clk_clk,
	key_external_connection_export,
	reset_reset_n,
	sw_external_connection_export,
	hex_0_external_connection_export,
	hex_1_external_connection_export,
	hex_2_external_connection_export);	

	input		clk_clk;
	input	[31:0]	key_external_connection_export;
	input		reset_reset_n;
	input	[31:0]	sw_external_connection_export;
	output	[31:0]	hex_0_external_connection_export;
	output	[31:0]	hex_1_external_connection_export;
	output	[31:0]	hex_2_external_connection_export;
endmodule
