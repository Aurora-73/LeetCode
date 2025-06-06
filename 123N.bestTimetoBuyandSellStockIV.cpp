// Created: 2025-05-25
#include "MyUtils.hpp"

/*  188. 买卖股票的最佳时机 IV
给你一个整数数组 prices 和一个整数 k ，其中 prices[i] 是某支给定的股票在第 i 天的价格。
设计一个算法来计算你所能获取的最大利润。你最多可以完成 k 笔交易。也就是说，你最多可以买 k 次，卖 k 次。
注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。*/

class Solution1 {
public:
	int maxProfit(int k, vector<int> &prices) {
		this->k = k, n = prices.size();
		return dfs(prices, 0, 0);
	}

private:
	int n, k;
	int dfs(vector<int> &prices, int day, int state) {
		if(day >= n || state == 2 * k) return 0;
		int keep, move;
		if(state % 2 == 0) { // state % 2 == 0：手中没有股票
			keep = dfs(prices, day + 1, state);
			move = dfs(prices, day + 1, state + 1) - prices[day];
		} else { // state % 2 == 1：手中有股票
			keep = dfs(prices, day + 1, state);
			move = dfs(prices, day + 1, state + 1) + prices[day];
		}
		return max(keep, move);
	}
}; // 将任意一天的操作抽象成两种：1、保持当前状态 2、进行状态转移（只能移动到下一种状态）
// 状态分为两种类型：1、手中没有股票 2、手中有股票

class Solution2 {
public:
	int maxProfit(int k, vector<int> &prices) {
		this->k = k, n = prices.size();
		memo.resize(prices.size(), vector<int>(2 * k, INT_MAX));
		return dfs(prices, 0, 0);
	}

private:
	int n, k;
	vector<vector<int>> memo;
	int dfs(vector<int> &prices, int day, int state) {
		if(day >= n || state == 2 * k) return 0;
		if(memo[day][state] == INT_MAX) {
			int keep, move;
			if(state % 2 == 0) { // state % 2 == 0：手中没有股票
				keep = dfs(prices, day + 1, state);
				move = dfs(prices, day + 1, state + 1) - prices[day];
			} else { // state % 2 == 1：手中有股票
				keep = dfs(prices, day + 1, state);
				move = dfs(prices, day + 1, state + 1) + prices[day];
			}
			memo[day][state] = max(keep, move);
		}
		return memo[day][state];
	}
}; // 记忆化存储

class Solution3 {
public:
	int maxProfit(int k, vector<int> &prices) {
		int n = prices.size();
		vector<vector<int>> dp(prices.size() + 1, vector<int>(2 * k + 1));
		for(int i = n - 1; i >= 0; --i) {
			for(int j = 0; j < k; ++j) {
				dp[i][2 * j] = max(dp[i + 1][2 * j], dp[i + 1][2 * j + 1] - prices[i]);
				dp[i][2 * j + 1] = max(dp[i + 1][2 * j + 1], dp[i + 1][2 * j + 2] + prices[i]);
			}
		}
		return dp[0][0];
	}
}; // 动态规划

class Solution {
public:
	int maxProfit(int k, vector<int> &prices) {
		int n = prices.size();
		vector<int> dp(2 * k + 1);
		for(int i = n - 1; i >= 0; --i) {
			for(int j = 0; j < k; ++j) {
				dp[2 * j] = max(dp[2 * j], dp[2 * j + 1] - prices[i]);
				dp[2 * j + 1] = max(dp[2 * j + 1], dp[2 * j + 2] + prices[i]);
			}
		}
		return dp[0];
	}
}; // 状态压缩

int main() {
	Solution sol;
	vector<int> a { 3, 3, 5, 0, 0, 3, 1, 4 };
	cout << sol.maxProfit(4, a);
}