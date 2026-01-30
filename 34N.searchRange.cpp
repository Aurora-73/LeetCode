// Created: 2025-05-15
#include "MyUtils.hpp"

/* 34. 在排序数组中查找元素的第一个和最后一个位置
给你一个按照非递减顺序排列的整数数组 nums，和一个目标值 target。
请你找出给定目标值在数组中的开始位置和结束位置。
如果数组中不存在目标值 target，返回{-1, -1}。
你必须设计并实现时间复杂度为O(log n)的算法解决此问题。
示例 1：
	输入：nums = {5,7,7,8,8,10}, target = 8
	输出：{3,4}
示例2：
	输入：nums = {5,7,7,8,8,10}, target = 6
	输出：{-1,-1}
示例 3：
	输入：nums = {}, target = 0
	输出：{-1,-1}
提示：
	0 <= nums.length <= 10^5
	-10^9<= nums{i}<= 10^9
	nums是一个非递减数组
	-10^9<= target<= 10^9 */

class Solution1 {
public:
	vector<int> searchRange(vector<int> &nums, int target) {
		auto left = lower_bound(nums.begin(), nums.end(), target);
		if(left == nums.end() || *left != target) {
			return { -1, -1 };
		} // 不用算 right 就能判断
		auto right = upper_bound(left, nums.end(), target);
		return { int(left - nums.begin()), int(right - nums.begin() - 1) };
	}
};

class Solution2 {
public:
	vector<int> searchRange(vector<int> &nums, int target) {
		int left = lower_bound(nums, target);
		int right = upper_bound(nums, target, left);
		if(left == right) {
			return { -1, -1 };
		} else {
			return { left, right - 1 };
		}
	}
	int lower_bound(vector<int> &nums, int target) {
		int left = 0, right = nums.size();
		while(left < right) {
			int mid = left + (right - left) / 2;
			if(target <= nums[mid]) {
				left = mid + 1;
			} else {
				right = mid - 1;
			}
		}
		return left;
	}
	int upper_bound(vector<int> &nums, int target, int left) {
		int right = nums.size();
		while(left < right) {
			int mid = left + (right - left) / 2;
			if(target >= nums[mid]) {
				left = mid + 1;
			} else {
				right = mid - 1;
			}
		}
		return right;
	}
};

class Solution {
public:
	vector<int> searchRange(vector<int> &nums, int target) {
		int left = binarySearch(nums, target - 0.5, 0);
		if(left == nums.size() || nums[left] != target) {
			return { -1, -1 };
		}
		int right = binarySearch(nums, target + 0.5, left);
		return { left, right - 1 };
	}

private:
	int binarySearch(vector<int> &nums, double target, int left) {
		int right = nums.size();
		while(left < right) {
			int mid = left + (right - left) / 2;
			if(nums[mid] < target) {
				left = mid + 1;
			} else {
				right = mid;
			}
		}
		return left;
	}
}; /*这个二分在整个过程中，始终维护了一个不变量：
区间含义：
	[0, left) —— 所有元素 < target
	[right, n) —— 所有元素 ≥ target
	[left, right) —— 尚未确定
当递归到left == right的时候，[0, left)就是全部小于left的元素，因此left就是插入位置*/

int main() {
	Solution sol;
	vector<int> nums;
	int target;
	nums = { 5, 7, 7, 8, 8, 10 }, target = 8;
	cout << sol.searchRange(nums, target) << endl;

	nums = { 5, 7, 7, 8, 8, 10 }, target = 6;
	cout << sol.searchRange(nums, target) << endl;

	nums = {}, target = 0;
	cout << sol.searchRange(nums, target) << endl;
}
