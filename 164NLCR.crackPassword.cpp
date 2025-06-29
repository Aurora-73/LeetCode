// Created: 2025-06-29
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 164. 破解闯关密码
闯关游戏需要破解一组密码，闯关组给出的有关密码的线索是：
	一个拥有密码所有元素的非负整数数组 password
	密码是 password 中所有元素拼接后得到的最小的一个数
请编写一个程序返回这个密码。
示例 1：
	输入：password = {15, 8, 7}
	输出："1578"
示例2：
	输入：password = {0, 3, 30, 34, 5, 9}
	输出："03033459"
提示：
	0 < password.length <= 100
	说明: 
	输出结果可能非常大，所以你需要返回一个字符串而不是整数
	拼接起来的数字可能会有前导 0，最后结果不需要去掉前导 0 */

class Solution1 {
public:
	string crackPassword(vector<int> &password) {
		auto cmp = [](const string &a, const string &b) {
			int na = a.size(), nb = b.size();
			for(int i = 0; i < na + nb; ++i) {
				char ca = i < na ? a[i] : b[i - na];
				char cb = i < nb ? b[i] : a[i - nb];
				if(ca != cb) return ca > cb;
			}
			return false;
		}; // 注意普通的string比较算法不可行
		priority_queue<string, vector<string>, decltype(cmp)> pq(cmp);
		for(auto p : password) {
			pq.emplace(std::move(to_string(p))); // 使用移动构造函数
		}
		string res;
		while(!pq.empty()) {
			res += pq.top();
			pq.pop();
		}
		return res;
	}
};

class Solution {
public:
	string crackPassword(vector<int> &password) {
		int n = password.size();
		vector<string> passstring;
		passstring.reserve(n);
		for(auto p : password) {
			passstring.emplace_back(std::move(to_string(p)));
		}
		auto cmp = [](const string &a, const string &b) {
			int na = a.size(), nb = b.size();
			for(int i = 0; i < na + nb; ++i) {
				char ca = i < na ? a[i] : b[i - na];
				char cb = i < nb ? b[i] : a[i - nb];
				if(ca != cb) return ca < cb;
			}
			return false;
		}; // 注意普通的string比较算法不可行
		ranges::sort(passstring, cmp);
		string res;
		for(auto &ps : passstring) {
			res.append(ps);
		}
		return res;
	}
};

int main() {
	Solution sol;
	vector<int> password;
	password = { 15, 8, 7 };
	cout << sol.crackPassword(password) << endl; // "1578"
	password = { 0, 3, 30, 34, 5, 9 };
	cout << sol.crackPassword(password) << endl; // "03033459"
}