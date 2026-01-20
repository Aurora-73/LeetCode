#include "MyDateGen.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个只包括 "("，")"，"{"，"}"，"{"，"}"的字符串 s，判断字符串是否有效。
有效字符串需满足：
	左括号必须用相同类型的右括号闭合。
	左括号必须以正确的顺序闭合。
	每个右括号都有一个对应的相同类型的左括号。
示例 1：
	输入：s = "()"
	输出：true
示例 2：
	输入：s = "(){}{}"
	输出：true
示例 3：
	输入：s = "(}"
	输出：false
示例 4：
	输入：s = "({})"
	输出：true
示例 5：
	输入：s = "({)}"
	输出：false
提示：
	1 <= s.length <= 10^4
	s 仅由括号 "(){}{}" 组成 */

class Solution1 {
public:
	bool isValid(string s) {
		stack<char> sta;
		for(auto c : s) {
			if(c == '(' || c == '{' || c == '[') {
				sta.push(c);
			}
			if(c == ')') {
				if(sta.size() > 0 && sta.top() == '(')
					sta.pop();
				else
					return false;
			}
			if(c == '}') {
				if(sta.size() > 0 && sta.top() == '{')
					sta.pop();
				else
					return false;
			}
			if(c == ']') {
				if(sta.size() > 0 && sta.top() == '[')
					sta.pop();
				else
					return false;
			}
		}
		return sta.size() == 0;
	}
};

class Solution {
public:
	bool isValid(const string &s) {
		if(s.size() % 2 == 1) return false;
		const unordered_map<char, char> match = { { ')', '(' }, { ']', '[' }, { '}', '{' } };
		stack<char> st;

		for(char c : s) {
			if(c == '(' || c == '[' || c == '{') {
				st.push(c);
			} else { // 右括号
				if(st.empty() || st.top() != match.at(c)) return false;
				st.pop();
			}
		}
		return st.empty();
	}
};

int main() {
	string s;
	Solution sol;
	
	s = "({)}";
	cout << sol.isValid(s) << endl;

	s = "({})";
	cout << sol.isValid(s) << endl;

	s = "(}";
	cout << sol.isValid(s) << endl;

	s = "(){}{}";
	cout << sol.isValid(s) << endl;

	s = "()";
	cout << sol.isValid(s) << endl;

	s = "(([]){})";
	cout << sol.isValid(s) << endl;
}
