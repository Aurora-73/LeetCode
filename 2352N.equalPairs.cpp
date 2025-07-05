// Created: 2025-07-05
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 2352. 相等行列对
给你一个下标从 0 开始、大小为 n x n 的整数矩阵 grid，
返回满足 Ri 行和 Cj 列相等的行列对 (Ri, Cj) 的数目。
如果行和列以相同的顺序包含相同的元素（即相等的数组），则认为二者是相等的。
示例 1：
	输入：grid = {{3,2,1},{1,7,6},{2,7,7}}
	输出：1
	解释：存在一对相等行列对：
	- (第 2 行，第 1 列)：{2,7,7}
示例 2：
	输入：grid = {{3,1,2,2},{1,4,4,5},{2,4,2,2},{2,4,2,2}}
	输出：3
	解释：存在三对相等行列对：
	- (第 0 行，第 0 列)：{3,1,2,2}
	- (第 2 行, 第 2 列)：{2,4,2,2}
	- (第 3 行, 第 2 列)：{2,4,2,2}
提示：
	n == grid.length == grid{i}.length
	1 <= n <= 200
	1 <= grid{i}{j} <= 10^5 */

class Solution1 {
public:
	int equalPairs(vector<vector<int>> &grid) {
		int res = 0, n = grid.size();
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < n; ++j) {
				for(int k = 0; k < n; ++k) {
					if(grid[i][k] != grid[k][j]) {
						--res;
						break;
					}
				}
				++res;
			}
		}
		return res;
	}
};

class Solution2 {
public:
	int equalPairs(vector<vector<int>> &grid) {
		int res = 0, n = grid.size();
		vector<vector<int>> line;
		line.reserve(n);
		for(int i = 0; i < n; ++i) {
			line.push_back({});
			auto &back = line.back();
			back.reserve(n);
			for(int j = 0; j < n; ++j) {
				back.push_back(grid[j][i]);
			}
		}
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < n; ++j) {
				if(grid[i] == line[j]) ++res;
			}
		}
		return res;
	}
};

class Solution {
public:
	int equalPairs(vector<vector<int>> &grid) {
		int res = 0, n = grid.size();
		map<vector<int>, int> lines;
		for(int i = 0; i < n; ++i) {
			vector<int> now;
			now.reserve(n);
			for(int j = 0; j < n; ++j) {
				now.push_back(grid[j][i]);
			}
			++lines[std::move(now)];
		}
		for(int i = 0; i < n; ++i) {
			auto it = lines.find(grid[i]);
			if(it != lines.end()) {
				res += it->second;
			}
		}
		return res;
	}
};

int main() {
	Solution sol;
	vector<vector<int>> grid;
	grid = { { 3, 2, 1 }, { 1, 7, 6 }, { 2, 7, 7 } };
	cout << sol.equalPairs(grid) << endl; // 1
	grid = { { 3, 1, 2, 2 }, { 1, 4, 4, 5 }, { 2, 4, 2, 2 }, { 2, 4, 2, 2 } };
	cout << sol.equalPairs(grid) << endl; // 3
}