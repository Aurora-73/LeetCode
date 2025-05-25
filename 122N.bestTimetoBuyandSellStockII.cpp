// Created: 2025-05-25
#include "MyUtils.h"

/*122. 买卖股票的最佳时机 II
给你一个整数数组 prices ，其中 prices[i] 表示某支股票第 i 天的价格。
在每一天，你可以决定是否购买和/或出售股票。
你在任何时候 最多 只能持有 一股 股票。你也可以先购买，然后在 同一天 出售。
返回 你能获得的 最大 利润 。*/

class Solution {
public:
	int maxProfit(vector<int> &prices) {
		int sum = 0, n = prices.size();
		for(int i = 1; i < n; ++i) {
			sum += max(prices[i] - prices[i - 1], 0);
		}
		return sum;
	}
};

int main() {
	Solution sol;
}