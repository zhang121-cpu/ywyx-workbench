module top(
  input clk,
  input rst,
  output [7:0] led
);

  reg [15:0] count;

  always @(posedge clk ) begin
    if (rst)
      count <= 0;
    else 
      count <= count + 1;
  end

  assign led[7] = (count[15])&(count[14])&(count[13]);
  assign led[6] = (count[15])&(count[14])&(~count[13]);
  assign led[5] = (count[15])&(~count[14])&(count[13]);
  assign led[4] = (count[15])&(~count[14])&(~count[13]);
  assign led[3] = (~count[15])&(count[14])&(count[13]);
  assign led[2] = (~count[15])&(count[14])&(~count[13]);
  assign led[1] = (~count[15])&(~count[14])&(count[13]);
  assign led[0] = (~count[15])&(~count[14])&(~count[13]);

endmodule
