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
    BITS = {{bits}}
    # W = 2^BIT
    P = {{mod}}.{{us}}
    P2 = P << 1
    # 1 / y - P = 0
    R = begin
          y = P;6.times{ y &*= 2.{{us}} &- P &* y }
          &-y
        end
    # (W^2 - P) % P = W^2 % P
    R2 = (&-P.{{ds}} % P).{{us}}
    MAX = new(-1)
    MIN = new(0)
    property v : {{u_tp}}
    @v = 0.{{us}}
    # reduce(x)=x/W
    @[AlwaysInline]
    def self.reduce(x : {{d_tp}})
      ((x &+ (x.{{us}} &* R).{{ds}} * P) >> BITS).{{us}}
    end
    def self.mod
      P
    end
    def self.zero
      new 0
    end
    def zero?
      val == 0
    end
    def val
      x = self.class.reduce @v
      x &- P >> BITS - 1 == 0 ? x - P : x
    end
    def to_i;val;end
    def initialize;@v = 0;end
    def initialize(x : Int);@v = self.class.reduce((x.to_i128! % P).{{ds}} * R2);end
    def initialize(x : {{u_tp}}, d);@v = x;end
    def initialize(x : self);@v = x.v;end
    def ==(other : self)
      val == other.val
    end
    def -
        @v == 0 ? self.class.new(0.{{us}}, 0) : self.class.new(P2 - @v, 0)
    end
    def +(other : self)
      z = self.class.new(@v &+ other.v, 0)
      z.v &-= P2 if z.v &- P2 >> BITS - 1 == 0
      z
    end
    def -(other : self)
      z = self.class.new(@v &- other.v, 0)
      z.v &+= P2 if z.v >> BITS - 1 != 0
      z
    end
    def *(other : self)
      self.class.new(self.class.reduce(@v.{{ds}}*other.v), 0)
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
  class IOset
    def putv(x : {{name}});write_int x.val;end
  end
  struct Int
    def +(other : {{name}});other + self;end
    def -(other : {{name}});-other + self;end
    def *(other : {{name}});other * self;end
    def /(other : {{name}});other.inv * self;end
    def ==(other : {{name}});other == self;end
  end
end
modint_gen(F998244353, 998244353)
require "spec"
# ※ ライブラリが定義されているファイルをここでrequireしてください
# require "../src/math_lib.cr"
    MOD = 998244353i64

describe "Number Theory Library" do
  describe "inv_gcd & modinv" do
    it "correctly computes extended gcd and modular inverse" do
      # 正常系: 互いに素な場合
      g_inv, gcd = inv_gcd(3, 7)
      gcd.should eq(1)
      (g_inv % 7).should eq(5) # 3 * 5 = 15 ≡ 1 mod 7
      modinv(3, 7).should eq(5)

      # 逆元が存在しない場合（互いに素でない）
      _, gcd2 = inv_gcd(4, 6)
      gcd2.should eq(2)
      modinv(4, 6).should eq(0)
    end
  end

  describe "crt (Chinese Remainder Theorem)" do
    it "solves standard simultaneous congruences" do
      # x ≡ 2 (mod 3), x ≡ 3 (mod 5), x ≡ 2 (mod 7) => x = 23 (mod 105)
      r = [2i64, 3i64, 2i64]
      m = [3i64, 5i64, 7i64]
      rem, mod = crt(r, m)
      rem.should eq(23)
      mod.should eq(105)
    end

    it "handles cases where moduli are not coprimes" do
      # x ≡ 2 (mod 6), x ≡ 8 (mod 9) => x = 8 (mod 18)
      rem, mod = crt([2i64, 8i64], [6i64, 9i64])
      rem.should eq(8)
      mod.should eq(18)
    end

    it "returns {0, 0} for impossible congruences" do
      # x ≡ 2 (mod 4), x ≡ 3 (mod 6) => 偶数かつ奇数となり矛盾
      rem, mod = crt([2i64, 3i64], [4i64, 6i64])
      rem.should eq(0)
      mod.should eq(0)
    end
  end

  describe "modpow" do
    it "computes modular exponentiation correctly" do
      modpow(2i64, 10i64, 998244353i64).should eq(1024)
      modpow(3i64, 45i64, 1_000_000_007i64).should eq(322671501)
      modpow(5i64, 0i64, 13i64).should eq(1) # 指数が0
    end
  end

  describe "linear_modinv" do
    it "enumerates modular inverses up to n" do
      m = 998244353i64
      invs = linear_modinv(10, m)
      (1..10).each do |i|
        (i.to_i64 * invs[i] % m).should eq(1)
      end
    end
  end

  describe "primitive_root" do
    it "finds the minimum primitive root for a prime" do
      primitive_root(998244353).should eq(3)
      primitive_root(7).should eq(3)
      primitive_root(2).should eq(1)
    end
  end

  describe "discrete_log" do
    it "computes baby-step giant-step correctly" do
      # 3^x ≡ 27 mod 998244353 => x = 3
      discrete_log(3i64, 27i64, 998244353i64).should eq(3)

      # 3^x ≡ 400 mod 998244353
      x = discrete_log(3i64, 400i64, 998244353i64)
      x.should_not eq(-1)
      modpow(3i64, x.to_i64, 998244353).should eq(400)
    end

    it "returns -1 when no solution exists" do
      discrete_log(2i64, 3i64, 4i64).should eq(-1)
    end
  end

  describe "Montgomery ModInt (F998244353)" do

    it "initializes and restores original values correctly" do
      a = F998244353.new(123456789)
      a.val.should eq(123456789)

      # 負の数やMOD以上の数からの初期化
      b = F998244353.new(-1)
      b.val.should eq(MOD - 1)

      c = F998244353.new(MOD + 5)
      c.val.should eq(5)
    end

    it "performs basic arithmetic operations correctly" do
      a = F998244353.new(500_000_000)
      b = F998244353.new(600_000_000)

      # 加算 (オーバーフローのラップアラウンド確認)
      (a + b).val.should eq((500_000_000i64 + 600_000_000) % MOD)

      # 減算 (アンダーフローの P2 加算確認)
      (a - b).val.should eq((500_000_000i64 - 600_000_000) % MOD)

      # 乗算 (Montgomery Reduction の正常性確認)
      (a * b).val.should eq((500_000_000i64 * 600_000_000) % MOD)

      # 単項マイナス
      (-a).val.should eq(MOD - 500_000_000)
    end

    it "supports mixed operations with primitive Integers" do
      a = F998244353.new(10)
      (a + 5).val.should eq(15)
      (a - 12).val.should eq(MOD - 2)
      (a * 3).val.should eq(30)

      # プリミティブ側が左辺のパターン
      (5 + a).val.should eq(15)
      (20 - a).val.should eq(10)
      (3 * a).val.should eq(30)
    end

    it "computes powers and inverses correctly" do
      a = F998244353.new(2)
      a.pow(10).val.should eq(1024)

      # 逆元と除算
      b = F998244353.new(3)
      b_inv = b.inv
      (b * b_inv).val.should eq(1)

      c = F998244353.new(10)
      (c / b).val.should eq((c * b_inv).val)
    end
  end
end
