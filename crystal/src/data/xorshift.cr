struct Xorshift32
  @state : UInt32
  def initialize(seed = 2463534242);@state = seed.to_u32!;end
  def next_u
    x = @state
    x ^= x << 13
    x ^= x >> 17
    x ^= x << 5
    @state = x
  end
  def rand;next_u.to_i32!;end
end
struct Xorshift64
  @state : UInt64
  def initialize(seed = 2463534242);@state = seed.to_u64!;end
  def next_u
    x = @state
    x ^= x << 7
    x ^= x >> 9
    @state = x
  end
  def rand;next_u.to_i64!;end
end
