// Created: 2025-05-24
#include "MyUtils.h"

/* 121. 买卖股票的最佳时机
给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。
你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。设计一个算法来计算你所能获取的最大利润。
返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0。*/

class Solution1 {
public:
	int maxProfit(vector<int> &prices) {
		int max_diff = 0;
		for(size_t i = 0; i < prices.size(); ++i) {
			for(size_t j = i + 1; j < prices.size(); j++) {
				max_diff = max(prices[j] - prices[i], max_diff);
			}
		}
		return max_diff;
	}
}; // 求 max(prices[j] - prices[i]) 0 <= i <= j < n

class Solution2 {
public:
	int maxProfit(vector<int> &prices) {
		n = prices.size();
		return dfs(prices, 0, -1);
	}

private:
	int n, max_pro = 0;
	int dfs(vector<int> &prices, int day, int paied) {
		if(day >= n) {
			return 0;
		}
		bool buyed = paied != -1;
		if(buyed) {
			return max(dfs(prices, day + 1, paied), prices[day] - paied);
		}
		if(!buyed) {
			return max(dfs(prices, day + 1, paied), dfs(prices, day + 1, prices[day]));
		}
		return 0;
	}
};

struct pair_hash {
	size_t operator()(const pair<int, int> &p) const noexcept {
		// 简单地把两个 int 拼成一个 size_t ( int 32位，size_t 64位，直接拼接即可 )
		return ((size_t)p.first << 32) ^ (size_t)p.second;
	}
};

class Solution3 {
public:
	int maxProfit(vector<int> &prices) {
		n = prices.size();
		return dfs(prices, 0, -1);
	}

private:
	int n, max_pro = 0;
	unordered_map<pair<int, int>, int, pair_hash> profits;
	int dfs(vector<int> &prices, int day, int paied) {
		if(day >= n) {
			return 0;
		}
		auto it = profits.find({ day, paied });
		if(it != profits.end()) {
			return it->second;
		}
		int now;
		if(paied != -1) {
			now = max(dfs(prices, day + 1, paied), prices[day] - paied);
		} else {
			now = max(dfs(prices, day + 1, paied), dfs(prices, day + 1, prices[day]));
		}
		profits[{ day, paied }] = now;
		return now;
	}
};

class Solution4 {
public:
	int maxProfit(vector<int> &prices) {
		int n = prices.size();
		if(n == 0) return 0;

		vector<int> dp(n, 0);      // dp[i] 表示第 i 天卖出的最大利润
		int min_price = prices[0]; // 第 0 天作为初始最小价格

		for(int i = 1; i < n; ++i) {
			dp[i] = max(dp[i - 1], prices[i] - min_price);
			min_price = min(min_price, prices[i]);
		}

		return dp[n - 1]; // 返回最后一天的最大利润
	}
};

class Solution {
public:
	int maxProfit(vector<int> &prices) {
		int minprice = INT_MAX, maxprofit = 0;
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
	vector<int> a { 1, 2 };
	cout << sol.maxProfit(a);
}