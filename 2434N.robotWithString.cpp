// Created: 2025-06-06
#include "MyUtils.h"

/*  2434. 使用机器人打印字典序最小的字符串
给你一个字符串 s 和一个机器人，机器人当前有一个空字符串 t 。执行以下操作之一，直到 s 和 t 都变成空字符串：
    操作1：删除字符串 s 的 第一个 字符，并将该字符给机器人。机器人把这个字符添加到 t 的尾部。
    操作2：删除字符串 t 的 最后一个 字符，并将该字符给机器人。机器人将该字符写到纸上。
请你返回纸上能写出的字典序最小的字符串。*/

class Solution {
public:
	string robotWithString(string &s) {
		n = s.size(), sleft = 0, pright = 0;
		dfs(s);
		return minStr;
	}

private:
	int n, sleft, pright;
	// 左闭右开 s[0, pright) 纸上的部分; s[pright, sleft) 空闲部分; s[sleft, n) s当前部分
	stack<char> t;
	string minStr;
	void dfs(string &s) {
		if(pright == n) {
			if(s < minStr || minStr.empty()) {
				minStr = s;
			}
			return;
		}

		// 操作1 使用条件是 s非空
		if(sleft < n) {
			char temp = s[sleft];
			++sleft;
			t.push(temp);
			dfs(s);
			t.pop();
			--sleft;
			s[sleft] = temp;
		}

		// 操作2 使用条件是 t非空
		if(!t.empty()) {
			char temp1 = t.top(), temp2 = s[pright];
			t.pop();
			s[pright] = temp1;
			++pright;
			dfs(s);
			--pright;
			s[pright] = temp2;
			t.push(temp1);
		}
	}
}; // 回朔解法会超时

class Solution {
public:
	string &robotWithString(string &s) {
		int n = s.size(), top = 0;
		vector<char> backMin(n); // 某个位置后面的子串中最小的元素
		backMin.back() = CHAR_MAX;
		for(int i = n - 2; i >= 0; --i) {
			backMin[i] = min(s[i + 1], backMin[i + 1]);
		}
		stack<char> st;
		for(int i = 0; i < n; ++i) {
			st.push(s[i]);
			while(!st.empty() && st.top() <= backMin[i]) {
				s[top] = st.top();
				++top;
				st.pop();
			}
		}
		return s; // 为了让结果直接在传入的 s 上改写并返回，避免再额外拷贝生成新的 string，才把返回类型写成 string&。这样比 return string 的写法少了一次拷贝。
	}
};
// 什么时候将栈中的元素放入结果？当后续的元素都比栈顶大的时候！

int main() {
	Solution sol;
}