// Created: 2025-07-10
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 2300. 咒语和药水的成功对数
给你两个正整数数组spells 和potions，长度分别为n 和m，
其中spells{i}表示第i个咒语的能量强度，potions{j}表示第j瓶药水的能量强度。
同时给你一个整数success。一个咒语和药水的能量强度 相乘 如果大于等于success，那么它们视为一对成功的组合。
请你返回一个长度为 n的整数数组pairs，其中pairs{i}是能跟第 i个咒语成功组合的 药水数目。
示例 1：
	输入：spells = {5,1,3}, potions = {1,2,3,4,5}, success = 7
	输出：{4,0,3}
	解释：
	- 第 0 个咒语：5 * {1,2,3,4,5} = {5,10,15,20,25}。总共 4 个成功组合。
	- 第 1 个咒语：1 * {1,2,3,4,5} = {1,2,3,4,5}。总共 0 个成功组合。
	- 第 2 个咒语：3 * {1,2,3,4,5} = {3,6,9,12,15}。总共 3 个成功组合。
	所以返回 {4,0,3}。
示例 2：
	输入：spells = {3,1,2}, potions = {8,5,8}, success = 16
	输出：{2,0,2}
	解释：
	- 第 0 个咒语：3 * {8,5,8} = {24,15,24}。总共 2 个成功组合。
	- 第 1 个咒语：1 * {8,5,8} = {8,5,8}。总共 0 个成功组合。
	- 第 2 个咒语：2 * {8,5,8} = {16,10,16}。总共 2 个成功组合。
	所以返回 {2,0,2}。
提示：
	n == spells.length
	m == potions.length
	1 <= n, m <= 10^5
	1 <= spells{i}, potions{i} <= 10^5
	1 <= success <= 10^10 */

class Solution {
public:
	vector<int> successfulPairs(vector<int> &spells, vector<int> &potions, long long success) {
		std::sort(potions.begin(), potions.end());
		int n = spells.size();
		vector<int> res;
		res.reserve(n);
		for(auto sp : spells) {
			double need = (success * 1.0) / sp;
			res.push_back(potions.end() - lower_bound(potions.begin(), potions.end(), need));
		}
		return res;
	}
};

int main() {
	Solution sol;
	vector<int> spells, potions;
	long long success;
	spells = { 5, 1, 3 }, potions = { 1, 2, 3, 4, 5 }, success = 7;
	cout << sol.successfulPairs(spells, potions, success) << endl; // {4,0,3}
	spells = { 3, 1, 2 }, potions = { 8, 5, 8 }, success = 16;
	cout << sol.successfulPairs(spells, potions, success) << endl; // {2,0,2}
}