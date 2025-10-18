require "data/sortedset.cr"
class Map(K, V)
	def initialize(@gen : Proc(V));@data  = Sortedset(Tuple(K,V)).new;end
	def initialize(@gen : Proc(V), @data : Sortedset(Tuple(K,V)));end
	def clone;Map.new(@gen, @data);end
	def head;@data.head;end
	def tail;@data.tail;end
	def empty?;@data.empty?;end
	def size;@data.size;end
	def clear;@data.clear;end
	def [](key : K)
		it = @data.lower_bound({key,@gen.call})
		if it != @data.tail && it.v[0] == key
			it.v[1]
		elsif it != @data.head && (it-1).v[0] == key
			(it-1).v[1]
		else
			v = @gen.call
			@data << {key, v}
			v
		end
	end
	def []=(key : K, val : V)
		it = @data.lower_bound({key,@gen.call})
		if it != @data.tail && it.v[0] == key
			it.v = {key,val}
		elsif it != @data.head && (it-1).v[0] == key
			(it-1).v = {key,val}
		else
			@data << {key, val}
		end
		val
	end
	def erase(key : K)
		it = lower_bound(key)
		return false if it == tail || it.v[0] != key
		@data.erase(it.v)
	end
	def count(key : K)
		it = @data.lower_bound({key,@gen.call})
		if it != @data.tail && it.v[0] == key
			true
		elsif it != @data.head && (it-1).v[0] == key
			true
		else
			false
		end
	end
	def find(key : K);count key;end
	def contains(key : K);count key;end
	def lower_bound(key : K)
		it = @data.lower_bound({key,@gen.call})
		if it != @data.tail && it.v[0] == key
			it
		elsif it != @data.head && (it-1).v[0] == key
			it-1
		else
			tail
		end
	end
	def upper_bound(key : K)
		it = @data.lower_bound({key,@gen.call})
		if it == @data.tail
			it
		elsif it.v[0] <= key
			it+1
		else
			it
		end
	end
	def to_a;@data.to_a;end
	def keys;@data.to_a.map(&.[0]);end
	def values;@data.to_a.map(&.[1]);end
end
