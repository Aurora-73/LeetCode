// Created: 2026-01-02
#include "MyUtils.hpp"
#include <numeric>
// #ifdef MY_UTILS_H

/* 给定一个二维平面及平面上的 N 个点列表Points，其中第i个点的坐标为Points{i}={Xi,Yi}。
请找出一条直线，其通过的点的数目最多。
设穿过最多点的直线所穿过的全部点编号从小到大排序的列表为S，你仅需返回{S{0},S{1}}作为答案，
若有多条直线穿过了相同数量的点，则选择S{0}值较小的直线返回，S{0}相同则选择S{1}值较小的直线返回。
示例：
    输入： {{0,0},{1,1},{1,0},{2,0}}
    输出： {0,2}
解释： 所求直线穿过的3个点的编号为{0,2,3}
提示：
	2 <= len(Points) <= 300
	len(Points{i}) = 2 */

class Solution1 {
public:
	vector<int> bestLine(vector<vector<int>> &points) {
		int n = points.size(), max_cnt = 0;
		vector<int> res { n, n };
		for(int i = 0; i + max_cnt < n; ++i) {
			unordered_map<double, pair<int, int>> rate_map;
			pair<int, int> nan_rate { 0, 0 };
			for(int j = i + 1; j < n; ++j) {
				if(points[i][1] == points[j][1]) {
					if(nan_rate.second == 0) {
						nan_rate.first = j;
					}
					++nan_rate.second;
				} else {
					double rate
					    = 1.0 * (points[i][0] - points[j][0]) / (points[i][1] - points[j][1]);
					auto it = rate_map.emplace(rate, make_pair(j, 0));
					++it.first->second.second;
				}
			}
			if(nan_rate.second > max_cnt) {
				max_cnt = nan_rate.second;
				res = { i, nan_rate.first };
			}
			if(nan_rate.second == max_cnt && res[0] == i) {
				res[1] = min(res[1], nan_rate.first);
			}
			for(auto &[_, pa] : rate_map) {
				if(pa.second > max_cnt) {
					max_cnt = pa.second;
					res = { i, pa.first };
				}
				if(pa.second == max_cnt && res[0] == i) {
					res[1] = min(res[1], pa.first);
				}
			}
		}
		return res;
	}
}; // 浮点数哈希很危险，而且没有考虑重复点

class Solution {
public:
	vector<int> bestLine(vector<vector<int>> &points) {
		int n = points.size();
		int max_cnt = 0;          // 已记录的最大 "不含 i 的其他点数"
		vector<int> res { n, n }; // 结果索引对，初值为不可能的值
		for(int i = 0; i < n && i + max_cnt < n; ++i) {
			unordered_map<pair<int, int>, pair<int, int>, PairHash> mp;
			// map: slope_key -> (first_j_index, count_of_j)
			int duplicates = 0;
			int first_dup = n; // 若有重复点，记录第一个重复点的索引

			for(int j = i + 1; j < n; ++j) {
				int dx = (int)points[j][0] - points[i][0];
				int dy = (int)points[j][1] - points[i][1];

				if(dx == 0 && dy == 0) { // 重复点
					if(duplicates == 0) first_dup = j;
					++duplicates;
					continue;
				}

				int adx = dx < 0 ? -dx : dx;
				int ady = dy < 0 ? -dy : dy;
				int g = std::gcd(adx, ady);
				dx /= g;
				dy /= g;
				// 归一化符号：保证唯一表示
				if(dx < 0) {
					dx = -dx;
					dy = -dy;
				}
				if(dx == 0 && dy < 0) dy = -dy;
				pair<int, int> key { dx, dy };
				auto &entry = mp[key];
				if(entry.second == 0) entry.first = j; // 记录该斜率的第一个 j（最小的 j）
				++entry.second;
			}
			// 先考虑只有重复点的情况（所有 j 都与 i 重合）
			if(duplicates > max_cnt) {
				max_cnt = duplicates;
				res = { i, first_dup };
			} else if(duplicates == max_cnt && res[0] == i) {
				res[1] = min(res[1], first_dup);
			}
			// 再遍历每个斜率桶，计入 duplicates
			for(auto &kv : mp) {
				int cnt_excluding_i = kv.second.second + duplicates; // 不含 i 的其他点数
				int first_j = kv.second.first;
				if(cnt_excluding_i > max_cnt) {
					max_cnt = cnt_excluding_i;
					res = { i, first_j };
				} else if(cnt_excluding_i == max_cnt && res[0] == i) {
					res[1] = min(res[1], first_j);
				}
			}
		}
		return res;
	}

private:
	struct PairHash {
		size_t operator()(const pair<int, int> &p) const noexcept {
			return ((uint64_t)(uint32_t)p.first << 32) ^ (uint64_t)(uint32_t)p.second;
		}
	};
};

int main() {
	Solution sol;
	vector<vector<int>> points;
	points = { { -38935, 27124 },
		{ -39837, 19604 },
		{ -7086, 42194 },
		{ -11571, -23257 },
		{ 115, -23257 },
		{ 20229, 5976 },
		{ 24653, -18488 },
		{ 11017, 21043 },
		{ -9353, 16550 },
		{ -47076, 15237 },
		{ -36686, 42194 },
		{ -17704, 1104 },
		{ 31067, 7368 },
		{ -20882, 42194 },
		{ -19107, -10597 },
		{ -14898, 24506 },
		{ -20801, 42194 },
		{ -52268, 40727 },
		{ -14042, 42194 },
		{ -23254, 42194 },
		{ -30837, -53882 },
		{ 1402, 801 },
		{ -33961, -984 },
		{ -6411, 42194 },
		{ -12210, 22901 },
		{ -8213, -19441 },
		{ -26939, 20810 },
		{ 30656, -23257 },
		{ -27195, 21649 },
		{ -33780, 2717 },
		{ 23617, 27018 },
		{ 12266, 3608 } };
	cout << sol.bestLine(points) << endl;

	points = { { 0, 0 }, { 1, 1 }, { 1, 0 }, { 2, 0 }, { 2, 2 } };
	cout << sol.bestLine(points) << endl; // [0,1]

	points = { { 0, 0 }, { 1, 1 }, { 1, 0 }, { 2, 0 } };
	cout << sol.bestLine(points) << endl;
}