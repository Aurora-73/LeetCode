// Created: 2025-12-06
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给你一个整数数组 nums。
镜像对是指一对满足下述条件的下标(i, j)：
	0 <= i < j < nums.length，并且
	reverse(nums{i}) == nums{j}，其中 reverse(x) 表示将整数 x 的数字反转后形成的整数。
反转后会忽略前导零，例如 reverse(120) = 21。
返回任意镜像对的下标之间的最小绝对距离。下标i 和 j 之间的绝对距离为 abs(i - j)。
如果不存在镜像对，返回 -1。
示例 1：
	输入： nums = {12,21,45,33,54}
	输出： 1
	解释：
	镜像对为：
	(0, 1)，因为 reverse(nums{0}) = reverse(12) = 21 = nums{1}，
	绝对距离为 abs(0 - 1) = 1。
	(2, 4)，因为 reverse(nums{2}) = reverse(45) = 54 = nums{4}，
	绝对距离为 abs(2 - 4) = 2。
	所有镜像对中的最小绝对距离是 1。
示例 2：
	输入： nums = {120,21}
	输出： 1
	解释：
	只有一个镜像对 (0, 1)，因为 reverse(nums{0}) = reverse(120) = 21 = nums{1}。
	最小绝对距离是 1。
示例 3：
	输入： nums = {21,120}
	输出： -1
	解释：
	数组中不存在镜像对。
提示：
	1 <= nums.length <= 10^5
	1 <= nums{i} <= 10^9 */

class Solution {
public:
	int minMirrorPairDistance(vector<int> &nums) {
		int n = nums.size(), res = n;
		unordered_map<int, int> map;
		for(int i = 0; i < n; ++i) {
			auto it = map.find(nums[i]);
			if(it != map.end()) {
				res = min(i - it->second, res);
			}
			map[getMirror(nums[i])] = i;
			// 必须是保存翻转后的值，查找当前值，因为需要去掉翻转后的前导0
		}
		return res < n ? res : -1;
	}

private:
	int getMirror(int num) {
		int mirror = 0;
		while(num > 0) {
			mirror *= 10;
			mirror += num % 10;
			num /= 10;
		}
		return mirror;
	}
};
// 不需要multimap，因为找的是最近的，从左往右遍历的时候直接覆盖即可，始终保持当前的下标是最靠右的

int main() {
	Solution sol;
	vector<int> nums;
	nums = { 120, 21 };
	cout << sol.minMirrorPairDistance(nums) << endl;
}