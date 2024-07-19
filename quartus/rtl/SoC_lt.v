module SoC_lt(
	input				CLOCK_50,
	input		[1:0] KEY,
	input		[9:0]	SW,
	output	[0:6] HEX0, HEX1, HEX2, HEX3, HEX4, HEX5
);

system u_sys(
	.clk_clk(CLOCK_50),
	.key_external_connection_export(KEY[1]),
	.reset_reset_n(KEY[0]),
	.sw_external_connection_export(SW),
	.hex_0_external_connection_export({HEX1, HEX0}),
	.hex_1_external_connection_export({HEX3, HEX2}),
	.hex_2_external_connection_export({HEX5, HEX4})
);


endmodule