class BinaryHeap(T)
	def initialize(&comp : T, T -> Bool);@comp=comp;@data = Array(T).new;end
	def initialize(@data : Array(T), &comp : T, T -> Bool);@comp=comp;end
	def clone;BinaryHeap.new(@data.clone, &@comp);end
	def empty?;@data.empty?;end
	def size;@data.size;end
	def a;@data;end
	def to_a;@data;end
	def push(val : T)
		n =	@data.size
		@data << val
		while n > 0
			p =	(n-1) >> 1
			break if @comp.call(@data[p], @data[n])
			@data[n], @data[p] = @data[p], @data[n]
			n=p
		end
	end
	def <<(val : T);push(val); self;end
	def top : T
		raise "heap is empty!!" if @data.empty?
		@data[0]
	end
	def pop : T
		raise "heap is empty!!" if @data.empty?
		n, res , last = 0, @data[0], @data.pop
		return res if @data.empty?
		@data[0]=last
		loop do
			lc, rc ,c = (n << 1) + 1, (n + 1) << 1, n
			c = lc if lc < @data.size && !@comp.call(@data[c], @data[lc])
			c = rc if rc < @data.size && !@comp.call(@data[c], @data[rc]) && @data[c] != @data[rc]
			break if c == n
			@data[n], @data[c] = @data[c], @data[n]
			n = c
		end
		res
	end
end
class Gpq(T) < BinaryHeap(T);def initialize;super { |a, b| a < b };end;end
class Lpq(T) < BinaryHeap(T);def initialize;super { |a, b| a > b };end;end
