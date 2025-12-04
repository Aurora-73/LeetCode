// Created: 2025-07-16
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 007. 三数之和
给定一个包含 n 个整数的数组nums，判断nums中是否存在三个元素a，b，
c，使得a + b + c = 0 ？请找出所有和为 0 且不重复的三元组。
示例 1：
	输入：nums = {-1,0,1,2,-1,-4}
	输出：{{-1,-1,2},{-1,0,1}}
示例 2：
	输入：nums = {}
	输出：{}
示例 3：
	输入：nums = {0}
	输出：{}
提示：
	0 <= nums.length <= 3000
	-10^5 <= nums{i} <= 10^5
注意：本题与主站 15题相同：
	https://leetcode-cn.com/problems/3sum/ */

class Solution1 {
public:
	vector<vector<int>> threeSum(vector<int> &nums) {
		ranges::sort(nums);
		int n = nums.size();
		vector<vector<int>> res;
		for(int i = 0; i < n - 2; ++i) {
			if(i > 0 && nums[i] == nums[i - 1]) {
				continue;
			} // 去重
			for(int j = i + 1; j < n - 1; ++j) {
				if(j > i + 1 && nums[j] == nums[j - 1]) {
					continue;
				} // 去重
				int need = -nums[i] - nums[j];
				if(binary_search(nums.begin() + j + 1, nums.end(), need)) {
					res.push_back({ nums[i], nums[j], need });
				}
			}
		}
		return res;
	}
}; // 排序 + 双重循环 + 二分查找 O(n ^ 2 * log n)，注意去重

class Solution {
public:
	vector<vector<int>> threeSum(vector<int> &nums) {
		int n = nums.size();
		vector<vector<int>> res;
		if(n < 3) return res;
		res.reserve(n);
		sort(nums.begin(), nums.end());
		for(int i = 0; i < n - 2; ++i) {
			if(nums[i] > 0) break;                        // 早停
			if(i > 0 && nums[i] == nums[i - 1]) continue; // 去重
			// 两数之和，双指针，一次只移动一侧
			int l = i + 1, r = n - 1, target = -nums[i];
			// 如果最小的 l 都比 target 大，或者最大的 r 都比 target 小，也可以提前跳过
			if(nums[l] + nums[l + 1] > target) continue;
			if(nums[r] + nums[r - 1] < target) continue;

			while(l < r) {
				int sum = nums[l] + nums[r];
				if(sum < target) {
					++l;
				} else if(sum > target) {
					--r;
				} else {
					res.push_back({ nums[i], nums[l], nums[r] });
					while(l < r && nums[l] == nums[l + 1]) ++l;
					while(l < r && nums[r] == nums[r - 1]) --r;
					++l;
					--r;
				}
			}
		}
		return res;
	}
}; // 排序 + 枚举 + 两数之和，时间复杂度O(n ^ 2)

int main() {
	Solution sol;
	vector<int> nums;
	nums = { -1, 0, 1, 2, -1, -4 };
	cout << sol.threeSum(nums) << endl;
	nums = { 0, 0, 0, 0, 0, 0 };
	cout << sol.threeSum(nums) << endl;
}