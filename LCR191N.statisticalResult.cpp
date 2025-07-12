// Created: 2025-07-02
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 191. 按规则计算统计结果
为了深入了解这些生物群体的生态特征，你们进行了大量的实地观察和数据采集。
数组 arrayA 记录了各个生物群体数量数据，其中 arrayA{i} 表示第 i 个生物群体的数量。请返回一个数组 arrayB，
该数组为基于数组 arrayA 中的数据计算得出的结果，其中 arrayB{i} 表示将第 i 个生物群体的数量从总体中排除后的其他数量的乘积。
示例 1：
	输入：arrayA = {2, 4, 6, 8, 10}
	输出：{1920, 960, 640, 480, 384}
提示：
	所有元素乘积之和不会溢出 32 位整数
	arrayA.length <= 100000 */

class Solution1 {
public:
	vector<int> statisticalResult(vector<int> &arrayA) {
		int zeroIndex = -1, n = arrayA.size(), allMul = 1;
		vector<int> res(n);
		for(int i = 0; i < n; ++i) {
			if(arrayA[i] == 0) {
				if(zeroIndex == -1) {
					zeroIndex = i;
				} else {
					return res;
				}
			} else {
				allMul *= arrayA[i];
			}
		}
		if(zeroIndex != -1) {
			res[zeroIndex] = allMul;
		} else {
			for(int i = 0; i < n; ++i) {
				res[i] = allMul / arrayA[i];
			}
		}
		return res;
	}
};

class Solution2 {
public:
	vector<int> statisticalResult(vector<int> &arrayA) {
		int n = arrayA.size();
		if(!n) return {};
		vector<int> res(n), left(n), right(n);
		left.front() = right.back() = 1;
		for(int i = 1; i < n; ++i) {
			left[i] = left[i - 1] * arrayA[i - 1];
			right[n - i - 1] = right[n - i] * arrayA[n - i];
		}
		for(int i = 0; i < n; ++i) {
			res[i] = left[i] * right[i];
		}
		return res;
	}
};

class Solution {
public:
	vector<int> statisticalResult(vector<int> &arrayA) {
		int n = arrayA.size(), left = 1, right = 1;
		if(!n) return {};
		vector<int> res(n, 1);
		for(int i = 1; i < n; ++i) {
			left *= arrayA[i - 1];
			res[i] *= left;
			right *= arrayA[n - i];
			res[n - i - 1] *= right;
		}
		return res;
	}
};

int main() {
	Solution sol;
	vector<int> arrayA;
	arrayA = { 2, 4, 6, 8, 10 };
	cout << sol.statisticalResult(arrayA) << endl; // {1920, 960, 640, 480, 384}
	arrayA = { 2, 4, 6, 0, 10 };
	cout << sol.statisticalResult(arrayA) << endl; // { 0, 0, 0, 480, 0 }
	arrayA = { 2, 0, 6, 0, 10 };
	cout << sol.statisticalResult(arrayA) << endl; // { 0, 0, 0, 0, 0 }
}