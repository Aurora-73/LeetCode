// Created: 2026-01-04
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定两个整数数组，请交换一对数值（每个数组中取一个数值），使得两个数组所有元素的和相等。
返回一个数组，第一个元素是第一个数组中要交换的元素，第二个元素是第二个数组中要交换的元素。
若有多个答案，返回任意一个均可。若无满足条件的数值，返回空数组。
示例 1：
	输入：array1 = {4, 1, 2, 1, 1, 2}, array2 = {3, 6, 3, 3}
	输出：{1, 3}
示例 2：
	输入：array1 = {1, 2, 3}, array2 = {4, 5, 6}
	输出：{}
提示：
	1 <= array1.length, array2.length <= 100000 */

class Solution1 {
public:
	vector<int> findSwapValues(vector<int> &array1, vector<int> &array2) {
		if(array1.size() < array2.size()) swap(array1, array2);
		int n1 = array1.size(), n2 = array2.size();
		long long sum1 = 0, sum2 = 0;
		for(int i = 0; i < n1; ++i) sum1 += array1[i];
		for(int i = 0; i < n2; ++i) sum2 += array2[i];
		if((sum1 - sum2) % 2) return {}; // 不能实现奇数差的交换
		int differ = (sum1 - sum2) / 2;  // 寻找 array1[x] - array2[y] = differ
		sort(array2.begin(), array2.end());
		unordered_set<int> visited;
		for(int x : array1) {
			if(!visited.insert(x).second) continue; // 避免重复访问
			int need = x - differ;
			auto it = lower_bound(array2.begin(), array2.end(), need);
			if(it != array2.end() && *it == need) {
				return { x, need };
			}
		}
		return {};
	}
}; // 对小的排序，然后二分查找，O(n log n)

class Solution {
public:
	vector<int> findSwapValues(vector<int> &array1, vector<int> &array2) {
		int n1 = array1.size(), n2 = array2.size();
		long long sum1 = 0, sum2 = 0;
		for(int i = 0; i < n1; ++i) sum1 += array1[i];
		for(int i = 0; i < n2; ++i) sum2 += array2[i];
		if((sum1 - sum2) % 2) return {}; // 不能实现奇数差的交换
		int differ = (sum1 - sum2) / 2;  // 寻找 array1[x] - array2[y] = differ
		unordered_set<int> set2, visited;
		for(int y : array2) set2.insert(y);
		for(int x : array1) {
			if(!visited.insert(x).second) continue; // 避免重复访问
			int need = x - differ;
			if(set2.count(need)) {
				return { x, need };
			}
		}
		return {};
	}
}; // 直接用哈希表判断存不存在，O(n)

int main() {
	Solution sol;
	vector<int> array1, array2;
	array1 = { 4, 1, 2, 1, 1, 2 }, array2 = { 3, 6, 3, 3 };
	cout << sol.findSwapValues(array1, array2) << endl;

	array1 = { 1, 2, 3 }, array2 = { 4, 5, 6 };
	cout << sol.findSwapValues(array1, array2) << endl;
}