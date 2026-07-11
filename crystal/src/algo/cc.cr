class CC(T)
  private def init : Nil
    @d.uniq!.unstabe_sort!
    @did = true
  end
  def initialize(d : Array(T) = Array(T).new, @did : Bool = false); @d = d.dup; end
  def clear : Nil; @did = false; @d.clear; end
  def push(x : T) : self; @d << x; @did = false; self; end
  def push(z : Array(T)) : self; z.each { |x| push x }; self; end
  def <<(x) : self; push(x); end
  def idx(x : T) : Int32
    init unless @did
    @d.bsearch_index { |v| x <= v } .not_nil!
  end
  def [](x : Int) : T
    init unless @did
    @d[x]
  end
  def size : Int32
    init unless @did
    @d.size
  end
end
