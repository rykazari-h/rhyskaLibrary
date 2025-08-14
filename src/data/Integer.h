#pragma once
#include <vector>
#include <utility>
#include <algorithm>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <math/math.h>
#include <montgomerymint.h>
#include<atcoder/all>
//there are some bugs in "lib/src/modint.h"
class Integer {
	using u64 = unsigned long long;
	using i64 = long long;
	using i16 = short;
#define i16 i64
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
			buf[i-a] = '\0';
			v[j] = (i16)(std::atoi(buf));
		}
		while (v.size() > 1 && !v.back()) v.pop_back();
		return *this;
	}
	Integer& operator=(const std::string s) {return *this = s.c_str();}
	template<class T> Integer& operator=(const T& s) {return *this = std::to_string(s);}
	bool operator==(const Integer& s) const {return inList == s.inList;}
	bool operator!=(const Integer& s) const {return !(*this==s);}
	operator bool()const{return !(inList.size()==1&&inList[0]==0);}
	bool operator<(const Integer&s)const{return compare_array(inList,s.inList)==-1;}
	Integer& operator+=(const Integer& a) {add(inList, a.inList); return *this;}
	Integer& operator-=(const Integer& a) {sub(inList, a.inList); return *this;}
	Integer& operator*=(const Integer&a) {
		//if(std::min(a.inList.size(), inList.size()) < 53) inList = mul_brute(inList, a.inList);
		//else inList = mul(inList, a.inList);
		inList=mul(inList,a.inList);
		return *this;
	}
	friend Integer operator*(Integer a, const Integer& b) {return a*=b;}
	void half() {
		inList[0] >>= 1;
		for (i64 i = 1, sz = inList.size(); i < sz; ++i) {
			inList[i-1] += (inList[i] & 1) * 5000;
			inList[i] >>= 1;
		}
		light_carry(inList);
	}
	void shfr() {
		inList.erase(inList.begin());
		if (inList.empty()) inList.push_back(0);
	}
	void shfl() {
		inList.push_back(0);
		std::rotate(inList.rbegin(), inList.rbegin() + 1, inList.rend());
	}
	std::vector<i16> inList;
	static constexpr i64 Base = 10000;
	static int compare_array(const std::vector<i16>&a,const std::vector<i16>&b){
		i64 A=a.size(),B=b.size();
		if(A>B)return 1;
		if(A<B)return -1;
		for(i64 i=A-1;i>=0;--i){
			if(a[i]>b[i])return 1;
			if(a[i]<b[i])return -1;
		}
		return 0;
	}
	//verified
	static void light_carry(std::vector<i16>& v) {
		for (i64 i = 0, sz = v.size(); i < sz - 1; ++i) if(v[i] >= Base) v[i] -= Base, ++v[i+1];
		if(v.back() >= Base) v.back() -= Base, v.push_back(1);
	}
	//verified
	static void heavy_carry(std::vector<i64>& v) {
		for (i64 i = 0, sz = v.size(); i < sz - 1; i++) if (v[i] >= Base) {
			i64 up = v[i] / Base;
			v[i] -= up * Base;
			v[i+1] += up;
		}
		while (v.back() >= Base) {
			i64 up = v.back() / Base;
			v.back() -= up * Base;
			v.push_back(up);
		}
	}
	//verified
	static std::vector<i16> mul_brute(const std::vector<i16>& a, const std::vector<i16>& b) {
		i64 as = a.size(), bs = b.size();
		if(as == 1 && a[0] == 0)return {0};
		if(bs == 1 && b[0] == 0)return {0};
		i64 n = as + bs - 1;
		std::vector<i64> c(n);
		for (i64 i = 0; i < as; i++)
			for ( i64 j = 0; j < bs; j++)
				c[i+j] += (i64)a[i] * b[j];
		heavy_carry(c);
		std::vector<i16> d;
		d.reserve(c.size());
		for (auto&&x : c) d.push_back(x);
		return d;
	}
	//verified
	static void add(std::vector<i16>& a, const std::vector<i16>& b) {
		for (i64 i = 0, sz = std::min(a.size(), b.size()); i < sz; i++) a[i] += b[i];
		if (a.size() < b.size()) {
			i64 i=a.size();
			a.resize(b.size());
			for (i64 sz = b.size(); i < sz; i++)a[i] = b[i];
		}
		light_carry(a);
	}
	//verified
	static void sub(std::vector<i16>& a, const std::vector<i16>& b) {
		i64 i = 0, lim = b.size();
		bool carry = 0;
		for (; i < lim; ++i) {
			a[i] -= b[i] + carry;
			carry = 0;
			if (a[i] < 0) {
				carry = 1;
				a[i] += Base;
			}
		}
		while (carry) {
			carry = 0;
			--a[i];
			if (a[i] < 0) carry = 1, a[i] += Base;
			++i;
		}
		while (a.size() >= 2 && !a.back())a.pop_back();
	}
	//	template <class mint,int g = math::primitive_root(mint::mod())>
	//		struct rottable {
	//			static constexpr int rank2 = __builtin_ctz(mint::mod() - 1);
	//			std::array<mint, rank2 + 1> root;   // root[i]^(2^i) == 1
	//			std::array<mint, rank2 + 1> iroot;  // root[i] * iroot[i] == 1
	//
	//			std::array<mint, std::max(0, rank2 - 2 + 1)> rate2;
	//			std::array<mint, std::max(0, rank2 - 2 + 1)> irate2;
	//
	//			std::array<mint, std::max(0, rank2 - 3 + 1)> rate3;
	//			std::array<mint, std::max(0, rank2 - 3 + 1)> irate3;
	//
	//			rottable() {
	//				root[rank2] = mint(g).pow((mint::mod() - 1) >> rank2);
	//				iroot[rank2] = root[rank2].inv();
	//				for (int i = rank2 - 1; i >= 0; i--) {
	//					root[i] = root[i + 1] * root[i + 1];
	//					iroot[i] = iroot[i + 1] * iroot[i + 1];
	//				}
	//
	//				{
	//					mint prod = 1, iprod = 1;
	//					for (int i = 0; i <= rank2 - 2; i++) {
	//						rate2[i] = root[i + 2] * prod;
	//						irate2[i] = iroot[i + 2] * iprod;
	//						prod *= iroot[i + 2];
	//						iprod *= root[i + 2];
	//					}
	//				}
	//				{
	//					mint prod = 1, iprod = 1;
	//					for (int i = 0; i <= rank2 - 3; i++) {
	//						rate3[i] = root[i + 3] * prod;
	//						irate3[i] = iroot[i + 3] * iprod;
	//						prod *= iroot[i + 3];
	//						iprod *= root[i + 3];
	//					}
	//				}
	//			}
	//		};
	//
	//	template <class mint>
	//		static void dft(std::vector<mint>& a) {
	//			int n = int(a.size());
	//			int h = __builtin_ctz((unsigned int)n);
	//
	//			static const rottable<mint> info;
	//
	//			int len = 0;  // a[i, i+(n>>len), i+2*(n>>len), ..] is transformed
	//			while (len < h) {
	//				if (h - len == 1) {
	//					int p = 1 << (h - len - 1);
	//					mint rot = 1;
	//					for (int s = 0; s < (1 << len); s++) {
	//						int offset = s << (h - len);
	//						for (int i = 0; i < p; i++) {
	//							auto l = a[i + offset];
	//							auto r = a[i + offset + p] * rot;
	//							a[i + offset] = l + r;
	//							a[i + offset + p] = l - r;
	//						}
	//						if (s + 1 != (1 << len))
	//							rot *= info.rate2[__builtin_ctz(~(unsigned int)(s))];
	//					}
	//					len++;
	//				} else {
	//					// 4-base
	//					int p = 1 << (h - len - 2);
	//					mint rot = 1, imag = info.root[2];
	//					for (int s = 0; s < (1 << len); s++) {
	//						mint rot2 = rot * rot;
	//						mint rot3 = rot2 * rot;
	//						int offset = s << (h - len);
	//						for (int i = 0; i < p; i++) {
	//							auto mod2 =  mint(mint::mod() * mint::mod());
	//							auto a0 = a[i + offset];
	//							auto a1 = a[i + offset + p]*rot;
	//							auto a2 = a[i + offset + 2 * p]* rot2;
	//							auto a3 = a[i + offset + 3 * p]* rot3;
	//							auto a1na3imag =
	//								mint(a1 + mod2 - a3)* imag;
	//							auto na2 = mod2 - a2;
	//							a[i + offset] = a0 + a2 + a1 + a3;
	//							a[i + offset + 1 * p] = a0 + a2 + ( mod2*2 - (a1 + a3));
	//							a[i + offset + 2 * p] = a0 + na2 + a1na3imag;
	//							a[i + offset + 3 * p] = a0 + na2 + (mod2 - a1na3imag);
	//						}
	//						if (s + 1 != (1 << len))
	//							rot *= info.rate3[__builtin_ctz(~(unsigned int)(s))];
	//					}
	//					len += 2;
	//				}
	//			}
	//		}
	//
	//	template <class mint>
	//		static void idft(std::vector<mint>& a) {
	//			int n = int(a.size());
	//			int h = __builtin_ctz((unsigned int)n);
	//
	//			static const rottable<mint> info;
	//
	//			int len = h;  // a[i, i+(n>>len), i+2*(n>>len), ..] is transformed
	//			while (len) {
	//				if (len == 1) {
	//					int p = 1 << (h - len);
	//					mint irot = 1;
	//					for (int s = 0; s < (1 << (len - 1)); s++) {
	//						int offset = s << (h - len + 1);
	//						for (int i = 0; i < p; i++) {
	//							auto l = a[i + offset];
	//							auto r = a[i + offset + p];
	//							a[i + offset] = l + r;
	//							a[i + offset + p] =
	//								(l-r) *
	//								irot;
	//						}
	//						if (s + 1 != (1 << (len - 1)))
	//							irot *= info.irate2[__builtin_ctz(~(unsigned int)(s))];
	//					}
	//					len--;
	//				} else {
	//					// 4-base
	//					int p = 1 << (h - len);
	//					mint irot = 1, iimag = info.iroot[2];
	//					for (int s = 0; s < (1 << (len - 2)); s++) {
	//						mint irot2 = irot * irot;
	//						mint irot3 = irot2 * irot;
	//						int offset = s << (h - len + 2);
	//						for (int i = 0; i < p; i++) {
	//							auto a0 = a[i + offset + 0 * p];
	//							auto a1 = a[i + offset + 1 * p];
	//							auto a2 = a[i + offset + 2 * p];
	//							auto a3 = a[i + offset + 3 * p];
	//
	//							auto a2na3iimag =
	//								mint((mint::mod() + a2 - a3) * iimag);
	//
	//							a[i + offset] = a0 + a1 + a2 + a3;
	//							a[i + offset + 1 * p] =
	//								(a0 + (mint::mod() - a1) + a2na3iimag) * irot;
	//							a[i + offset + 2 * p] =
	//								(a0 + a1 + (mint::mod() - a2) + (mint::mod() - a3)) *
	//								irot2;
	//							a[i + offset + 3 * p] =
	//								(a0 + (mint::mod() - a1) + (mint::mod() - a2na3iimag)) *
	//								irot3;
	//						}
	//						if (s + 1 != (1 << (len - 2)))
	//							irot *= info.irate3[__builtin_ctz(~(unsigned int)(s))];
	//					}
	//					len -= 2;
	//				}
	//			}
	//		}
	//	template<u64 MOD> static std::vector<i64> conv(const std::vector<i16>&a, const std::vector<i16>&b) {
	//		using mint = montgomerymint<MOD>;
	//		i64 m = a.size(), n = b.size();
	//		i64 s = m + n -1;
	//		i64 sz = 1;while (sz < s) sz <<= 1;
	//		assert((mint::mod() - 1) % sz == 0);
	//
	//		std::vector<mint> a2(sz),b2(sz);
	//		for (i64 i = 0; i < m; i++) a2[i] = mint(a[i]);
	//		for (i64 i = 0; i < n; i++) b2[i] = mint(b[i]);
	//		dft<mint>(a2);
	//		dft<mint>(b2);
	//		for (i64 i = 0; i < sz; ++i) a2[i] *= b2[i];
	//		idft<mint>(a2);
	//		mint invn = mint(sz).inv();
	//		for (i64 i = 0; i < s; ++i) a2[i] *= invn;
	//		std::vector<i64>c(s);
	//		for (i64 i = 0; i < s; i++) c[i] = a2[i].val();
	//		return c;
	//	}
	template<class mint>struct rottable{ 
		static constexpr int M=mint::mod()-1;M2=__builtin_ctz(M),pr=math::primitive_root(mint::mod());
		std::array<mint,M2+1> w,y;
		rottable(){
			mint z=mint(pr).pow((mint::mod()-1)/M),x=z.inv();
			int j=M2;
			for(;j>>=1;z*=z,x*=x)w[j]=z,y[j]=x;
			y[0]=w[0]=1;
			j=M2;
			for(int js=2;js<j;js<<=1){
				z=w[js],x=y[js];
				for(int k=js+1,k2=1;k2<js;++k,++k2)w[k]=w[k2]*z,y[k]=y[k2]*x;
			}
		}
	};
	template<class mint>static void fft(std::vector<mint> &a, int k) {
		static const rottable<mint> rou;
		if (k & 1){
			int v = 1 << (k - 1);
			for (int j = 0; j < v; ++j) {
				mint ajv = a[j + v];
				a[j + v] = a[j] - ajv;
				a[j] += ajv;
			}
		}
		int u = 1 << (k & 1);
		int v = 1 << (k - 2 - (k & 1));
		while (v) {
			// jh = 0
			{
				int j0 = 0;
				int j1 = v;
				int j2 = j1 + v;
				int j3 = j2 + v;
				int je = v;
				for ( ; j0 < je; ++j0, ++j1, ++j2, ++j3){
					mint t0 = a[j0], t1 = a[j1], t2 = a[j2], t3 = a[j3];
					mint t0p2 = t0 + t2, t1p3 = t1 + t3;
					mint t0m2 = t0 - t2, t1m3 = (t1 - t3) * rou.w[1];
					a[j0] = t0p2 + t1p3 , a[j1] = t0p2 - t1p3;
					a[j2] = t0m2 + t1m3 , a[j3] = t0m2 - t1m3; 
				}
			}
			// jh >= 1
			for (int jh = 1; jh < u; ++jh) {
				int j0 = jh * v * 4;
				int j1 = j0 + v;
				int j2 = j1 + v;
				int j3 = j2 + v;
				int je = j1;
				mint ww = rou.w[jh];
				mint xx = rou.w[jh << 1];
				mint wx = ww * xx;
				for ( ; j0 < je; ++j0, ++j1, ++j2, ++j3){
					mint t0 = a[j0], t1 = a[j1] * xx , t2 = a[j2] * ww, t3 = a[j3] * wx;
					mint t0p2 = t0 + t2, t1p3 = t1 + t3;
					mint t0m2 = t0 - t2, t1m3 = (t1 - t3) * rou.w[1];
					a[j0] = t0p2 + t1p3 , a[j1] = t0p2 - t1p3;
					a[j2] = t0m2 + t1m3 , a[j3] = t0m2 - t1m3; 
				}
			}
			/*
				 cerr << "debug " << u << " " << v << endl;
				 for(int i = 0 ; i < (int)a.size(); i++)
				 cerr << a[i].get() << " ";
				 cerr << endl;
				 */

			u <<= 2;
			v >>= 2;
		}
	}

	template<class mint>static void ifft(std::vector<mint> &a, int k) {
		static const rottable<mint> rou;
		int u = 1 << (k - 1);
		int v = 1;
		while (u) {
			for (int j = 0; j < v; ++j) {
				mint ajv = a[j] - a[j + v];
				a[j] += a[j + v];
				a[j + v] = ajv;
			}
			for (int jh = 1; jh < u; ++jh) {
				mint wj = rou.y[jh];
				int je = jh * v * 2 + v;
				for (int j = jh * v * 2; j < je; ++j) {
					mint ajv = a[j] - a[j + v];
					a[j] += a[j + v];
					a[j + v] = wj * ajv;
				}
			}
			u >>= 1;
			v <<= 1;
		}
	}

	template<u64 MOD>static std::vector<i64> conv(const std::vector<i16>&a,const std::vector<i16>&b){
		using mint=montgomerymint<MOD>;
		int n=a.size(),m=b.size();
		int l = n+m - 1;
		int k = 2, M = 4;
		while (M < l) M <<= 1, ++k;
		std::vector<mint>s(M),t(M);
		for(int i=0;i<n;i++)s[i]=a[i];
		for(int i=0;i<m;i++)t[i]=b[i];
		fft(s, k);
		fft(t, k);
		for (int i = 0; i < M; ++i) s[i] *= t[i];
		ifft(s, k);
		s.resize(l);
		mint iz = mint(M).inv();
		std::vector<i64> c(l);
		for(int i=0;i<l;i++)c[i]=(s[i]*iz).val();
		return c;
	}

	//probably... this func is correct.
	//conv or dft or rottable are wrong.
	static std::vector<i16> mul(const std::vector<i16>& a, const std::vector<i16>& b) {
		//greater ctz(mod-1)
		static constexpr u64 mod1 = 0x2D000001, mod2 = 0xA000001, mod3 = 0x1C000001;//smaller than 2^30
		i64 sz=a.size() + b.size();
		auto c1 = conv<mod1>(a, b);
		auto c2 = conv<mod2>(a, b);
		auto c3 = conv<mod3>(a, b);
		std::vector<i64> c(sz - 1);
		static constexpr u64 mod12 = mod1 * mod2, mod23 = mod2 * mod3, mod13 = mod1 * mod3, mod123 = mod1 * mod2 * mod3;
		static constexpr  u64 u1 = 190329765, u2 = 58587104, u3 = 187290749;//inv
		static constexpr u64 offset[5] = {0, 0, mod123, mod123*2, mod123*3};
		for (int i = 0; i < sz - 1; ++i) {
			u64 x = c1[i]*u1%mod1*mod23+c2[i]*u2%mod2*mod13+c3[i]*u3%mod3*mod12;
			i64 d=c1[i]-((i64)x%mod1+mod1)%mod1;
			if(d < 0) d+=mod1;
			x -= offset[d % 5];
			c[i] = x;
		}
		heavy_carry(c);
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
inline Integer operator"" _i(const char*s,std::size_t){return Integer(s);}
inline Integer operator"" _i(unsigned long long x){return Integer(x);}
