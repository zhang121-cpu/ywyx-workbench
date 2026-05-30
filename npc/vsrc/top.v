module top(
  input clk,
  input rst,
  output led[7:0]
);

  reg [7:0] count;

  always @(posedge clk ) begin
    if (rst)
      count <= 0;
    else 
      count <= count + 1;
  end

  assign led[7] = (count[7])&(count[6])&(count[5]);
  assign led[6] = (count[7])&(count[6])&(~count[5]);
  assign led[5] = (count[7])&(~count[6])&(count[5]);
  assign led[4] = (count[7])&(~count[6])&(~count[5]);
  assign led[3] = (~count[7])&(count[6])&(count[5]);
  assign led[2] = (~count[7])&(count[6])&(~count[5]);
  assign led[1] = (~count[7])&(~count[6])&(count[5]);
  assign led[0] = (~count[7])&(~count[6])&(~count[5]);

endmodule
