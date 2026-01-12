// Created: 2025-05-14
#include "MyUtils.hpp"

/*53. 最大子数组和
给你一个整数数组 nums，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
子数组 是数组中的一个连续部分。
示例 1：
	输入：nums = {-2,1,-3,4,-1,2,1,-5,4}
	输出：6
	解释：连续子数组{4,-1,2,1} 的和最大，为6。
示例 2：
	输入：nums = {1}
	输出：1
示例 3：
	输入：nums = {5,4,-1,7,8}
	输出：23
提示：
	1 <= nums.length <= 10^5
	-10^4 <= nums{i} <= 10^4
	进阶：如果你已经实现复杂度为 O(n) 的解法，尝试使用更为精妙的 分治法 求解。*/

class Solution1 {
public:
	int maxSubArray(vector<int> &nums) {
		int n = nums.size(), res = INT_MIN;
		vector<int> dp(n + 1);
		for(int i = 1; i < n + 1; ++i) {
			dp[i] = max(dp[i - 1], 0) + nums[i - 1];
			res = max(res, dp[i]);
		}
		return res;
	}
}; // dp[i]的含义以第i个数结尾的最大连续子数组和，注意不能返回dp.back()

class Solution {
public:
	int maxSubArray(vector<int> &nums) {
		int n = nums.size(), res = INT_MIN, prev_sum = 0;
		for(int i = 0; i < n; ++i) {
			prev_sum = max(prev_sum, 0);
			prev_sum += nums[i];
			res = max(res, prev_sum);
		}
		return res;
	}
}; // 贪心，如果前一个最大子数组小于0就直接抛弃，反之则保留，依次计算以第i个数结尾的最大连续子数组和

int main() {
	Solution sol;
	vector<int> nums;
	nums = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
	cout << sol.maxSubArray(nums) << endl;

	nums = { 1 };
	cout << sol.maxSubArray(nums) << endl;

	nums = { 5, 4, -1, 7, 8 };
	cout << sol.maxSubArray(nums) << endl;
}