// Created: 2026-01-13
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给你一个整数数组nums，请你将该数组升序排列。
你必须在 不使用任何内置函数 的情况下解决问题，时间复杂度为 O(nlog(n))，并且空间复杂度尽可能小。
示例 1：
	输入：nums = {5,2,3,1}
	输出：{1,2,3,5}
	解释：数组排序后，某些数字的位置没有改变（例如，2 和 3），而其他数字的位置发生了改变（例如，1 和 5）。
示例 2：
	输入：nums = {5,1,1,2,0,0}
	输出：{0,0,1,1,2,5}
	解释：请注意，nums 的值不一定唯一。
提示：
	1 <= nums.length <= 5 * 10^4
	-5 * 10^4 <= nums{i} <= 5 * 10^4 */

class Solution1 {
public:
	vector<int> sortArray(vector<int> &nums) {
		vector<int> temp(nums.size());
		mergeSort(nums, temp, 0, nums.size() - 1);
		return nums;
	}

private:
	void mergeSort(vector<int> &nums, vector<int> &temp, int left, int right) {
		if(right <= left) return;
		int mid = left + (right - left) / 2;
		mergeSort(nums, temp, left, mid);
		mergeSort(nums, temp, mid + 1, right);
		if(nums[mid] <= nums[mid + 1]) return; // 已经有序
		merge(nums, temp, left, mid, right);
	}

	void merge(vector<int> &nums, vector<int> &temp, int left, int mid, int right) {
		int a = left, b = mid + 1, c = left;
		while(a <= mid && b <= right) {
			if(nums[a] <= nums[b]) { // 等于号才能保证稳定性
				temp[c++] = nums[a++];
			} else {
				temp[c++] = nums[b++];
			}
		}
		while(a <= mid) temp[c++] = nums[a++];
		while(b <= right) temp[c++] = nums[b++];
		for(; left <= right; ++left) nums[left] = temp[left];
	}
}; // 归并排序

class Solution2 {
public:
	vector<int> sortArray(vector<int> &nums) {
		int n = nums.size();
		if(n <= 1) return nums;

		// 建大根堆
		for(int i = (n - 2) / 2; i >= 0; --i) {
			adjustHeap(nums, n, i);
		}

		// 依次取堆顶
		for(int i = n - 1; i > 0; --i) {
			swap(nums[0], nums[i]);
			adjustHeap(nums, i, 0);
		}
		return nums;
	}

private:
	void adjustHeap(vector<int> &nums, int n, int parent) {
		int pivot = nums[parent];
		int child = parent * 2 + 1; // 左孩子, nums[i] 的孩子是nums[i * 2 + 1]和nums[i * 2 + 2]

		while(child < n) {
			// 选更大的孩子
			if(child + 1 < n && nums[child + 1] > nums[child]) {
				++child;
			}
			if(nums[child] > pivot) {
				nums[parent] = nums[child];
				parent = child;
				child = parent * 2 + 1;
			} else {
				break;
			}
		}
		nums[parent] = pivot;
	} // 对节点k进行下滤操作
}; // 堆排序

class Solution {
public:
	vector<int> sortArray(vector<int> &nums) {
		quickSort(nums, 0, nums.size() - 1);
		return nums;
	}

private:
	void quickSort(vector<int> &nums, int l, int r) {
		if(r - l < 1) return;
		auto [eq, gt] = partition(nums, l, r);
		quickSort(nums, l, eq - 1);
		quickSort(nums, gt + 1, r);
	}
	pair<int, int> partition(vector<int> &nums, int l, int r) {
		int pivot = ((long long)nums[l] + nums[r] + nums[(r - l) / 2 + l]) / 3;
		int eq = l, gt = r, k = l;
		while(k <= gt) {
			if(nums[k] == pivot) {
				++k;
			} else if(nums[k] > pivot) {
				swap(nums[k], nums[gt]);
				--gt;
			} else {
				swap(nums[k], nums[eq]);
				++eq, ++k;
			}
		}
		return { eq, gt };
	}
}; // 快速排序——三路划分

int main() {
	Solution sol;
	vector<int> nums;
	nums = { 5, 2, 3, 1 };
	cout << sol.sortArray(nums) << endl;

	nums = { 5, 1, 1, 2, 0, 0 };
	cout << sol.sortArray(nums) << endl;
}