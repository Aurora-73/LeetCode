// Created: 2025-05-26
#include "MyUtils.hpp"

/*746. 使用最小花费爬楼梯
给你一个整数数组 cost ，其中 cost[i] 是从楼梯第 i 个台阶向上爬需要支付的费用。
一旦你支付此费用，即可选择向上爬一个或者两个台阶。
你可以选择从下标为 0 或下标为 1 的台阶开始爬楼梯。
请你计算并返回达到楼梯顶部的最低花费。*/

class Solution1 {
public:
	int minCostClimbingStairs(vector<int> &cost) {
		int n = cost.size();
		vector<int> cost2end(n + 2);
		cost2end[n - 1] = cost2end[n - 2] = 0;
		for(int i = n - 1; i >= 0; --i) {
			cost2end[i] = cost[i] + min(cost2end[i + 1], cost2end[i + 2]);
		}
		return cost2end[0];
	}
};

class Solution {
public:
	int minCostClimbingStairs(vector<int> &cost) {
		int n = cost.size();
		int prepre = 0, pre = 0, now;
		for(int i = n - 1; i >= 0; --i) {
			now = cost[i] + min(prepre, pre);
			prepre = pre;
			pre = now;
		}
		return min(prepre, pre);
	}
};

int main() {
	Solution sol;
}