// Created: 2025-12-28
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给你一个由数字和运算符组成的字符串expression，按不同优先级组合数字和运算符，计算并返回所有可能组合的结果。
你可以 按任意顺序 返回答案。
生成的测试用例满足其对应输出值符合 32 位整数范围，不同结果的数量不超过 10^4。
示例 1：
	输入：expression = "2-1-1"
	输出：{0,2}
	解释：
	((2-1)-1) = 0 
	(2-(1-1)) = 2
示例 2：
	输入：expression = "2*3-4*5"
	输出：{-34,-14,-10,-10,10}
	解释：
	(2*(3-(4*5))) = -34 
	((2*3)-(4*5)) = -14 
	((2*(3-4))*5) = -10 
	(2*((3-4)*5)) = -10 
	(((2*3)-4)*5) = 10
提示：
	1 <= expression.length <= 20
	expression 由数字和算符 "+"、"-" 和 "*" 组成。
	输入表达式中的所有整数值在范围 {0, 99}
	输入表达式中的所有整数都没有前导"-"或"+" 表示符号。 */

class Solution {
public:
	vector<int> diffWaysToCompute(string &expression) {
		res.clear();
		vector<int> expre;
		int n = expression.size(), curr = 0;
		for(int i = 0; i < n; ++i) {
			char ch = expression[i];
			if(ch == '+' || ch == '-' || ch == '*') {
				expre.push_back(curr);
				curr = 0;
				int op = numeric_limits<int>::max() - (ch == '+' ? 1 : (ch == '-' ? 2 : 3));
				expre.push_back(op);
			} else {
				curr *= 10;
				curr += ch - '0';
			}
		}
		expre.push_back(curr);
		dfs(expre);
		return std::move(res);
	} // 运算结果不会超过10000，因此，(numeric_limits<int>::max() - 1)表示+, (numeric_limits<int>::max() - 2)表示-，(numeric_limits<int>::max() - 3)表示*

private:
	vector<int> res;
	void dfs(const vector<int> &expre) {
		if(expre.size() == 1) {
			res.push_back(expre[0]);
		}
		int n = expre.size(), on = (n - 1) / 2;
		for(int i = 1; i <= on; ++i) {
			vector<int> nexte;
			nexte.reserve(n - 2);
			for(int j = 0; j < 2 * i - 2; ++j) {
				nexte.push_back(expre[j]);
			}
			int l = expre[2 * i - 2], op = expre[2 * i - 1], r = expre[2 * i], result;
			if(op == (numeric_limits<int>::max() - 1)) {
				result = l + r;
			} else if(op == (numeric_limits<int>::max() - 2)) {
				result = l - r;
			} else if(op == (numeric_limits<int>::max() - 3)) {
				result = l * r;
			} else {
				cout << "ERROR" << endl;
			}
			nexte.push_back(result);
			for(int j = 2 * i + 1; j < n; ++j) {
				nexte.push_back(expre[j]);
			}
			dfs(nexte);
		}
	}
};

int main() {
	Solution sol;
	string expression;
	expression = "2-1-1";
	cout << sol.diffWaysToCompute(expression) << endl;

	expression = "2*3-4*5";
	cout << sol.diffWaysToCompute(expression) << endl;
}