// Created: 2025-06-01
#include "MyUtils.h"

/*435. 无重叠区间
给定一个区间的集合 intervals ，其中 intervals{i} = {starti, endi} 。返回 需要移除区间的最小数量，使剩余区间互不重叠 。
注意 只在一点上接触的区间是 不重叠的。例如 {1, 2} 和 {2, 3} 是不重叠的。
示例 1:
    输入: intervals = {{1,2},{2,3},{3,4},{1,3}}
    输出: 1
    解释: 移除 {1,3} 后，剩下的区间没有重叠。*/

class Solution {
public:
	int eraseOverlapIntervals(vector<vector<int>> &intervals) {
		std::sort(intervals.begin(), intervals.end(), [](const auto &u, const auto &v) {
			return u[0] < v[0]; // 比默认的比较函数快一半
		});
		int n = intervals.size(), count = 0, preVal = intervals[0][1];
		for(int i = 1; i < n; ++i) {
			auto &interval = intervals[i];
			if(preVal > interval[0]) {
				++count;
				preVal = min(preVal, interval[1]);
			} else {
				preVal = interval[1];
			}
		}
		return count;
	}
};

int main() {
	Solution sol;
	vector<vector<int>> intervals { { 1, 100 }, { 11, 22 }, { 1, 11 }, { 2, 12 } };
	cout << sol.eraseOverlapIntervals(intervals) << endl;
	intervals = { { 1, 2 },
		{ 2, 3 },
		{ 3, 4 },
		{ 1, 3 },
		{ 2, 3 },
		{ 3, 4 },
		{ 1, 3 },
		{ 1, 2 },
		{ 1, 2 },
		{ 2, 3 } };
	cout << sol.eraseOverlapIntervals(intervals) << endl;
}