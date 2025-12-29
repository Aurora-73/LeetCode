// Created: 2025-12-29
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 搜索旋转数组。
给定一个排序后的数组，包含n个整数，但这个数组已被旋转过很多次了，次数不详。
请编写代码找出数组中的某个元素，假设数组元素原先是按升序排列的。若有多个相同元素，返回索引值最小的一个。
示例 1：
    输入：arr = {15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14}, target = 5
    输出：8（元素5在该数组中的索引）
示例 2：
    输入：arr = {15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14}, target = 11
    输出：-1 （没有找到）
提示:
	arr 长度范围在{1, 1000000}之间 */

class Solution1 {
public:
	int search(vector<int> &arr, int target) {
		if(target == arr[0]) return 0;
		int n = arr.size(), l = 0, r = n - 1;
		while(l < r) {
			int mid = l + (r - l) / 2;
			if(arr[mid] > arr[r]) {
				l = mid + 1;
			} else if(arr[mid] < arr[r]) {
				r = mid;
			} else { // arr[mid] == arr[r], 无法确定旋转点，r-- 保证二分不会死循环
				r--;
			}
		}
		if(arr[l] == arr.back()) {
			l = n - 1;
			while(l > 0 && arr[l - 1] == arr.back()) {
				--l;
			}
		} // { 1, 1, 1, 1, 1, 2, 1, 1, 1 }这种情况无法通过二分查找找到旋转点，必须从后往前重新寻找
		int partID = l; // 寻找可以将数组划分为两个有序子数组的分割点
		if(arr[partID] == target) return partID;
		vector<int>::iterator it;
		if(partID > 0 && target >= arr[0]) {
			it = lower_bound(arr.begin(), arr.begin() + partID, target);
		} else {
			// 目标在右段（[partID, n)）或左段不存在
			it = lower_bound(arr.begin() + partID, arr.end(), target);
		}
		return *it == target ? it - arr.begin() : -1;
	}
};

class Solution2 {
public:
	int search(vector<int> &arr, int target) {
		int n = arr.size();
		int left = 0, right = n - 1;
		while(left <= right) {
			// 重点1：当left符合时直接返回，因为找的是最小的索引
			if(arr[left] == target) return left;
			int mid = left + (right - left) / 2;
			// 重点2：当中间值等于目标值，将右边界移到中间，因为左边可能还有相等的值
			if(arr[mid] == target) {
				right = mid;
			} else if(arr[0] < arr[mid]) {
				if(arr[0] <= target && target < arr[mid]) {
					right = mid - 1;
				} else {
					left = mid + 1;
				}
			} else if(arr[0] > arr[mid]) {
				if(arr[mid] < target && target <= arr[n - 1]) {
					left = mid + 1;
				} else {
					right = mid - 1;
				}
			} else {
				// 重点3：当中间数字与左边数字相等时，将左边界右移
				left++;
			}
		}
		return -1;
	}
};

class Solution {
public:
	int search(vector<int> &arr, int target) {
		int l = 0, r = arr.size() - 1;
		while(r >= 0 && arr[r] == arr[0]) --r; // 直接移除掉右侧多余的相同元素，肯定取不到的值
		if(r == 0) return arr[0] == target ? 0 : -1;
		while(l < r) {
			int mid = l + (r - l) / 2;
			if(arr[mid] >= arr[0]) {
				l = mid + 1;
			} else {
				r = mid;
			}
		}
		int partID = l;
		vector<int>::iterator it;
		if(target >= arr[0]) {
			it = lower_bound(arr.begin(), arr.begin() + partID, target);
		} else {
			it = lower_bound(arr.begin() + partID, arr.end(), target);
		}
		return *it == target ? it - arr.begin() : -1;
	}
}; // 难点在于右侧有和首元素相同的值，直接移除这些元素，因为他们肯定取不到

int main() {
	Solution sol;
	vector<int> arr;
	int target;
	arr = { 1, 2, 3, 4, 5 }, target = 3;
	cout << sol.search(arr, target) << endl; // 2

	arr = { 2, 1, 2, 2, 2 }, target = 1;
	cout << sol.search(arr, target) << endl; // 1

	arr = { 1, 1, 1, 1, 1, 2, 1, 1, 1 }, target = 2;
	cout << sol.search(arr, target) << endl; // 5

	arr = { 15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14 }, target = 5;
	cout << sol.search(arr, target) << endl; // 8

	arr = { 15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14 }, target = 11;
	cout << sol.search(arr, target) << endl; // -1
}