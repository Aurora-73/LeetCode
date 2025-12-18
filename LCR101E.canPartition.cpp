// Created: 2025-12-14
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个非空的正整数数组 nums，请判断能否将这些数字分成元素和相等的两部分。
示例 1：
	输入：nums = {1,5,11,5}
	输出：true
	解释：nums 可以分割成 {1, 5, 5} 和 {11}。
示例 2：
	输入：nums = {1,2,3,5}
	输出：false
	解释：nums 不可以分为和相等的两部分
提示：
	1 <= nums.length <= 200
	1 <= nums{i} <= 100 */

class Solution1 {
public:
	bool canPartition(vector<int> &nums) {
		int sum = 0, n = nums.size();
		for(int i = 0; i < n; ++i) {
			sum += nums[i];
		}
		if(sum % 2) return false;
		int target = sum / 2;
		return dfs(0, target, nums);
	}

private:
	bool dfs(int i, int target, vector<int> &nums) {
		if(target == 0) return true;
		if(i == nums.size()) return false;
		if(target == nums[i]) return true;
		if(target > nums[i]) return dfs(i + 1, target - nums[i], nums) || dfs(i + 1, target, nums);
		return dfs(i + 1, target, nums);
	}
}; /* DFS 在算什么？
	你在 DFS 里，其实一直在回答这个问题：
	前 i 个数，能不能凑出 target?
	这就是 DP 状态的雏形。 
	*/

class Solution2 {
public:
	bool canPartition(vector<int> &nums) {
		int sum = 0, n = nums.size();
		for(int i = 0; i < n; ++i) sum += nums[i];
		if(sum % 2) return false;
		int target = sum / 2;
		vector<vector<bool>> dp(n + 1, vector<bool>(target + 1));
		for(int i = 0; i < n + 1; ++i) dp[i][0] = 1;
		for(int i = 1; i < n + 1; ++i) {
			for(int j = 1; j < target + 1; ++j) {
				dp[i][j] = dp[i - 1][j] || (j - nums[i - 1] >= 0 && dp[i - 1][j - nums[i - 1]]);
			}
		}
		return dp.back().back();
	}
}; // dp[i][j]：前i个数中，和为j的组合，是否存在
// 有两种可能：1、前i - 1个数已经存在和为j的组合了，不需要nums[i - 1]
//			  2、前i - 1个数不存在和为j的组合，需要nums[i - 1]，前i - 1个数应该提供j - nums[i - 1]

class Solution3 {
public:
	bool canPartition(vector<int> &nums) {
		int sum = 0, n = nums.size();
		for(int i = 0; i < n; ++i) sum += nums[i];
		if(sum % 2) return false;
		int target = sum / 2;
		vector<bool> curr(target + 1), next(target + 1);
		curr[0] = 1;
		for(int i = 1; i < n + 1; ++i) {
			for(int j = 1; j < target + 1; ++j) {
				next[j] = curr[j] || (j - nums[i - 1] >= 0 && curr[j - nums[i - 1]]);
			}
			std::swap(curr, next);
		}
		return curr.back();
	}
}; // 滚动数组优化

class Solution {
public:
	bool canPartition(vector<int> &nums) {
		int sum = 0, n = nums.size();
		for(int i = 0; i < n; ++i) sum += nums[i];
		if(sum % 2) return false;
		int target = sum / 2;
		vector<bool> dp(target + 1, false);
		dp[0] = true;
		for(int num : nums) {
			for(int j = target; j >= num; --j) {
				dp[j] = dp[j] || dp[j - num];
			} // 从后往前遍历，防止新增加的值被遍历到，也就是防止重复使用同一个元素多次
		}
		return dp[target];
	}
}; // 对值dp

int main() {
	Solution sol;
	vector<int> nums;
	nums = { 1, 5, 11, 5 };
	cout << sol.canPartition(nums) << endl;
	nums = { 1, 2, 3, 5 };
	cout << sol.canPartition(nums) << endl;
}