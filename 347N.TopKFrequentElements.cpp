// Created: 2025-06-15
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 347. 前 K 个高频元素
给你一个整数数组 nums 和一个整数 k，请你返回其中出现频率前 k 高的元素。
你可以按 任意顺序 返回答案。
示例 1:
	输入: nums = {1,1,1,2,2,3}, k = 2
	输出: {1,2}
示例 2:
	输入: nums = {1}, k = 1
	输出: {1}
提示：
	1 <= nums.length <= 10^5
	k 的取值范围是 {1, 数组中不相同的元素的个数}
	题目数据保证答案唯一，换句话说，数组中前 k 个高频元素的集合是唯一的
	进阶：你所设计算法的时间复杂度 必须 优于 O(n log n)，其中 n是数组大小。 */

class Solution1 {
public:
	vector<int> topKFrequent(vector<int> &nums, int k) {
		unordered_map<int, int> count;
		for(auto n : nums) {
			++count[n];
		}
		auto cmp = [](const pair<int, int> &a, const pair<int, int> &b) {
			return a.second > b.second;
		};
		priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);
		for(auto &pair : count) {
			if(int(pq.size()) < k) {
				pq.push(pair);
			} else if(pair.second > pq.top().second) {
				pq.pop();
				pq.push(pair);
			}
		}
		vector<int> res;
		res.reserve(k);
		while(!pq.empty()) {
			res.push_back(pq.top().first);
			pq.pop();
		}
		return res;
	}
}; // O(N logk)

class Solution {
public:
	vector<int> topKFrequent(vector<int> &nums, int k) {
		unordered_map<int, int> count;
		int max_count = 0;
		for(auto n : nums) {
			auto &val = count[n];
			++val;
			max_count = max(max_count, val);
		}
		vector<vector<int>> bucket(max_count + 1);
		for(auto &[n, c] : count) {
			bucket[c].push_back(n);
		}
		vector<int> res;
		res.reserve(k);
		for(auto it = bucket.rbegin(); it != bucket.rend() && k > 0; ++it) {
			k -= it->size();
			for(auto n : *it) {
				res.push_back(n);
			}
		}
		return res;
	}
};

int main() {
	Solution sol;
	vector<int> nums;
	int k;
	nums = { 1, 1, 1, 2, 2, 3 }, k = 2;
	cout << sol.topKFrequent(nums, k) << endl; // {1,2}
	nums = { 1 }, k = 1;
	cout << sol.topKFrequent(nums, k) << endl; // {1}
}