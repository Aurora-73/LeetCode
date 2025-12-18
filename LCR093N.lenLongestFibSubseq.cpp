// Created: 2025-12-18
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 如果序列X_1, X_2, ..., X_n满足下列条件，就说它是斐波那契式的：
	n >= 3
	对于所有i + 2 <= n，都有X_i + X_{i+1} = X_{i+2}
给定一个严格递增的正整数数组形成序列 arr，找到 arr 中最长的斐波那契式的子序列的长度。
如果一个不存在，返回0。
（回想一下，子序列是从原序列 arr 中派生出来的，它从 arr 中删掉任意数量的元素（也可以不删），
而不改变其余元素的顺序。例如，{3, 5, 8}是{3, 4, 5, 6, 7, 8}的一个子序列）
示例 1：
	输入: arr = {1,2,3,4,5,6,7,8}
	输出: 5
	解释: 最长的斐波那契式子序列为 {1,2,3,5,8}。
示例2：
	输入: arr = {1,3,7,11,12,14,18}
	输出: 3
	解释: 最长的斐波那契式子序列有 {1,11,12}、{3,11,14} 以及 {7,11,18}。
提示：
	3 <= arr.length <= 1000
	1 <= arr{i} < arr{i + 1} <= 10^9 */

class Solution1 {
public:
	int lenLongestFibSubseq(vector<int> &arr) {
		int n = arr.size(), maxLen = 0;
		unordered_map<int, int> map;
		for(int i = 0; i < n; ++i) {
			// 两数之和查找有没有存在的前缀，找到一个就继续前推，直到无法前推
			for(int j = i - 1; j >= 0; --j) {
				int a = i, b = j, currLen = 2;
				auto it = map.find(arr[a] - arr[b]);
				while(it != map.end() && it->second < b) {
					++currLen;
					a = b, b = it->second;
					it = map.find(arr[a] - arr[b]);
				}
				maxLen = max(currLen, maxLen);
			}
			map[arr[i]] = i;
		}
		return maxLen > 2 ? maxLen : 0;
	}
}; // 这道题要从斐波那契数列的后两位往前推，从前往后推的状态太多，无法贪心求解

class Solution2 { // 127 ms  146.5 MB
public:
	int lenLongestFibSubseq(vector<int> &arr) {
		int n = arr.size(), maxLen = 0;
		unordered_map<int, int> map;
		vector<vector<int>> dp(n, vector<int>(n)); // 初始化为2更慢，不如max函数判断是否小于3
		for(int i = 0; i < n; ++i) {
			for(int j = i - 1; j >= 0 && arr[j] * 2 > arr[i]; --j) {
				auto it = map.find(arr[i] - arr[j]);
				if(it != map.end() && it->second < j) {
					dp[i][j] = max(dp[j][it->second] + 1, 3);
					maxLen = max(dp[i][j], maxLen);
				}
			}
			map[arr[i]] = i;
		}
		return maxLen > 2 ? maxLen : 0;
	}
}; // dp[i][j]：i > j，(前i个数中)，以i，j结尾的最大斐波那契数列长度

class Solution3 { // 109 ms 17.8 MB
public:
	int lenLongestFibSubseq(vector<int> &arr) {
		int n = arr.size(), maxLen = 0;
		unordered_map<int, int> map;
		unordered_map<pair<int, int>, int, myHash> dp;
		for(int i = 0; i < n; ++i) {
			for(int j = i - 1; j >= 0 && arr[j] * 2 > arr[i]; --j) {
				auto it = map.find(arr[i] - arr[j]);
				if(it != map.end() && it->second < j) {
					auto dpit = dp.find({ j, it->second });
					int val = (dpit != dp.end()) ? (dpit->second + 1) : 3;
					dp[{ i, j }] = val;
					maxLen = max(val, maxLen);
				}
			}
			map[arr[i]] = i;
		}
		return maxLen > 2 ? maxLen : 0;
	}

private:
	struct myHash {
		uint64_t operator()(const pair<int, int> &pa) const {
			return ((uint64_t)pa.first << 32) | (uint64_t)pa.second;
		}
	};
}; // 大部分dp位用不到，用hash优化

class Solution { // 102 ms 17.3 MB
public:
	int lenLongestFibSubseq(vector<int> &arr) {
		int n = arr.size(), maxLen = 0;
		unordered_map<int, int> map;
		unordered_map<uint64_t, int> dp;
		for(int i = 0; i < n; ++i) {
			for(int j = i - 1; j >= 0 && arr[j] * 2 > arr[i]; --j) {
				auto it = map.find(arr[i] - arr[j]);
				if(it != map.end() && it->second < j) {
					auto dpit = dp.find(p2u(j, it->second));
					int val = (dpit != dp.end()) ? (dpit->second + 1) : 3;
					dp[p2u(i, j)] = val;
					maxLen = max(val, maxLen);
				}
			}
			map[arr[i]] = i;
		}
		return maxLen > 2 ? maxLen : 0;
	}

private:
	inline uint64_t p2u(int a, int b) {
		return ((uint64_t)a << 32) | (uint64_t)b;
	} // pair<int, int> 转为 uint64_t
}; // 哈希表的 pair<int, int> 直接转为 uint64_t

int main() {
	Solution sol;
	vector<int> arr;
	arr = { 1, 2, 3, 4, 5, 6, 7, 8 };
	cout << sol.lenLongestFibSubseq(arr) << endl;
	arr = { 1, 3, 7, 11, 12, 14, 18 };
	cout << sol.lenLongestFibSubseq(arr) << endl;
}