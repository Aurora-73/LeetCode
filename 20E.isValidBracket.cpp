#include "MyUtils.hpp"
#include "MyDateGen.h"
// #ifdef MY_UTILS_H

/*
给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。

有效字符串需满足：

左括号必须用相同类型的右括号闭合。
左括号必须以正确的顺序闭合。
每个右括号都有一个对应的相同类型的左括号。
*/

class Solution {
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

int main() {
	string str;
}