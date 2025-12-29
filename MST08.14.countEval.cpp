// Created: 2025-12-28
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个布尔表达式和一个期望的布尔结果 result，
布尔表达式由 0 (false)、1 (true)、& (AND)、 | (OR) 和 ^ (XOR) 符号组成。
实现一个函数，算出有几种可使该表达式得出 result 值的括号方法。
示例 1：
	输入：s = "1^0|0|1", result = 0
	输出：2
	解释：两种可能的括号方法是
	1^(0|(0|1))
	1^((0|0)|1)
示例 2：
	输入：s = "0&0&0&1^1|0", result = 1
	输出：10
提示：
	运算符的数量不超过 19 个 */

class Solution {
public:
	int countEval(string &s, int target) {
		return dfs(s, target + '0');
	}

private:
	int dfs(const string &s, char target) {
		if(s.size() == 1) return s[0] == target;
		int n = s.size(), on = (n - 1) / 2, res = 0;
		for(int i = 1; i <= on; ++i) {
			char l = s[2 * i - 2], op = s[2 * i - 1], r = s[2 * i], result;
			if(op == '&') {
				result = (l == r && l == '1') + '0';
			} else if(op == '|') {
				result = (l == '1' || r == '1') + '0';
			} else if(op == '^') {
				result = (l != r) + '0';
			} else {
				cout << "ERROR" << endl;
			}
			string nexts = s.substr(0, 2 * i - 2) + result + s.substr(2 * i + 1);
			res += dfs(nexts, target);
		}
		return res;
	}
};

int main() {
	Solution sol;
	string s;
	int result;

	s = "1^0|0|1", result = 0;
	cout << sol.countEval(s, result) << endl; // 2

	s = "0&0&0&1^1|0", result = 1;
	cout << sol.countEval(s, result) << endl; // 10
}