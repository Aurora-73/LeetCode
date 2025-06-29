// Created: 2025-06-29
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 158. 库存管理 II
仓库管理员以数组 stock 形式记录商品库存表。
stock{i} 表示商品 id，可能存在重复。请返回库存表中数量大于 stock.length / 2 的商品 id。
示例1：
输入：stock = {6, 1, 3, 1, 1, 1}
输出：1
提示：
	1 <= stock.length <= 50000
	给定数组为非空数组，且存在结果数字 */

class Solution {
public:
	int inventoryManagement(vector<int> &stock) {
		int now = -1, cnt = 0;
		for(auto s : stock) {
			if(now == s) {
				++cnt;
			} else {
				--cnt;
			}
			if(cnt <= 0) {
				now = s;
				cnt = 1;
			}
		}
		return now;
	}
}; // Boyer-Moore 投票算法

int main() {
	Solution sol;
	vector<int> stock;
	stock = { 6, 1, 3, 1, 1, 1 };
	cout << sol.inventoryManagement(stock) << endl;
}