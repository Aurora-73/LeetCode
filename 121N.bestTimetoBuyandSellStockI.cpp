// Created: 2025-05-24
#include "MyUtils.hpp"

/* 121. 买卖股票的最佳时机
给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。
你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。设计一个算法来计算你所能获取的最大利润。
返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0。*/

class Solution1 {
public:
	int maxProfit(vector<int> &prices) {
		return dfs(prices, 0, false);
	}

private:
	int dfs(vector<int> &prices, int day, bool has_stock) {
		if(day >= (int)prices.size()) return 0;
		int keep, move;
		if(!has_stock) { // 当前未持股：可以选择今天买入，或跳过
			keep = dfs(prices, day + 1, false);
			move = dfs(prices, day + 1, true) - prices[day];
		} else { // 当前已持股（已经买入）：只能选择今天卖出，或继续持有
			keep = dfs(prices, day + 1, true);
			move = prices[day];
		}
		return max(keep, move);
	}
}; // 从第 day 天开始，在当前是否持股为 has_stock 的状态下，所能获得的“最大利润”。如果已经持有，不考虑持有的成本

class Solution2 {
public:
	int maxProfit(vector<int> &prices) {
		n = prices.size();
		memo.resize(n, { numeric_limits<int>::max(), numeric_limits<int>::max() });
		return dfs(prices, 0, false);
	}

private:
	int n;
	vector<array<int, 2>> memo;
	int dfs(vector<int> &prices, int day, bool has_stock) {
		if(day >= n) return 0;
		if(memo[day][has_stock] == numeric_limits<int>::max()) {
			int keep, move;
			if(!has_stock) {
				keep = dfs(prices, day + 1, false);
				move = dfs(prices, day + 1, true) - prices[day];
			} else {
				keep = dfs(prices, day + 1, true);
				move = prices[day];
			}
			memo[day][has_stock] = max(keep, move);
		}
		return memo[day][has_stock];
	}
}; // 记忆化存储

class Solution3 {
public:
	int maxProfit(vector<int> &prices) {
		int n = prices.size();
		vector<array<int, 2>> dp(n + 1);
		dp.back().fill(0);

		for(int i = n - 1; i >= 0; --i) {
			dp[i][0] = max(dp[i + 1][0], dp[i + 1][1] - prices[i]);
			dp[i][1] = max(prices[i], dp[i + 1][1]);
		}
		return dp[0][0];
	}
}; // 动态规划

class Solution4 {
public:
	int maxProfit(vector<int> &prices) {
		int profit_no_stock = 0, profit_have_stock = 0;
		for(int i = prices.size() - 1; i >= 0; --i) {
			profit_no_stock = max(profit_no_stock, profit_have_stock - prices[i]);
			profit_have_stock = max(prices[i], profit_have_stock);
		}
		return profit_no_stock;
	}
}; // 压缩为 profit_no_stock 和 profit_have_stock

class Solution {
public:
	int maxProfit(vector<int> &prices) {
		int minprice = numeric_limits<int>::max(), maxprofit = 0;
		for(int price : prices) {
			if(price > minprice) {
				maxprofit = max(maxprofit, price - minprice);
			} else {
				minprice = price;
			}
		}
		return maxprofit;
	}
};
/* 显然，如果我们真的在买卖股票，我们肯定会想：如果我是在历史最低点买的股票就好了！
太好了，在题目中，我们只要用一个变量记录一个历史最低价格 minprice，我们就可以假设自己的股票是在那天买的。
那么我们在第 i 天卖出股票能得到的利润就是 prices[i] - minprice。
因此，我们只需要遍历价格数组一遍，记录历史最低点，然后在每一天考虑这么一个问题：
如果我是在历史最低点买进的，那么我今天卖出能赚多少钱？当考虑完所有天数之时，我们就得到了最好的答案。*/

int main() {
	Solution sol;
	vector<int> a { 1, 2, 3, 1, 2, 3, 5, 4, 6 };
	cout << sol.maxProfit(a);
}