// Created: 2026-01-05
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 有个马戏团正在设计叠罗汉的表演节目，一个人要站在另一人的肩膀上。
出于实际和美观的考虑，在上面的人要比下面的人矮一点且轻一点。已知马戏团每个人的身高和体重，请编写代码计算叠罗汉最多能叠几个人。
示例：
输入：height = {65,70,56,75,60,68} weight = {100,150,90,190,95,110}
输出：6
解释：从上往下数，
叠罗汉最多能叠 6 层：(56,90), (60,95), (65,100), (68,110), (70,150), (75,190)
提示：
	height.length == weight.length <= 10000 */

class Solution1 {
public:
	int bestSeqAtIndex(vector<int> &height, vector<int> &weight) {
		int n = height.size(), res = 0;
		vector<int> index;
		index.reserve(n);
		for(int i = 0; i < n; ++i) index.push_back(i);
		std::sort(index.begin(), index.end(), [&](int l, int r) { return height[l] < height[r]; });
		vector<int> dp(n + 1);
		for(int i = 0; i < n; ++i) {
			int hi = height[index[i]], wi = weight[index[i]], curr = 0;
			for(int j = i - 1; j >= curr; --j) {
				if(hi > height[index[j]] && wi > weight[index[j]]) {
					curr = max(curr, dp[j]);
				}
			}
			dp[i] = ++curr;
			res = max(res, curr);
		}
		return res;
	}
}; // 排序 + 带贪心的动态规划

class Solution2 {
public:
	int bestSeqAtIndex(vector<int> &height, vector<int> &weight) {
		int n = height.size();
		vector<int> index;
		index.reserve(n);
		for(int i = 0; i < n; ++i) index.push_back(i);
		std::sort(index.begin(), index.end(), [&](int l, int r) {
			if(height[l] != height[r])
				return height[l] < height[r];
			else
				return weight[l] > weight[r];
		});
		vector<int> lst;
		lst.reserve(n);
		for(int i = 0; i < n; ++i) {
			int we = weight[index[i]];
			auto it = lower_bound(lst.begin(), lst.end(), we);
			if(it != lst.end()) {
				*it = we;
			} else {
				lst.push_back(we);
			}
		}
		return lst.size();
	}
}; // 一个维度排序，一个维度做LST，注意等大不能放，因此第一维相等第二维要倒序

class Solution {
public:
	int bestSeqAtIndex(vector<int> &height, vector<int> &weight) {
		int n = height.size();
		vector<pair<int, int>> combo;
		combo.reserve(n);
		for(int i = 0; i < n; ++i) combo.emplace_back(height[i], weight[i]);
		std::sort(
		    combo.begin(), combo.end(), [&](const pair<int, int> &l, const pair<int, int> &r) {
			    return l.first != r.first ? l.first < r.first : l.second > r.second;
		    });
		vector<int> lst;
		lst.reserve(n);
		for(auto [w, h] : combo) {
			auto it = lower_bound(lst.begin(), lst.end(), h);
			if(it != lst.end()) {
				*it = h;
			} else {
				lst.push_back(h);
			}
		}
		return lst.size();
	}
}; // 一个维度排序，一个维度做LST，注意等大不能放，因此第一维相等第二维要倒序

int main() {
	Solution sol;
	vector<int> height, weight;
	height = { 65, 70, 56, 75, 60, 68 }, weight = { 100, 150, 90, 190, 95, 110 };
	cout << sol.bestSeqAtIndex(height, weight) << endl;
}