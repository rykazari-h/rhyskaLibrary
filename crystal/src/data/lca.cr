class Lca
  property g : Array(Array(Int32))
  def initialize(@n : Int32, @root : Int32 = 0)
    @k = @n == 1 ? 1 : (@n - 1).bit_length
    @g = Array.new(@n) { [] of Int32 }
    @dist = Array(Int32).new(@n, 0)
    @parent = Array(Array(Int32)).new(@k) { Array.new(@n, @root) }
    @initialized = false
  end
  def add(u : Int32, v : Int32) : Nil
    g[u] << v
    g[v] << u
    @initialized = false
  end
  private def dfs(u : Int32, p : Int32, d : Int32) : Nil
    @dist[u] = d
    @parent[0][u] = p
    g[u].each do |v|
      dfs v, u, d + 1 if v != p
    end
  end
  def init : Nil
    dfs @root, @root, 0
    (@k - 1).times do |i|
      @n.times do |u|
        @parent[i + 1][u] = @parent[i][@parent[i][u]]
      end
    end
  end
  def lca(u : Int32, v : Int32)
    init if !@initialized && (@initialized = true)
    u, v = v, u if @dist[u] < @dist[v]
    @k.times do |i|
      u = @parent[i][u] if @dist[u] - @dist[v] >> i & 1 == 1
    end
    if u == v
      u
    else
      (@k - 1).downto(0) do |i|
        u, v = @parent[i][u], @parent[i][v] if @parent[i][u] != @parent[i][v]
      end
      @parent[0][u]
    end
  end
  def dist(u : Int32, v : Int32)
    init if !@initialized && (@initialized = true)
    t = lca(u, v)
    @dist[u] + @dist[v] - @dist[t] - @dist[t]
  end
end
