// Created: 2025-05-25
#include "MyUtils.hpp"

/*  123. 买卖股票的最佳时机 III
给定一个数组，它的第 i 个元素是一支给定的股票在第 i 天的价格。
设计一个算法来计算你所能获取的最大利润。你最多可以完成 两笔 交易。
注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。*/

class Solution0 {
public:
	int maxProfit(vector<int> &prices) {
		return dfs(prices, 0, 0);
	}

private:
	int dfs(vector<int> &prices, int day, int state) {
		if(day >= (int)prices.size()) return 0;
		if(state == 0) { // state = 0：未进行过任何操作
			int skip = dfs(prices, day + 1, 0);
			int buy = dfs(prices, day + 1, 1) - prices[day];
			return max(skip, buy);
		} else if(state == 1) { // state = 1：只进行过一次买操作
			int hold = dfs(prices, day + 1, 1);
			int sell = dfs(prices, day + 1, 2) + prices[day];
			return max(hold, sell);
		} else if(state == 2) { // state = 2：进行过一次买卖操作，尚未买入第二次
			int skip = dfs(prices, day + 1, 2);
			int buy = dfs(prices, day + 1, 3) - prices[day];
			return max(skip, buy);
		} else if(state == 3) { // state = 3：已买入第二次
			int hold = dfs(prices, day + 1, 3);
			int sell = dfs(prices, day + 1, 4) + prices[day];
			return max(hold, sell);
		} else {
			return 0;
		}
	}
};

class Solution1 {
public:
	int maxProfit(vector<int> &prices) {
		return dfs(prices, 0, 0);
	}

private:
	int dfs(vector<int> &prices, int day, int state) {
		if(day >= (int)prices.size() || state == 4) return 0;
		int keep, move;
		if(state == 0) { // state = 0：未进行过任何操作
			keep = dfs(prices, day + 1, state);
			move = dfs(prices, day + 1, state + 1) - prices[day];
		} else if(state == 1) { // state = 1：只进行过一次买操作
			keep = dfs(prices, day + 1, state);
			move = dfs(prices, day + 1, state + 1) + prices[day];
		} else if(state == 2) { // state = 2：进行过一次买卖操作，尚未买入第二次
			keep = dfs(prices, day + 1, state);
			move = dfs(prices, day + 1, state + 1) - prices[day];
		} else if(state == 3) { // state = 3：已买入第二次
			keep = dfs(prices, day + 1, state);
			move = dfs(prices, day + 1, state + 1) + prices[day];
		}
		return max(keep, move);
	}
}; // 将任意一天的操作抽象成两种：1、保持当前状态 2、进行状态转移（只能移动到下一种状态）

class Solution2 {
public:
	int maxProfit(vector<int> &prices) {
		memo.resize(prices.size(), { INT_MAX, INT_MAX, INT_MAX, INT_MAX });
		return dfs(prices, 0, 0);
	}

private:
	vector<array<int, 4>> memo;
	int dfs(vector<int> &prices, int day, int state) {
		if(day >= (int)prices.size() || state == 4) return 0;
		if(memo[day][state] == INT_MAX) {
			int keep, move;
			if(state == 0) { // state = 0：未进行过任何操作
				keep = dfs(prices, day + 1, state);
				move = dfs(prices, day + 1, state + 1) - prices[day];
			} else if(state == 1) { // state = 1：只进行过一次买操作
				keep = dfs(prices, day + 1, state);
				move = dfs(prices, day + 1, state + 1) + prices[day];
			} else if(state == 2) { // state = 2：进行过一次买卖操作，尚未买入第二次
				keep = dfs(prices, day + 1, state);
				move = dfs(prices, day + 1, state + 1) - prices[day];
			} else if(state == 3) { // state = 3：已买入第二次
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
	int maxProfit(vector<int> &prices) {
		int n = prices.size();
		vector<array<int, 4>> dp(prices.size() + 1);
		dp.back().fill(0);
		for(int i = n - 1; i >= 0; --i) {
			dp[i][0] = max(dp[i + 1][0], dp[i + 1][1] - prices[i]);
			dp[i][1] = max(dp[i + 1][1], dp[i + 1][2] + prices[i]);
			dp[i][2] = max(dp[i + 1][2], dp[i + 1][3] - prices[i]);
			dp[i][3] = max(dp[i + 1][3], 0 + prices[i]);
		}
		return dp[0][0];
	}
}; // 动态规划

class Solution {
public:
	int maxProfit(vector<int> &prices) {
		int n = prices.size();
		array<int, 4> dp { 0 }; // array 不会像 vector 那样自动初始化为 0
		for(int i = n - 1; i >= 0; --i) {
			dp[0] = max(dp[0], dp[1] - prices[i]);
			dp[1] = max(dp[1], dp[2] + prices[i]);
			dp[2] = max(dp[2], dp[3] - prices[i]);
			dp[3] = max(dp[3], 0 + prices[i]);
		}
		return dp[0];
	}
}; // 状态压缩

int main() {
	Solution sol;
	vector<int> a { 3, 3, 5, 0, 0, 3, 1, 4 };
	cout << sol.maxProfit(a);
}