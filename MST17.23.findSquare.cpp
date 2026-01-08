// Created: 2026-01-08
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个方阵，其中每个单元(像素)非黑即白。
设计一个算法，找出 4 条边皆为黑色像素的最大子方阵。
返回一个数组 {r, c, size}，其中r,c分别代表子方阵左上角的行号和列号，size 是子方阵的边长。
若有多个满足条件的子方阵，返回 r 最小的，若 r 相同，返回 c 最小的子方阵。若无满足条件的子方阵，返回空数组。
示例 1：
	输入：
	{
	  {1,0,1},
	  {0,0,1},
	  {0,0,1}
	}
	输出：{1,0,2}
	解释：输入中 0 代表黑色，1 代表白色，标粗的元素即为满足条件的最大子方阵
示例 2：
	输入：
	{
	  {0,1,1},
	  {1,0,1},
	  {1,1,0}
	}
	输出：{0,0,1}
提示：
	matrix.length == matrix{0}.length <= 200 */

class Solution1 {
public:
	vector<int> findSquare(vector<vector<int>> &matrix) {
		int n = matrix.size();
		vector<int> res { -1, -1, -1 };
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < n; ++j) {
				int offset = 0;
				while(i + offset < n && j + offset < n && matrix[i + offset][j] == 0
				    && matrix[i][j + offset] == 0) {
					if(offset + 1 > res.back()) {
						bool find = true;
						for(int k = 1; k <= offset; ++k) {
							if(matrix[i + offset][j + k] != 0 || matrix[i + k][j + offset] != 0) {
								find = false;
								break;
							}
						}
						if(find) {
							res = { i, j, offset + 1 };
						}
					}
					++offset;
				}
			}
		}
		return res.back() > 0 ? res : vector<int>();
	}
};

class Solution2 {
public:
	vector<int> findSquare(vector<vector<int>> &matrix) {
		int n = matrix.size();
		vector<int> res { -1, -1, -1 };
		vector<vector<int>> left(n, vector<int>(n)), up(n, vector<int>(n));
		for(int i = 0; i < n; ++i) {
			left[i].front() = !matrix[i].front();
			up.front()[i] = !matrix.front()[i];
		}
		for(int i = 1; i < n; ++i) {
			for(int j = 0; j < n; ++j) {
				up[i][j] = matrix[i][j] ? 0 : up[i - 1][j] + 1;
				left[j][i] = matrix[j][i] ? 0 : left[j][i - 1] + 1;
			}
		}
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < n; ++j) {
				int offset = 0;
				while(i + offset < n && j + offset < n && matrix[i + offset][j] == 0
				    && matrix[i][j + offset] == 0) {
					if(offset + 1 > res.back()) {
						bool find = up[i + offset][j + offset] > offset
						    && left[i + offset][j + offset] > offset;
						if(find) {
							res = { i, j, offset + 1 };
						}
					}
					++offset;
				}
			}
		}
		return res.back() > 0 ? res : vector<int>();
	}
};

class Solution {
public:
	// matrix: 0 表示黑色，1 表示白色
	vector<int> findSquare(vector<vector<int>> &matrix) {
		int n = matrix.size();
		if(n == 0) return {};
		// row[i][j] : 第 i 行前 j 个元素（j 从 0..n）中黑色(0)的个数
		vector<vector<int>> row(n, vector<int>(n + 1, 0));
		// col[i][j] : 第 j 列前 i 个元素（i 从 0..n）中黑色(0)的个数
		vector<vector<int>> col(n + 1, vector<int>(n, 0));

		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < n; ++j) {
				int isBlack = (matrix[i][j] == 0) ? 1 : 0;
				row[i][j + 1] = row[i][j] + isBlack;
				col[i + 1][j] = col[i][j] + isBlack;
			}
		}

		auto exists_with_size = [&](int s, int &out_r, int &out_c) -> bool {
			// 检查是否存在边长为 s 的满足条件的子方阵
			// 若存在，则把最小 (r,c) 写入 out_r/out_c（按 r 升序，c 升序）
			for(int r = 0; r + s - 1 < n; ++r) {
				for(int c = 0; c + s - 1 < n; ++c) {
					int r2 = r + s - 1, c2 = c + s - 1;
					// 上边
					if(row[r][c + s] - row[r][c] != s) continue;
					// 下边
					if(row[r2][c + s] - row[r2][c] != s) continue;
					// 左边
					if(col[r + s][c] - col[r][c] != s) continue;
					// 右边
					if(col[r + s][c2] - col[r][c2] != s) continue;
					out_r = r;
					out_c = c;
					return true;
				}
			}
			return false;
		};

		int lo = 1, hi = n, best = 0;
		int best_r = -1, best_c = -1;
		while(lo <= hi) {
			int mid = (lo + hi) / 2;
			int found_r = -1, found_c = -1;
			if(exists_with_size(mid, found_r, found_c)) {
				// mid 可行，记录并试更大
				best = mid;
				best_r = found_r;
				best_c = found_c;
				lo = mid + 1;
			} else {
				hi = mid - 1;
			}
		}

		if(best == 0) return {}; // 无解
		// 注意：二分过程中我们已经保存了某个可行 size 对应的最小 (r,c)。
		// 因为我们在 exists_with_size 中是按 r,c 升序遍历，第一个就是最小的。
		return { best_r, best_c, best };
	}
}; // 前缀和 + 二分查找，如何suff[i + len] - suff[i] == len，则说明这段区域内没有黑色
// 二分查找，一开始查找最大值，如果发现黑色，则减半查找，直到找到为止 O(n ^ 2 log n)

int main() {
	Solution sol;
	vector<vector<int>> matrix;
	matrix = { { 1, 0, 1 }, { 0, 0, 1 }, { 0, 0, 1 } };
	cout << sol.findSquare(matrix) << endl;

	matrix = { { 0, 1, 1 }, { 1, 0, 1 }, { 1, 1, 0 } };
	cout << sol.findSquare(matrix) << endl;

	matrix = { { 1, 1, 1, 0, 1, 1, 0, 1, 0, 0 },
		{ 0, 1, 0, 1, 1, 0, 0, 0, 1, 1 },
		{ 0, 0, 1, 1, 0, 0, 1, 1, 1, 0 },
		{ 0, 1, 1, 1, 0, 1, 0, 0, 1, 0 },
		{ 1, 1, 0, 1, 1, 0, 1, 0, 0, 1 },
		{ 0, 1, 1, 0, 0, 0, 0, 1, 1, 0 },
		{ 1, 0, 0, 0, 0, 1, 1, 1, 1, 1 },
		{ 1, 0, 1, 0, 1, 0, 0, 0, 1, 0 },
		{ 1, 1, 1, 1, 0, 1, 0, 1, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 0 } };
	cout << sol.findSquare(matrix) << endl;
}