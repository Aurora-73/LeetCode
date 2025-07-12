// Created: 2025-06-25
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 128. 库存管理 I
仓库管理员以数组 stock 形式记录商品库存表。
stock{i} 表示商品 id，可能存在重复。原库存表按商品 id 升序排列。现因突发情况需要进行商品紧急调拨，
管理员将这批商品 id 提前依次整理至库存表最后。请你找到并返回库存表中编号的 最小的元素 以便及时记录本次调拨。
示例 1：
	输入：stock = {4,5,8,3,4}
	输出：3
示例 2：
	输入：stock = {5,7,9,1,2}
	输出：1
提示：
	1 <= stock.length <= 5000
	-5000 <= stock{i} <= 5000 */

class Solution1 {
public:
	int inventoryManagement(vector<int> &stock) {
		int i = 0, j = stock.size() - 1; // 注意这是左闭右开写法
		while(i < j) {
			int m = (i + j) / 2;
			if(stock[m] > stock[j]) // 注意这里不是和back比较
				i = m + 1;
			else if(stock[m] < stock[j])
				j = m;
			else {
				--j;
			}
		}
		return stock[i];
	}
}; // 寻找递增区间的起点

class Solution {
public:
	int inventoryManagement(vector<int> &stock) {
		int i = 0, j = stock.size();
		while(i < j - 1 && stock[i] == stock.back()) ++i;
		while(i < j) {
			int mid = i + (j - i) / 2;
			if(stock[mid] > stock.back()) {
				i = mid + 1;
			} else {
				j = mid;
			}
		}
		return stock[i];
	}
};
// 正常的二分法在遇到两侧元素相等时会发生错误，因此先移动左边界，去掉左边的相等元素，但是注意至少要保留一个元素，因此是i < j - 1

int main() {
	Solution sol;
	vector<int> stock;
	stock = { 2, 1, 2 };
	cout << sol.inventoryManagement(stock) << endl; // 1
	stock = { 4, 5, 8, 3, 4 };
	cout << sol.inventoryManagement(stock) << endl; // 3
	stock = { 5, 7, 9, 1, 2 };
	cout << sol.inventoryManagement(stock) << endl; // 1
}