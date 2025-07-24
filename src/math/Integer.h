#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include<math/math.h>
class Integer {
	using u64 = unsigned long long;
	using i64 = long long;
	using i16 = short;
	public:
	Integer():inList(0,0){}
	template<class T> Integer(const T& s) {*this = s;}
	Integer& operator=(const char* s) {
		std::vector<i16>& v = inList;
		const i64 len = std::strlen(s);
		v.resize((len+3) >> 2);
		for (i64 i = len, j = 0; i > 0;i -= 4, j++) {
			i64 a = std::max(0LL, i - 4);
			char buf[5]{};
			std::strncpy(buf, s + a, i - a);
			v[j] = (i16)(std::atoi(buf));
		}
		return *this;
	}
	Integer& operator=(const std::string s) {return *this = s.c_str();}
	bool operator==(const Integer& s) const {
		return inList == s.inList;
	}
	template<class T> Integer& operator=(const T& s) {return *this = std::to_string(s);}
	Integer operator+(const Integer& a) const {
		Integer c;
		c.inList = add(inList, a.inList);
		return c;
	}
	Integer operator-(const Integer& a) const {
		Integer c;
		c.inList = sub(inList, a.inList);
		return c;
	}
	Integer operator*(const Integer&a) const {
		Integer c;
		if(std::min(a.inList.size(), inList.size()) < 53) c.inList = mul_brute(inList, a.inList);
		else c.inList = mul(inList, a.inList);
		return c;
	}
	std::vector<i16> inList;
	static constexpr i64 Base = 10000;



	static std::vector<i16> mul_brute(const std::vector<i16>& a, const std::vector<i16>& b) {
		i64 as = a.size(), bs = b.size();
		if(as == 1 && a[0] == 0)return {0};
		if(bs == 1 && b[0] == 0)return {0};
		i64 n = as + bs - 1;
		std::vector<i64> c(n);
		for (i64 i = 0; i < as; i++)
			for ( i64 j = 0; j < bs; j++)
				c[i+j] += (i64)a[i] * b[j];
		for (i64 i = 0; i < n - 1; i++)
			if (c[i] >= Base) {
				i64 up = c[i] / Base;
				c[i] -= up * Base;
				c[i+1] += up;
			}
		while (c.back() >= Base) {
			i64 up = c.back() / Base;
			c.back() -= up * Base;
			c.push_back(up);
		}
		while (c.size() > 1 && !c.back()) c.pop_back();
		std::vector<i16> d;
		d.reserve(c.size());
		for (auto&&x : c) d.push_back(x);
		return d;
	}







	static std::vector<i16> add(const std::vector<i16>& a, const std::vector<i16>& b) {
		std::vector<i16> c;
		c.reserve( std::max(a.size(), b.size()) + 1);
		bool carry = 0;
		const std::vector<i16>& x = a.size() >= b.size() ? a : b;
		const std::vector<i16>& y = a.size() >= b.size() ? b : a;
		for (i64 i = 0, n = y.size(); i < n; i++) {
			i16 tmp = x[i] + y[i] + carry;
			if (tmp >= Base) {
				tmp -= Base;
				carry = 1;
			}
			else carry = 0;
			c.push_back(tmp);
		}
		for (i64 i = y.size(), n = x.size(); i < n; i++) {
			i16 tmp = x[i]+carry;
			if (tmp >= Base) {
				tmp -= Base;
				carry = 1;
			}
			else carry = 0;
			c.push_back(tmp);
		}
		if (carry) c.push_back(1);
		return c;
	}
	static std::vector<i16> sub(const std::vector<i16>& a, const std::vector<i16>& b) {
		std::vector<i16> c = a;
		i64 i = 0, lim = std::min(a.size(), b.size());
		bool carry = 0;
		for (; i < lim; i++) {
			c[i] = a[i] - b[i] - carry;
			carry = 0;
			if (c[i] < 0) {
				carry = 1;
				c[i] += Base;
			}
		}
		while (carry) {
			carry = 0;
			c[i]--;
			if (c[i] < 0) carry = 1, c[i] += Base;
			i++;
		}
		while (c.size() >= 2 && !c.back())c.pop_back();
		return c;
	}

