// Created: 2026-01-02
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 你正在使用一堆木板建造跳水板。
有两种类型的木板，其中长度较短的木板长度为shorter，长度较长的木板长度为longer。
你必须正好使用k块木板。编写一个方法，生成跳水板所有可能的长度。
返回的长度需要从小到大排列。
示例 1：
	输入：
	shorter = 1
	longer = 2
	k = 3
	输出：{3,4,5,6}
	解释：
	可以使用 3 次 shorter，得到结果 3；使用 2 次 shorter 和 1 次 longer，
	得到结果 4。以此类推，得到最终结果。
提示：
	0 < shorter <= longer
	0 <= k <= 100000 */

class Solution {
public:
	vector<int> divingBoard(int shorter, int longer, int k) {
		if(k == 0) return {}; // 没有木板，没有可能
		int diff = longer - shorter;
		vector<int> res { shorter * k };
		if(diff == 0) return res; // 仅有一种木板，只有一种可能

		res.reserve(k + 1);
		for(int i = 0; i < k; ++i) {
			res.push_back(res.back() + diff);
		}
		return res;
	}
};

int main() {
	Solution sol;
	int shorter = 1, longer = 2, k = 3;
	cout << sol.divingBoard(shorter, longer, k) << endl;
}