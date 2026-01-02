// Created: 2026-01-02
#include "MyUtils.hpp"
#include <numeric>
// #ifdef MY_UTILS_H

/* 给你一个下标从 0开始的二维整数数组flowers，
其中flowers{i} = {starti, endi}表示第i朵花的 花期从starti到endi（都 包含）。
同时给你一个下标从 0开始大小为 n的整数数组people，people{i}是第i个人来看花的时间。
请你返回一个大小为 n的整数数组answer，其中answer{i}是第i个人到达时在花期内花的数目。
示例 1：
	输入：flowers = {{1,6},{3,7},{9,12},{4,13}}, people = {2,3,7,11}
	输出：{1,2,2,2}
	解释：上图展示了每朵花的花期时间，和每个人的到达时间。
	对每个人，我们返回他们到达时在花期内花的数目。
示例 2：
	输入：flowers = {{1,10},{3,3}}, people = {3,3,2}
	输出：{2,2,1}
	解释：上图展示了每朵花的花期时间，和每个人的到达时间。
	对每个人，我们返回他们到达时在花期内花的数目。
提示：
	1 <= flowers.length <= 5 * 10^4
	flowers{i}.length == 2
	1 <= starti <= endi <= 10^9
	1 <= people.length <= 5 * 10^4
	1 <= people{i} <= 10^9 */

class Solution1 {
public:
	vector<int> fullBloomFlowers(vector<vector<int>> &flowers, vector<int> &people) {
		int np = people.size();
		vector<int> index;
		index.reserve(np);
		for(int i = 0; i < np; ++i) index.push_back(i);
		std::sort(index.begin(), index.end(), [&](int l, int r) { return people[l] < people[r]; });
		// 需要按照人出现的顺序处理，因此用index记录序号

		map<int, int> increment;
		for(auto &fl : flowers) {
			++increment[fl[0]];
			--increment[fl[1] + 1];
		} // 记录每个时间花的增减量

		vector<int> res(np);
		int id = 0, curr = 0;
		for(auto [day, inc] : increment) {
			while(id < np && people[index[id]] < day) {
				res[index[id]] = curr;
				++id;
			} // 处理两个间隔之间的人
			curr += inc;
		} // 来的太晚的人，没有看到花，已经初始化过0了
		return res;
	}
}; // 计算差分数组，类似于MST16.01，注意如果不用map而是用数组会超内存，在数值集中的时候好用，本题不好用

class Solution {
public:
	vector<int> fullBloomFlowers(vector<vector<int>> &flowers, vector<int> &people) {
		int np = people.size(), nf = flowers.size();
		vector<int> res, begs, ends;
		res.reserve(np), begs.reserve(nf), ends.reserve(nf);
		for(auto &fl : flowers) {
			begs.push_back(fl[0]);
			ends.push_back(fl[1]);
		}
		std::sort(begs.begin(), begs.end());
		std::sort(ends.begin(), ends.end());
		for(int day : people) {
			int birth = upper_bound(begs.begin(), begs.end(), day) - begs.begin();
			int death = lower_bound(ends.begin(), ends.end(), day) - ends.begin();
			res.push_back(birth - death);
		}
		return res;
	}
};
/* 值域很小（固定范围）：优先用固定长度差分数组 + 前缀和，时间 O(n + R)，R 很小（本题 R=101）——最快且最简单。
值域大但问点与区间都很多：用事件排序（差分+扫描线），O((n+m) log(n+m))，常数小，通用。
只想写短代码，且 n 和 m 都 ≤ 5e4：用排序 + 二分，O(n log n + m log n)，实现最简洁且面试友好。
需要处理任意时间范围且想避免排序事件的常数开销：也可以用 map 做差分（但 map 常数较大），或先合并重复 start / end 再二分。*/

int main() {
	Solution sol;
	vector<vector<int>> flowers;
	vector<int> people;
	flowers = { { 1, 6 }, { 3, 7 }, { 9, 12 }, { 4, 13 } }, people = { 2, 3, 7, 11 };
	cout << sol.fullBloomFlowers(flowers, people) << endl;

	flowers = { { 1, 10 }, { 3, 3 } }, people = { 3, 3, 2 };
	cout << sol.fullBloomFlowers(flowers, people) << endl;
}