// Created: 2025-06-06
#include "MyDateGen.h"
#include "MyUtils.hpp"

/*Q1. 选择不同 X 值三元组使 Y 值之和最大
给你两个整数数组 x 和 y，长度均为 n。你必须选择三个 不同 的下标 i，j 和 k，满足以下条件：
x{i} != x{j}
x{j} != x{k}
x{k} != x{i}
你的目标是在满足这些条件下 最大化 y{i} + y{j} + y{k} 的值。
返回通过选择这样一组三元组下标所能获得的 最大 可能和。
如果不存在这样的三元组，返回 -1。
示例 1：
	输入：x = {1,2,1,3,2}, y = {5,3,4,6,2}
	输出：14
	解释：
	选择 i = 0（x{i} = 1，y{i} = 5），j = 1（x{j} = 2，
	y{j} = 3），k = 3（x{k} = 3，y{k} = 6）。
	选出的三个 x 中的值互不相同。5 + 3 + 6 = 14 是我们能获得的最大值。因此输出为 14。
示例 2：
	输入：x = {1,2,1,2}, y = {4,5,6,7}
	输出：-1
	解释：
	x 中只有两个不同的值。因此输出为 -1。
提示：
	n == x.length == y.length
	3 <= n <= 10^5
	1 <= x{i}, y{i} <= 10^6*/

class Solution1 {
public:
	int maxSumDistinctTriplet(vector<int> &x, vector<int> &y) {
		int n = y.size();
		vector<int> index(n);
		for(int i = 0; i < n; ++i) {
			index[i] = i;
		}
		std::sort(index.begin(), index.end(), [&](int a, int b) { return y[b] < y[a]; });
		int res = -1;
		int i = 0, j, k;
		for(j = i + 1; j < n; ++j) {
			if(x[index[i]] != x[index[j]]) {
				break;
			}
		}
		for(k = j + 1; k < n; ++k) {
			if(x[index[k]] != x[index[j]] && x[index[k]] != x[index[i]]) {
				break;
			}
		}
		if(i < n && j < n && k < n) {
			res = y[i] + y[j] + y[k];
		}
		return res;
	}
};

class Solution {
public:
	int maxSumDistinctTriplet(vector<int> &x, vector<int> &y) {
		unordered_map<int, int> uniqueMap;
		int n = x.size();
		for(int i = 0; i < n; ++i) {
			if(uniqueMap.count(x[i])) {
				uniqueMap[x[i]] = max(uniqueMap[x[i]], y[i]);
			} else {
				uniqueMap[x[i]] = y[i];
			}
		}
		if(uniqueMap.size() < 3) return -1;
		vector<int> vals;
		for(auto &pair : uniqueMap) vals.push_back(pair.second);
		sort(vals.begin(), vals.end(), greater<int>());
		return vals[0] + vals[1] + vals[2];
	}
};

int main() {
	Solution sol;
	Solution1 sol1;
	vector<int> x, y;
	x = { 1, 2, 1, 3, 2 }, y = { 5, 3, 4, 6, 2 };
	cout << sol.maxSumDistinctTriplet(x, y) << endl;
	x = { 1, 2, 1, 2 }, y = { 4, 5, 6, 7 };
	cout << sol.maxSumDistinctTriplet(x, y) << endl;
	x = randomIntVector(10000, 0, 100000);
	y = randomIntVector(10000, 0, 100000);
	cout << sol.maxSumDistinctTriplet(x, y) << endl;
	cout << sol1.maxSumDistinctTriplet(x, y) << endl;
}