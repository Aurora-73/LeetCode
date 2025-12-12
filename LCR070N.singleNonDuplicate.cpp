// Created: 2025-12-11
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个只包含整数的有序数组 nums，每个元素都会出现两次，唯有一个数只会出现一次，请找出这个唯一的数字。
示例 1：
	输入: nums = {1,1,2,3,3,4,4,8,8}
	输出: 2
示例 2：
	输入: nums =  {3,3,7,7,10,11,11}
	输出: 10
提示：
	1 <= nums.length <= 10^5
	0 <= nums{i}<= 10^5
	进阶：采用的方案可以在 O(log n) 时间复杂度和 O(1) 空间复杂度中运行吗？
注意：本题与主站 540题相同： */

class Solution1 {
public:
	int singleNonDuplicate(vector<int> &nums) {
		int n = nums.size(), l = 0, r = n;
		while(l < r) {
			int mid = l + (r - l) / 2, beg;
			if(mid > 0 && nums[mid] == nums[mid - 1]) {
				beg = mid - 1;
			} else if(mid < n - 1 && nums[mid] == nums[mid + 1]) {
				beg = mid;
			} else {
				return nums[mid];
			}
			if(beg % 2 == 0) {
				l = beg + 2;
			} else {
				r = beg;
			}
		}
		return nums[l];
	}
}; // 左侧两次 | res | 右侧两次：对于某个元素，记录重复开始的下标i，若i % 2 == 0说明i在左侧，反之则在右侧

class Solution2 {
public:
	int singleNonDuplicate(vector<int> &nums) {
		int n = nums.size(), l = 0, r = n / 2;
		while(l < r) {
			int mid = l + (r - l) / 2;
			if(mid * 2 < n - 1 && nums[mid * 2] == nums[mid * 2 + 1]) {
				l = mid + 1;
			} else if(mid > 0 && nums[mid * 2] == nums[mid * 2 - 1]) {
				r = mid;
			} else {
				return nums[mid * 2];
			}
		}
		return nums[l * 2];
	}
}; // 仅遍历偶数下标，如果该下标的元素和后一个相等，则说明位于左侧；如果与前一个相等则位于右侧；不难发现结果一定位于偶数下标处，都不相等直接输出

class Solution {
public:
	int singleNonDuplicate(vector<int> &nums) {
		int low = 0, high = nums.size() - 1;
		while(low < high) {
			int mid = (high - low) / 2 + low;
			mid = mid / 2 * 2;
			if(nums[mid] == nums[mid + 1]) {
				low = mid + 2;
			} else {
				high = mid;
			}
		}
		return nums[low];
	}
}; // 正常遍历，但是将mid选择偶数下标处

int main() {
	Solution sol;
	vector<int> nums;
	nums = { 1, 1, 2 };
	cout << sol.singleNonDuplicate(nums) << endl; // 2
	nums = { 1, 1, 2, 3, 3, 4, 4, 8, 8 };
	cout << sol.singleNonDuplicate(nums) << endl; // 2
	nums = { 3, 3, 7, 7, 10, 11, 11 };
	cout << sol.singleNonDuplicate(nums) << endl; // 10
}