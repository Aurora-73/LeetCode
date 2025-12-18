// Created: 2025-12-18
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定不同面额的硬币 coins 和一个总金额 amount。
编写一个函数来计算可以凑成总金额所需的最少的硬币个数。如果没有任何一种硬币组合能组成总金额，返回-1。
你可以认为每种硬币的数量是无限的。
示例1：
    输入：coins = {1, 2, 5}, amount = 11
    输出：3 
    解释：11 = 5 + 5 + 1
示例 2：
	输入：coins = {2}, amount = 3
	输出：-1
示例 3：
	输入：coins = {1}, amount = 0
	输出：0
示例 4：
	输入：coins = {1}, amount = 1
	输出：1
示例 5：
	输入：coins = {1}, amount = 2
	输出：2
提示：
	1 <= coins.length <= 12
	1 <= coins{i} <= 2^31 - 1
	0 <= amount <= 10^4 */

class Solution1 {
public:
	int coinChange(vector<int> &coins, int amount) {
		int n = coins.size();
		vector<vector<int>> dp(n + 1, vector<int>(amount + 1, -1));
		for(int i = 0; i < n + 1; ++i) dp[i][0] = 0;
		for(int i = 1; i < n + 1; ++i) {
			for(int j = 1; j < amount + 1; ++j) {
				int min_cost = -1;
				for(int k = 0; k * coins[i - 1] <= j; ++k) {
					int prev = dp[i - 1][j - coins[i - 1] * k];
					if(min_cost == -1 && prev != -1) {
						min_cost = prev + k;
					} else if(prev != -1) {
						min_cost = min(min_cost, prev + k);
					}
				}
				dp[i][j] = min_cost;
			}
		}
		return dp.back().back();
	}
}; // dp[i][j]: 用前i个硬币，兑换j元需要的最小数目， dp[i][j] = min({dp[i - 1][j - coins[i - 1] * k]  + k});

class Solution2 {
public:
	int coinChange(vector<int> &coins, int amount) {
		int n = coins.size();
		vector<vector<int>> dp(n + 1, vector<int>(amount + 1, amount + 1));
		for(int i = 0; i < n + 1; ++i) dp[i][0] = 0;
		for(int i = 1; i < n + 1; ++i) {
			for(int j = 1; j < amount + 1; ++j) {
				if(j >= coins[i - 1])
					dp[i][j] = min(dp[i - 1][j], dp[i][j - coins[i - 1]] + 1);
				else
					dp[i][j] = dp[i - 1][j];
			}
		}
		cout << dp << endl;
		return dp.back().back() > amount ? -1 : dp.back().back();
	}
}; // 完全dp只需要可以取元素是递归到 dp[i][..] 而非 dp[i - 1][..] 即可实现重复多次选一个硬币，不需要真的遍历取到的次数

class Solution {
public:
	int coinChange(vector<int> &coins, int amount) {
		int n = coins.size();
		vector<int> dp(amount + 1, amount + 1);
		dp[0] = 0;
		for(int i = 1; i < n + 1; ++i) {
			for(int j = 1; j < amount + 1; ++j) {
				if(j >= coins[i - 1])
					dp[j] = min(dp[j], dp[j - coins[i - 1]] + 1);
				else
					dp[j] = dp[j];
			} // 某个元素的值依赖同行左侧的值（从左往右遍历，因为要用到），而非上一行左侧的值（从右往左遍历，防止复写）
		}
		return dp.back() > amount ? -1 : dp.back();
	}
}; // 一维数组 + 倒序遍历优化

int main() {
	Solution sol;
	vector<int> coins;
	int amount;
	coins = { 1, 2, 5 }, amount = 11;
	cout << sol.coinChange(coins, amount) << endl;
	coins = { 2 }, amount = 3;
	cout << sol.coinChange(coins, amount) << endl;
	coins = { 1 }, amount = 0;
	cout << sol.coinChange(coins, amount) << endl;
	coins = { 1 }, amount = 1;
	cout << sol.coinChange(coins, amount) << endl;
	coins = { 1 }, amount = 2;
	cout << sol.coinChange(coins, amount) << endl;
}