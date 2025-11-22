struct Xorshift32
  @state : UInt32
  def initialize(seed : UInt32 = 2463534242);@state = seed;end
  def next_u32
    x = @state
    x ^= x << 13
    x ^= x >> 17
    x ^= x << 5
    @state = x
  end
  def urandom;next_u32;end
end
