// Created: 2025-06-14
#include "MyDateGen.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个经过编码的字符串，返回它解码后的字符串。
编码规则为: k[encoded_string]，
表示其中方括号内部的 encoded_string 正好重复 k 次。注意 k 保证为正整数。
你可以认为输入字符串总是有效的；输入字符串中没有额外的空格，且输入的方括号总是符合格式要求的。
此外，你可以认为原始数据不包含数字，所有的数字只表示重复的次数 k，例如不会出现像3a或2[4]的输入。
测试用例保证输出的长度不会超过10^5。
示例 1：
	输入：s = "3[a]2[bc]"
	输出："aaabcbc"
示例 2：
	输入：s = "3[a2[c]]"
	输出："accaccacc"
示例 3：
	输入：s = "2[abc]3[cd]ef"
	输出："abcabccdcdcdef"
示例 4：
	输入：s = "abc3[cd]xyz"
	输出："abccdcdcdxyz"
提示：
	1 <= s.length <= 30
	s由小写英文字母、数字和方括号"[]" 组成
	s保证是一个有效的输入。
	s中所有整数的取值范围为[1, 300] */

class Solution1 {
public:
	string decodeString(string &s) {
		string res;
		stack<string> st;
		stack<int> times;
		int n = s.size(), i = 0;
		while(i < n) {
			if(isdigit(s[i])) {
				size_t len;
				times.push(stoi(s.substr(i), &len, 10));
				i += len;
			} else if(s[i] == '[') {
				st.push("");
				++i;
			} else if(s[i] == ']') {
				string tmp = std::move(st.top());
				st.pop();
				int repeat = times.top();
				times.pop();
				string expanded;
				for(int k = 0; k < repeat; ++k) expanded += tmp;
				if(!st.empty()) {
					st.top() += expanded;
				} else {
					res += expanded;
				}
				++i;
			} else {
				if(times.empty()) {
					res.push_back(s[i]);
				} else {
					st.top().push_back(s[i]);
				}
				++i;
			}
		}
		return res;
	}
}; // 类似于括号匹配算法，用栈解决

class Solution {
public:
	string decodeString(string &s) {
		string res;
		stack<pair<int, string>> st;
		int n = s.size(), i = 0;
		while(i < n) {
			if(isdigit(s[i])) {
				int cnt = 0;
				while(s[i] != '[') {
					cnt = cnt * 10 + s[i++] - '0';
				}
				st.emplace(cnt, "");
			} else if(s[i] == ']') {
				auto [cnt, curr] = std::move(st.top());
				st.pop();
				if(st.empty()) {
					while(cnt--) {
						res += curr;
					}
				} else {
					while(cnt--) {
						st.top().second += curr;
					}
				}
			} else if(s[i] != '[') {
				if(st.empty()) {
					res.push_back(s[i]);
				} else {
					st.top().second.push_back(s[i]);
				}
			}
			++i;
		}
		return res;
	}
};

int main() {
	Solution sol;
	string s;
	s = "3[a]2[bc]";
	cout << sol.decodeString(s) << endl; // "aaabcbc"

	s = "3[a2[c]]";
	cout << sol.decodeString(s) << endl; // "accaccacc"

	s = "2[abc]3[cd]ef";
	cout << sol.decodeString(s) << endl; // "abcabccdcdcdef"

	s = "abc3[cd]xyz";
	cout << sol.decodeString(s) << endl; // "abccdcdcdxyz"
}