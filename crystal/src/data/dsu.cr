class Dsu
  def initialize(@n : Int32);@p = Array(Int32).new(@n, -1);end
  def merge(a : Int32, b : Int32)
    a = root(a);b = root(b)
    return false if a == b
    if @p[a] < @p[b]
      @p[a] += @p[b];@p[b] = a
    else
      @p[b] += @p[a];@p[a] = b
    end
    true
  end
  def same(a : Int32, b : Int32);root(a) == root(b);end
  def root(a : Int32);return a if @p[a] < 0;@p[a] = root(@p[a]);end
  def size(z : Int32);-@p[root(z)];end
  def size;count = Array(Int32).new(@n, 0);n.times { |i| count[root(i)] = 1 };count.sum;end
  def groups
    res = Array(Array(Int32)).new(@n) { [] of Int32 };n.times { |i| res[root(i)] << i }
    res.reject { |v| v.empty? }
  end
end
