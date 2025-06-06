// Created: 2025-05-16
#include "MyUtils.hpp"

/*136. 只出现一次的数字
给你一个 非空 整数数组 nums ，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。
你必须设计并实现线性时间复杂度的算法来解决此问题，且该算法只使用常量额外空间。*/

class Solution {
public:
	int singleNumber(vector<int> &nums) {
		int res = 0;
		for(auto &x : nums) {
			res ^= x;
		}
		return res;
	}
};
// 任何数异或他自身都是0，0异或任何数等于原数，异或满足交换律
// a ^ b ^ a ^ c ^ b = a ^ a ^ b ^ b ^ c = 0 ^ c = c
// 整数异或 是 阿贝尔群，封闭、可结合、有幺元0、每个元素的逆元均是自身、可交换

int main() {
	Solution sol;
}