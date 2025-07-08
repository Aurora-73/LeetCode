// Created: 2025-07-08
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 2462. 雇佣 K 位工人的总代价
给你一个下标从 0开始的整数数组costs，其中costs{i}是雇佣第 i位工人的代价。
同时给你两个整数k 和candidates。我们想根据以下规则恰好雇佣k位工人：
	总共进行k轮雇佣，且每一轮恰好雇佣一位工人。
	在每一轮雇佣中，从最前面 candidates和最后面 candidates人中选出代价最小的一位工人，
如果有多位代价相同且最小的工人，选择下标更小的一位工人。
		比方说，costs = {3,2,7,7,1,2} 且candidates = 2，
第一轮雇佣中，我们选择第4位工人，因为他的代价最小{3,2,7,7,1,2}。
		第二轮雇佣，我们选择第1位工人，因为他们的代价与第4位工人一样都是最小代价，
而且下标更小，{3,2,7,7,2}。注意每一轮雇佣后，剩余工人的下标可能会发生变化。
	如果剩余员工数目不足 candidates人，那么下一轮雇佣他们中代价最小的一人，
如果有多位代价相同且最小的工人，选择下标更小的一位工人。
	一位工人只能被选择一次。
返回雇佣恰好k位工人的总代价。
示例 1：
	输入：costs = {17,12,10,2,7,2,11,20,8}, k = 3, candidates = 4
	输出：11
	解释：我们总共雇佣 3 位工人。总代价一开始为 0。
	- 第一轮雇佣，我们从 {17,12,10,2,2,11,20,8} 中选择。最小代价是 2，
	有两位工人，我们选择下标更小的一位工人，即第 3 位工人。总代价是 0 + 2 = 2。
	- 第二轮雇佣，我们从 {17,12,10,7,2,11,20,8} 中选择。
	最小代价是 2，下标为 4，总代价是 2 + 2 = 4。
	- 第三轮雇佣，我们从 {17,12,10,7,11,20,8} 中选择，最小代价是 7，下标为 3，
	总代价是 4 + 7 = 11。注意下标为 3 的工人同时在最前面和最后面 4 位工人中。
	总雇佣代价是 11。
示例 2：
	输入：costs = {1,2,4,1}, k = 3, candidates = 3
	输出：4
	解释：我们总共雇佣 3 位工人。总代价一开始为 0。
	- 第一轮雇佣，我们从 {1,2,4,1} 中选择。最小代价为 1，有两位工人，我们选择下标更小的一位工人，
	即第 0 位工人，总代价是 0 + 1 = 1。注意，下标为 1 和 2 的工人同时在最前面和最后面 3 位工人中。
	- 第二轮雇佣，我们从 {2,4,1} 中选择。最小代价为 1，下标为 2，总代价是 1 + 1 = 2。
	- 第三轮雇佣，少于 3 位工人，我们从剩余工人 {2,4} 中选择。最小代价是 2，下标为 0。总代价为 2 + 2 = 4。
	总雇佣代价是 4。
提示：
	1 <= costs.length <= 10^5 
	1 <= costs{i} <= 10^5
	1 <= k, candidates <= costs.length */

class Solution1 {
public:
	long long totalCost(vector<int> &costs, int k, int candidates) {
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
		long long res = 0;
		int n = costs.size(), l = 0, r = n - 1;
		for(int i = 0; i < candidates; ++i) {
			if(l <= r) {
				pq.emplace(costs[l], l);
				++l;
				if(l <= r) {
					pq.emplace(costs[r], r);
					--r;
				}
			}
		}
		for(int i = 0; i < k; ++i) {
			auto [cost, index] = pq.top();
			pq.pop();
			res += cost;
			if(l <= r) {
				if(index < l) {
					pq.emplace(costs[l], l);
					++l;
				} else if(index > r) {
					pq.emplace(costs[r], r);
					--r;
				}
			}
		}
		return res;
	}
}; // 同时保存值和下标，使用l r 防止重复放置

class Solution {
public:
	long long totalCost(vector<int> &costs, int k, int candidates) {
		int n = costs.size(), l = 0, r = n - 1;
		if(candidates * 2 + k > n) {
			ranges::nth_element(costs, costs.begin() + k);
			return accumulate(costs.begin(), costs.begin() + k, 0LL);
		}
		priority_queue<int, vector<int>, greater<>> left, right;
		long long res = 0;
		for(int i = 0; i < candidates; ++i) {
			if(l <= r) {
				left.push(costs[l]);
				++l;
				if(l <= r) {
					right.push(costs[r]);
					--r;
				}
			}
		}
		for(int i = 0; i < k; ++i) {
			if(left.top() <= right.top()) {
				res += left.top();
				left.pop();
				if(l <= r) {
					left.push(costs[l]);
					++l;
				}
			} else {
				res += right.top();
				right.pop();
				if(l <= r) {
					right.push(costs[r]);
					--r;
				}
			}
		}
		return res;
	}
};

int main() {
	Solution sol;
	vector<int> costs;
	int k, candidates;
	costs = { 31, 25, 72, 79, 74, 65, 84, 91, 18, 59, 27, 9, 81, 33, 17, 58 };
	k = 11, candidates = 2;
	cout << sol.totalCost(costs, k, candidates) << endl; // 423
	costs = { 17, 12, 10, 2, 7, 2, 11, 20, 8 }, k = 3, candidates = 4;
	cout << sol.totalCost(costs, k, candidates) << endl; // 11
	costs = { 1, 2, 4, 1 }, k = 3, candidates = 3;
	cout << sol.totalCost(costs, k, candidates) << endl; // 4
}