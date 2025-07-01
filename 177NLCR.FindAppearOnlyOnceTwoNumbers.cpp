// Created: 2025-07-01
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 177. 撞色搭配
整数数组 sockets 记录了一个袜子礼盒的颜色分布情况，其中 sockets{i} 表示该袜子的颜色编号。
礼盒中除了一款撞色搭配的袜子，每种颜色的袜子均有两只。请设计一个程序，
在时间复杂度 O(n)，空间复杂度O(1) 内找到这双撞色搭配袜子的两个颜色编号。
示例 1：
	输入：sockets = {4, 5, 2, 4, 6, 6}
	输出：{2,5} 或 {5,2}
示例 2：
	输入：sockets = {1, 2, 4, 1, 4, 3, 12, 3}
	输出：{2,12} 或 {12,2}
提示：
	2 <= sockets.length <= 10000 */

class Solution {
public:
	vector<int> sockCollocation(vector<int> &sockets) {
		int xorAll = 0, xor1 = 0, xor2 = 0, set = 1;
		for(auto s : sockets) {
			xorAll ^= s;
		}
		while(!(xorAll & set)) {
			set <<= 1;
		}
		for(auto s : sockets) {
			if(s & set) {
				xor1 ^= s;
			} else {
				xor2 ^= s;
			}
		}
		return { xor1, xor2 };
	}
};
// 先对全部值异或，得到两个仅出现一次的数的异或值，这个结果表示这两个数哪些位不同
// 根据其中一个不同位进行分组，分别进行异或，即可得到这两个数

int main() {
	Solution sol;
	vector<int> sockets;
	sockets = { 4, 5, 2, 4, 6, 6 };
	cout << sol.sockCollocation(sockets) << endl;
	sockets = { 1, 2, 4, 1, 4, 3, 12, 3 };
	cout << sol.sockCollocation(sockets) << endl;
}