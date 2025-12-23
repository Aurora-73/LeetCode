// Created: 2025-12-23
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 字符串压缩。
利用字符重复出现的次数，编写一种方法，实现基本的字符串压缩功能。比如，字符串aabcccccaaa会变为a2b1c5a3。
若“压缩”后的字符串没有变短，则返回原先的字符串。你可以假设字符串中只包含大小写英文字母（a至z）。
示例 1：
	输入："aabcccccaaa"
	输出："a2b1c5a3"
示例 2：
	输入："abbccd"
	输出："abbccd"
	解释："abbccd"压缩后为"a1b2c2d1"，比原字符串长度更长。
提示：
	字符串长度在 {0, 50000} 范围内。 */

class Solution1 {
public:
	string compressString(string &str) {
		if(str.size() < 2) return str;
		unsigned i = 1, n = str.size(), cnt = 1;
		string res;
		res.reserve(n);
		res.push_back(str[0]);
		while(i < n) {
			if(str[i] == res.back()) {
				++cnt;
			} else {
				res += std::to_string(cnt);
				cnt = 1;
				res.push_back(str[i]);
			}
			if(res.size() >= n) {
				return str;
			}
			++i;
		}
		res += std::to_string(cnt);
		return (res.size() >= n) ? str : res; // 注意最后需要加上cnt，且可能长度不为1
	}
}; // 拼接cnt不能用'0' + cnt，应该用 to_string(cnt)

class Solution {
public:
	string compressString(string &s) {
		string res;
		unsigned n = s.size();
		res.reserve(n);
		for(unsigned i = 0; i < n;) {
			unsigned j = i + 1;
			while(j < n && s[j] == s[i]) ++j;
			res.push_back(s[i]);
			res += to_string(j - i);
			i = j;
			if(n <= res.size()) return s;
		}
		return (n <= res.size()) ? s : res;
	}
};

int main() {
	Solution sol;
	string S;
	S = "aabcccccaaa";
	cout << sol.compressString(S) << endl; // "a2b1c5a3"

	S = "abbccd";
	cout << sol.compressString(S) << endl; // "abbccd"

	S = "tttttttttttoooooooooooooooooooooooooooooooooooooooooooooooooooooooooobbbbbbbbbbbbxxxxxxxxx"
	    "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxdddddddddddddddddddddddddddddddMMMMMMMMMMMMMMMMMMMM"
	    "MMMMMMpppppppppppppppppCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCkkkkkk"
	    "kkkkkkkkkkkkkknnnnnnnnnnnncccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccyyy"
	    "yyyyyyyyyyyyyyyyyyyyyoooooooooooJJJQQQQQQQQQQQQQQQQQQQQQQQQQQQQQCCCCCCCCCCCCCvvvvvvvvvvvvv"
	    "vvvvvvvvvqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO"
	    "OIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIICCCCCCCCCCCCCCCCCCCCCCCCCCEE"
	    "EEEEEEEEEEEEEEEEEEEE";
	cout << sol.compressString(S)
	     << endl; // "t11o58b12x48d31M26p17C61k20n12c61y24o11J3Q29C13v22q47O35I61C26E22"
}