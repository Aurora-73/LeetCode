#include "MyUtils.hpp"

/*56. 合并区间
以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals{i} = {starti, endi}。
请你合并所有重叠的区间，并返回一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间。
示例 1：
	输入：intervals = {{1,3},{2,6},{8,10},{15,18}}
	输出：{{1,6},{8,10},{15,18}}
	解释：区间 {1,3} 和 {2,6} 重叠, 将它们合并为 {1,6}.
示例2：
	输入：intervals = {{1,4},{4,5}}
	输出：{{1,5}}
	解释：区间 {1,4} 和 {4,5} 可被视为重叠区间。
示例 3：
	输入：intervals = {{4,7},{1,4}}
	输出：{{1,7}}
	解释：区间 {1,4} 和 {4,7} 可被视为重叠区间。
提示：
	1 <= intervals.length <= 10^4
	intervals{i}.length == 2
	0 <= starti <= endi <= 10^4 */

class Solution1 {
public:
	vector<vector<int>> merge(vector<vector<int>> &intervals) {
		sort(intervals.begin(), intervals.end());
		int i = 0, j = 1, n = intervals.size();
		vector<vector<int>> res { intervals[0] };
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

class Solution {
public:
	vector<vector<int>> merge(vector<vector<int>> &intervals) {
		std::sort(intervals.begin(), intervals.end());
		int i = 0, j = 0, n = intervals.size();
		while(i < n) {
			intervals[j][0] = intervals[i][0];
			int end = intervals[i][1];
			++i;
			while(i < n && end >= intervals[i][0]) { // 左端点小于end的都可以合并进去
				end = max(end, intervals[i][1]);     // 右端点更新
				++i;
			}
			intervals[j][1] = end; // 赋值更新右端点
			++j;
		}
		intervals.resize(j);
		return intervals;
	}
};

int main() {
	Solution sol;
	vector<vector<int>> intervals;
	intervals = { { 1, 3 }, { 2, 6 }, { 8, 10 }, { 15, 18 } };
	cout << sol.merge(intervals) << endl;

	intervals = { { 1, 4 }, { 4, 5 } };
	cout << sol.merge(intervals) << endl;

	intervals = { { 4, 7 }, { 1, 4 } };
	cout << sol.merge(intervals) << endl;
}