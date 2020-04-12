`default_nettype none 

module pulsedemo_top (
	input CLOCK,
	output PULSE);

reg [10:0]		counter = 'd0;
reg				pulse_int = 'b0;

always @(posedge CLOCK) begin
	counter <= counter + 1;

	pulse_int <= 'd1;
	if (counter > 'd6) begin
		pulse_int <= 'd0;
	end

	if (counter > 'd800)  begin
		counter <= 'd0;
	end
end

assign PULSE = pulse_int;

endmodule