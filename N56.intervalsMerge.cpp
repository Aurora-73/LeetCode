#include "MyUtils.h"

/*56. 合并区间
以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。请你合并所有重叠的区间，并返回 一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。
示例 1：
输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
输出：[[1,6],[8,10],[15,18]]
解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].
示例 2：
输入：intervals = [[1,4],[4,5]]
输出：[[1,5]]
解释：区间 [1,4] 和 [4,5] 可被视为重叠区间。*/

class Solution {
public:
	vector<vector<int>> merge(vector<vector<int>> &intervals) {
		sort(
		    intervals.begin(), intervals.end(), [](const vector<int> &a, const vector<int> &b) { return a[0] < b[0]; });
		int i = 0, j = 1, n = intervals.size();
		vector<vector<int>> res{intervals[0]};
		while(j < n) {
			if(res[i][1] >= intervals[j][0]) {
				// merge
				res[i][1] = max(intervals[j][1], res[i][1]); // 有可能完全被包含
			} else {
				res.push_back(intervals[j]);
				i++;
			}
			j++;
		}
		return res;
	}
};

int main() {
	Solution sol;
	vector<vector<int>> intervals = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
	cout << sol.merge(intervals) << endl;
}