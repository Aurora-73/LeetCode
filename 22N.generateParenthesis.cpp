// Created: 2025-05-12
#include "MyUtils.hpp"

/*22. 括号生成
数字 n代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。
示例 1：
	输入：n = 3
	输出：{"((()))","(()())","(())()","()(())","()()()"}
示例 2：
	输入：n = 1
	输出：{"()"}
提示：
	1 <= n <= 8 */

class Solution1 {
public:
	vector<string> generateParenthesis(int n) {
		size = 2 * n;
		temp.resize(size);
		res.reserve(cnt[n]);
		dfs();
		return std::move(res); // 成员变量无法进行NRVO
	}

private:
	vector<string> res;
	string temp;
	int top = 0, left = 0, size;
	inline static constexpr array<int, 9> cnt { 0, 1, 3, 8, 22, 64, 196, 625, 2055 };
	void dfs() {
		if(top == size) {
			res.push_back(temp);
			return;
		}
		if(left * 2 < size) {
			temp[top++] = '(';
			++left;
			dfs();
			--top;
			--left;
		}
		if(top < left * 2) {
			temp[top++] = ')';
			dfs();
			--top;
		}
	}
};

class Solution {
public:
	vector<string> generateParenthesis(int n) {
		vector<string> res;
		res.reserve(cnt[n]);
		string temp(2 * n, ' ');
		dfs(res, temp, 0, 0, n);
		return res; // NRVO
	}

private:
	inline static constexpr array<int, 9> cnt { 0, 1, 3, 8, 22, 64, 196, 625, 2055 };
	void dfs(vector<string> &res, string &temp, int top, int left, int n) {
		if(top == 2 * n) {
			res.emplace_back(temp); // 不需要检查
			return;
		}

		if(left < n) { // 不会多左括号
			temp[top] = '(';
			dfs(res, temp, top + 1, left + 1, n);
		}

		int right = top - left;
		if(right < left) { // 不会多右括号
			temp[top] = ')';
			dfs(res, temp, top + 1, left, n);
		}
	}
}; // 因为回朔时已经保证 不会多添加左括号，也不会多添加有括号，所以结束时不需要检查可以直接放入结果

int main() {
	Solution sol;
	for(int i = 1; i < 5; ++i) {
		cout << sol.generateParenthesis(i) << endl;
	}
}