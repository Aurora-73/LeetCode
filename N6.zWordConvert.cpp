#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

/*
将一个给定字符串 s 根据给定的行数 numRows ，以从上往下、从左到右进行 Z 字形排列。
比如输入字符串为 "PAYPALISHIRING" 行数为 3 时，排列如下：
P   A   H   N
A P L S I I G
Y   I   R
之后，你的输出需要从左往右逐行读取，产生出一个新的字符串，比如："PAHNAPLSIIGYIR"。
请你实现这个将字符串进行指定行数变换的函数：
string convert(string s, int numRows);
*/

class Solution {
public:
	string convert(string s, int n) {
		if(n == 1)
			return s;
		string r;
		r.resize(s.length(), '@');
		int now = 0;
		for(int i = 0; i < n; i++) {
			// 除了首尾两列，均有两个，一个竖着，一个斜着
			// 竖着的之间的间隔为 2 * (n - 1)
			// 斜着的距离左侧的竖着的间隔为 2 * (n - 1 - i)
			// 斜着的距离右侧的竖着的间隔为 2 * i
			int j = i;
			if(i != 0 && i != n - 1) {
				while(1) {
					if(j >= s.length())
						break;
					r[now++] = s[j];
					j += 2 * (n - 1 - i);
					if(j >= s.length())
						break;
					r[now++] = s[j];
					j += 2 * i;
				}
			} else {
				while(1) {
					if(j >= s.length())
						break;
					r[now++] = s[j];
					j += 2 * (n - 1);
				}
			}
		}
		return r;
	}
};

int main() {
	Solution sol;
	cout << sol.convert("PAYPALISHIRING", 4) << "|";
}