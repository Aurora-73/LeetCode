// Created: 2025-06-06
#include "MyDateGen.h"
#include "MyUtils.hpp"

/*	Q3. 最大子数组 GCD 分数
给你一个正整数数组 nums 和一个整数 k。
你最多可以执行 k 次操作。在每次操作中，你可以选择数组中的一个元素并将其值 翻倍。每个元素 最多 只能翻倍一次。
连续 子数组 的 分数 定义为其所有元素的最大公约数 (GCD) 与子数组长度的 乘积。
你的任务是返回修改后数组中选择一个连续子数组可以获得的最大 分数。
注意：
	子数组 是数组中连续的元素序列。
	数组的 最大公约数 (GCD) 是能整除数组所有元素的最大整数。
	示例 1:
	输入: nums = {2,4}, k = 1
	输出: 8
	解释:
	使用一次操作将 nums{0} 翻倍到 4。修改后的数组变为 {4, 4}。
	子数组 {4, 4} 的 GCD 是 4，长度是 2。
	因此，最大可能分数是 2 × 4 = 8。
	示例 2:
	输入: nums = {3,5,7}, k = 2
	输出: 14
	解释:
	使用一次操作将 nums{2} 翻倍到 14。修改后的数组变为 {3, 5, 14}。
	子数组 {14} 的 GCD 是 14，长度是 1。
	因此，最大可能分数是 1 × 14 = 14。
	示例 3:
	输入: nums = {5,5,5}, k = 1
	输出: 15
	解释:
	子数组 {5, 5, 5} 的 GCD 是 5，长度是 3。
	因为翻倍任何元素都不能提高分数，所以最大分数是 3 × 5 = 15。
提示：
	1 <= n == nums.length <= 1500
	1 <= nums{i} <= 10 ^ 9
	1 <= k <= n	*/

class Solution {
public:
	long long maxGCDScore(vector<int> &nums, int k) {
		int n = nums.size();
		long long ans = 0;
		for(int l = 0; l < n; ++l) {
			vector<long long> dp(k + 1, 0);
			for(int r = l; r < n; ++r) {
				vector<long long> ndp(k + 1, 0);
				for(int used = 0; used <= k; ++used) {
					long long g1 = gcd(dp[used], (long long)nums[r]);
					ndp[used] = max(ndp[used], g1);
					if(used < k && dp[used] % 2 == 0) {
						long long g2 = gcd(dp[used], (long long)nums[r] * 2);
						ndp[used + 1] = max(ndp[used + 1], g2);
					}
				}
				dp = ndp;
				for(int used = 0; used <= k; ++used) {
					ans = max(ans, dp[used] * (r - l + 1));
				}
			}
		}
		return ans;
	}
};

int main() {
	Solution sol;
	vector<int> nums;
	int k;
	nums = { 2, 4 }, k = 1;
	cout << sol.maxGCDScore(nums, k) << endl;
	nums = { 3, 5, 7 }, k = 2;
	cout << sol.maxGCDScore(nums, k) << endl;
	nums = { 5, 5, 5 }, k = 1;
	cout << sol.maxGCDScore(nums, k) << endl;
}