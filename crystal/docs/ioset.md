# IOset
高速な入出力クラス。インスタンスを作成すること。  
入力はIO.getsなどcrystalの標準入力と混用しないこと。[参考提出](https://judge.yosupo.jp/submission/383345)
## usage
```crystal
ios = IOset.new # 必ずインスタンスを生成する。
ios1 = IOset.new
ios1.set_io input: File.open("./input.txt", "r"), output: IO::Memory.new # in/out先は変えられる。インスタンスにするのはこのため。
# 最適化が必要な場合はすべてクラス関数にし、入力はmmapで行うこと。また、llvmのsimd命令を使うのもよい
# ---input---
ios.fill # バッファに読み込む
ios.eof? # eofかどうか判定
ios.read_byte : UInt8? # 一文字読み込む。eofならnil
ios.getc : Char # 空白を飛ばし一文字読み込む。eofなら例外を投げる
ios.gets : String # 空白ごとに文字列を読み込む。eofなら例外を投げる
ios.read_line : String # \nごとに文字列を読み込む。eofなら例外を投げる
ios.geti : Int # 整数を読み込む。bigintはios.getbi, その他メソッドはgeti{{bit}}の形にすること
# ---output---
ios.write_byte(b : UInt8) # 一文字出力
ios.write(s : String) # 文字列を出力
ios.write_int(x : Int) # 整数を出力
ios.setprecision(x : Int) # write_floatの小数点以下桁数を指定します。x <= 16
ios.write_float(x : Float) # 浮動小数点数を出力
ios.flush # flushする
ios.putv(x : Int | Float | Bool | Char | String | Indexable) # 単一要素の出力。多次元Arrayは改行区切りで出力, Boolは1/0で出力される
ios.print(*x) # xの各要素を順位出力
ios.outl(*x, sep : String | Char =  ' ', endl : String | Char = '\n') # printに同じ。sepを要素間に挿入し、endlを最後に出力する。
```
