// Created: 2025-06-19
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 416. 分割等和子集
给你一个 只包含正整数 的 非空 数组nums。
请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。
示例 1：
	输入：nums = {1,5,11,5}
	输出：true
	解释：数组可以分割成 {1, 5, 5} 和 {11}。
示例 2：
	输入：nums = {1,2,3,5}
	输出：false
	解释：数组不能分割成两个元素和相等的子集。
提示：
	1 <= nums.length <= 200
	1 <= nums{i} <= 100 */

class Solution1 {
public:
	bool canPartition(vector<int> &nums) {
		int n = nums.size(), sum = 0;
		for(auto n : nums) {
			sum += n;
		}
		if(sum % 2) return 0;
		sum /= 2;
		vector<vector<bool>> dp(n + 1, vector<bool>(sum + 1));
		for(int i = 0; i <= n; ++i) dp[i][0] = 1;
		for(int i = 1; i <= n; ++i) {
			for(int j = 1; j <= sum; ++j) {
				int suf = j - nums[i - 1];
				dp[i][j] = (dp[i - 1][j]) || ((suf >= 0) && dp[i - 1][suf]);
			}
		}
		return dp.back().back();
	}
}; // 类似 01背包问题
// dp[i][j]: 前 i 个数中和为 j 是否存在

class Solution2 {
public:
	bool canPartition(vector<int> &nums) {
		int n = nums.size(), sum = 0;
		for(auto n : nums) {
			sum += n;
		}
		if(sum % 2) return 0;
		sum /= 2;
		vector<bool> prev(sum + 1);
		for(int i = 1; i <= n; ++i) {
			prev.front() = 1;
			vector<bool> curr(sum + 1);
			for(int j = 1; j <= sum; ++j) {
				int suf = j - nums[i - 1];
				curr[j] = prev[j] || ((suf >= 0) && prev[suf]);
			}
			prev = std::move(curr);
		}
		return prev.back();
	}
}; // 滚动数组优化

class Solution3 {
public:
	bool canPartition(vector<int> &nums) {
		int sum = 0, n = nums.size();
		for(int i = 0; i < n; ++i) {
			sum += nums[i];
		}
		if(sum % 2) return false;
		int target = sum / 2;
		vector<bool> dp(target + 1, false);
		dp[0] = true;
		for(int num : nums) {
			if(num > target) return false;
			// 从后往前遍历，避免重复使用同一个数
			for(int j = target; j >= num; --j) {
				dp[j] = dp[j] || dp[j - num];
			}
			if(dp[target]) return true; // 早停
		}
		return dp[target];
	}
};
/* 进一步空间优化: 
    其实一维 dp 可以只用一个数组，从后往前遍历，避免 curr/prev 复制，空间复杂度依然 O(sum)，但常数更小。
剪枝优化:
    如果某个数大于 sum/2，可以直接返回 false。
早停优化:
    如果在遍历过程中 dp[sum] 已经为 true，可以提前返回 true。 */

class Solution {
public:
	bool canPartition(vector<int> &nums) {
		int sum = 0, n = nums.size();
		for(int i = 0; i < n; ++i) sum += nums[i];

		if(sum % 2) {
			return false;
		}
		sum /= 2;
		bitset<10001> f; // sum(nums[i]) / 2 <= 10000 bitset的大小必须在编译期确定
		f[0] = 1;
		for(int x : nums) {
			f |= f << x; // 或等于 相当于选(原始) 或者 不选(左移 x 位)
		}
		return f[sum]; // 判断 f 中第 s 位是否为 1
	}
};

int main() {
	Solution sol;
	vector<int> nums;
	nums = { 1, 2, 5 };
	cout << sol.canPartition(nums) << endl; // 0
	nums = { 1, 5, 11, 5 };
	cout << sol.canPartition(nums) << endl; // 1
	nums = { 1, 2, 3, 5 };
	cout << sol.canPartition(nums) << endl; // 0
}