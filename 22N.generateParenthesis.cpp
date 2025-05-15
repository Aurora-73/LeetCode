// Created: 2025-05-12
#include "MyUtils.h"

/*22. 括号生成
数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。*/

class Solution1 {
public:
	vector<string> generateParenthesis(int n) {
		size = 2 * n;
		temp.resize(size);
		int *aa = new int[9]{0, 1, 3, 8, 22, 64, 196, 625, 2055};
		res.reserve(aa[n]);
		delete[] aa;
		dfs();
		return std::move(res);
	}

private:
	vector<string> res;
	string temp;
	int top = 0, left = 0, size;
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

class Solution2 {
public:
	vector<string> generateParenthesis(int n) {
		vector<string> res;
		int *aa = new int[9]{0, 1, 3, 8, 22, 64, 196, 625, 2055};
		res.reserve(aa[n]);
		delete[] aa;
		string temp(2 * n, ' ');
		dfs(res, temp, 0, 0, n);
		return std::move(res);
	}

private:
	// top: 当前写入位置
	// left: 当前左括号数量
	// n: 原始括号对数
	void dfs(vector<string> &res, string &temp, int top, int left, int n) {
		if(top == 2 * n) {
			res.push_back(temp);
			return;
		}

		if(left < n) {
			temp[top] = '(';
			dfs(res, temp, top + 1, left + 1, n);
		}

		int right = top - left;
		if(right < left) {
			temp[top] = ')';
			dfs(res, temp, top + 1, left, n);
		}
	}
};

int main() {
	Solution1 sol1;
	for(int i = 1; i < 4; ++i) {
		cout << sol1.generateParenthesis(i) << endl;
	}
}