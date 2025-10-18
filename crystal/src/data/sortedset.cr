require "array_ext.cr"
class Sortedset(T)
	struct Iterator(T)
		def initialize(@outer : Int32, @inner : Int32, @bag : Array(Array(T)));end
		def v;@bag[@outer][@inner];end
		def v=(x : T);@bag[@outer][@inner]=x;end
		def +(n : Int32)
			outer, inner = @outer, @inner
			if n >= 0
				while @bag[outer].size-1-inner < n;n -= @bag[outer].size - inner;inner = 0;outer += 1;end
				inner += n
			else
				n = -n
				while inner < n;n -= inner+1;inner = @bag[outer-=1].size-1;end
				inner -= n
			end
			Iterator(T).new(outer, inner, @bag)
		end
		def -(n : Int32);self + (-n);end
		def -(b : Iterator(T))
			dist, sign = 0, 1
			ain, aout = @inner, @outer
			bin, bout = b.@inner, b.@outer
			if aout < bout || (aout == bout && ain < bin)
				ain, bin = bin, ain
				aout, bout = bout, aout
				sign = -1
			end
			while aout > bout;dist += @bag[bout].size - bin;bin = 0;bout += 1;end
			dist += ain - bin
			dist * sign
		end
		include Comparable(Iterator(T))
		def <=>(other : Iterator(T))
			cmp = @outer <=> other.@outer
			cmp != 0 ? cmp : @inner <=> other.@inner
		end
	end
	def head;Iterator(T).new(0, 0, @list);end
	def tail;Iterator(T).new(@list.size, 0, @list);end
	RATIO = 8
	BOUND = 20
	def initialize;@size = 0;@list = [] of Array(T);end
	def initialize(@size : Int32, @list : Array(Array(T)));end
	def initialize(z : Array(T))
		@size = z.size
		s = Math.sqrt(@size.to_f/ RATIO).ceil.to_i
		@list = Array(Array(T)).new(s) { [] of T }
		z.sort!
		z.unique!
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
		(@list = [[x]]; @size = 1; return true) if empty?
		bi, i = _position(x)
		return false if i != @list[bi].size && @list[bi][i] == x
		@list[bi].insert(i, x)
		@size += 1
		if @list[bi].size > @list.size*BOUND
			mid = @list[bi].size >> 1
			nb = @list[bi][mid..]
			@list[bi].delete_at(mid..)
			@list.insert(bi + 1, nb)
		end
		true
	end
	def erase(x : T)
		return false if empty?
		bi, i = _position(x)
		return false if i == @list[bi].size || @list[bi][i] != x
		_pop(bi, i)
		return true
	end
	def toggle(x : T)
		insert(x) ? true : !erase(x)
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
	def count(x : T);find(x);end
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
	def to_a;@list.flatten;end
	def lower_bound(x : T)
		@list.size.times { |i| return Iterator(T).new(i, @list[i].bsearch_index { |v| v >= x }.not_nil!,@list) if !@list[i].empty? && @list[i][-1] >= x }
		tail
	end
	def upper_bound(x : T)
		@list.size.times { |i| return Iterator(T).new(i, @list[i].bsearch_index { |v| v > x }.not_nil!,@list) if !@list[i].empty? && @list[i][-1] > x }
		tail
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
