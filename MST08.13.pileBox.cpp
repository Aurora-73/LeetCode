// Created: 2025-12-29
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 堆箱子。
给你一堆n个箱子，箱子宽 wi、深 di、高 hi。箱子不能翻转，将箱子堆起来时，
下面箱子的宽度、高度和深度必须大于上面的箱子。实现一种方法，搭出最高的一堆箱子。箱堆的高度为每个箱子高度的总和。
输入使用数组{wi, di, hi}表示每个箱子。
示例 1：
	输入：box = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}}
	输出：6
示例 2：
	输入：box = {{1, 1, 1}, {2, 3, 4}, {2, 6, 7}, {3, 4, 5}}
	输出：10
提示:
	箱子的数目不大于3000个。 */

class Solution1 {
public:
	int pileBox(vector<vector<int>> &box) {
		ranges::sort(box);
		int res = 0;
		for(unsigned i = 0; i < box.size(); ++i) {
			res = max(res, dfs(i, box));
		}
		return res;
	}

private:
	int dfs(unsigned i, const vector<vector<int>> &box) {
		if(i == box.size()) {
			return 0;
		}
		int res = 0;
		for(unsigned j = i + 1; j < box.size(); ++j) {
			if(box[i][0] < box[j][0] && box[i][1] < box[j][1] && box[i][2] < box[j][2]) {
				res = max(res, dfs(j, box));
			}
		}
		return res + box[i][2];
	}
}; // 可以用动态规划

class Solution {
public:
	int pileBox(vector<vector<int>> &box) {
		ranges::sort(box); // 注意这里
		int n = box.size(), res = 0;
		vector<int> dp(n + 1, 0);
		for(int i = n - 1; i >= 0; --i) {
			int curr = 0;
			for(int j = i + 1; j < n; ++j) {
				if(box[i][0] < box[j][0] && box[i][1] < box[j][1] && box[i][2] < box[j][2]) {
					curr = max(curr, dp[j]);
				}
			}
			dp[i] = curr + box[i][2];
			res = max(res, dp[i]);
		}
		return res;
	}
}; // 这道题无法用LIS的“最趴数链”解决
// 这道题有一个有趣的性质：箱子之间是部分可比的。以箱子 box[i] 为例，其他箱子可以分为三类：
// S1[i] = {可以放在 box[i] 上的箱子}，S2[i] = {既不能放在 box[i] 上，也不能被 box[i] 放置的箱子}，S3[i] = {可以包裹 box[i] 的箱子}
// 对于 box[j] ∈ S2[i]，其 S1[j]、S2[j]、S3[j] 可能与 box[i] 的分类不同， 因此整个数组不存在全局单调性，无法用 LIS 解决。
//
// 但是排序排序可以使得原数组满足 S1, S2, S3这样的整体有序性，从而实现动态规划所需的“贪心”
// - 虽然排序不能保证后面的箱子一定比前面的箱子大，
// - 但可以保证后面的箱子 **不会被放到前面箱子里**，即消除了非法堆叠的可能。
// 这样，动态规划的转移就可以安全地只考虑前面箱子，而不遗漏合法组合。

int main() {
	Solution sol;
	vector<vector<int>> box;
	box = { { 1, 1, 1 }, { 2, 2, 2 }, { 3, 3, 3 } };
	cout << sol.pileBox(box) << endl;

	box = { { 1, 1, 1 }, { 2, 3, 4 }, { 2, 6, 7 }, { 3, 4, 5 } };
	cout << sol.pileBox(box) << endl;
}