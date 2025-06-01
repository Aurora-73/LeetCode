// Created: 2025-05-22
#include "MyUtils.h"

/*300. 最长递增子序列
给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。
子序列 是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。例如，[3,6,2,7]
是数组 [0,3,1,6,2,2,7] 的子序列。*/

class Solution1 {
public:
	int lengthOfLIS(vector<int> &nums) {
		int n = nums.size();
		memo.assign(n, -1);
		return dfs(nums, -1);
	}

private:
	vector<int> memo;

	int dfs(const vector<int> &nums, int prev) {
		int n = nums.size();
		if(prev >= 0 && memo[prev] != -1) {
			return memo[prev];
		}

		int best = 0;
		for(int i = prev + 1; i < n; ++i) {
			if(prev < 0 || nums[i] > nums[prev]) {
				best = max(best, dfs(nums, i) + 1);
			}
		}

		if(prev >= 0) {
			memo[prev] = best;
		}
		return best;
	}
};

class Solution2 {
public:
	int lengthOfLIS(vector<int> &nums) {
		int n = nums.size();
		vector<int> dp(n, 1);
		for(int i = n - 2; i >= 0; --i) {
			for(int j = i + 1; j < n; ++j) {
				if(nums[j] > nums[i]) {
					dp[i] = max(dp[j] + 1, dp[i]);
				}
			}
		}
		return *max_element(dp.begin(), dp.end());
	}
}; // dp O(n ^ 2)

class Solution {
public:
	int lengthOfLIS(vector<int> &nums) {
		vector<int> minTails;
		for(auto &x : nums) {
			auto it = lower_bound(minTails.begin(), minTails.end(), x);
			if(it == minTails.end()) {
				minTails.push_back(x);
			} else {
				*it = x;
			}
		}
		return minTails.size();
	}
}; // 贪心 + 二分查找   https://writings.sh/post/longest-increasing-subsequence-revisited

int main() {
	Solution sol;
	vector<int> nums = { 0, 1, 0, 3, 2, 3 };
	cout << sol.lengthOfLIS(nums);
}