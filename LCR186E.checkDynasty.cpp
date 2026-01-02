// Created: 2025-06-29
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 186. 文物朝代判断
展览馆展出来自 13 个朝代的文物，每排展柜展出 5 个文物。
某排文物的摆放情况记录于数组 places，其中 places{i} 表示处于第 i 位文物的所属朝代编号。其中，
编号为 0 的朝代表示未知朝代。请判断并返回这排文物的所属朝代编号是否能够视为连续的五个朝代
（如遇未知朝代可算作连续情况）。
示例 1：
	输入：places = {0, 6, 9, 0, 7}
	输出：True
示例2：
	输入：places = {7, 8, 9, 10, 11}
	输出：True
提示：
	places.length = 5
	0 <= places{i} <= 13 */

class Solution1 {
public:
	bool checkDynasty(vector<int> &places) {
		ranges::sort(places);
		int zeroCount = 0;
		for(int i = 0; i < 5 && places[i] == 0; ++i) ++zeroCount;
		if(zeroCount == 5) return true;
		int prev = places[zeroCount];
		for(int i = zeroCount + 1; i < 5; ++i) {
			if(places[i] == prev) {
				return false;
			} else if(places[i] > prev + 1) {
				while(places[i] > prev + 1) {
					if(zeroCount) {
						--zeroCount, ++prev;
					} else {
						return false;
					}
				}
			}
			prev = places[i];
		}
		return true;
	}
};

class Solution2 {
public:
	bool checkDynasty(vector<int> &places) {
		unordered_set<int> repeat;
		int ma = 0, mi = 14;
		for(int place : places) {
			if(place == 0) continue;                             // 跳过未知朝代
			ma = max(ma, place);                                 // 最大编号朝代
			mi = min(mi, place);                                 // 最小编号朝代
			if(repeat.find(place) != repeat.end()) return false; // 若有重复，提前返回 false
			repeat.insert(place);                                // 添加此朝代至 Set
		}
		return ma - mi < 5; // 最大编号朝代 - 最小编号朝代 < 5 则连续
	}
};

class Solution {
public:
	bool checkDynasty(vector<int> &places) {
		int max_val = numeric_limits<int>::min(), min_val = numeric_limits<int>::max(), set = 0;
		for(auto p : places) {
			if(p != 0) {
				if(set & 1 << p) return false;
				set |= 1 << p; // 0 <= places{i} <= 13 直接位运算
				max_val = max(max_val, p);
				min_val = min(min_val, p);
			}
		}
		if(max_val - min_val > 4) return false;
		return true;
	}
};

int main() {
	Solution sol;
	vector<int> places;
	places = { 9, 0, 6, 0, 10 };
	cout << sol.checkDynasty(places) << endl; // true
	places = { 0, 6, 9, 0, 7 };
	cout << sol.checkDynasty(places) << endl; // true
	places = { 7, 8, 9, 10, 11 };
	cout << sol.checkDynasty(places) << endl; // true
	places = { 5, 5, 5, 5, 5 };
	cout << sol.checkDynasty(places) << endl; // false
	places = { 5, 6, 8, 9, 4 };
	cout << sol.checkDynasty(places) << endl; // false
	places = { 1, 2, 12, 0, 3 };
	cout << sol.checkDynasty(places) << endl; // false
}