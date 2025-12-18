// Created: 2025-12-18
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个正整数数组 nums 和一个整数 target。
向数组中的每个整数前添加"+" 或 "-"，然后串联起所有整数，可以构造一个 表达式 ：
	例如，nums = {2, 1}，可以在 2 之前添加 "+"，在 1 之前添加 "-"，然后串联起来得到表达式 "+2-1"。
返回可以通过上述方法构造的、运算结果等于 target 的不同 表达式 的数目。
示例 1：
	输入：nums = {1,1,1,1,1}, target = 3
	输出：5
	解释：一共有 5 种方法让最终目标和为 3。
	-1 + 1 + 1 + 1 + 1 = 3
	+1 - 1 + 1 + 1 + 1 = 3
	+1 + 1 - 1 + 1 + 1 = 3
	+1 + 1 + 1 - 1 + 1 = 3
	+1 + 1 + 1 + 1 - 1 = 3
示例 2：
	输入：nums = {1}, target = 1
	输出：1
提示：
	1 <= nums.length <= 20
	0 <= nums{i} <= 1000
	0 <= sum(nums{i}) <= 1000
	-1000 <= target <= 1000 */

class Solution1 {
public:
	int findTargetSumWays(vector<int> &nums, int target) {
		int n = nums.size(), sum = 0, j = 0, zeroNum = 0;
		for(int i = 0; i < n; ++i) {
			sum += nums[i];
			if(nums[i]) {
				nums[j] = nums[i];
				++j;
			} else {
				++zeroNum;
			}
		}
		nums.resize(j), n = j;
		if((sum - target) % 2 || (sum - target < 0)) return 0;
		int negative = (sum - target) / 2;
		vector<vector<int>> dp(n + 1, vector<int>(negative + 1));
		for(int i = 0; i < n + 1; ++i) dp[i][0] = 1;
		for(int i = 1; i < n + 1; ++i) {
			for(int j = 1; j < negative + 1; ++j) {
				dp[i][j] = dp[i - 1][j] + ((j >= nums[i - 1] ? dp[i - 1][j - nums[i - 1]] : 0));
			}
		}
		return dp.back().back() << zeroNum;
	}
}; // dp[i][j]：前i个数和为j的组合个数，dp[i][j] = dp[i - 1][j] + ((j > nums[i - 1] ?  dp[i - 1][j - nums[i - 1]] : 0));
// 即dp[i][j]分为两种情况：1、不使用nums[i - 1]，直接在前i - 1个中找j;  2、使用nums[i - 1]，在前i - 1个中找j - nums[i - 1]
// 注意数组中包含0的处理：先计算不包含0的情况下的组合数，然后乘以2 ^ zeroNum，即左移zeroNum位

class Solution2 {
public:
	int findTargetSumWays(vector<int> &nums, int target) {
		int n = nums.size(), sum = 0, j = 0, zeroNum = 0;
		for(int i = 0; i < n; ++i) {
			sum += nums[i];
			if(nums[i])
				nums[j++] = nums[i];
			else
				++zeroNum;
		}
		nums.resize(j), n = j;
		if((sum - target) % 2 || (sum - target < 0)) return 0;
		int negative = (sum - target) / 2;
		vector<int> curr(negative + 1), next(negative + 1);
		curr[0] = 1, next[0] = 1;
		for(int i = 1; i < n + 1; ++i) {
			for(int j = 1; j < negative + 1; ++j) {
				next[j] = curr[j] + ((j >= nums[i - 1] ? curr[j - nums[i - 1]] : 0));
			}
			std::swap(curr, next);
		}
		return curr.back() << zeroNum;
	}
}; // 滚动数组优化

class Solution {
public:
	int findTargetSumWays(vector<int> &nums, int target) {
		int n = nums.size(), sum = 0, j = 0, zeroNum = 0;
		for(int i = 0; i < n; ++i) {
			sum += nums[i];
			if(nums[i])
				nums[j++] = nums[i];
			else
				++zeroNum;
		}
		nums.resize(j), n = j;
		if((sum - target) % 2 || (sum - target < 0)) return 0;
		int negative = (sum - target) / 2;
		vector<int> dp(negative + 1);
		dp[0] = 1;
		for(int i = 1; i < n + 1; ++i) {
			for(int j = negative; j >= 1; --j) { // 倒序遍历，避免重复使用同一元素
				dp[j] = dp[j] + ((j >= nums[i - 1] ? dp[j - nums[i - 1]] : 0));
			}
		}
		return dp.back() << zeroNum;
	}
}; // 单数组优化，也可以理解的值域dp，而非下标dp

int main() {
	Solution sol;
	vector<int> nums;
	int target;
	nums = { 1, 1, 1, 1, 1 }, target = 3;
	cout << sol.findTargetSumWays(nums, target) << endl;
	nums = { 1 }, target = 1;
	cout << sol.findTargetSumWays(nums, target) << endl;
}