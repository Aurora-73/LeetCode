// Created: 2025-06-13
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 2616. 最小化数对的最大差值
给你一个下标从 0开始的整数数组nums和一个整数p。
请你从nums中找到p 个下标对，每个下标对对应数值取差值，
你需要使得这 p 个差值的最大值最小。同时，你需要确保每个下标在这p个下标对中最多出现一次。
对于一个下标对i和j，这一对的差值为|nums{i} - nums{j}|，其中|x|表示 x的 绝对值。
请你返回 p个下标对对应数值 最大差值的 最小值。
示例 1：
	输入：nums = {10,1,2,7,1,3}, p = 2
	输出：1
	解释：第一个下标对选择 1 和 4，第二个下标对选择 2 和 5。
	最大差值为 max(|nums{1} - nums{4}|, |nums{2} - nums{5}|) = max(0, 1) = 1。
	所以我们返回 1。
示例 2：
	输入：nums = {4,2,1,2}, p = 1
	输出：0
	解释：选择下标 1 和 3 构成下标对。差值为 |2 - 2| = 0，这是最大差值的最小值。
提示：
	1 <= nums.length <= 10 ^ 5
	0 <= nums{i} <= 10 ^ 9
	0 <= p <= (nums.length)/2 */

class Solution {
public:
	int minimizeMax(vector<int> &nums, int p) {
		sort(nums.begin(), nums.end());
		auto check = [&](int mx) -> bool {
			int cnt = 0;
			for(int i = 0; i < nums.size() - 1; i++) {
				if(nums[i + 1] - nums[i] <= mx) {
					cnt++;
					i++;
				}
			}
			return cnt >= p;
		};
		int left = 0, right = nums.back() - nums[0];
		while(left < right) {
			int mid = (left + right) >> 1;
			if(check(mid)) {
				right = mid;
			} else {
				left = mid + 1;
			}
		}
		return left;
	}
}; // 还没搞懂

int main() {
	Solution sol;
	vector<int> nums;
	int p;
	nums = { 10, 1, 2, 7, 1, 3 }, p = 2;
	cout << sol.minimizeMax(nums, p) << endl; // 1
	nums = { 4, 2, 1, 2 }, p = 1;
	cout << sol.minimizeMax(nums, p) << endl; // 0
}