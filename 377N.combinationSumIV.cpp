// Created: 2025-06-07
#include "MyDateGen.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/*  377. 组合总和 Ⅳ
给你一个由 不同 整数组成的数组nums, 和一个目标整数 target。
请你从 nums 中找出并返回总和为 target 的元素组合的个数。
示例 1：
    输入：nums = [1,2,3], target = 4
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
    1 <= nums[i] <= 1000
    nums 中的所有元素 互不相同
    1 <= target <= 1000 */

class Solution1 {
public:
	int combinationSum4(vector<int> &nums, int target) {
		std::sort(nums.begin(), nums.end());
		vector<int> dp(target + 1);
		dp.front() = 1;
		for(int i = 1; i < target + 1; ++i) {
			for(auto j : nums) {
				if(j > i) {
					break;
				}
				if(INT_MAX - dp[i] < dp[i - j]) {
					dp[i] = INT_MAX;
				} else {
					dp[i] += dp[i - j];
				}
			}
		}
		return dp.back();
	}
}; // 注意与 518N.CoinChangeII 对比

class Solution2 {
public:
	int combinationSum4(vector<int> &nums, int target) {
		vector<int> dp(target + 1);
		dp.front() = 1;
		for(int i = 1; i < target + 1; ++i) {
			for(auto j : nums) {
				if(j > i) {
					continue;
				}
				if(INT_MAX - dp[i] < dp[i - j]) {
					dp[i] = INT_MAX;
				} else {
					dp[i] += dp[i - j];
				}
			}
		}
		return dp.back();
	}
}; // 注意与 518N.CoinChangeII 对比

int main() {
	Solution1 sol1;
	Solution2 sol2;
	auto nums = randomIntArray(2000, 1, 10000, 0, 1);
	cout << nums << endl;
	auto t0 = std::chrono::system_clock::now();
	int res1 = sol1.combinationSum4(nums, 10000);
	auto t1 = std::chrono::system_clock::now();
	int res2 = sol2.combinationSum4(nums, 10000);
	auto t2 = std::chrono::system_clock::now();
	cout << res1 << " " << res2 << endl;
	cout << t1 - t0 << " " << t2 - t1 << endl;
}