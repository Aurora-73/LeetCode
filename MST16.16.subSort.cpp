// Created: 2026-01-03
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个整数数组，编写一个函数，找出索引m和n，只要将索引区间{m,n}的元素排好序，整个数组就是有序的。
注意：n-m尽量最小，也就是说，找出符合条件的最短序列。函数返回值为{m,n}，
	若不存在这样的m和n（例如整个数组是有序的），请返回{-1,-1}。
	示例：
	输入： {1,2,4,7,10,11,7,12,6,7,16,18,19}
	输出： {3,9}
提示：
	0 <= len(array) <= 1000000 */

class Solution {
public:
	vector<int> subSort(vector<int> &array) {
		if(array.size() < 2) return { -1, -1 };
		int n = array.size(), l = -1, r = -1;
		vector<int> lMax(n);
		lMax[0] = array[0];
		for(int i = 1; i < n; ++i) {
			lMax[i] = max(lMax[i - 1], array[i]);
		}
		int rMin = array.back();
		for(int i = n - 1; i >= 0; --i) {
			rMin = min(rMin, array[i]);
			if(rMin < lMax[i] && r == -1) {
				r = i;
			} else if(rMin >= lMax[i] && r != -1 && l == -1) {
				l = i + 1;
			}
		}
		if(r != -1 && l == -1) {
			l = 0;
		}
		return { l, r };
	}
}; // 左边的最大值和右边的最小值不能交叉，交叉则为乱序

int main() {
	Solution sol;
	vector<int> array;
	array = { 5, 4, 3, 2, 1, 6, 7 };
	cout << sol.subSort(array) << endl;

	array = { 1, 2, 4, 7, 10, 11, 7, 12, 6, 7, 16, 18, 19 };
	cout << sol.subSort(array) << endl;
}