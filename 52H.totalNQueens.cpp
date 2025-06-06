// Created: 2025-05-13
#include "MyUtils.hpp"

/*52. N 皇后 II
n 皇后问题 研究的是如何将 n 个皇后放置在 n × n 的棋盘上，并且使皇后彼此之间不能相互攻击。
给你一个整数 n ，返回 n 皇后问题 不同的解决方案的数量。*/

class Solution {
public:
	int totalNQueens(int nn) {
		n = nn;
		line.resize(n, false);
		right.resize(2 * n - 1, false);
		left.resize(2 * n - 1, false);
		dfs(0);
		return find;
	}

private:
	size_t find = 0, n;
	vector<bool> line, right, left; // 分别表示该列，右侧斜线，左侧斜线是否有元素
	inline size_t ij2right(size_t i, size_t j) {
		return n - 1 + i - j;
	}
	inline size_t ij2left(size_t i, size_t j) {
		return i + j;
	}
	void dfs(size_t i) {
		if(i == n) {
			++find;
			return;
		}
		for(size_t j = 0; j < n; j++) {
			if(!line[j] && !right[ij2right(i, j)] && !left[ij2left(i, j)]) {
				line[j] = true;
				left[ij2left(i, j)] = true;
				right[ij2right(i, j)] = true;
				dfs(i + 1);
				line[j] = false;
				left[ij2left(i, j)] = false;
				right[ij2right(i, j)] = false;
			}
		}
	}
}; // ij2right 和 ij2left 可以通过在格子的左上角画一个x朝右，y朝下的坐标轴，画出y = -x + k 和 y = x + k 的平行线得到

class Solution {
public:
	int totalNQueens(int n) {
		this->n = n;
		find = 0;
		dfs(0, 0, 0, 0);
		return find;
	}

private:
	int find = 0, n;
	// 参数含义：
	// row 当前行
	// col 当前列已经放了哪些（按位为1）
	// ld 左对角线攻击区域（↙）
	// rd 右对角线攻击区域（↘）
	void dfs(int row, int col, int ld, int rd) {
		if(row == n) {
			++find;
			return;
		}
		// 当前可用位置：在 n 位范围内是 1，排除已有攻击位置
		int pos = ((1 << n) - 1) & (~(col | ld | rd));
		while(pos) {
			// 取最低位的1放皇后
			int p = pos & -pos;
			pos -= p;
			dfs(row + 1, col | p, (ld | p) << 1, (rd | p) >> 1);
		}
	}
}; // 使用位运算代替visited数组

class Solution {
public:
	int totalNQueens(int nn) {
		n = nn;
		dfs(0);
		return find;
	}

private:
	size_t find = 0, n;
	bitset<17> line, right, left = 0;
	// 分别表示该列，右侧斜线，左侧斜线是否有元素
	void dfs(size_t i) {
		if(i == n) {
			++find;
			return;
		}
		for(size_t j = 0; j < n; j++) {
			size_t l = i + j, r = n - 1 + i - j;
			if(!line[j] && !right[r] && !left[l]) {
				line.set(j), left.set(l), right.set(r);
				dfs(i + 1);
				line.reset(j), left.reset(l), right.reset(r);
			}
		}
	}
}; // 使用bitset

int main() {
	Solution sol;
}