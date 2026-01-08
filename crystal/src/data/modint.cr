require "math/math_ext.cr"
macro modint_gen(name, mod)
  {% if mod <= 0xffffffffu64 %}
    {% u_tp = "UInt32".id %}
    {% d_tp = "UInt64".id %}
    {% us = "to_u32!".id %}
    {% ds = "to_u64!".id %}
    {% bits = 32 %}
  {% else %}
    {% u_tp = "UInt64".id %}
    {% d_tp = "UInt128".id %}
    {% us = "to_u64!".id %}
    {% ds = "to_u128!".id %}
    {% bits = 64 %}
  {% end %}

  struct {{name}}
    alias U = {{u_tp}}
    alias D = {{d_tp}}
    BITS = {{bits}}
    P = {{mod}}.{{us}}
    P2 = P << 1
    R = ->{ y = P;6.times{ y &*= 2.{{us}} &- P &* y };&-y }.call
    R2 = (&-P.{{ds}} % P).{{us}}
    property v : U
    @v = 0.{{us}}
    @[AlwaysInline]
    def self.reduce(x : D)
      ((x &+ (x.{{us}} &* R).{{ds}} * P) >> BITS).{{us}}
    end
    def self.mod
      P
    end
    def val
      x = self.class.reduce v
      x &- P >> BITS - 1 == 0 ? x - P : x
    end
    def initialize;@v = 0;end
    def initialize(x : Int);@v = self.class.reduce((x % P).{{ds}} * R2);end
    def initialize(x : U, d);@v = x;end
    def initialize(x : self);@v = x.v;end
    def ==(other : self)
      val == other.val
    end
    def -
        v == 0 ? self.class.new(0.{{us}}, 0) : self.class.new(P2 - v, 0)
    end
    def +(other : self)
      z = self.class.new(v &+ other.v, 0)
      z.v -= P2 if (z.v &- P2) >> BITS - 1 == 0
      z
    end
    def -(other : self)
      z = self.class.new(v &- other.v, 0)
      z.v &+= P2 if z.v >> BITS - 1 != 0
      z
    end
    def *(other : self)
      self.class.new(self.class.reduce(v.{{ds}}*other.v), 0)
    end
    def /(other : self)
      self * other.inv
    end
    def +(other : Int);self + self.class.new(other);end
    def -(other : Int);self - self.class.new(other);end
    def *(other : Int);self * self.class.new(other);end
    def /(other : Int);self / self.class.new(other);end
    def ==(other : Int);val == other;end
    def pow(k)
      res = self.class.new(1)
      a = self
      while k != 0
        res *= a if k & 1 != 0
        k >>= 1
        a *= a
      end
      res
    end
    def inv
      self.class.new modinv val.to_i64, P.to_i64
    end
  end
  struct Int
    def +(other : {{name}});other + self;end
    def -(other : {{name}});-other + self;end
    def *(other : {{name}});other * self;end
    def /(other : {{name}});other.inv * self;end
    def ==(other : {{name}});other == self;end
  end
end
