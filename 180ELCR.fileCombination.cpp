// Created: 2025-06-29
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 180. 文件组合
待传输文件被切分成多个部分，按照原排列顺序，每部分文件编号均为一个 正整数（至少含有两个文件）。
传输要求为：连续文件编号总和为接收方指定数字 target 的所有文件。请返回所有符合该要求的文件传输组合列表。
注意，返回时需遵循以下规则：
	每种组合按照文件编号 升序 排列；
	不同组合按照第一个文件编号 升序 排列。
示例 1：
	输入：target = 12
	输出：{{3, 4, 5}}
	解释：在上述
	示例中，存在一个连续正整数序列的和为 12，为 {3, 4, 5}。
示例 2：
	输入：target = 18
	输出：{{3,4,5,6},{5,6,7}}
	解释：在上述
	示例中，存在两个连续正整数序列的和分别为 18，分别为 {3, 4, 5, 6} 和 {5, 6, 7}。
提示：
	1 <= target <= 10^5 */

class Solution {
public:
	vector<vector<int>> fileCombination(int target) {
		vector<vector<int>> res;
		for(int n = target / 2; n >= 2; --n) {
			int add = (static_cast<long long>(n) * (n - 1)) / 2, a = (target - add) / n;
			if(a > 0 && n * a + add == target) {
				res.push_back({});
				res.back().reserve(n);
				for(int i = 0; i < n; ++i) {
					res.back().push_back(a + i);
				}
			}
		}
		return res;
	}
}; // 假设可分，则从左到右依次是a, a + 1, .... , a + i

int main() {
	Solution sol;
	int target;
	target = 12;
	cout << sol.fileCombination(target) << endl; // {{3, 4, 5}}
	target = 18;
	cout << sol.fileCombination(target) << endl; // {{3,4,5,6},{5,6,7}}
}