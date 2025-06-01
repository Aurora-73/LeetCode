// Created: 2025-05-30
#include "MyUtils.h"

/*1047. 删除字符串中的所有相邻重复项
给出由小写字母组成的字符串 s，重复项删除操作会选择两个相邻且相同的字母，并删除它们。
在 s 上反复执行重复项删除操作，直到无法继续删除。
在完成所有重复项删除操作后返回最终的字符串。答案保证唯一。*/

class Solution1 {
public:
	string removeDuplicates(string s) {
		stack<char> st;
		for(int i = s.size() - 1; i >= 0; --i) {
			char first = s[i], second = st.empty() ? '\0' : st.top();
			while(!st.empty() && first == second) {
				st.pop();
				first = st.empty() ? '\0' : st.top();
				if(!st.empty()) {
					st.pop();
				}
				second = st.empty() ? '\0' : st.top();
			}
			if(first != '\0') {
				st.push(first);
			}
		}
		string res;
		while(!st.empty()) {
			res.push_back(st.top());
			st.pop();
		}
		return res;
	}
};

class Solution2 {
public:
	string removeDuplicates(const string &s) {
		int top = -1, n = s.size();
		string st;
		st.reserve(n / 2);
		for(int i = 0; i < n; ++i) {
			char first = s[i], second = top < 0 ? '\0' : st[top];
			while(top >= 0 && first == second) {
				top--;
				first = top < 0 ? '\0' : st[top];
				if(top >= 0) {
					top--;
				}
				second = top < 0 ? '\0' : st[top];
			}
			if(first != '\0') {
				++top;
				if(static_cast<int>(st.size()) < top + 1) {
					st.push_back(first);
				} else {
					st[top] = first;
				}
			}
		}
		return st.substr(0, top + 1);
	}
};

class Solution {
public:
	string removeDuplicates(string s) {
		string stk;
		for(char ch : s) {
			if(!stk.empty() && stk.back() == ch) {
				stk.pop_back();
			} else {
				stk.push_back(ch);
			}
		}
		return stk;
	}
}; // 栈内已经保证没有相邻的相同元素了

int main() {
	Solution sol;
	cout << sol.removeDuplicates("aaabaaaaa") << endl;
	cout << sol.removeDuplicates("abbaca") << endl;
	cout << sol.removeDuplicates("abdanfawiudawhacaodwadfessssddvvdvvdddsaafdwdaaddwaaabb") << endl;
}