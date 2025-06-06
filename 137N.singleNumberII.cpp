// Created: 2025-05-16
#include "MyUtils.hpp"

/*137. 只出现一次的数字 II
给你一个整数数组 nums ，除某个元素仅出现 一次 外，其余每个元素都恰出现 三次 。请你找出并返回那个只出现了一次的元素。
你必须设计并实现线性时间复杂度的算法且使用常数级空间来解决此问题。
1 <= nums.length <= 3 * 104
-231 <= nums[i] <= 231 - 1
nums 中，除某个元素仅出现 一次 外，其余每个元素都恰出现 三次*/

class Solution {
public:
	int singleNumber(vector<int> &nums) {
		int res = 0;
		for(int i = 0; i < 32; ++i) {
			int count = 0;
			for(auto &x : nums) {
				if((x >> i) & 1) {
					++count;
				}
			} // 统计每一位出现的1的次数
			if(count % 3) {
				res |= (1 << i);
			} // 如果出现次数不能被 3 整除，说明只出现一次的数该位为 1
		}
		return res;
	}
};

int main() {
	Solution sol;
}