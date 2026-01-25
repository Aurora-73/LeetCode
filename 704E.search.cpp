// Created: 2026-01-25
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个n个元素有序的（升序）整型数组nums 和一个目标值target，
写一个函数搜索nums中的 target，如果target 存在返回下标，否则返回 -1。
你必须编写一个具有 O(log n) 时间复杂度的算法。
示例 1:
	输入: nums = {-1,0,3,5,9,12}, target = 9
	输出: 4
	解释: 9 出现在 nums 中并且下标为 4
示例2:
	输入: nums = {-1,0,3,5,9,12}, target = 2
	输出: -1
	解释: 2 不存在 nums 中因此返回 -1
提示：
	你可以假设 nums中的所有元素是不重复的。
	n将在{1, 10000}之间。
	nums的每个元素都将在{-9999, 9999}之间。 */

class Solution1 {
public:
	int search(vector<int> &nums, int target) {
		int l = 0, r = nums.size(); // 左闭右开
		while(l < r) {
			int mid = l + (r - l) / 2;
			if(nums[mid] == target) {
				return mid;
			} else if(nums[mid] < target) {
				l = mid + 1;
			} else {
				r = mid;
			}
		}
		return -1;
	}
}; // 左闭右开

class Solution {
public:
	int search(vector<int> &nums, int target) {
		int l = 0, r = nums.size() - 1; // 左闭右闭
		while(l <= r) {
			int mid = l + (r - l) / 2;
			if(nums[mid] == target) {
				return mid;
			} else if(nums[mid] < target) {
				l = mid + 1;
			} else {
				r = mid - 1;
			}
		}
		return -1;
	}
}; // 左闭右闭

int main() {
	Solution sol;
	vector<int> nums;
	int target;
	nums = { -1, 0, 3, 5, 9, 12 }, target = 9;
	cout << sol.search(nums, target) << endl;

	nums = { -1, 0, 3, 5, 9, 12 }, target = 2;
	cout << sol.search(nums, target) << endl;
}