# IOset
速度としては、scnaf,printfと同じほど  
outlはつよつよな函数になっている
## method
* `self.read_byte` 一文字読んで、u8?を返す
* `self.trim` 空白を除去する
* `self.read_line` 改行までを読んで、stringを返す
* `self.gets` 空白までを読んで、stringを返す
* `self.geti/self.geti64` 空白までを読んで、intを返す
* `self.write_byte` u8を書き込む
* `self.write` 文字列を書き込む
* `self.write_int` 整数を書き込む
* `self.write_float` 浮動小数点数を書き込む。精度は事前に指定する
* `self.setprecision` write_floatの精度を指定する。正確には、小数点以下桁数を指定する
* `self.flush` flushする
* `self.putv x` xを書き込む(Int,Char,Float,String,Bool,Tuple,Array  
	Arrayは、二次元以上のとき間に改行が、そうでないとき空白が挿入される  
	また、Boolは1/0が書き込まれる
* `ios.outl *x,sep:" ",endl:"\n"` xの各要素を書き込む
	例えば、`ios.outl 998,244,353,sep:" + "`としたとき、`998 + 244 + 353`と書き込まれる
