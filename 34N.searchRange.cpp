// Created: 2025-05-15
#include "MyUtils.hpp"

/*34. 在排序数组中查找元素的第一个和最后一个位置
给你一个按照非递减顺序排列的整数数组 nums，和一个目标值 target。请你找出给定目标值在数组中的开始位置和结束位置。
如果数组中不存在目标值 target，返回 [-1, -1]。
你必须设计并实现时间复杂度为 O(log n) 的算法解决此问题。*/

class Solution1 {
public:
	vector<int> searchRange(vector<int> &nums, int target) {
		int left = binarySearch(nums, target - 0.5, 0),
		    right = binarySearch(nums, target + 0.5, left);
		if(left == right) {
			return { -1, -1 };
		} else {
			return { left, right - 1 };
		}
	}
	int binarySearch(vector<int> &nums, double target, int left) {
		int right = nums.size() - 1;
		while(left <= right) {
			int mid = left + (right - left) / 2;
			if(nums[mid] < target) {
				left = mid + 1;
			} else {
				right = mid - 1;
			}
		}
		return left;
	}
};

class Solution2 {
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

class Solution3 {
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

int main() {
	Solution1 sol1;
}