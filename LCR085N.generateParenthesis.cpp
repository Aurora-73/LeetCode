// Created: 2025-12-16
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 正整数n代表生成括号的对数，请设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。
示例 1：
	输入：n = 3
	输出：{"((()))","(()())","(())()","()(())","()()()"}
示例 2：
	输入：n = 1
	输出：{"()"}
提示：
	1 <= n <= 8 */

class Solution {
public:
	vector<string> generateParenthesis(int n) {
		int size = 2 * n; // 注意是n对儿，不是n个
		vector<string> res;
		curr.resize(size);
		dfs(res, 0, 0, size);
		return res;
	}

private:
	string curr;
	void dfs(vector<string> &res, int i, int lSubr, int size) {
		if(i == size) {
			if(lSubr == 0) res.push_back(curr);
			return;
		}
		if(lSubr > size - i) return; // lSubr一定大于等于0
		curr[i] = '(';
		dfs(res, i + 1, lSubr + 1, size);
		if(lSubr > 0) {
			curr[i] = ')';
			dfs(res, i + 1, lSubr - 1, size);
		}
	}
};

int main() {
	Solution sol;
	int n;
	n = 3;
	cout << sol.generateParenthesis(n) << endl;
}