// Created: 2025-05-23
#include "MyUtils.h"

/*  980. 不同路径 III
在二维网格 grid 上，有 4 种类型的方格：
1 表示起始方格。且只有一个起始方格。
2 表示结束方格，且只有一个结束方格。
0 表示我们可以走过的空方格。
-1 表示我们无法跨越的障碍。
返回在四个方向（上、下、左、右）上行走时，从起始方格到结束方格的不同路径的数目。
每一个无障碍方格都要通过一次，但是一条路径中不能重复通过同一个方格。 */

class Solution1 {
public:
	int uniquePathsIII(vector<vector<int>> &grid) {
		m = grid.size(), n = grid[0].size();
		count = 0, all_need = 0;
		for(int i = 0; i < m; ++i) {
			for(int j = 0; j < n; ++j) {
				if(grid[i][j] != -1) {
					++all_need;
				}
			}
		}
		for(int i = 0; i < m; ++i) {
			for(int j = 0; j < n; ++j) {
				if(grid[i][j] == 1) {
					return dfs(grid, i, j);
				}
			}
		}
		return 0;
	}

private:
	int m, n, count, all_need;
	const vector<vector<int>> dirs = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
	int dfs(vector<vector<int>> &grid, int i, int j) {
		if(i < 0 || j < 0 || i >= m || j >= n || grid[i][j] == -1) {
			return 0;
		} else if(grid[i][j] == 2) {
			return count == all_need - 1;
		}
		++count;
		int all_paths = 0, temp = grid[i][j];
		grid[i][j] = -1;
		for(auto &dir : dirs) {
			all_paths += dfs(grid, i + dir[0], j + dir[1]);
		}
		grid[i][j] = temp;
		--count;
		return all_paths;
	}
};

struct pair_hash {
	size_t operator()(const pair<int, int> &p) const noexcept {
		// 简单地把两个 int 拼成一个 size_t ( int 32位，size_t 64位，直接拼接即可 )
		return ((size_t)p.first << 32) ^ (size_t)p.second;
	}
};

class Solution2 {
public:
	int uniquePathsIII(vector<vector<int>> &grid) {
		m = grid.size();
		n = grid[0].size();
		all_mask = (1 << (m * n)) - 1;

		init_vis = 0;
		int si = 0, sj = 0;
		for(int i = 0; i < m; ++i) {
			for(int j = 0; j < n; ++j) {
				int pos = i * n + j;
				if(grid[i][j] == -1) {
					init_vis |= (1 << pos);
				}
				if(grid[i][j] == 1) {
					si = i;
					sj = j;
				}
			}
		}

		memo.clear();
		// 起点也要标记为已访问
		int start_pos = si * n + sj;
		return dfs(si, sj, init_vis | (1 << start_pos), grid);
	}

private:
	int m, n;
	int all_mask;
	int init_vis;
	// 把 (vis, pos) 作为 key
	unordered_map<pair<int, int>, int, pair_hash> memo;
	const vector<pair<int, int>> dirs = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

	int dfs(int i, int j, int vis, vector<vector<int>> &grid) {
		int pos = i * n + j;
		pair<int, int> key = { vis, pos };
		auto it = memo.find(key);
		if(it != memo.end()) {
			return it->second;
		}

		// 到达终点，判断是否已访问全集
		if(grid[i][j] == 2) {
			return memo[key] = (vis == all_mask ? 1 : 0);
		}

		int ways = 0;
		for(auto &d : dirs) {
			int ni = i + d.first;
			int nj = j + d.second;
			if(ni < 0 || nj < 0 || ni >= m || nj >= n) continue;

			int npos = ni * n + nj;
			if((vis >> npos) & 1) continue;

			ways += dfs(ni, nj, vis | (1 << npos), grid);
		}

		return memo[key] = ways;
	}
};
// 为什么不能只用 dp[i][j]？
//     因为合法路径的数量不仅仅取决于你当前所在的格子 (i,
//     j)，还取决于「哪些格子已经走过」，否则就可能重复走或者漏走。单纯地把状态压缩成 dp[i][j]
//     是没法表达「已访问集合」的。
// 为什么不把整个 grid 作为参数？
//     由于直接复制或修改整个 grid 太重，才改用「位掩码
//     vis」来记录哪些格子已访问，这样就实现了“无后效”的状态传递。
// 为什么用位运算？
//     把二维坐标 (i,j) 映射到一个整型下标 pos = i*n + j。
//     用 vis 的第 pos 位表示该格子是否已访问。

int main() {
	Solution2 sol;
}