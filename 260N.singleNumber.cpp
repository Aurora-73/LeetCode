// Created: 2025-05-16
#include "MyUtils.hpp"

/*260. 只出现一次的数字 III
给你一个整数数组 nums，其中恰好有两个元素只出现一次，其余所有元素均出现两次。 找出只出现一次的那两个元素。你可以按 任意顺序 返回答案。
你必须设计并实现线性时间复杂度的算法且仅使用常量额外空间来解决此问题。*/

class Solution1 {
public:
	vector<int> singleNumber(vector<int> &nums) {
		int OXR = 0;
		for(const auto &x : nums) {
			OXR ^= x;
		}
		int one = 0;
		for(; one < 32; ++one) {
			if(OXR >> one & 1) {
				break;
			}
		}
		int a = 0, b = 0;
		for(const auto &x : nums) {
			if(x >> one & 1) {
				a ^= x;
			} else {
				b ^= x;
			}
		}
		return { a, b };
	}
};
// 类似于136，但是要先找出两个数第一个不同的位，异或的时候让该位为 0 和 1 的分开异或

class Solution2 {
public:
	vector<int> singleNumber(vector<int> &nums) {
		int xorsum = 0;
		for(int x : nums) {
			xorsum ^= x;
		}
		int lowbit = (xorsum == INT_MIN ? xorsum : xorsum & -xorsum);
		vector<int> ans(2);
		for(int x : nums) {
			ans[(x & lowbit) != 0] ^= x;
		}
		return ans;
	}
};
/* 对任意整数 x（非 0）：x & (-x)  会保留 x 中最低位的 1，其余位清零 */

class Solution {
public:
	vector<int> singleNumber(vector<int> &nums) {
		unsigned int xorsum = 0;
		for(int x : nums) {
			xorsum ^= x;
		}
		int lowbit = xorsum & -xorsum;
		vector<int> ans(2);
		for(int x : nums) {
			ans[(x & lowbit) != 0] ^= x;
		}
		return ans;
	}
}; // 无符号整型可以防止 -INT_MIN的错误

int main() {
	Solution1 sol;
}