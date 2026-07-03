class Dsu
  @n : Int32
  def initialize(@n : Int);@p = Pointer(Int32).malloc(@n, -1); @sz = @n;end
  def merge(a : Int, b : Int)
    a = root(a);b = root(b)
    return false if a == b
    @sz -= 1
    if @p[a] < @p[b]
      @p[a] += @p[b];@p[b] = a
    else
      @p[b] += @p[a];@p[a] = b
    end
    true
  end
  def reset
    @sz = @n
    @n.times { |i| @p[i] = -1 }
  end
  def same(a : Int, b : Int);root(a) == root(b);end
  def root(a : Int);return a if @p[a] < 0;@p[a] = root(@p[a]);end
  def size(z : Int);-@p[root(z)];end
  def size;@sz;end
  def roots
    res = Array.new(@sz, 0)
    idx = 0
    @n.times do |i|
      if i == root i
        res[idx] = i
        idx += 1
      end
    end
    res
  end
  def groups
    id = Pointer(Int32).malloc(@n, -1)
    id_c = 0
    res = Array(Array(Int32)).new @sz
    cnt = Pointer(Int32).malloc(@sz)
    @n.times do |i|
      r = root i
      (id[r] = id_c; id_c += 1) if id[r] == -1
      cnt[id[r]] += 1
    end
    @sz.times { |i| res << Array(Int32).new cnt[i] }
    @n.times { |i| res[id[root(i)]] << i }
    res
  end
end
