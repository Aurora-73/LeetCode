// Created: 2025-06-06
#include "MyUtils.hpp"

/*714. 买卖股票的最佳时机含手续费
给定一个整数数组 prices，其中 prices[i]表示第 i 天的股票价格 ；整数 fee 代表了交易股票的手续费用。
你可以无限次地完成交易，但是你每笔交易都需要付手续费。如果你已经购买了一个股票，在卖出它之前你就不能再继续购买股票了。
返回获得利润的最大值。
注意：这里的一笔交易指买入持有并卖出股票的整个过程，每笔交易你只需要为支付一次手续费。
示例 1：
    输入：prices = [1, 3, 2, 8, 4, 9], fee = 2
    输出：8
    解释：能够达到的最大利润:  
    在此处买入 prices[0] = 1
    在此处卖出 prices[3] = 8
    在此处买入 prices[4] = 4
    在此处卖出 prices[5] = 9
    总利润: ((8 - 1) - 2) + ((9 - 4) - 2) = 8*/

class Solution1 {
public:
	int maxProfit(vector<int> &prices, int fee) {
		int n = prices.size();
		vector<int> notHave(n), have(n);
		have.back() = prices.back();
		for(int i = n - 2; i >= 0; --i) {
			notHave[i] = max(notHave[i + 1], have[i + 1] - prices[i] - fee);
			have[i] = max(have[i + 1], notHave[i + 1] + prices[i]);
		}
		return notHave[0];
	}
};

class Solution {
public:
	int maxProfit(vector<int> &prices, int fee) {
		int n = prices.size(), notHave = 0, have = prices.back(), notHave_pre, have_pre;
		// 给 notHave 和 have 赋值，防止仅有一个元素的时候返回未定义的值
		for(int i = n - 2; i >= 0; --i) {
			notHave_pre = notHave;
			have_pre = have;
			notHave = max(notHave_pre, have_pre - prices[i] - fee);
			have = max(have_pre, notHave_pre + prices[i]);
		}
		return notHave;
	}
};

class Solution {
public:
	int maxProfit(vector<int> &prices, int fee) {
		int n = prices.size();
		int buy = prices[0] + fee;
		int profit = 0;
		for(int i = 1; i < n; ++i) {
			if(prices[i] + fee < buy) {
				buy = prices[i] + fee;
			} else if(prices[i] > buy) {
				profit += prices[i] - buy;
				buy = prices[i];
			}
		}
		return profit;
	}
};

int main() {
	Solution sol;
}