// Created: 2025-05-24
#include "MyUtils.hpp"

/* 221. 最大正方形
在一个由 0 和 1 组成的二维矩阵内，找到只包含 1 的最大正方形，并返回其面积。
示例 1：
	输入：matrix = {{'1','0','1','0','0'},{'1','0','1','1','1'},{'1','1','1','1','1'},{'1','0','0','1','0'}}
	输出：4
示例 2：
	输入：matrix = {{'0','1'},{'1','0'}}
	输出：1
示例 3：
	输入：matrix = {{'0'}}
	输出：0
提示：
	m == matrix.length
	n == matrix{i}.length
	1 <= m, n <= 300
	matrix{i}{j} 为 0 或 1 */

class Solution1 {
public:
	int maximalSquare(vector<vector<char>> &matrixc) {
		m = matrixc.size(), n = matrixc[0].size();
		bool have_len = false;
		int len = 0;
		vector<vector<int>> matrix(m, vector<int>(n, 0));

		// 初始化所有为 '1' 的位置为 1，找到至少一个 '1' 就初始化 len 为 1
		for(int i = 0; i < m; ++i) {
			for(int j = 0; j < n; ++j) {
				if(matrixc[i][j] == '1') {
					matrix[i][j] = 1;
					have_len = true;
				}
			}
		}
		if(have_len) len = 1;

		while(have_len) {
			have_len = dfs(matrix, len + 1);
			len += have_len;
		}
		return len * len;
	}

private:
	int m, n;
	bool dfs(vector<vector<int>> &matrix, int len) {
		bool have_len = false;
		for(int i = 0; i + len - 1 < m; ++i) {
			for(int j = 0; j + len - 1 < n; ++j) {
				if(matrix[i][j] == len - 1 && matrix[i + 1][j] == len - 1
				    && matrix[i][j + 1] == len - 1 && matrix[i + 1][j + 1] == len - 1) {
					matrix[i][j] = len;
					have_len = true;
				}
			}
		}
		return have_len;
	}
}; /* 以正方形的左上角和正方形的长度为正方形的标记 [i, j, n]
则 某个 长为 n 的扩展成长为 n + 1 的要求 右 下 右下 也均是长为 n 的
即 [i, j, n] + [i + 1, j, n] + [i, j + 1, n] + [i + 1, j + 1, n] -> [i, j, n + 1]
从长度 0 开始扩展，从左上角开始扩展  */

class Solution2 {
public:
	int maximalSquare(vector<vector<char>> &matrixc) {
		m = matrixc.size(), n = matrixc[0].size();
		bool have_len = true;
		int len = 0;
		vector<vector<int>> matrix(m, vector<int>(n)); // char会溢出
		for(int i = 0; i < m; ++i) {
			for(int j = 0; j < n; ++j) {
				matrix[i][j] = matrixc[i][j] - '0';
			}
		}
		while(have_len) {
			have_len = dfs(matrix, len + 1);
			len += have_len;
		}
		return len * len;
	}

private:
	int m, n;
	bool dfs(vector<vector<int>> &matrix, int len) {
		bool have_len = false;
		for(int i = 0; i < m; ++i) {
			for(int j = 0; j < n; ++j) {
				if(matrix[i][j] == len) {
					have_len = true;
					if(i < m - 1 && j < n - 1 && matrix[i + 1][j + 1] == len
					    && matrix[i + 1][j] == len && matrix[i][j + 1] == len) {
						++matrix[i][j];
					}
				}
			}
		}
		return have_len;
	}
}; /* 检查当前，并且为下一次做准备 */

class Solution3 {
public:
	int maximalSquare(vector<vector<char>> &matrixc) {
		uint16_t m = matrixc.size(), n = matrixc[0].size(), len = 0;
		vector<vector<uint16_t>> matrix(m, vector<uint16_t>(n)); // char会溢出
		for(int i = 0; i < m; ++i) {
			for(int j = 0; j < n; ++j) {
				matrix[i][j] = matrixc[i][j] - '0';
			}
		}
		// 然后从倒数第2行/列开始做转移
		for(int i = m - 2; i >= 0; --i) {
			for(int j = n - 2; j >= 0; --j) {
				if(matrix[i][j] > 0) {
					matrix[i][j]
					    = min({ matrix[i + 1][j], matrix[i][j + 1], matrix[i + 1][j + 1] }) + 1;
					len = max(len, matrix[i][j]);
				}
			}
		}
		for(int i = 0; i < m && !len; ++i) len = max(len, matrix[i][n - 1]);
		for(int j = 0; j < n && !len; ++j) len = max(len, matrix[m - 1][j]);
		// 为了防止仅边缘有 1 导致漏过，剪枝
		return int(len) * len;
	}
}; /* 动态规划，从右下角开始，如果当前不为空，则当前值等于 右 下 右下 的最小值 + 1, 注意如果不想扩大一圈，则需要额外考虑边缘为 1 的情况 */

