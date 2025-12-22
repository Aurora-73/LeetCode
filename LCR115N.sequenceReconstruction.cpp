// Created: 2025-12-22
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个长度为 n 的整数数组 nums，其中 nums 是范围为 {1，n} 的整数的排列。
还提供了一个 2D 整数数组sequences，其中sequences{i}是nums的子序列。
检查 nums 是否是唯一的最短超序列。最短 超序列 是 长度最短 的序列，
并且所有序列sequences{i}都是它的子序列。对于给定的数组sequences，可能存在多个有效的 超序列。
	例如，对于sequences = {{1,2},{1,3}}，有两个最短的 超序列，{1,2,3} 和 {1,3,2}。
	而对于sequences = {{1,2},{1,3},{1,2,3}}，
唯一可能的最短 超序列 是 {1,2,3}。{1,2,3,4} 是可能的超序列，但不是最短的。
如果 nums 是序列的唯一最短 超序列，则返回 true，否则返回 false。
子序列 是一个可以通过从另一个序列中删除一些元素或不删除任何元素，而不改变其余元素的顺序的序列。
示例 1：
	输入：nums = {1,2,3}, sequences = {{1,2},{1,3}}
	输出：false
	解释：有两种可能的超序列：{1,2,3}和{1,3,2}。
	序列 {1,2} 是{1,2,3}和{1,3,2}的子序列。
	序列 {1,3} 是{1,2,3}和{1,3,2}的子序列。
	因为 nums 不是唯一最短的超序列，所以返回false。
示例 2：
	输入：nums = {1,2,3}, sequences = {{1,2}}
	输出：false
	解释：最短可能的超序列为 {1,2}。
	序列 {1,2} 是它的子序列：{1,2}。
	因为 nums 不是最短的超序列，所以返回false。
示例 3：
	输入：nums = {1,2,3}, sequences = {{1,2},{1,3},{2,3}}
	输出：true
	解释：最短可能的超序列为{1,2,3}。
	序列 {1,2} 是它的一个子序列：{1,2,3}。
	序列 {1,3} 是它的一个子序列：{1,2,3}。
	序列 {2,3} 是它的一个子序列：{1,2,3}。
	因为 nums 是唯一最短的超序列，所以返回true。
提示：
	n == nums.length
	1 <= n <= 10^4
	nums是{1, n}范围内所有整数的排列
	1 <= sequences.length <= 10^4
	1 <= sequences{i}.length <= 10^4
	1 <= sum(sequences{i}.length) <= 10^5
	1 <= sequences{i}{j} <= n
	sequences的所有数组都是 唯一 的
	sequences{i}是nums 的一个子序列 */

class Solution {
public:
	bool sequenceReconstruction(vector<int> &nums, vector<vector<int>> &sequences) {
		int n = nums.size();
		vector<bool> exists(n + 1, 0); // 如果有数不存在，则过长了
		exists[0] = 1;
		vector<vector<int>> outs(n + 1); // 如果有数不存在，则过长了
		vector<int> inDegrees(n + 1, 0);
		for(auto &seq : sequences) {
			if(seq.size() == 1) exists[seq[0]] = 1; // 注意处理长度为 1 的情况
			for(unsigned i = 1; i < seq.size(); ++i) {
				exists[seq[i - 1]] = exists[seq[i]] = 1;
				outs[seq[i - 1]].push_back(seq[i]);
				++inDegrees[seq[i]];
			}
		}
		for(auto e : exists) {
			if(!e) return false;
		} // 不是最短
		queue<int> que;
		for(int i = 1; i < n + 1; ++i) {
			if(inDegrees[i] == 0) {
				que.push(i);
			}
		}
		int k = 0;
		while(que.size()) {
			if(que.size() > 1) return false; // 不唯一
			int curr = que.front();
			que.pop();
			if(curr != nums[k]) return false;
			++k;
			for(int j : outs[curr]) {
				if(--inDegrees[j] == 0) {
					que.push(j);
				}
			}
		}
		return true;
	}
};

int main() {
	Solution sol;
	vector<int> nums;
	vector<vector<int>> sequences;
	nums = { 1 }, sequences = { { 1 } };
	cout << sol.sequenceReconstruction(nums, sequences) << endl; // 1

	nums = { 1, 2, 3 }, sequences = { { 1, 2 }, { 1, 3 } };
	cout << sol.sequenceReconstruction(nums, sequences) << endl; // 0

	nums = { 1, 2, 3 }, sequences = { { 1, 2 } };
	cout << sol.sequenceReconstruction(nums, sequences) << endl; // 0

	nums = { 1, 2, 3 }, sequences = { { 1, 2 }, { 1, 3 }, { 2, 3 } };
	cout << sol.sequenceReconstruction(nums, sequences) << endl; // 1
}