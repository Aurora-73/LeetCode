// Created: 2025-05-21
#include "MyUtils.h"
#include <numeric>

/*149. 直线上最多的点数
给你一个数组 points ，其中 points[i] = [xi, yi] 表示 X-Y
平面上的一个点。求最多有多少个点在同一条直线上。*/

// 哈希函数，用于unordered_map中pair<int, int>作为key
struct pair_hash {
	size_t operator()(const pair<int, int> &p) const {
		return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
	}
};

class Solution {
public:
	int maxPoints(vector<vector<int>> &points) {
		int max_points = 0, n = points.size();
		// 枚举每个点，作为直线的起点
		for(int i = 0; i < n; ++i) {
			unordered_map<pair<int, int>, int, pair_hash> rates; // 统计斜率出现次数
			int same = 1;                                        // 记录与i重合的点（包括自身）
			for(int j = 0; j < n; ++j) {
				if(i == j) continue; // 跳过自身
				int dx = points[j][0] - points[i][0];
				int dy = points[j][1] - points[i][1];
				if(dx == 0 && dy == 0) {
					// 点j与点i重合
					++same;
					continue;
				}
				// 计算dx和dy的最大公约数，进行约分
				int gdc_num = std::gcd(dx, dy);
				dx /= gdc_num;
				dy /= gdc_num;
				// 保证斜率唯一性，处理符号
				if(dx < 0) {
					dx = -dx;
					dy = -dy;
				} else if(dx == 0) {
					// 垂直线，dy只保留正号
					dy = abs(dy); // 0 与任意整数 a 的最大公约数是 |a|（a 的绝对值）。
				}
				// 统计该斜率出现的次数
				++rates[{ dx, dy }];
			}
			int cur_max = 0;
			// 找出当前点为起点时，最多的共线点数
			for(auto &rate : rates) {
				cur_max = max(cur_max, rate.second);
			}
			// 更新全局最大值（加上与i重合的点）
			max_points = max(max_points, cur_max + same);
		}
		return max_points;
	}
};

int main() {
	Solution sol;
	vector<vector<int>> points = { { 1, 1 }, { 3, 2 }, { 5, 3 }, { 4, 1 }, { 2, 3 }, { 1, 4 } };
	cout << sol.maxPoints(points) << endl;
}