// Created: 2025-06-06
#include "MyDateGen.h"
#include "MyUtils.hpp"

/* Q2. 买卖股票的最佳时机 V
给你一个整数数组 prices，其中 prices{i} 是第 i 天股票的价格（美元），以及一个整数 k。
你最多可以进行 k 笔交易，每笔交易可以是以下任一类型：
普通交易：在第 i 天买入，然后在之后的第 j 天卖出，其中 i < j。你的利润是 prices{j} - prices{i}。
做空交易：在第 i 天卖出，然后在之后的第 j 天买回，其中 i < j。你的利润是 prices{i} - prices{j}。
注意：你必须在开始下一笔交易之前完成当前交易。此外，你不能在已经进行买入或卖出操作的同一天再次进行买入或卖出操作。
	通过进行 最多 k 笔交易，返回你可以获得的最大总利润。
	示例 1:
	输入: prices = {1,7,9,8,2}, k = 2
	输出: 14
	解释:
	我们可以通过 2 笔交易获得 14 美元的利润：
	一笔普通交易：第 0 天以 1 美元买入，第 2 天以 9 美元卖出。
	一笔做空交易：第 3 天以 8 美元卖出，第 4 天以 2 美元买回。
	示例 2:
	输入: prices = {12,16,19,19,8,1,19,13,9}, k = 3
	输出: 36
	解释:
	我们可以通过 3 笔交易获得 36 美元的利润：
	一笔普通交易：第 0 天以 12 美元买入，第 2 天以 19 美元卖出。
	一笔做空交易：第 3 天以 19 美元卖出，第 4 天以 8 美元买回。
	一笔普通交易：第 5 天以 1 美元买入，第 6 天以 19 美元卖出。
提示:
	2 <= prices.length <= 10^3
	1 <= prices{i} <= 10^9
	1 <= k <= prices.length / 2*/

class Solution1 {
public:
	long long maximumProfit(vector<int> &prices, int k) {
		this->k = k, n = prices.size();
		memo.assign(n + 1,
		    vector<vector<long long>>(
		        k + 1, vector<long long>(3, numeric_limits<long long>::min())));
		return dfs(prices, 0, 0, 0);
	}

private:
	int n, k;
	vector<vector<vector<long long>>> memo;
	long long dfs(vector<int> &prices, int day, int times, int state) {
		// times：表示已经完成了几笔交易
		// state: 0：可以开始新的交易 	1：已经买入，没有卖出（普通）
		// 2：已经卖出，没有买入（做空） 3：处于冷却期
		if(day >= n || times == k) return 0;
		if(memo[day][times][state] != numeric_limits<long long>::min())
			return memo[day][times][state];
		long long res = dfs(prices, day + 1, times, state); // 不操作

		if(state == 0) {
			// 普通买入
			res = max(res, dfs(prices, day + 1, times, 1) - prices[day]);
			// 做空卖出
			res = max(res, dfs(prices, day + 1, times, 2) + prices[day]);
		} else if(state == 1) {
			// 普通卖出，完成一次交易
			res = max(res, dfs(prices, day + 1, times + 1, 3) + prices[day]);
		} else if(state == 2) {
			// 做空买回，完成一次交易
			res = max(res, dfs(prices, day + 1, times + 1, 3) - prices[day]);
		}
		memo[day][times][state] = res;
		return res;
	}
};

class Solution {
public:
	long long maximumProfit(vector<int> &prices, int k) {
		this->k = k, n = prices.size();
		memo.assign(n,
		    vector<vector<long long>>(
		        k + 1, vector<long long>(3, numeric_limits<long long>::min())));
		return dfs(prices, 0, 0, 0);
	}

private:
	int n, k;
	vector<vector<vector<long long>>> memo;
	long long dfs(vector<int> &prices, int day, int times, int state) {
		if(day == n - 1 && state == 0) {
			return 0;
		}
		if(day == n - 1 && state == 2) {
			return -prices.back();
		}
		if(day >= n || times == k) return 0;
		if(memo[day][times][state] != numeric_limits<long long>::min())
			return memo[day][times][state];
		long long res = dfs(prices, day + 1, times, state); // 不操作

		if(state == 0) {
			// 普通买入
			res = max(res, dfs(prices, day + 1, times, 1) - prices[day]);
			// 做空卖出
			res = max(res, dfs(prices, day + 1, times, 2) + prices[day]);

		} else if(state == 1) {
			// 普通卖出，完成一次交易
			res = max(res, dfs(prices, day + 1, times + 1, 0) + prices[day]);
		} else if(state == 2) {
			// 做空买回，完成一次交易
			res = max(res, dfs(prices, day + 1, times + 1, 0) - prices[day]);
		}
		memo[day][times][state] = res;
		return res;
	}
};

int main() {
	Solution sol;
	vector<int> prices;
	int k;
	prices = { 1, 7, 9, 8, 2 }, k = 2;
	cout << sol.maximumProfit(prices, k) << endl;
	prices = { 12, 16, 19, 19, 8, 1, 19, 13, 9 }, k = 3;
	cout << sol.maximumProfit(prices, k) << endl;
}