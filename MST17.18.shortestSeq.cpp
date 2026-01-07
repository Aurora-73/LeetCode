// Created: 2026-01-07
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 假设你有两个数组，一个长一个短，短的元素均不相同。
找到长数组中包含短数组所有的元素的最短子数组，其出现顺序无关紧要。
返回最短子数组的左端点和右端点，如有多个满足条件的子数组，返回左端点最小的一个。若不存在，返回空数组。
示例 1：
	输入：
	big = {7,5,9,0,2,1,3,5,7,9,1,1,5,8,8,9,7}
	small = {1,5,9}
	输出：{7,10}
示例 2：
	输入：
	big = {1,2,3}
	small = {4}
	输出：{}
提示：
	big.length<= 100000
	1 <= small.length<= 100000 */

class Solution {
public:
	vector<int> shortestSeq(vector<int> &big, vector<int> &small) {
		int ns = small.size(), nb = big.size();
		unordered_map<int, int> cnt;
		for(auto num : small) {
			++cnt[num];
		}
		int i = 0, bcnt = 0, best_i = 0, best_j = INT_MAX;
		for(int j = 0; j < nb; ++j) {
			auto itj = cnt.find(big[j]);
			if(itj != cnt.end()) {
				if(itj->second > 0) ++bcnt;
				--itj->second;
				if(bcnt == ns) {
					auto iti = cnt.find(big[i]);
					while(iti == cnt.end() || iti->second < 0) {
						if(iti != cnt.end() && iti->second < 0) {
							++iti->second;
						}
						++i;
						iti = cnt.find(big[i]);
					}
					if(j - i < best_j - best_i) {
						best_j = j;
						best_i = i;
					}
				}
			}
		}
		return best_j < nb ? vector<int> { best_i, best_j } : vector<int>();
	}
}; // 滑动窗口

int main() {
	Solution sol;
	vector<int> big, small;
	big = { 7, 5, 9, 0, 2, 1, 3, 5, 7, 9, 1, 1, 5, 8, 8, 9, 7 }, small = { 1, 5, 9 };
	cout << sol.shortestSeq(big, small) << endl;

	big = { 1, 2, 3 }, small = { 4 };
	cout << sol.shortestSeq(big, small) << endl;
}