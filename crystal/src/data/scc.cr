class Scc
  def initialize(@n : Int32)
    @gn = 0
    @g = Array(Array(Int32)).new(@n) { [] of Int32 }
    @rg = Array(Array(Int32)).new(@n) { [] of Int32 }
    @cmp = [-1]*@n
    @ord = [] of Int32
    @used = [false]*@n
  end
  def add(u, v)
    @g[u] << v; @rg[v] << u
  end
  def dfs(v)
    @used[v] = true
    @g[v].each { |u| dfs u if !@used[u] }
    @ord << v
  end
  def dfs2(v, k)
    @cmp[v] = k
    @rg[v].each { |u| dfs2 u, k if @cmp[u] == -1 }
  end
  def scc
    @n.times { |i| dfs i if !@used[i] }
    (@n - 1).downto(0) { |i| dfs2(@ord[i], (@gn += 1) - 1) if @cmp[@ord[i]] == -1 }
    res = Array(Array(Int32)).new(@gn) { [] of Int32 }
    @n.times { |i| res[@cmp[i]] << i }
    res
  end
end
