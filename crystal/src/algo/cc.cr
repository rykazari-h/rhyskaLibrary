struct CC(T)
  private def init : Nil
    @d = @d.uniq.sort
    @did = true
  end
  def initialize(@d : Array(T) = Array(T).new, @did : Bool = false); end
  def clear; @did = false; @d.clear; end
  def push(x : T); @d << x; @did = false; end
  def push(z : Array(T)); z.each { |x| push x }; end
  def <<(x); push(x); self; end
  def idx(x : T)
    init unless @did
    @d.bsearch_index { |v| x <= v } .not_nil!
  end
  def [](x : Int)
    init unless @did
    @d[x]
  end
  def size
    init unless @did
    @d.size
  end
end
