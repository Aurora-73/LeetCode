// Created: 2025-05-24
#include "MyUtils.h"

/* 122. 买卖股票的最佳时机 II
给你一个整数数组 prices ，其中 prices[i] 表示某支股票第 i 天的价格。
在每一天，你可以决定是否购买和/或出售股票。你在任何时候最多只能持有一股股票。
你也可以先购买，然后在同一天出售。返回你能获得的最大利润 。*/

class Solution1 {
public:
	int maxProfit(vector<int> &prices) {
		return dfs(prices, 0, 0);
	}

private:
	int dfs(vector<int> &prices, int day, bool state) {
		if(day >= (int)prices.size()) return 0;
		int keep, move;
		if(state == 0) { // state = 0：当前不持股，要么保持不持股，要么买入
			keep = dfs(prices, day + 1, 0);
			move = dfs(prices, day + 1, 1) - prices[day];
		} else { // state = 1：当前持股，要么保持持股，要么卖出
			keep = dfs(prices, day + 1, 1);
			move = dfs(prices, day + 1, 0) + prices[day];
		}
		return max(keep, move);
	}
};

class Solution2 {
public:
	int maxProfit(vector<int> &prices) {
		memo.resize(prices.size(), { INT_MAX, INT_MAX });
		return dfs(prices, 0, 0);
	}

private:
	vector<array<int, 2>> memo;
	int dfs(vector<int> &prices, int day, bool state) {
		if(day >= (int)prices.size()) return 0;
		if(memo[day][state] == INT_MAX) {
			int keep, move;
			if(!state) {
				keep = dfs(prices, day + 1, 0);
				move = dfs(prices, day + 1, 1) - prices[day];
			} else {
				keep = dfs(prices, day + 1, 1);
				move = dfs(prices, day + 1, 0) + prices[day];
			}
			memo[day][state] = max(keep, move);
		}
		return memo[day][state];
	}
};

class Solution3 {
public:
	int maxProfit(vector<int> &prices) {
		int n = prices.size();
		vector<array<int, 2>> dp(n + 1);
		dp.back().fill(0);
		for(int i = n - 1; i >= 0; --i) {
			dp[i][0] = max(dp[i + 1][0], dp[i + 1][1] - prices[i]);
			dp[i][1] = max(dp[i + 1][1], dp[i + 1][0] + prices[i]);
		}
		return dp[0][0];
	}
};
/*dp[i][0]：第 i 天开始，不持有股票时，能获得的最大利润
dp[i][1]：第 i 天开始，持有股票时，能获得的最大利润*/

class Solution4 {
public:
	int maxProfit(vector<int> &prices) {
		int n = prices.size();
		int profit_no_stock = 0;   // 当前不持股时的最大利润 dp[i][0]
		int profit_have_stock = 0; // 当前持股时的最大利润 dp[i][1]

		for(int i = n - 1; i >= 0; --i) {
			int next_profit_no_stock = profit_no_stock; // 暂存旧的 dp[i+1][0]
			// 当前不持股：要么不操作（保持 dp[i+1][0]），要么今天买入（花 -prices[i]）
			profit_no_stock = max(profit_no_stock, profit_have_stock - prices[i]);
			// 当前持股：要么继续持有（dp[i+1][1]），要么今天卖出（赚 prices[i]）
			profit_have_stock = max(profit_have_stock, next_profit_no_stock + prices[i]);
		}
		return profit_no_stock;
	}
};

class Solution {
public:
	int maxProfit(vector<int> &prices) {
		int sum = 0, n = prices.size();
		for(int i = 1; i < n; ++i) {
			sum += max(prices[i] - prices[i - 1], 0);
		}
		return sum;
	}
}; // 直接加和全部的增量，不要减少的

int main() {
	Solution sol;
	vector<int> a { 1, 2, 3, 4, 5, 1, 2, 4 };
	cout << sol.maxProfit(a);
}