# math_ext
## inv_gcd(a : Int64, m : Int64)
{mod m におけるaの逆元, gcd(a, m)}を返す  
詳細はコードを参照
## modinv(a : Int64, m : Int64)
mod mにおけるaの逆元を返す
## crt(r, m)
rとmの配列長Nは揃えること。  
i = 1-Nについて、mod miでriと合同な数を{x, mod}の形で返す  
存在しない時、{0, 0}を返す
## modpow(a, p, m)
a^p mod mを返す
## primitive_root(n)
nが素数であることを要求する
## discrete_log(g, b, m)
g^x = b mod mなるxを返す
