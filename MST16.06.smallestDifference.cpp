// Created: 2026-01-02
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定两个整数数组a和b，计算具有最小差绝对值的一对数值（每个数组中取一个值），并返回该对数值的差
示例：
输入：{1, 3, 15, 11, 2}, {23, 127, 235, 19, 8}
输出：3，即数值对(11, 8)
提示：
	1 <= a.length, b.length <= 100000
	-2147483648 <= a{i}, b{i} <= 2147483647
	正确结果在区间 {0, 2147483647} 内 */

class Solution1 {
public:
	int smallestDifference(vector<int> &a, vector<int> &b) {
		ranges::sort(a), ranges::sort(b);
		int na = a.size(), nb = b.size(), i = 0, j = 0;
		long long res = numeric_limits<long long>::max();
		while(i < na && j < nb) {
			res = min(res, abs(a[i] + 0ll - b[j]));
			if(res == 0) return 0;
			if(a[i] < b[j]) {
				++i;
			} else {
				++j;
			}
		}
		return res;
	}
}; // 大部分设备上long和int的范围是一样的，都是32位
// 但是long long至少64位

class Solution2 {
public:
	int smallestDifference(vector<int> &a, vector<int> &b) {
		if(a.size() > b.size()) swap(a, b);
		ranges::sort(a);
		int na = a.size(), nb = b.size();
		long long res = numeric_limits<long long>::max();
		for(int i = 0; i < nb; ++i) {
			auto it = lower_bound(a.begin(), a.end(), b[i]);
			if(it != a.end()) {
				res = min(res, abs(*it + 0ll - b[i]));
				if(res == 0) return 0;
			}
			if(it != a.begin()) {
				res = min(res, abs(*prev(it) + 0ll - b[i]));
				if(res == 0) return 0;
			}
		}
		return res;
	}
}; // 对短的排序，当两个数组长度差别较大时更有效

class Solution {
public:
	int smallestDifference(vector<int> &a, vector<int> &b) {
		if(a.empty() || b.empty()) return numeric_limits<int>::max();
		int na = a.size(), nb = b.size();
		int minn = min(na, nb), maxn = max(na, nb);
		if(minn * 1.5 <= maxn) {
			return twoPointerBothSorted(a, b);
		} else {
			if(nb < na) {
				return binarySearchShortSorted(b, a);
			} else {
				return binarySearchShortSorted(a, b);
			}
		}
	}

private:
	int twoPointerBothSorted(vector<int> &a, vector<int> &b) {
		sort(a.begin(), a.end()), sort(b.begin(), b.end());
		const int na = (int)a.size(), nb = (int)b.size();
		int i = 0, j = 0;
		long long best = numeric_limits<long long>::max();
		while(i < na && j < nb) {
			long long diff = 0ll + a[i] - b[j];
			long long ad = diff < 0 ? -diff : diff;
			if(ad < best) best = ad;
			if(best == 0) return 0;
			if(a[i] < b[j])
				++i;
			else
				++j;
		}
		return (int)best;
	} // 两个都排序，然后双指针

	// 只排序短的数组，对长数组逐元素二分查找
	// 要求 smallVec 已经比 bigVec 短
	int binarySearchShortSorted(vector<int> &smallVec, vector<int> &bigVec) {
		sort(smallVec.begin(), smallVec.end());
		long long best = numeric_limits<long long>::max();
		const int nb = (int)bigVec.size();
		for(int i = 0; i < nb; ++i) {
			int x = bigVec[i];
			auto it = lower_bound(smallVec.begin(), smallVec.end(), x);
			if(it != smallVec.end()) {
				long long ad = abs(0ll + *it - x);
				if(ad < best) best = ad;
				if(best == 0) return 0;
			}
			if(it != smallVec.begin()) {
				long long ad = abs(0ll + *prev(it) - x);
				if(ad < best) best = ad;
				if(best == 0) return 0;
			}
		}
		return (int)best;
	} // 对短的排序，当两个数组长度差别较大时更有效
};

int main() {
	Solution sol;
	vector<int> a, b;
	a = { 1, 3, 15, 11, 2 };
	b = { 23, 127, 235, 19, 8 };
	cout << sol.smallestDifference(a, b) << endl;
}