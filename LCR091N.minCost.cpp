// Created: 2025-12-18
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 假如有一排房子，共 n 个，每个房子可以被粉刷成红色、蓝色或者绿色这三种颜色中的一种，
你需要粉刷所有的房子并且使其相邻的两个房子颜色不能相同。
当然，因为市场上不同颜色油漆的价格不同，所以房子粉刷成不同颜色的花费成本也是不同的。
每个房子粉刷成不同颜色的花费是以一个n x 3的正整数矩阵 costs 来表示的。
例如，costs{0}{0} 表示第 0 号房子粉刷成红色的成本花费；costs{1}{2}表示第 1 号房子粉刷成绿色的花费，
以此类推。
请计算出粉刷完所有房子最少的花费成本。
示例 1：
	输入: costs = {{17,2,17},{16,16,5},{14,3,19}}
	输出: 10
	解释: 将 0 号房子粉刷成蓝色，1 号房子粉刷成绿色，2 号房子粉刷成蓝色。
	    最少花费: 2 + 5 + 3 = 10。
示例 2：
	输入: costs = {{7,6,2}}
	输出: 2
提示:
	costs.length == n
	costs{i}.length == 3
	1 <= n <= 100
	1 <= costs{i}{j} <= 20 */

class Solution1 {
public:
	int minCost(vector<vector<int>> &costs) {
		return dfs(costs, 0, 4);
	}

private:
	int dfs(vector<vector<int>> &costs, int i, int prevj) {
		if(i == costs.size()) return 0;
		int minCost = INT_MAX;
		for(int j = 0; j < 3; ++j) {
			if(prevj != j) minCost = min(dfs(costs, i + 1, j) + costs[i][j], minCost);
		}
		return minCost;
	}
}; // 状态有两个，i：当前位置的下标，prevj：前一个房子的颜色

class Solution2 {
public:
	int minCost(vector<vector<int>> &costs) {
		int n = costs.size();
		vector<vector<int>> dp(n + 1, vector<int>(3));
		for(int i = n - 1; i >= 0; --i) {
			for(int j = 0; j < 3; ++j) {
				int curr = INT_MAX;
				for(int prevj = 0; prevj < 3; ++prevj) {
					if(prevj != j) curr = min(dp[i + 1][prevj] + costs[i][j], curr);
				}
				dp[i][j] = curr;
			}
		}
		return ranges::min(dp[0]);
	}
};

class Solution {
public:
	int minCost(vector<vector<int>> &costs) {
		int n = costs.size();
		array<int, 3> curr, prev {};
		for(int i = 0; i < n; ++i) {
			curr[0] = min(prev[1], prev[2]) + costs[i][0];
			curr[1] = min(prev[0], prev[2]) + costs[i][1];
			curr[2] = min(prev[0], prev[1]) + costs[i][2];
			prev = curr;
		}
		return min(min(curr[0], curr[1]), curr[2]);
	}
};

int main() {
	Solution sol;
	vector<vector<int>> costs;
	costs = { { 17, 2, 17 }, { 16, 16, 5 }, { 14, 3, 19 } };
	cout << sol.minCost(costs) << endl;
	costs = { { 7, 6, 2 } };
	cout << sol.minCost(costs) << endl;
}