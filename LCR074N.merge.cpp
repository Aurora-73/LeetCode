// Created: 2025-12-12
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals{i} = {starti, endi}。
请你合并所有重叠的区间，并返回一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间。
示例 1：
	输入：intervals = {{1,3},{2,6},{8,10},{15,18}}
	输出：{{1,6},{8,10},{15,18}}
	解释：区间 {1,3} 和 {2,6} 重叠, 将它们合并为 {1,6}.
示例2：
	输入：intervals = {{1,4},{4,5}}
	输出：{{1,5}}
	解释：区间 {1,4} 和 {4,5} 可被视为重叠区间。
提示：
	1 <= intervals.length <= 10^4
	intervals{i}.length == 2
	0 <= starti <= endi <= 10^4 */

class Solution {
public:
	vector<vector<int>> merge(vector<vector<int>> &intervals) {
		std::sort(intervals.begin(), intervals.end());
		int i = 0, j = 1, endi = intervals[0][1], n = intervals.size();
		while(j < n) {
			if(intervals[j][0] > endi) {
				intervals[i][1] = endi;
				++i;
				intervals[i][0] = intervals[j][0];
			}
			endi = max(endi, intervals[j][1]);
			++j;
		}
		intervals[i][1] = endi;
		intervals.resize(i + 1);
		return intervals;
	}
};

int main() {
	Solution sol;
	vector<vector<int>> intervals;
	intervals = { { 1, 3 }, { 2, 6 }, { 8, 10 }, { 15, 18 } };
	cout << sol.merge(intervals) << endl;
}