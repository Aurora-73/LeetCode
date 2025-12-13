// Created: 2025-12-12
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。
请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。
示例 1：
	输入：nums = {3,2,1,5,6,4}, k = 2
	输出：5
示例 2：
	输入：nums = {3,2,3,1,2,4,5,5,6}, k = 4
	输出：4
提示： 
	1 <= k <= nums.length <= 10^4
	-10^4<= nums{i} <= 10^4 */

class Solution1 {
public:
	int findKthLargest(vector<int> &nums, int k) {
		priority_queue<int, vector<int>, greater<int>> pq; // 默认是大根堆，这里要用小根堆
		for(auto num : nums) {
			if(pq.size() < k) {
				pq.push(num);
			} else if(pq.top() < num) {
				pq.push(num);
				pq.pop();
			}
		}
		return pq.top();
	}
}; // 堆排序延伸：优先队列

class Solution {
public:
	int findKthLargest(vector<int> &nums, int k) {
		int n = nums.size(), l = 0, r = n - 1, target = n - k;
		while(l < r) {
			int pivotIndex = partition(nums, l, r);
			if(pivotIndex == target) {
				break;
			} else if(pivotIndex < target) {
				l = pivotIndex + 1;
			} else {
				r = pivotIndex - 1;
			}
		}
		return nums[target];
	}

private:
	int partition(vector<int> &nums, int l, int r) {
		int pivot = nums[l];
		while(l < r) {
			while(l < r && nums[r] >= pivot) --r;
			nums[l] = nums[r];
			while(l < r && nums[l] <= pivot) ++l;
			nums[r] = nums[l];
		}
		nums[l] = pivot;
		return l;
	}
}; // 快速排序延伸：划分算法

int main() {
	Solution sol;
	vector<int> nums;
	int k;
	nums = { 3, 2, 1, 5, 6, 3 }, k = 2;
	cout << sol.findKthLargest(nums, k) << endl;

	nums = { 3, 2, 3, 1, 2, 4, 5, 5, 6 }, k = 4;
	cout << sol.findKthLargest(nums, k) << endl;
}