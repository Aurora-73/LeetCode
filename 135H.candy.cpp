// Created: 2025-05-25
#include "MyUtils.h"

/*135. 分发糖果
n 个孩子站成一排。给你一个整数数组 ratings 表示每个孩子的评分。
你需要按照以下要求，给这些孩子分发糖果：
每个孩子至少分配到 1 个糖果。
相邻两个孩子评分更高的孩子会获得更多的糖果。
请你给每个孩子分发糖果，计算并返回需要准备的 最少糖果数目 。*/

class Solution {
public:
	int candy(vector<int> &ratings) {
		int n = ratings.size(), sum = n;
		vector<int> candy(n);
		for(int i = 1; i < n; ++i) {
			if(ratings[i] > ratings[i - 1]) {
				candy[i] = candy[i - 1] + 1;
			}
		}
		for(int i = n - 2; i >= 0; --i) {
			if(ratings[i] > ratings[i + 1]) {
				candy[i] = max(candy[i + 1] + 1, candy[i]);
			}
		}
		for(auto &x : candy) {
			sum += x;
		}
		return sum;
	}
};

int main() {
	Solution sol;
}