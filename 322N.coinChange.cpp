// Created: 2025-05-22
#include "MyUtils.hpp"

/*   322. 零钱兑换
给你一个整数数组 coins ，表示不同面额的硬币；以及一个整数 amount ，表示总金额。
计算并返回可以凑成总金额所需的 最少的硬币个数 。如果没有任何一种硬币组合能组成总金额，返回 -1 。
你可以认为每种硬币的数量是无限的。1 <= coins.length <= 12
1 <= coins[i] <= 2^31 - 1
0 <= amount <= 10^4 */

class Solution1 {
public:
	int coinChange(vector<int> &coins, int amount) {
		sort(coins.begin(), coins.end());
		return dfs(coins, amount);
	}

private:
	int dfs(vector<int> &coins, int amount) {
		if(amount == 0) return 0;
		int min_count = -1;
		for(auto x : coins) {
			if(amount == x) {
				min_count = 1;
				break;
			} else if(amount < x) {
				break;
			} else {
				int child = dfs(coins, amount - x);
				if(child != -1 && (min_count == -1 || min_count > child + 1)) {
					min_count = child + 1;
				}
			}
		}
		return min_count;
	}
};

class Solution2 {
public:
	int coinChange(vector<int> &coins, int amount) {
		sort(coins.begin(), coins.end());
		min_count.resize(amount + 1, -1);
		return dfs(coins, amount);
	}

private:
	vector<int> min_count;
	int dfs(vector<int> &coins, int amount) {
		if(amount == 0) return 0;
		if(min_count[amount] != -1) return min_count[amount];
		int now = -1;
		for(auto x : coins) {
			if(amount == x) {
				now = 1;
				break;
			} else if(amount < x) {
				break;
			} else {
				int child = dfs(coins, amount - x);
				if(child != -1 && (now == -1 || now > child + 1)) {
					now = child + 1;
				}
			}
		}
		min_count[amount] = now;
		return now;
	}
}; // 记忆化存储

class Solution3 {
public:
	int coinChange(vector<int> &coins, int amount) {
		vector<int> min_count(amount + 1, -1);
		min_count[amount] = 0;
		for(int i = amount - 1; i >= 0; --i) {
			for(auto x : coins) {
				if(i <= amount - x && min_count[x + i] != -1) { // 用减法而不是加法，防止溢出
					if(min_count[i] == -1 || min_count[i] > min_count[x + i] + 1)
						min_count[i] = min_count[x + i] + 1;
				}
			}
		}
		return min_count[0];
	}
}; // 逆序计算，不再递归
// 没有必要剪枝，剪枝也没有动态规划快

class Solution4 {
public:
	int coinChange(vector<int> &coins, int amount) {
		vector<int> f(amount + 1, INT_MAX >> 1);
		f[0] = 0;
		for(const auto &x : coins) {
			for(int v = x; v <= amount; v++) {
				f[v] = min(f[v], f[v - x] + 1);
			}
		}
		if(f[amount] > amount) f[amount] = -1;
		return f[amount];
	}
}; // 先对硬币进行变量后对 dp 数组进行遍历 提高缓存命中率

int main() {
	Solution sol;
	vector<int> coins = { 1, 2, 5 };
	int amount = 11;
	sol.coinChange(coins, amount);
}