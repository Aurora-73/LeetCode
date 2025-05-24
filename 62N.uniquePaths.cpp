// Created: 2025-05-23
#include "MyUtils.h"

/*62. 不同路径
一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。
机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish” ）。
问总共有多少条不同的路径？*/

class Solution1 {
public:
	int uniquePaths(int m, int n) {
		vector<vector<int>> dp(m, vector<int>(n));
		for(int i = 0; i < m; ++i) {
			dp[i][n - 1] = 1;
		}
		for(int j = 0; j < n; ++j) {
			dp[m - 1][j] = 1;
		}
		for(int i = m - 2; i >= 0; --i) {
			for(int j = n - 2; j >= 0; --j) {
				dp[i][j] = dp[i + 1][j] + dp[i][j + 1];
			}
		}
		return dp[0][0];
	}
};

class Solution2 {
public:
	int uniquePaths(int m, int n) {
		if(m < n) swap(m, n);
		// dp[j]：表示当前正在处理的行，从列 j 到终点有多少条路径
		vector<int> dp(n, 1);
		// 最底行初始化为 1（只能一路向右）
		// 然后从倒数第二行开始向上“滚动”
		for(int i = m - 2; i >= 0; --i) {
			// 最右列 dp[n-1] 本身也是 1（只能一路向下）
			for(int j = n - 2; j >= 0; --j) {
				// dp[j] (原来是 dp[i+1][j]) + dp[j+1] (dp[i][j+1])
				dp[j] += dp[j + 1];
			}
		}
		return dp[0];
	}
}; // 处理到第 i 行时，让 dp[j] 等于「从点 (i,j) 出发，到终点 (m-1,n-1) 的路径数」。
/*举个例子，在计算 dp[1][1] 时，会用到 dp[0][1]，但是之后就不再用到了。
那么干脆把 dp[1][1] 记到 dp[0][1] 中，这样对于 dp[1][2] 来说，它需要的数据就在 dp[0][1] 和 dp[0][2]
中。 dp[1][2] 算完后也可以同样记到 dp[0][2] 中。*/

class Solution {
public:
	int uniquePaths(int m, int n) {
		long long ans = 1;
		for(int x = n, y = 1; y < m; ++x, ++y) {
			ans = ans * x / y;
		}
		return ans;
	}
}; // 组合数，m + n - 2 里选 m -1 次向下

int main() {
	Solution sol;
	cout << sol.uniquePaths(3, 2);
}