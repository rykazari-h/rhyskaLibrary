# WS_easywrite_doc
これらのツールはあくまでWhitespaceのコーディングの補助のためのものです。<br>
詳しいことは本家サイト（閉鎖中）のアーカイブ、もしくはWikiから。<br>
[The original](http://compsoc.dur.ac.uk/whitespace/tutorial.php)<br>[Archive](https://web.archive.org/web/20150618184706/http://compsoc.dur.ac.uk/whitespace/tutorial.php)<br>
[Wikipedia(en)](http://compsoc.dur.ac.uk/whitespace/tutorial.php](https://en.wikipedia.org/wiki/Whitespace_(programming_language)))<br>
仕様でわからないことがあっても、easy_debugのscriptやインタプリタを見たら大体わかります。<br>
## なんとなくで解けるAtCoderの問題
AtcoderにはWhitespaceが実装されています。
1. [ABC081A-Placing Marbles](https://atcoder.jp/contests/abc081/tasks/abc081_a) -入力と四則演算ができれば解けます。
2. [ABC214A-New Generation ABC](https://atcoder.jp/contests/abc214/tasks/abc214_a) -フロー制御が必要です。
3. [ABC204A-Rock-paper-scissors](https://atcoder.jp/contests/abc204/tasks/abc204_a) -入力が少し難しいです。
4. [ABC083B-Some Sums](https://atcoder.jp/contests/abc083/tasks/abc083_b) -関数を使えると楽です。
5. [ABC085C-Otoshidama](https://atcoder.jp/contests/abc085/tasks/abc085_c) -AtCoderのWSは速いので多重ループで解けます。
## Command Table
| Category | Command & Description |
|----------|----------------------|
| **StdIn/Out** | **geti**: Read a number and place it in the location given by the top of the stack (TNTT) |
| | **getc**: Read a character and place it in the location given by the top of the stack (TNTS) |
| | **puti**: Output the number at the top of the stack (TNST) |
| | **putc**: Output the character at the top of the stack (TNSS) |
| **Heap Access** | **stor**: Store in heap (TTS) |
| | **retr**: Retrieve from heap (TTT) |
| **Arithmetic** | **add**: Addition (TSSS) |
| | **sub**: Subtraction (TSST) |
| | **mul**: Multiplication (TSSN) |
| | **div**: Integer division (TSTS) |
| | **mod**: Modulo (TSTT) |
| **Stack Manipulation** | **push**(takes param): Push the number onto the stack (SS) |
| | **dup**: Duplicate the top item on the stack (SNS) |
| | **swap**: Swap the top two items on the stack (SNT) |
| | **pop**: Discard the top item on the stack (SNN) |
| **Flow Control** | **mark**(takes param): Mark a location in the program (NSS) |
| | **call**(takes param): Call a subroutine (NST) |
| | **jump**(takes param): Jump to a label (NSN) |
| | **ujump**(takes param): Jump to a label if the top of the stack is zero (NTS) |
| | **njump**(takes param): Jump to a label if the top of the stack is negative (NTT) |
| | **end**: End a subroutine and transfer control back to the caller (NTN) |
| | **exit**: End the program (NNN) |
| **Int Literal** | **Decimal-number**: ex)114514(STTSTTTTTTSTSTSSTSN),-810(TTTSSTSTSTSN)|
||**Binary-number**: ex)0b1101(STTSTN),0b-110101(TTTSTSTN)|
