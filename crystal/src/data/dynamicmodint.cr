require "math/math_ext.cr"
struct DynamicModint
	property mod : Int64
	getter v : Int64
	@mod = 1i64
	def initialize(@v : Int64 = 0i64, @mod, reduce = true); @v %= @mod if reduce; end
	def self.zero(m : Int64 = 1i64)
		new 0i64, m, false
	end
	def val; @v; end
	def to_i; @v; end
	def ==(other : self)
		@v == other.v
	end
	def -
			self.class.new @v == 0 ? 0i64 : @mod - @v, @mod, false
	end
	def +(other : self)
		v = @v + other.v
		v -= @mod if @mod <= v
		self.class.new v, @mod, false
	end
	def -(other : self)
		v = @v - other.v
		v += @mod if v < 0
		self.class.new v, @mod, false
	end
	def *(other : self)
		self.class.new (@v.to_i128 * other.v % @mod).to_i64, @mod, false
	end
	def /(other : self)
		self.class.new @v.to_i128 * modinv(other.v, @mod) % @mod, @mod, false
	end
	def +(other : Int)
		v = @v + other % @mod
		v -= @mod if @mod <= v
		self.class.new v, @mod, false
	end
	def -(other : Int)
		v = @v - other % @mod
		v += @mod if v < 0
		self.class.new v, @mod, false
	end
	def *(other : Int)
		self.class.new (@v.to_i128 * (other % @mod) % @mod).to_i64, @mod, false
	end
	def /(other : Int)
		self.class.new (@v.to_i128 * modinv(other % @mod, @mod) % @mod).to_i64, @mod, false
	end
	def ==(other : Int); @v == other; end
	def pow(k)
		res = self.class.new 1, @mod, false
		a = self
		while k != 0
			res *= a if k & 1 != 0
			k >>= 1
			a *= a
		end
		res
	end
	def inv
		self.class.new modinv(@v, @mod), @mod, false
	end
end
class IOset
	def self.putv(x : DynamicModint); write_int x.v; end
end
struct Int
	def +(other : DynamicModint); other + self; end
	def -(other : DynamicModint); -other + self; end
	def *(other : DynamicModint); other * self; end
	def /(other : DynamicModint); other.inv * self; end
	def ==(other : DynamicModint); other == self; end
end
