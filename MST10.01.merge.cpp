// Created: 2025-12-29
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定两个排序后的数组 A 和 B，其中 A 的末端有足够的缓冲空间容纳 B。
编写一个方法，将 B 合并入 A 并排序。
初始化A 和 B 的元素数量分别为m 和 n。
输入：
    A = {1,2,3,0,0,0}, m = 3
    B = {2,5,6},       n = 3
输出：
    {1,2,2,3,5,6}
说明：
	A.length == n + m */

class Solution1 {
public:
	void merge(vector<int> &A, int m, vector<int> &B, int n) {
		vector<int> res(m + n);
		int i = 0, j = 0;
		for(int k = 0; k < m + n; ++k) {
			if(i < m && j < n) {
				if(A[i] < B[j]) {
					res[k] = A[i++];
				} else {
					res[k] = B[j++];
				}
			} else if(i < m) {
				res[k] = A[i++];
			} else {
				res[k] = B[j++];
			}
		}
		A = std::move(res);
	}
};

class Solution {
public:
	void merge(vector<int> &A, int m, vector<int> &B, int n) {
		int i = m - 1, j = n - 1;
		for(int k = m + n - 1; k >= 0; --k) {
			if(i >= 0 && j >= 0) {
				if(A[i] > B[j]) {
					A[k] = A[i--];
				} else {
					A[k] = B[j--];
				}
			} else if(i >= 0) {
				A[k] = A[i--];
			} else {
				A[k] = B[j--];
			}
		}
	}
}; // 因为A前面已经有数，且后面是空的，可以直接进行倒序赋值，这样不会覆盖且不用额外空间

int main() {
	Solution sol;
	vector<int> A, B;
	int n, m;
	A = { 1, 2, 3, 0, 0, 0 }, m = 3, B = { 2, 5, 6 }, n = 3;
	sol.merge(A, m, B, n);
	cout << A << endl;
}