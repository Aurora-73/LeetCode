// Created: 2025-06-22
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 179. 查找总价格为目标值的两个商品
购物车内的商品价格按照升序记录于数组 price。
请在购物车中找到两个商品的价格总和刚好是 target。若存在多种情况，返回任一结果即可。
示例 1：
	输入：price = {3, 9, 12, 15}, target = 18
	输出：{3,15} 或者 {15,3}
示例 2：
	输入：price = {8, 21, 27, 34, 52, 66}, target = 61
	输出：{27,34} 或者 {34,27}
提示：
	1 <= price.length <= 10^5
	1 <= price{i} <= 10^6
	1 <= target <= 2*10^6 */

class Solution1 {
public:
	vector<int> twoSum(vector<int> &price, int target) {
		unordered_set<int> set;
		int n = price.size();
		for(int i = 0; i < n; ++i) {
			if(set.count(target - price[i])) {
				return { price[i], target - price[i] };
			}
			set.insert(price[i]);
		}
		return {};
	}
};

class Solution {
public:
	vector<int> twoSum(vector<int> &price, int target) {
		int n = price.size();
		int i = 0, j = n - 1;
		while(i < j) {
			if(price[i] + price[j] == target) {
				return { price[i], price[j] };
			} else if(price[i] + price[j] < target) {
				++i;
			} else {
				--j;
			}
		}
		return {};
	}
}; // 有序数组的两数之和，双指针法，一个指向头，一个指向尾，小了左边右移，大了右边左移

int main() {
	Solution sol;
	vector<int> price;
	int target;
	price = { 3, 9, 12, 15 }, target = 18;
	cout << sol.twoSum(price, target) << endl;
	price = { 8, 21, 27, 34, 52, 66 }, target = 61;
	cout << sol.twoSum(price, target) << endl;
}