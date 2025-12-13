// Created: 2025-12-12
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定两个数组，arr1 和arr2，
	arr2中的元素各不相同
	arr2 中的每个元素都出现在arr1中
对 arr1中的元素进行排序，使 arr1 中项的相对顺序和arr2中的相对顺序相同。
未在arr2中出现过的元素需要按照升序放在arr1的末尾。
示例：
输入：arr1 = {2,3,1,3,2,4,6,7,9,2,19}, arr2 = {2,1,4,3,9,6}
输出：{2,2,2,1,4,3,3,9,6,7,19}
提示：
	1 <= arr1.length, arr2.length <= 1000
	0 <= arr1{i}, arr2{i} <= 1000
	arr2中的元素arr2{i}各不相同
	arr2 中的每个元素arr2{i}都出现在arr1中 */

class Solution {
public:
	vector<int> relativeSortArray(vector<int> &arr1, vector<int> &arr2) {
		unordered_map<int, int> map;
		int n2 = arr2.size();
		for(int i = 0; i < n2; ++i) {
			map[arr2[i]] = n2 - i;
		} // 由于map对于不存在的元素，值为0，因此只要让所有存在的元素的值都大于0，且排在前面的值更大，然后按照map越大越靠前排序即可
		auto cmp = [&](int l, int r) {
			int diff = map[l] - map[r];
			if(diff != 0) {
				return diff > 0;
			}
			return l < r;
		};
		sort(arr1.begin(), arr1.end(), cmp);
		return arr1;
	}
}; // 排序的比较函数可以看做 cmp(type l, type r) 当l应该放到r前面的时候返回true，反之返回false

class Solution1 {
public:
	vector<int> relativeSortArray(vector<int> &arr1, vector<int> &arr2) {
		unordered_map<int, int> order;
		for(int i = 0; i < arr2.size(); i++) order[arr2[i]] = i;
		sort(arr1.begin(), arr1.end(), [&](int a, int b) {
			bool ea = order.count(a), eb = order.count(b);
			if(ea && eb) return order[a] < order[b];
			if(ea) return true;
			if(eb) return false;
			return a < b;
		});
		return arr1;
	}
};

int main() {
	Solution sol;
	vector<int> arr1, arr2;
	arr1 = { 2, 3, 1, 3, 2, 4, 6, 7, 9, 2, 19 }, arr2 = { 2, 1, 4, 3, 9, 6 };
	cout << sol.relativeSortArray(arr1, arr2) << endl;
}