class Sortedlist(T)
	RATIO = 8
	BOUND = 20
	def initialize;@size = 0;@list = [] of Array(T);end
	def initialize(@size : Int32, @list : Array(Array(T)));end
	def initialize(z : Array(T))
		@size = z.size
		s = Math.sqrt(@size.to_f/RATIO).ceil.to_i
		@list = Array(Array(T)).new(s) { [] of T }
		s.times { |i| @list[i] = z[(@size*i// s)...(@size*(i + 1)// s)] }
	end
	def empty?;@size == 0;end
	def size;@size;end
	def clear;@size = 0; @list.clear;end
	def clone;Sortedlist(T).new(@size,@list);end
	def _position(x : T)
		sz = @list.size
		sz.times { |i| return {i, @list[i].bsearch_index { |v| v >= x }.not_nil!} if x <= @list[i][-1] }
		{sz - 1, @list[-1].size}
	end
	def _pop(bi, i)
		v = @list[bi][i]
		@list[bi].delete_at(i)
		@size -= 1
		@list.delete_at(bi) if @list[bi].empty?
		v
	end
	def <<(x : T);insert(x);end
	def insert(x : T)
		(@list = [[x]]; @size = 1; return) if empty?
		bi, i = _position(x)
		@list[bi].insert(i, x)
		@size += 1
		return if @list[bi].size <= @list.size*BOUND
		mid = @list[bi].size >> 1
		nb = @list[bi][mid..]
		@list[bi].delete_at(mid..)
		@list.insert(bi + 1, nb)
	end
	def erase(x : T)
		return false if empty?
		bi, i = _position(x)
		return false if i == @list[bi].size || @list[bi][i] != x
		_pop(bi, i)
		return true
	end
	def erase_all(x : T)
		return false if empty?
		bi, i = _position(x)
		return false if i == @list[bi].size || @list[bi][i] != x
		while true
			@size -= @list[bi].count(x)
			@list[bi].delete(x)
			if @list[bi].empty?
				@list.delete_at(bi)
			else
				bi += 1
			end
			break if bi == @list.size || @list[bi][0] != x
		end
		return true
	end
	def pop(i : Int32 = -1)
		if i >= 0
			@list.size.times do |b|
				return _pop(b, i) if i < @list[b].size
				i -= @list[b].size
			end
		else
			(@list.size - 1).downto(0) do |b|
				i += @list[b].size
				return _pop(b, i) if i >= 0
			end
		end
		@list[-1][-1]
	end
	def count(x : T);index_rg(x) - index(x);end
	def find(x : T)
		return false if empty?
		bi, i = _position(x)
		i != @list[bi].size && @list[bi][i] == x
	end
	def contains(x : T);find(x);end
	def [](i : Int32)
		if i >= 0
			@list.size.times do |b|
				return @list[b][i] if i < @list[b].size
				i -= @list[b].size
			end
		else
			(@list.size - 1).downto(0) do |b|
				i += @list[b].size
				return @list[b][i] if i >= 0
			end
		end
		@list[-1][-1]
	end
	def []=(i : Int32, x : T)
		if i >= 0
			@list.size.times do |b|
				return @list[b][i] = x if i < @list[b].size
				i -= @list[b].size
			end
		else
			(@list.size - 1).downto(0) do |b|
				i += @list[b].size
				return @list[b][i] = x if i >= 0
			end
		end
		@list[-1][-1]
	end
	def a;@list;end
	def to_a
		r=[] of T
		@list.each{|v|r.concat(v)}
		r
	end
	def [](i : Tuple(Int32, Int32));@list[i[0]][i[1]];end
	def []=(i : Tuple(Int32, Int32), x : T);@list[i[0]][i[1]] = x;end
	def lower_bound(x : T)
		@list.size.times { |i| return {i, @list[i].bsearch_index { |v| v >= x }.not_nil!} if !@list[i].empty? && @list[i][-1] >= x }
		{@list.size, 0}
	end
	def upper_bound(x : T)
		@list.size.times { |i| return {i, @list[i].bsearch_index { |v| v > x }.not_nil!} if !@list[i].empty? && @list[i][-1] > x }
		{@list.size, 0}
	end
	def index(x : T)
		res = 0
		@list.each { |z| return res + z.bsearch_index { |v| v >= x }.not_nil! if z[-1] >= x; res += z.size }
		res
	end
	def index_rg(x : T)
		res = 0
		@list.each { |z| return res + z.bsearch_index { |v| v > x }.not_nil! if z[-1] > x; res += z.size }
		res
	end
end
