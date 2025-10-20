# FastIO
入力はfrに、出力はfwにまとめれられている  
```crystal
# 定義
fr = Fastread.new
fw = Fastwrite.new
at_exit	{ fw.flush }
```
## method
* `fr.new_byte` 一文字読んで、u8?を返す
* `fr.trim` 空白を除去する
* `fr.read_line` 改行までを読んで、stringを返す
* `fr.gets` 空白までを読んで、stringを返す
* `fr.geti/fr.geti64` 空白までを読んで、intを返す
* `fw.write_byte` u8を書き込む
* `fw.write` 文字列を書き込む
* `fw.write_int` 整数を書き込む
* `fw.write_float` 浮動小数点数を書き込む。精度は事前に指定する
* `fw.setprecision` write_floatの精度を指定する。正確には、小数点以下桁数を指定する
* `fw.flush` flushする
* `fw.putv x` xを書き込む(Int,Char,Float,String,Bool,Tuple,Array
	Arrayは、二次元以上のとき間に改行が、そうでないとき空白が挿入される  
	また、Boolは1/0が書き込まれる
* `fw.outl *x,sep:" ",endl:"\n"` xの各要素を書き込む
	例えば、`fw.outl 998,244,353,sep:" + "`としたとき、`998 + 244 + 353`と書き込まれる
