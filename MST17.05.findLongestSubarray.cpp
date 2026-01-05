// Created: 2026-01-05
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个放有字母和数字的数组，找到最长的子数组，且包含的字母和数字的个数相同。
返回该子数组，若存在多个最长子数组，返回左端点下标值最小的子数组。若不存在这样的数组，返回一个空数组。
示例 1：
	输入：{"A","1","B","C","D","2","3","4","E","5","F","G","6","7","H","I","J","K","L","M"}
	输出：{"A","1","B","C","D","2","3","4","E","5","F","G","6","7"}
示例 2：
	输入：{"A","A"}
	输出：{}
提示：
	array.length <= 100000 */

class Solution1 {
public:
	vector<string> findLongestSubarray(vector<string> &array) {
		int n = array.size(), curr = 0, best_begin = 0, best_last = -1;
		unordered_map<int, int> mp; // mp[i] = j 的语义是，前 i 个 str 的 |1| - |A| = j
		mp.reserve(n * 2), mp[0] = 0;
		for(int i = 0; i < n; ++i) {
			curr += isdigit(array[i][0]) ? 1 : -1;
			auto [it, succ] = mp.emplace(curr, i + 1);
			if(!succ) {
				int beg = it->second;
				if(i - beg > best_last - best_begin) {
					best_begin = beg;
					best_last = i;
				}
			}
		}
		if(best_last < 0) return {};
		return vector<string>(array.begin() + best_begin, array.begin() + best_last + 1);
	}
}; // 前缀和解法，重点在于确定mp的语义是什么，否则很容易出bug
// 这里的 emplace 并不会更快，因为插入是被很复杂，失败 =  查 + 构造参数 + 冲突处理 + 回滚

class Solution2 {
public:
	vector<string> findLongestSubarray(vector<string> &array) {
		int n = array.size(), curr = 0, best_begin = 0, best_last = -1;
		unordered_map<int, int> mp; // mp[i] = j 的语义是，前 i 个 str 的 |1| - |A| = j
		mp.reserve(n * 2), mp[0] = 0;
		for(int i = 0; i < n; ++i) {
			curr += isdigit(array[i][0]) ? 1 : -1;
			auto it = mp.find(curr);
			if(it != mp.end()) {
				int beg = it->second;
				if(i - beg > best_last - best_begin) {
					best_begin = beg;
					best_last = i;
				}
			} else {
				mp.emplace(curr, i + 1);
			}
		}
		if(best_last < 0) return {};
		return vector<string>(array.begin() + best_begin, array.begin() + best_last + 1);
	}
};

class Solution {
public:
	vector<string> findLongestSubarray(vector<string> &array) {
		int n = (int)array.size(), offset = n;
		if(n == 0) return {};

		// curr 的范围是 [-n, n]，所以数组长度取 2*n + 1
		vector<int> pos(2 * n + 1, -1); // 0xFFFFFFFF即全bit为1，也就是-1
		// pos[x + offset] 表示前缀和为 x 时，记录的“前缀长度”（也就是区间起点索引）
		pos[offset] = 0; // 前缀和为 0 时，前缀长度为 0（起点索引 0）

		int curr = 0, best_begin = 0, best_last = -1;

		for(int i = 0; i < n; ++i) {
			curr += std::isdigit(array[i][0]) ? 1 : -1;
			int idx = curr + offset;

			if(pos[idx] != -1) {
				int start = pos[idx];    // 区间起点
				int len = i - start + 1; // 当前区间长度
				int best_len = best_last - best_begin + 1;
				if(len > best_len) {
					best_begin = start;
					best_last = i;
				}
			} else {
				pos[idx] = i + 1; // 记录第一次出现：前缀长度为 i+1（起点索引 = i+1）
			}
		}

		if(best_last < 0) return {};
		return vector<string>(array.begin() + best_begin, array.begin() + best_last + 1);
	}
};

int main() {
	Solution sol;
	vector<string> array;
	array = { "42",
		"10",
		"O",
		"t",
		"y",
		"p",
		"g",
		"B",
		"96",
		"H",
		"5",
		"v",
		"P",
		"52",
		"25",
		"96",
		"b",
		"L",
		"Y",
		"z",
		"d",
		"52",
		"3",
		"v",
		"71",
		"J",
		"A",
		"0",
		"v",
		"51",
		"E",
		"k",
		"H",
		"96",
		"21",
		"W",
		"59",
		"I",
		"V",
		"s",
		"59",
		"w",
		"X",
		"33",
		"29",
		"H",
		"32",
		"51",
		"f",
		"i",
		"58",
		"56",
		"66",
		"90",
		"F",
		"10",
		"93",
		"53",
		"85",
		"28",
		"78",
		"d",
		"67",
		"81",
		"T",
		"K",
		"S",
		"l",
		"L",
		"Z",
		"j",
		"5",
		"R",
		"b",
		"44",
		"R",
		"h",
		"B",
		"30",
		"63",
		"z",
		"75",
		"60",
		"m",
		"61",
		"a",
		"5",
		"S",
		"Z",
		"D",
		"2",
		"A",
		"W",
		"k",
		"84",
		"44",
		"96",
		"96",
		"y",
		"M" };
	cout << sol.findLongestSubarray(array) << endl;

	array = { "A",
		"1",
		"B",
		"C",
		"D",
		"2",
		"3",
		"4",
		"E",
		"5",
		"F",
		"G",
		"6",
		"7",
		"H",
		"I",
		"J",
		"K",
		"L",
		"M" };
	cout << sol.findLongestSubarray(array) << endl;

	array = { "A", "A" };
	cout << sol.findLongestSubarray(array) << endl;
}