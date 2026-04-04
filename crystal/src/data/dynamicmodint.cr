require "math/math_ext.cr"
struct DynamicModint
	property mod
	getter v
	def initialize(@v : Int64 = 0i64, @mod = 1i64); @v %= @mod; end
	def self.zero(m : Int64 = 1i64)
		new 0i64, m
	end
	def val; @v; end
	def to_i; @v; end
	def ==(other : self)
		@v == other.v
	end
	def +(other : self)
		self.class.new (@v + other.v) % @mod, @mod
	end
	def -(other : self)
		self.class.new (@v - other.v) % @mod, @mod
	end
	def *(other : self)
		self.class.new (@v.to_i128 * other.v % @mod).to_i64, @mod
	end
	def /(other : self)
		self.class.new @v.to_i128 * modinv(other.v, @mod) % @mod, @mod
	end
	def +(other : Int); self + self.class.new(other, @mod); end
	def -(other : Int); self - self.class.new(other, @mod); end
	def *(other : Int); self * self.class.new(other, @mod); end
	def /(other : Int); self / self.class.new(other, @mod); end
	def ==(other : Int); @v == other; end
	def pow(k)
		res = self.class.new 1, @mod
		a = self
		while k != 0
			res *= a if k & 1 != 0
			k >>= 1
			a *= a
		end
		res
	end
	def inv
		self.class.new modinv @v, @mod
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
