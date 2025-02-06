/*
    使い方
    {
        "これ用のコードを入力するとそれに対応する\
        Whitespaceのコードを出力する。
    }
    文法について
    {
	    "一つのコマンドは空白を含まないStringliteralである必要がある。
	    "コマンド間には";"もしくは空白が必要。
	    "引数を持つ場合は":"で区切り、整数(32bit)を入力する。
    }
*/
#include <vector>
#include <string>
#include <map>
#include <iostream>
using namespace std;

string S= " ", T= "\t", N= "\n";
string maketwo(int x){
	string res= (x<0 ? T: S);
	x= abs(x);
	if (x == 0)res+= S;
	while (x) {
		res= res + (x&1 ? T: S);
		x/= 2;
	}
	return res;
}

vector<string> split(const string &s, char div= ';') {
	vector<string> res;
	string item;
	for (char ch: s) {
		if (ch == div) {
			if (item.size())
				res.push_back(item);
			item.clear();
		}
		else {
			item+= ch;
		}
	}
	if (item.size())
		res.push_back(item);
	return res;
}
//dict
map<string, string> cmd;
void Set(){
	//StdIn/Out
	{
		cmd["geti"]= T+N+T+T;
		cmd["gets"]= T+N+T+S;
		cmd["puti"]= T+N+S+T;
		cmd["puts"]= T+N+S+S;
	}
	//Heap Acces
	{
		cmd["store"]= T+T+S;
		cmd["take"] = T+T+T;
	}
	//Arithmetic
	{
		cmd["add"]= T+S+S+S;
		cmd["sub"]= T+S+S+T;
		cmd["mul"]= T+S+S+N;
		cmd["div"]= T+S+T+S;
		cmd["mod"]= T+S+T+T;
	}
	//Stack Manipulation
	{
		cmd["push"]= S+S;
		cmd["copy"]= S+N+S;
		cmd["swap"]= S+N+T;
		cmd["pop"] = S+N+N;
	}
	//Flow Control
	{
		cmd["mark"] = N+S+S;
		cmd["call"] = N+S+T;
		cmd["jump"] = N+S+N;
		cmd["ujump"]= N+T+S;
		cmd["njump"]= N+T+T;
		cmd["end"]  = N+T+N;
		cmd["exit"] = N+N+N;
	}
}
string trans(string x) {
	if (x.find(":")!=string::npos) {
		vector<string> spldata = split(x, ':');
		string res = cmd[spldata[0]];
		int give = stoi(spldata[1]);
		string plus = maketwo(give);
		return res + plus + N;
	}
	else{
		return cmd[x];
	}
}

int main() {
//If DBG
//S= "s"; T= "t";
//N= "n\n";
//N= "l";
	Set();
	string s;
	while (cin>>s) {
		vector<string> data = split(s);
		for(const string &x: data)cout << trans(x);
	}
}