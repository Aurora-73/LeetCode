// Created: 2025-06-28
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 170. 交易逆序对的总数
在股票交易中，如果前一天的股价高于后一天的股价，则可以认为存在一个「交易逆序对」。
请设计一个程序，输入一段时间内的股票交易记录 record，返回其中存在的「交易逆序对」总数。
示例 1：
	输入：record = {9, 7, 5, 4, 6}
	输出：8
	解释：交易中的逆序对为 (9, 7), (9, 5), (9, 4), (9, 6), (7, 5), (7, 4), (7, 6), (5, 4)。
	
提示：
	0 <= record.length <= 50000 */

class Solution {
public:
	int reversePairs(vector<int> &record) { }
};

int main() {
	Solution sol;
	vector<int> record;
	record = { 9, 7, 5, 4, 6 };
	cout << sol.reversePairs(record) << endl; // 8
}