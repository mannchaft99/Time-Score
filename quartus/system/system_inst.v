	system u0 (
		.clk_clk                          (<connected-to-clk_clk>),                          //                       clk.clk
		.key_external_connection_export   (<connected-to-key_external_connection_export>),   //   key_external_connection.export
		.reset_reset_n                    (<connected-to-reset_reset_n>),                    //                     reset.reset_n
		.sw_external_connection_export    (<connected-to-sw_external_connection_export>),    //    sw_external_connection.export
		.hex_0_external_connection_export (<connected-to-hex_0_external_connection_export>), // hex_0_external_connection.export
		.hex_1_external_connection_export (<connected-to-hex_1_external_connection_export>), // hex_1_external_connection.export
		.hex_2_external_connection_export (<connected-to-hex_2_external_connection_export>)  // hex_2_external_connection.export
	);

