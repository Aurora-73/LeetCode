// Created: 2025-12-16
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个只包含数字的字符串 s，用以表示一个 IP 地址，返回所有可能从s 获得的 有效 IP 地址。
你可以按任何顺序返回答案。
有效 IP 地址 正好由四个整数（每个整数位于 0 到 255 之间组成，且不能含有前导 0），整数之间用 "." 分隔。
例如："0.1.2.201" 和 "192.168.1.1" 是 有效 IP 地址，
但是 "0.011.255.245"、"192.168.1.312" 和 "192.168@1.1" 是 无效 IP 地址。
示例 1：
	输入：s = "25525511135" 
	输出：{"255.255.11.135","255.255.111.35"}
示例 2：
	输入：s = "0000"
	输出：{"0.0.0.0"}
示例 3：
	输入：s = "1111"
	输出：{"1.1.1.1"}
示例 4：
	输入：s = "010010"
	输出：{"0.10.0.10","0.100.1.0"}
示例 5：
	输入：s = "10203040"
	输出：{"10.20.30.40","102.0.30.40","10.203.0.40"}
提示：Z
	0 <= s.length <= 3000
	s 仅由数字组成 */

class Solution1 {
public:
	vector<string> restoreIpAddresses(string &s) {
		begins[0] = 0;
		if(s.size() < 4 || s.size() > 12) return {};
		n = s.size();
		dfs(s, 1, 1);
		return std::move(res);
	}

private:
	int n;
	array<int, 4> begins;
	vector<string> res;
	void dfs(string &s, int cnt, int i) {   // cnt: 已经确定起始位置的数字的个数
		if(i - begins[cnt - 1] > 3) return; // 剪枝，当前段长度大于3
		if(i == n || cnt == 4) {
			if(cnt == 4 && check({ s.begin() + begins.back(), s.end() })) {
				addToRes(s);
			}
			return;
		}
		if(check({ s.begin() + begins[cnt - 1], s.begin() + i })) {
			int remain = n - i, need = 4 - cnt;
			if(remain >= need && remain <= need * 3) { // 剪枝，后续的不够分了
				begins[cnt] = i;
				dfs(s, cnt + 1, i + 1);
			}
		}
		dfs(s, cnt, i + 1);
	}
	bool check(string_view sv) {
		if(sv.size() > 3 || sv.size() < 1) return false;
		if(sv[0] == '0' && sv.size() != 1) return false;
		int val = 0;
		for(auto c : sv) {
			val *= 10;
			val += c - '0';
		}
		return val <= 255;
	}
	void addToRes(string &s) {
		res.push_back("");
		res.back().reserve(n + 3);
		int a = 0, b = 1;
		while(a < n) {
			if(b < 4 && a == begins[b]) {
				res.back().push_back('.');
				++b;
			} else {
				res.back().push_back(s[a]);
				++a;
			}
		}
	}
}; // 每次调用不一定确定一个位置

class Solution {
public:
	vector<string> restoreIpAddresses(string &s) {
		n = s.size();
		if(n < 4 || n > 12) return {};
		this->s = std::move(s);
		dfs(0, 0);
		return std::move(res);
	}

private:
	int n;
	string s;
	vector<string> res;
	array<string, 4> path;

	void dfs(int pos, int seg) {
		if(seg == 4) {
			if(pos == n) {
				res.push_back(path[0] + "." + path[1] + "." + path[2] + "." + path[3]);
			}
			return;
		}
		int remain = n - pos;
		int need = 4 - seg;
		if(remain < need || remain > need * 3) return;
		int val = 0;
		for(int len = 1; len <= 3 && pos + len <= n; ++len) {
			if(len > 1 && s[pos] == '0') break;
			val = val * 10 + (s[pos + len - 1] - '0');
			if(val > 255) break;
			path[seg] = s.substr(pos, len);
			dfs(pos + len, seg + 1);
		}
	} // 每次调用确定一个位置
};

int main() {
	Solution sol;
	string s;
	s = "25525511135";
	cout << sol.restoreIpAddresses(s) << endl;
	s = "0000";
	cout << sol.restoreIpAddresses(s) << endl;
	s = "1111";
	cout << sol.restoreIpAddresses(s) << endl;
	s = "010010";
	cout << sol.restoreIpAddresses(s) << endl;
	s = "10203040";
	cout << sol.restoreIpAddresses(s) << endl;
}