class Solution4 {
public:
	int maximalSquare(vector<vector<char>> &matrixc) {
		uint16_t m = matrixc.size(), n = matrixc[0].size(), len = 0;
		vector<uint16_t> prev(n + 1, 0);

		for(int i = m - 1; i >= 0; --i) {
			vector<uint16_t> curr(n + 1);
			for(int j = n - 1; j >= 0; --j) {
				if(matrixc[i][j] == '1') {
					curr[j] = min(min(prev[j], curr[j + 1]), prev[j + 1]) + 1;
					len = max(len, curr[j]);
				} // 因为curr是刚声明过的，全0，所以不需要 else
			}
			prev = curr;
		}
		return int(len) * len;
	}
}; // 由于当前状态的计算仅依赖于前一行和当前行的之前计算过的值，因此仅保留前一次的值和当前值即可

class Solution {
public:
	int maximalSquare(vector<vector<char>> &matrixc) {
		uint16_t m = matrixc.size(), n = matrixc[0].size(), len = 0;
		vector<uint16_t> dp(n + 1, 0);
		for(int i = m - 1; i >= 0; --i) {
			uint16_t diag = 0; // 注意没有了重新声明curr，需要归 0
			for(int j = n - 1; j >= 0; --j) {
				uint16_t temp = dp[j]; // 为下一个(j - 1)保存prev[j + 1]
				if(matrixc[i][j] == '1') {
					dp[j] = min({ dp[j], dp[j + 1], diag }) + 1;
					// 对应的是 curr[j] = min({ prev[j], curr[j + 1], prev[j + 1] }) + 1;
					// 更新到当前位置时，prev[j]保存在dp[j]中，curr[j + 1]保存在dp[j + 1]中，但是prev[j + 1]已经被curr[j + 1]覆盖掉了
					// 因此需要一个额外的值保存 prev[j + 1]，即为 diag
					len = max(len, dp[j]);
				} else {
					dp[j] = 0; // 遇 '0' 或边界，无法构成正方形 // 没有了重新声明curr需要归 0
				}
				diag = temp; // 为下一个(j - 1)更新diag
			}
		}
		return int(len) * len;
	}
};
/* 进一步压缩思路：
要把两行合为一行，只需一个一维数组 dp[j]，在「从右到左」更新时，让它同时承担：
    更新前的 dp[j] —— 代表原来的 prev[j]（上一行同列）；
    更新后的 dp[j] —— 代表新的 curr[j]（本行同列）。
但这样就丢失了原来 prev[j+1]（上一行右列）的值，
所以需要额外一个变量来保存上一行右列的信息。我们把它叫做 diag（对角线，i+1,j+1 的位置）。*/

int main() {
	Solution sol;
	vector<vector<char>> matrix;
	matrix = { { '1', '1' }, { '1', '1' }, { '0', '1' } };
	cout << sol.maximalSquare(matrix) << endl;

	matrix = { { '1', '1' }, { '1', '1' } };
	cout << sol.maximalSquare(matrix) << endl;

	matrix = { { '1', '0', '0', '1', '1', '0', '1', '1' },
		{ '1', '0', '0', '0', '0', '1', '0', '0' },
		{ '0', '1', '1', '1', '0', '0', '1', '1' },
		{ '0', '0', '0', '1', '0', '0', '0', '1' },
		{ '0', '0', '0', '0', '0', '1', '1', '1' },
		{ '1', '1', '1', '1', '1', '1', '1', '1' },
		{ '1', '0', '0', '1', '0', '1', '1', '0' },
		{ '0', '1', '1', '0', '1', '1', '1', '0' } };
	cout << sol.maximalSquare(matrix) << endl;

	matrix = { { '1', '0', '1', '1', '1', '1', '0', '1', '1' },
		{ '0', '1', '0', '1', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '1', '0', '1', '1', '0' },
		{ '1', '1', '1', '0', '1', '0', '1', '0', '1' } };
	cout << sol.maximalSquare(matrix) << endl;

	matrix = { { '1', '0', '1', '0', '0' },
		{ '1', '0', '1', '1', '1' },
		{ '1', '1', '1', '1', '1' },
		{ '1', '0', '0', '1', '0' } };
	cout << sol.maximalSquare(matrix) << endl;

	matrix = { { '0', '1' }, { '1', '0' } };
	cout << sol.maximalSquare(matrix) << endl;

	matrix = { { '0' } };
	cout << sol.maximalSquare(matrix) << endl;
}

