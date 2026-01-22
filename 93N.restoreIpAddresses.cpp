// Created: 2026-01-22
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 有效 IP 地址 正好由四个整数（每个整数位于 0 到 255 之间组成，且不能含有前导 0），整数之间用 "." 分隔。
	例如："0.1.2.201" 和 "192.168.1.1" 是 有效 IP 地址，
但是 "0.011.255.245"、"192.168.1.312" 和 "192.168@1.1" 是 无效 IP 地址。
给定一个只包含数字的字符串 s，用以表示一个 IP 地址，返回所有可能的有效 IP 地址，
这些地址可以通过在 s 中插入"." 来形成。你 不能重新排序或删除 s 中的任何数字。你可以按 任何 顺序返回答案。
示例 1：
	输入：s = "25525511135"
	输出：{"255.255.11.135","255.255.111.35"}
示例 2：
	输入：s = "0000"
	输出：{"0.0.0.0"}
示例 3：
	输入：s = "101023"
	输出：{"1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"}
提示：
	1 <= s.length <= 20
	s 仅由数字组成 */

class Solution {
public:
	vector<string> restoreIpAddresses(const string &s) {
		n = s.size();
		traceBack(0, 0, s);
		return std::move(res);
	}

private:
	int n;
	vector<string> res;
	array<int, 4> dotPos {}; // 记录每段的结束位置
	void traceBack(int i, int j, const string &s) {
		if(i == n || j == 4) {
			if(i == n && j == 4) {
				addToRes(s);
			}
			return;
		}
		int curr = 0;
		for(; i < n; ++i) {
			curr = curr * 10 + s[i] - '0';
			if(curr > 255) return;
			dotPos[j] = i;
			traceBack(i + 1, j + 1, s);
			if(curr == 0) return; // 不能有前导0，已经加了一位还是0，说明首位为0
		}
	}
	void addToRes(const string &s) {
		string &curr = res.emplace_back();
		curr.reserve(n + 3);
		int j = 0;
		for(int i = 0; i < n; ++i) {
			curr.push_back(s[i]);
			if(j < 3 && i == dotPos[j]) {
				curr.push_back('.');
				++j;
			}
		}
	}
};

int main() {
	Solution sol;
	string s;
	s = "25525511135";
	cout << sol.restoreIpAddresses(s) << endl;

	s = "0000";
	cout << sol.restoreIpAddresses(s) << endl;

	s = "101023";
	cout << sol.restoreIpAddresses(s) << endl;
}