// Created: 2026-01-03
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个整数数组，找出总和最大的连续数列，并返回总和。
示例：
输入： {-2,1,-3,4,-1,2,1,-5,4}
输出： 6
解释： 连续子数组 {4,-1,2,1} 的和最大，为 6。
进阶：
如果你已经实现复杂度为 O(n) 的解法，尝试使用更为精妙的分治法求解。 */

class Solution {
public:
	int maxSubArray(vector<int> &nums) {
		int best_begin_sum = 0, curr_all_sum = 0, n = nums.size(), res = INT_MIN;
		for(int i = 0; i < n; ++i) {
			curr_all_sum += nums[i];
			if(curr_all_sum - best_begin_sum > res) {
				res = curr_all_sum - best_begin_sum;
			}
			if(curr_all_sum < best_begin_sum) {
				best_begin_sum = curr_all_sum;
			}
		}
		return res;
	}
}; // 从左往右遍历，curr_all_sum记录当前的前缀和，best_begin_sum记录最好的开始位置的前缀和
// 结果就是最好的结束位置的前缀和-最好的开始位置的前缀和，所谓的最好的开始位置即前缀和最小的位置

int main() {
	Solution sol;
	vector<int> nums;
	nums = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
	cout << sol.maxSubArray(nums) << endl;
}