/*在很多二维动态规划（DP）问题中，如果状态转移只依赖「上一行」或「同一行前面若干列」的值，就可以将原本需要 $O(n\times m)$ 空间的二维数组压缩为仅用两行（或一行）的滚动数组，从而把空间复杂度降到 $O(m)$。下面分三部分详细说明。
---
## 一、何时可以使用滚动数组压缩？
1. **依赖单行**
   如果转移方程中，状态 `dp[i][j]` 只依赖 `dp[i-1][·]`（上一行）和/或 `dp[i][j-1]`（本行左侧），就可以只保留两行：
   $$
     dp[i][j] = f\big(dp[i-1][j],\;dp[i][j-1],\dots\big)
   $$
   典型例子：最长公共子序列（LCS）、编辑距离、网格最小路径和等。
2. **依赖固定窗口行**
   如果状态还会依赖 `dp[i-2][·]`、`dp[i-3][·]`…，只要依赖的行数是常数 $k$，就可以保留 $k$ 行滚动。
   典型例子：某些最短路径或区间 DP，当依赖的「之前 $k$ 行」中 $k$ 是常数。
3. **只依赖本行以前列**
   这类问题往往更极端，如 0-1 背包：
   $$
     dp[j] = \max(dp[j],\;dp[j-w_i] + v_i)
   $$
   它只依赖同一行（即同一次遍历中）「左侧」的状态，可进一步压到一行，并且需要反向遍历防止覆盖。
---
## 二、为什么可以这样压缩？
1. **状态复用**
   由于对「更早」行（或列）的访问都只发生在「当前行更新前」或「当前列更新前」，老行/老列的数据已经用不着了，可以被新行/新列覆盖。
2. **滚动替换**
   用两行 $cur$ 和 $pre$ 交替存放：
   ```cpp
   for (int i = 1; i <= n; ++i) {
     swap(cur, pre);       // 上一行变成 pre，当前行写入 cur
     for (int j = 1; j <= m; ++j) {
       cur[j] = f(pre[j], cur[j-1], …);
     }
   }
   ```
   这样 $pre[j]$ 永远对应「上一行」的值，$cur[j-1]$ 对应「本行左侧」的值。
3. **空间从 2D → 1D／2D(k)**
   * 当只依赖上一行：只要两行即可。
   * 当只依赖自身左侧：只要一行，并按「j 从大到小」遍历以防覆盖。
   * 当依赖常数 $k$ 行：要 $k$ 行。
---
## 三、压缩时的注意事项
1. **正确初始化**
   * 每次处理新行（或新状态集）前，要先清或重置 `cur[...]`（或 1D 数组）为合法的初始值（如 $-\infty$、0、或边界值）。
   * 对于 0-1 背包等一维滚动，要在每次物品循环开始前保证 `dp[...]` 保持上一物品的结果。
2. **遍历顺序**
   * **依赖左侧**：必须「正序」遍历列（`j=1→m`），否则会错将本行刚更新的值当作左侧参考。
   * **依赖本行左侧**（如 0-1 背包）且压到一维时，因 `dp[j]` 会依赖 `dp[j - w]`（同一轮旧值），需要反向遍历 `j=m→w`，保证 `dp[j-w]` 还是上一轮的值。
3. **下标越界和别名**
   * 滚动数组常用两行交替：`dp[i%2][j]`，或用 `swap(cur,pre)`。务必确保下标映射正确，不要越界。
   * 混用 `i%2` 和直接 `i&1` 都可，但要保持一致。
4. **多行依赖的特殊处理**
   * 如果依赖 `k` 行，最好用大小为 $k$ 的循环队列：

     ```cpp
     static int dp[k][M];
     for (int i = 1; i <= n; ++i) {
       int cur = i % k, pre1 = (i-1)%k, pre2 = (i-2)%k;
       for (int j = 1; j <= m; ++j) {
         dp[cur][j] = f(dp[pre1][j], dp[pre2][j], ...);
       }
     }
     ```
   * 注意 `% k` 的计算成本极小，但要确保 $k$ 小于等于行依赖数。
5. **调试友好**
   * 滚动压缩虽省空间，但可读性差，出错后更难定位。建议在不超内存时优先用二维数组，确定逻辑正确后再压缩。
---
### 小结
* **何时**：当状态转移只依赖「上一行／常数行」或「当前行左侧」时。
* **为什么**：因为「老」数据一旦用完可安全覆盖，新旧互不干扰。
* **注意**：初始化、遍历方向、下标映射、多行依赖场景、可读性折衷。
掌握这些要点，就能在保证正确性的前提下，大幅度减少 DP 算法的空间消耗。祝编码顺利！
*/