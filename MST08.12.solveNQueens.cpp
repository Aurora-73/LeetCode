// Created: 2025-12-29
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 设计一种算法，打印 N 皇后在 N × N 棋盘上的各种摆法，其中每个皇后都不同行、不同列，也不在对角线上。
这里的“对角线”指的是所有的对角线，不只是平分整个棋盘的那两条对角线。
注意：本题相对原题做了扩展
示例：
	输入：4
	输出：{{".Q..","...Q","Q...","..Q."},{"..Q.","Q...","...Q",".Q.."}}
	解释：4 皇后问题存在如下两个不同的解法。
        {
        {".Q..", // 解法 1
        "...Q",
        "Q...",
        "..Q."},
        {"..Q.", // 解法 2
        "Q...",
        "...Q",
        ".Q.."}
        } */

class Solution1 {
public:
	vector<vector<string>> solveNQueens(int n) {
		vector<vector<string>> res;
		vector<string> curr = vector<string>(n, string(n, '.'));
		vector<pair<int, int>> placed(n);
		dfs(0, n, placed, res, curr);
		return res;
	}

private:
	void dfs(int i,
	    int n,
	    vector<pair<int, int>> &placed,
	    vector<vector<string>> &res,
	    vector<string> &curr) {
		if(i == n) {
			res.push_back(curr);
		}
		for(int j = 0; j < n; ++j) {
			bool canUse = true;
			for(int k = 0; k < i; ++k) { // 只有前i个是真的用了
				unsigned dx = abs(placed[k].first - i), dy = abs(placed[k].second - j);
				if(!dx || !dy) {
					canUse = false;
					break;
				}
				if(dx == dy) {
					canUse = false;
					break;
				}
			}
			if(!canUse) continue;
			placed[i] = { i, j };
			curr[i][j] = 'Q';
			dfs(i + 1, n, placed, res, curr);
			curr[i][j] = '.';
		}
	} // 控制范围为 abs(dx) == abs(dy) || dx = 0 || dy == 0
};

class Solution2 {
public:
	vector<vector<string>> solveNQueens(int n) {
		res.clear();
		curr = vector<string>(n, string(n, '.'));
		colUsed = vector<bool>(n, 0);
		diag1 = vector<bool>(2 * n - 1, 0);
		diag2 = vector<bool>(2 * n - 1, 0);
		dfs(0, n);
		return res;
	}

private:
	vector<string> curr;
	vector<bool> colUsed, diag1, diag2;
	vector<vector<string>> res;
	void dfs(int i, int n) {
		if(i == n) {
			res.push_back(curr);
		}
		for(int j = 0; j < n; ++j) {
			int diag1Index = i - j + n, diag2Index = i + j;
			if(colUsed[j] || diag1[diag1Index] || diag2[diag2Index]) continue;
			colUsed[j] = diag1[diag1Index] = diag2[diag2Index] = 1;
			curr[i][j] = 'Q';
			dfs(i + 1, n);
			curr[i][j] = '.';
			colUsed[j] = diag1[diag1Index] = diag2[diag2Index] = 0;
		}
	} // 同一主对角线: x - y = k，同一副对角线 x + y = k
};

class Solution {
public:
	vector<vector<string>> solveNQueens(int n) {
		curr = vector<int>(n);
		colUsed = vector<bool>(n, 0);
		diag1 = vector<bool>(2 * n - 1, 0);
		diag2 = vector<bool>(2 * n - 1, 0);
		vector<vector<string>> res;
		dfs(0, n, res);
		return res;
	}

private:
	vector<int> curr;
	vector<bool> colUsed, diag1, diag2;
	void dfs(int i, int n, vector<vector<string>> &res) {
		if(i == n) {
			res.emplace_back(n, string(n, '.'));
			for(int x = 0; x < n; ++x) {
				res.back()[x][curr[x]] = 'Q';
			} // 直接现场构造
			return;
		}
		for(int j = 0; j < n; ++j) {
			int diag1Index = i - j + n - 1, diag2Index = i + j;
			if(colUsed[j] || diag1[diag1Index] || diag2[diag2Index]) continue;
			colUsed[j] = diag1[diag1Index] = diag2[diag2Index] = 1;
			curr[i] = j;
			dfs(i + 1, n, res);
			colUsed[j] = diag1[diag1Index] = diag2[diag2Index] = 0;
		}
	} // 同一主对角线: x - y = k，同一副对角线 x + y = k
};

int main() {
	Solution sol;
	int n;
	n = 4;
	cout << sol.solveNQueens(n) << endl;

	n = 6;
	cout << sol.solveNQueens(n) << endl;
}