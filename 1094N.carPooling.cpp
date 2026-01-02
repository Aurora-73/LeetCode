// Created: 2026-01-02
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 车上最初有capacity个空座位。
车只能向一个方向行驶（也就是说，不允许掉头或改变方向）
给定整数capacity和一个数组 trips , trips{i} = {numPassengersi, fromi, toi}表示第 i 次旅行有numPassengersi乘客，
接他们和放他们的位置分别是fromi和toi。这些位置是从汽车的初始位置向东的公里数。
当且仅当你可以在所有给定的行程中接送所有乘客时，返回true，否则请返回 false。
to 为下车点，不占座位。
示例 1：
	输入：trips = {{2,1,5},{3,3,7}}, capacity = 4
	输出：false
示例 2：
	输入：trips = {{2,1,5},{3,3,7}}, capacity = 5
	输出：true
提示：
	1 <= trips.length <= 1000
	trips{i}.length == 3
	1 <= numPassengersi<= 100
	0 <= fromi< toi<= 1000
	1 <= capacity <= 10^5 */

class Solution {
public:
	bool carPooling(vector<vector<int>> &trips, int capacity) {
		array<int, 1002> increase {};
		for(auto &trip : trips) {
			increase[trip[1]] += trip[0];
			increase[trip[2]] -= trip[0];
		}
		int curr = 0;
		for(int inc : increase) {
			curr += inc;
			if(curr > capacity) {
				return false;
			}
		}
		return true;
	}
}; // 查分数组

int main() {
	Solution sol;
	vector<vector<int>> trips;
	int capacity;
	trips = { { 2, 1, 5 }, { 3, 3, 7 } }, capacity = 4;
	cout << sol.carPooling(trips, capacity) << endl;

	trips = { { 2, 1, 5 }, { 3, 3, 7 } }, capacity = 5;
	cout << sol.carPooling(trips, capacity) << endl;
}