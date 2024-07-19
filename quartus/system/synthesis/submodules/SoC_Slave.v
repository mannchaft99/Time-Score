module SoC_Slave(
	input				iClk,
	input				iReset_n,
	input				iWrite,
	input				iChipSelect,
	input				iRead,
	input		[1:0]	iAddr,
	input		[31:0]	iData,
	output reg	[31:0]	oData
);
	reg [31:0]	minute, second, point;
	always @(posedge iClk or negedge iReset_n) begin
		if(~iReset_n) begin
			oData <= 32'd0;
			minute <= 32'd0;	
			second <= 32'd0;
			point <= 32'd0;
		end
		else begin
			if(iChipSelect & iWrite) begin
				case (iAddr)
					2'd0: minute[15:0] <= iData[15:0];
					2'd1: second[15:0] <= iData[15:0];
					2'd2: point[15:0] <= iData[15:0];
				endcase
			end
			else if (iChipSelect & iRead) begin
				case (iAddr)
					2'd0: oData <= minute;
					2'd1: oData <= second;
					2'd2: oData <= point;
				endcase
			end
		end	
	end

endmodule
