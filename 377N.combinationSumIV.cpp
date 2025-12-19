// Created: 2025-06-07
#include "MyDateGen.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 377. 组合总和 Ⅳ
给你一个由 不同 整数组成的数组nums, 和一个目标整数 target。
请你从 nums 中找出并返回总和为 target 的元素组合的个数。
示例 1：
	输入：nums = {1,2,3}, target = 4
	输出：7
	    解释：
	    所有可能的组合为：
	    (1, 1, 1, 1)
	    (1, 1, 2)
	    (1, 2, 1)
	    (1, 3)
	    (2, 1, 1)
	    (2, 2)
	    (3, 1)
	请注意，顺序不同的序列被视作不同的组合。
提示：
	    1 <= nums.length <= 200
	    1 <= nums{i} <= 1000
	    nums 中的所有元素 互不相同
	    1 <= target <= 1000 */

class Solution1 {
public:
	int combinationSum4(vector<int> &nums, int target) {
		return dfs(nums, target);
	}

private:
	int dfs(vector<int> &nums, int remain) {
		if(remain == 0) return 1;
		if(remain < 0) return 0;
		int cnt = 0;
		for(auto num : nums) {
			cnt += dfs(nums, remain - num);
		}
		return cnt;
	} // 状态只有target一个
};

class Solution2 {
public:
	int combinationSum4(vector<int> &nums, int target) {
		memo.assign(target + 1, -1);
		return dfs(nums, target);
	}

private:
	vector<int> memo;
	int dfs(vector<int> &nums, int remain) {
		if(remain == 0) return 1;
		if(remain < 0) return 0;
		if(memo[remain] != -1) return memo[remain];
		long long cnt = 0;
		for(int num : nums) {
			cnt += dfs(nums, remain - num);
		}
		return memo[remain] = (int)cnt;
	}
};

class Solution {
public:
	int combinationSum4(vector<int> &nums, int target) {
		vector<int> dp(target + 1);
		dp.front() = 1;
		for(int i = 1; i <= target; ++i) {
			for(auto num : nums) {
				if(i >= num) dp[i] += min(dp[i - num], INT_MAX - dp[i]);
			}
		}
		return dp.back();
	} // target从小到大
};

int main() {
	Solution sol;
	vector<int> nums;
	int target;
	nums = { 1, 2, 3 }, target = 4;
	cout << sol.combinationSum4(nums, target) << endl; // 7
}