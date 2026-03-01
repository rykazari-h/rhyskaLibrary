class MaxFlow(T)
  class Edge(T)
    property to; property cap; property rev
    def initialize(@to : Int32 = 0, @cap : T = T.zero, @rev : Int32 = 0); end
  end
  def initialize(@n : Int32)
    @g  = Array.new(@n) { [] of Edge(T) }
    @dist = [] of Int32
    @tosee = [] of Int32
  end
  def add_edge(u : Int, v : Int, cap : T) : Nil
    @g[u] << Edge(T).new v.to_i, cap, @g[v].size
    @g[v] << Edge(T).new u.to_i, T.zero, @g[u].size - 1
  end
  def max_flow(s : Int, t : Int) : T
    flow = T.zero
    loop do
      bfs s.to_i
      break if @dist[t] == -1
      @tosee = Array.new @n , 0
      while 0 < (f = dfs(s.to_i, t.to_i, T::MAX))
        flow += f
      end
    end
    flow
  end
  private def bfs(s : Int32) : Nil
    @dist = Array.new @n, -1; @dist[s] = 0
    queue = Deque(Int32).new; queue << s
    until queue.empty?
      u = queue.shift
      @g[u].each do |e|
        if 0 < e.cap && @dist[e.to] == -1
          @dist[e.to] = @dist[u] + 1
          queue << e.to
        end
      end
    end
  end
  private def dfs(u : Int32, t : Int32, f : T) : T
    return f if u == t
    @tosee[u].upto(@g[u].size - 1) do |i|
      e = @g[u][i]
      if 0 < e.cap && @dist[u] < @dist[e.to]
        if 0 < (d = dfs e.to, t, f < e.cap ? f : e.cap)
          e.cap -= d
          g[e.to][e.rev].cap += d
          return d
        end
      end
      @tosee[u] += 1
    end
    T.zero
  end
end
