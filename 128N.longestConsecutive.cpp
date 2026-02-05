#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

/* 给定一个未排序的整数数组 nums，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。
请你设计并实现时间复杂度为O(n) 的算法解决此问题。
示例 1：
	输入：nums = {100,4,200,1,3,2}
	输出：4
	解释：最长数字连续序列是 {1, 2, 3, 4}。它的长度为 4。
示例 2：
	输入：nums = {0,3,7,2,5,8,4,6,0,1}
	输出：9
示例 3：
	输入：nums = {1,0,1,2}
	输出：3
提示：
	0 <= nums.length <= 10^5
	-10^9 <= nums{i} <= 10^9 */

class Solution1 {
public:
	int longestConsecutive(vector<int> &nums) {
		unordered_set<int> numset(nums.begin(), nums.end());
		int max = bool(nums.size());
		for(auto i : numset) {
			if(numset.count(i - 1)) {
				continue;
			} else {
				int max_i = 1;
				while(numset.count(i + max_i)) {
					max_i++;
				}
				max = max > max_i ? max : max_i;
			}
		}
		return max;
	}
};

class Solution {
public:
	int longestConsecutive(vector<int> &nums) {
		unordered_set<int> vals(nums.begin(), nums.end());
		int res = 0;
		for(auto val : vals) { // 遍历 vals，自动去重
			if(!vals.contains(val - 1)) {
				int len = 1;
				while(vals.contains(val + len)) ++len;
				res = max(res, len);
			}
		}
		return res;
	}
}; // 利用哈希表O(1)查找的性质，对于任何一个元素val，如果存在val-1则val一定不是最长连续序列的最小元素
// 反之则val可能是最长连续序列的最小元素，不断寻找val + len，直到扩展到最大长度
// 注意遍历时要在已经去重的哈希表中遍历，否则会多次重复查找相同元素，超时
// 这道题的关键点有两个：1、哈希表O(1)查找   2、最长连续序列在原数组中的出现顺序不考虑

int main() {
	Solution sol;
	vector<int> nums;

	nums = { 100, 4, 200, 1, 3, 2 };
	cout << sol.longestConsecutive(nums) << endl;

	nums = { 0, 3, 7, 2, 5, 8, 4, 6, 0, 1 };
	cout << sol.longestConsecutive(nums) << endl;

	nums = { 1, 0, 1, 2 };
	cout << sol.longestConsecutive(nums) << endl;
}