	template<u64 MOD>struct rottable {
		i64 max_h;
		std::vector<u64> rate2, irate2, rate3, irate3, root, iroot;
		static u64 modpowu64(u64 a, u64 e) {
			u64 r = 1;
			for (;e;e >>= 1) {
				if (e & 1) r = (__uint128_t)r * a % MOD;
				a = (__uint128_t)a * a % MOD;
			}
			return r;
		}
		void init() {
			int h = max_h = __builtin_ctz(MOD - 1);
			root.resize(h + 1);
			iroot.resize(h + 1);
			u64 g = MOD == 0x2D000001 ?  11 : 3;
			root[h] = modpowu64(g, (MOD - 1) >> h);
			iroot[h] = modpowu64(root[h], MOD - 2);
			for (int i = h - 1; i >= 0; --i) {
				root[i] = (__uint128_t)root[i + 1] * root[i + 1] % MOD;
				iroot[i] = (__uint128_t)iroot[i + 1] * iroot[i + 1] % MOD;
			}
			rate2.resize(h);
			irate2.resize(h);
			rate3.resize(h - 1);
			irate3.resize(h - 1);
			u64 pr2 = 1, ipr2 = 1;
			for (int i = 0; i + 2 <= h; ++i) {
				rate2[i] = (__uint128_t)root[i + 2] * pr2 % MOD;
				irate2[i] = (__uint128_t)iroot[i + 2] * ipr2 % MOD;
				pr2 = (__uint128_t)pr2 * iroot[i + 2] % MOD;
				ipr2 = (__uint128_t)ipr2 * root[i + 2] % MOD;
			}
			u64 pr3 = 1, ipr3 = 1;
			for (int i = 0; i + 3 <= h; ++i) {
				rate3[i] = (__uint128_t)root[i + 3] * pr3 % MOD;
				irate3[i] = (__uint128_t)iroot[i + 3] * ipr3 % MOD;
				pr3 = (__uint128_t)pr3 * iroot[i + 3] % MOD;
				ipr3 = (__uint128_t)ipr3 * root[i + 3] % MOD;
			}
		}
	};
	template<u64 MOD> static void ntt(rottable<MOD>& info, std::vector<u64>& a, bool inv){
	i64 n = a.size();
	i64 h = __builtin_ctz(n);
	i64 len = inv ? h : 0;
	while ((inv ? len : h - len) > 0) {
		if ((inv ? len == 1 : h - len == 1)) {
			i64 p = 1 << (inv ? (h - len) : (h - len - 1));
			u64 rot = 1;
			for (i64 s = 0, S = 1 << (inv ? (len - 1) : len); s < S; ++s) {
				i64 offset = s << (inv ? (h - len + 1) : (h - len));
				for (i64 i = 0; i < p; ++i) {
					u64 &l = a[offset + i];
					u64 &r = a[offset + i + p];
					if (!inv) {
						u64 t = (__uint128_t)r * rot % MOD;
						r = (l + MOD - t) % MOD;
						l = (l + t) % MOD;
					} else {
						u64 t = r;
						r = (__uint128_t)((l + MOD - t) % MOD) * rot % MOD;
						l = (l + t) % MOD;
					}
				}
				if (s + 1 != S) {
					rot = (__uint128_t)rot * (inv ? info.irate2[__builtin_ctz(~s)] : info.rate2[__builtin_ctz(~s)]) % MOD;
				}
			}
			len += inv ? -1 : 1;
		} else {
			i64 p = 1 << (inv ? (h - len) : (h - len - 2));
			u64 rot = 1, imag = inv ? info.iroot[2] : info.root[2];
			for (i64 s = 0, S = 1 << (inv ? (len - 2) : len); s < S; ++s) {
				u64 rot2 = (__uint128_t)rot * rot % MOD;
				u64 rot3 = (__uint128_t)rot2 * rot % MOD;
				i64 offset = s << (inv ? (h - len + 2) : (h - len));
				for (i64 i = 0; i < p; ++i) {
					u64 a0 = a[offset + i];
					u64 a1 = a[offset + i + p];
					u64 a2 = a[offset + i + 2*p];
					u64 a3 = a[offset + i + 3*p];
					if (!inv) {
						u64 m2 = MOD * (u64)MOD;
						u64 b0 = (__uint128_t)a1 * rot % MOD;
						u64 b1 = (__uint128_t)a2 * rot2 % MOD;
						u64 b2 = (__uint128_t)a3 * rot3 % MOD;
						u64 s02 = (a0 + b1) % MOD;
						u64 s13 = (b0 + b2) % MOD;
						u64 d02 = (a0 + MOD - b1) % MOD;
						u64 im = (__uint128_t)((a0 + ((m2 - (b0 + b2)%MOD) % MOD)) % MOD) * imag % MOD;
						a[offset + i] = (s02 + s13) % MOD;
						a[offset + i + p] = (s02 + MOD - s13) % MOD;
						a[offset + i + 2*p] = (d02 + im) % MOD;
						a[offset + i + 3*p] = (d02 + MOD - im) % MOD;
					} else {
						u64 im = (__uint128_t)((MOD + a2 - a3) % MOD) * imag % MOD;
						u64 s0123 = (a0 + a1 + a2 + a3) % MOD;
						u64 t1 = (__uint128_t)((a0 + MOD - a1 + im) % MOD) * rot % MOD;
						u64 t2 = (__uint128_t)((a0 + a1 + MOD - a2 + MOD - a3) % MOD) * rot2 % MOD;
						u64 t3 = (__uint128_t)((a0 + MOD - a1 + MOD - im) % MOD) * rot3 % MOD;
						a[offset + i] = s0123;
						a[offset + i + p] = t1;
						a[offset + i + 2*p] = t2;
						a[offset + i + 3*p] = t3;
					}
				}
				if (s + 1 != S) {
					rot = (__uint128_t)rot * (inv ? info.irate3[__builtin_ctz(~s)] : info.rate3[__builtin_ctz(~s)]) % MOD;
				}
			}
			len += inv ? -2 : 2;
		}
	}
}
template<u64 MOD>static std::vector<i64> conv(const std::vector<i64>& a_i, const std::vector<i64>& b_i) {
	i64 m = a_i.size(), n = b_i.size();
	i64 s = m + n -1;
	i64 sz = 1;while (sz < s) sz <<= 1;
	std::vector<u64> a(sz), b(sz);
	for (i64 i = 0; i < m; ++i) a[i] = (a_i[i] % MOD + MOD) % MOD;
	for (i64 i = 0; i < n; ++i) b[i] = (b_i[i] % MOD + MOD) % MOD;
	rottable<MOD> rot;
	rot.init();
	ntt<MOD>(rot,a,0);
	ntt<MOD>(rot,b,0);
	for (i64 i = 0; i < sz; ++i) a[i] = (__uint128_t)a[i] * b[i] % MOD;
	ntt<MOD>(rot,a,1);
	u64 invn = math::modinv(sz, MOD);
	std::vector<i64> c(s);
	for (i64 i = 0; i < s; ++i) c[i] = (i64)((__uint128_t)a[i] * invn % MOD);
	return c;
}
static std::vector<i16> mul(const std::vector<i16>& a_i, const std::vector<i16>& b_i) {
	std::vector<i64> a, b;
	a.reserve(a_i.size()); b.reserve(b_i.size());
	for (auto&&x : a_i) a.push_back(x);
	for (auto&&x : b_i) b.push_back(x);
	//greater ctz(mod-1)
	static constexpr u64 mod1 = 0xA000001, mod2 = 0x1C000001, mod3 = 0x2D000001;//smaller than 2^30
	i64 sz=a.size() + b.size();
	auto c1 = conv<mod1>(a, b);
	auto c2 = conv<mod2>(a, b);
	auto c3 = conv<mod3>(a, b);
	std::vector<i64> c(sz - 1);
	static constexpr u64 mod12 = mod1 * mod2, mod23 = mod2 * mod3, mod13 = mod1 * mod3, mod123 = mod1 * mod2 * mod3;
	static const u64 u1 = math::modinv(mod23, mod1), u2 = math::modinv(mod13, mod2), u3 = math::modinv(mod12, mod3);
	static constexpr u64 offset[5] = {0, 0, mod123, mod123*2, mod123*3};
	for (int i = 0; i < sz - 1; ++i) {
		u64 x = c1[i]*u1%mod1*mod23+c2[i]*u2%mod2*mod13+c3[i]*u3%mod3*mod12;
		i64 d=c1[i]-(x%mod1+mod1)%mod1;
		if(d < 0) d+=mod1;
		c[i] = x - offset[d % 5];
	}
	for (i64 i = 0; i < sz - 1; ++i)
		if (c[i] >= Base) {
			i64 up = c[i] / Base;
			c[i] -= up * Base;
			c[i+1] += up;
		}
	while (c.back() >= Base) {
		i64 up = c.back() / Base;
		c.back() -= up * Base;
		c.push_back(up);
	}
	while (c.size() > 1 && !c.back()) c.pop_back();
	std::vector<i16> d;
	d.reserve(c.size());
	for (auto&&x : c) d.push_back(x);
	return d;
}
friend std::ostream& operator<<(std::ostream& s, const Integer& a) {
	const std::vector<i16>& v = a.inList;
	for (i64 i = v.size()-1; i >= 0; i--) 
		if (i == (i64)v.size()-1) s << v[i];
		else if (v[i] >= 1000) s << v[i];
		else if (v[i] >= 100) s << 0 << v[i];
		else if (v[i] >= 10) s << "00" << v[i];
		else s << "000" << v[i];
	return s;
}
};
