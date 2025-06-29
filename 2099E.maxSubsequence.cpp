// Created: 2025-06-28
#include "MyDateGen.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 2099. 找到和最大的长度为 K 的子序列
给你一个整数数组nums和一个整数k。
你需要找到nums中长度为 k的 子序列，且这个子序列的和最大。
请你返回 任意 一个长度为k的整数子序列。
子序列定义为从一个数组里删除一些元素后，不改变剩下元素的顺序得到的数组。
示例 1：
	输入：nums = {2,1,3,3}, k = 2
	输出：{3,3}
	解释：
	子序列有最大和：3 + 3 = 6。
示例 2：
	输入：nums = {-1,-2,3,4}, k = 3
	输出：{-1,3,4}
	解释：
	子序列有最大和：-1 + 3 + 4 = 6。
示例 3：
	输入：nums = {3,4,3,3}, k = 2
	输出：{3,4}
	解释：
	子序列有最大和：3 + 4 = 7。
	另一个可行的子序列为 {4, 3}。
提示：
	1 <= nums.length <= 1000
	-10^5 <= nums{i} <= 10^5
	1 <= k <= nums.length */

class Solution1 {
public:
	vector<int> maxSubsequence(const vector<int> &nums, int k) {
		int n = nums.size();
		vector<int> res;
		res.reserve(n);
		for(int i = 0; i < n; ++i) {
			res.push_back(i);
		}
		std::sort(res.begin(), res.end(), [&](int i, int j) { return nums[i] > nums[j]; });
		res.resize(k);
		std::sort(res.begin(), res.end());
		for(int i = 0; i < k; ++i) {
			res[i] = nums[res[i]];
		}
		return res;
	}
};

class Solution2 {
public:
	vector<int> maxSubsequence(const vector<int> &nums, int k) {
		vector<int> res;
		res.reserve(k);
		auto cmp = [&](int i, int j) {
			return nums[i] > nums[j];
		};
		priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
		for(int i = 0; i < k; ++i) {
			pq.push(i);
		}
		int n = nums.size();
		for(int i = k; i < n; ++i) {
			if(nums[pq.top()] < nums[i]) {
				pq.pop();
				pq.push(i);
			}
		}
		while(!pq.empty()) {
			res.push_back(pq.top());
			pq.pop();
		}
		ranges::sort(res);
		for(int i = 0; i < k; ++i) {
			res[i] = nums[res[i]];
		}
		return res;
	}
};

using namespace chrono;

int main() {
	Solution1 sol1;
	Solution2 sol2;
	// nums = { 2, 1, 3, 3 }, k = 2;
	// cout << sol.maxSubsequence(nums, k) << endl; // {3,3}
	// nums = { -1, -2, 3, 4 }, k = 3;
	// cout << sol.maxSubsequence(nums, k) << endl; // {-1,3,4}
	// nums = { 3, 4, 3, 3 }, k = 2;
	// cout << sol.maxSubsequence(nums, k) << endl; // {3,4}
	std::chrono::duration<double, std::milli> t1(0), t2(0);
	for(int i = 200; i < 1201; ++i) {
		vector<int> nums = randomIntVector(20000, INT_MIN, INT_MAX);
		int k = 2 * i;
		auto b = std::chrono::system_clock::now();
		auto res1 = sol1.maxSubsequence(nums, k);
		auto e = std::chrono::system_clock::now();
		t1 += e - b;
		b = std::chrono::system_clock::now();
		auto res2 = sol2.maxSubsequence(nums, k);
		e = std::chrono::system_clock::now();
		t2 += e - b;
	}
	cout << "sol1: " << t1.count() << "ms" << endl;
	cout << "sol2: " << t2.count() << "ms" << endl;
}
