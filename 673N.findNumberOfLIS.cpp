// Created: 2025-05-29
#include "MyUtils.h"

/*673. 最长递增子序列的个数
给定一个未排序的整数数组 nums ， 返回最长递增子序列的个数 。
注意 这个数列必须是 严格 递增的。
示例 1:
	输入: [1,3,5,4,7]
	输出: 2
	解释: 有两个最长递增子序列，分别是 [1, 3, 4, 7] 和[1, 3, 5, 7]。
示例 2:
	输入: [2,2,2,2,2]
	输出: 5
	解释: 最长递增子序列的长度是1，并且存在5个子序列的长度为1，因此输出5。*/

class Solution {
public:
	int findNumberOfLIS(vector<int> &nums) {
		int n = nums.size(), res = 0, max_len = 0;
		vector<int> len(n), count(n, 1);
		for(int i = n - 1; i >= 0; --i) {
			int sub_len = 0;
			for(int j = i + 1; j < n; ++j) {
				if(nums[j] > nums[i]) {
					if(len[j] > sub_len) {
						sub_len = len[j];
						count[i] = count[j];
					} else if(len[j] == sub_len) {
						count[i] += count[j];
					}
				}
			}
			len[i] = sub_len + 1;
			if(len[i] > max_len) {
				max_len = len[i];
				res = count[i];
			} else if(len[i] == max_len) {
				res += count[i];
			}
		}
		return res;
	}
};

int main() {
	Solution sol;
	vector<int> nums { 1, 3, 5, 4, 7 };
	cout << sol.findNumberOfLIS(nums);
}