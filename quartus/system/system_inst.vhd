	component system is
		port (
			clk_clk                          : in  std_logic                     := 'X';             -- clk
			key_external_connection_export   : in  std_logic_vector(31 downto 0) := (others => 'X'); -- export
			reset_reset_n                    : in  std_logic                     := 'X';             -- reset_n
			sw_external_connection_export    : in  std_logic_vector(31 downto 0) := (others => 'X'); -- export
			hex_0_external_connection_export : out std_logic_vector(31 downto 0);                    -- export
			hex_1_external_connection_export : out std_logic_vector(31 downto 0);                    -- export
			hex_2_external_connection_export : out std_logic_vector(31 downto 0)                     -- export
		);
	end component system;

	u0 : component system
		port map (
			clk_clk                          => CONNECTED_TO_clk_clk,                          --                       clk.clk
			key_external_connection_export   => CONNECTED_TO_key_external_connection_export,   --   key_external_connection.export
			reset_reset_n                    => CONNECTED_TO_reset_reset_n,                    --                     reset.reset_n
			sw_external_connection_export    => CONNECTED_TO_sw_external_connection_export,    --    sw_external_connection.export
			hex_0_external_connection_export => CONNECTED_TO_hex_0_external_connection_export, -- hex_0_external_connection.export
			hex_1_external_connection_export => CONNECTED_TO_hex_1_external_connection_export, -- hex_1_external_connection.export
			hex_2_external_connection_export => CONNECTED_TO_hex_2_external_connection_export  -- hex_2_external_connection.export
		);

