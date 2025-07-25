// Created: 2025-07-04
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 1679. K 和数对的最大数目
给你一个整数数组 nums 和一个整数 k。
每一步操作中，你需要从数组中选出和为 k 的两个整数，并将它们移出数组。
返回你可以对数组执行的最大操作数。
示例 1：
	输入：nums = {1,2,3,4}, k = 5
	输出：2
	解释：开始时 nums = {1,2,3,4}：
	- 移出 1 和 4，之后 nums = {2,3}
	- 移出 2 和 3，之后 nums = {}
	不再有和为 5 的数对，因此最多执行 2 次操作。
示例 2：
	输入：nums = {3,1,3,4,3}, k = 6
	输出：1
	解释：开始时 nums = {3,1,3,4,3}：
	- 移出前两个 3，之后nums = {1,4,3}
	不再有和为 6 的数对，因此最多执行 1 次操作。
提示：
	1 <= nums.length <= 10^5
	1 <= nums{i} <= 10^9
	1 <= k <= 10^9 */

class Solution1 {
public:
	int maxOperations(vector<int> &nums, int k) {
		int res = 0;
		unordered_map<int, int> map;
		for(auto x : nums) {
			auto it = map.find(k - x);
			if(it != map.end() && it->second > 0) {
				++res, --it->second;
			} else {
				++map[x];
			}
		}
		return res;
	}
};

class Solution2 {
public:
	int maxOperations(vector<int> &nums, int k) {
		int n = nums.size();
		sort(nums.begin(), nums.end());
		int left = 0, right = n - 1;
		int cnt = 0;
		while(left < right) {
			if(nums[left] + nums[right] > k)
				right -= 1;
			else if(nums[left] + nums[right] < k)
				left += 1;
			else {
				// 相等移除两头元素
				left += 1;
				right -= 1;
				cnt += 1;
			}
		}
		return cnt;
	}
};

int main() {
	Solution1 sol1;
	Solution2 sol2;
	vector<int> nums;
	int k;
	nums = { 1, 2, 3, 4 }, k = 5;
	cout << sol1.maxOperations(nums, k) << endl;
	cout << sol2.maxOperations(nums, k) << endl;

	nums = { 3, 1, 3, 4, 3 }, k = 6;
	cout << sol1.maxOperations(nums, k) << endl;
	cout << sol2.maxOperations(nums, k) << endl;
}