// Created: 2025-07-01
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 178. 训练计划 VI
教学过程中，教练示范一次，学员跟做三次。
该过程被混乱剪辑后，记录于数组 actions，其中 actions{i} 表示做出该动作的人员编号。请返回教练的编号。
示例 1：
	输入：actions = {5, 7, 5, 5}
	输出：7
示例 2：
	输入：actions = {12, 1, 6, 12, 6, 12, 6}
	输出：1
提示：
	1 <= actions.length <= 10000
	1 <= actions{i} < 2^31 */

class Solution1 {
public:
	int trainingPlan(vector<int> &actions) {
		int res = 0;
		for(int i = 0; i < 32; ++i) {
			int cnt = 0, bit = 1 << i;
			for(int act : actions) {
				if(act & bit) ++cnt;
			}
			if(cnt % 3) {
				res |= bit;
			}
		}
		return res;
	}
};

class Solution {
public:
	int trainingPlan(vector<int> &actions) {
		int res = 0;
		array<int, 32> cnt { 0 };
		for(int act : actions) {
			for(int i = 0; i < 32; ++i) {
				cnt[i] += act & 1;
				act >>= 1;
			}
		}
		for(int i = 31; i >= 0; i--) {
			res <<= 1;
			res |= cnt[i] % 3; // 恢复第 i 位
		}
		return res;
	}
};

int main() {
	Solution sol;
	vector<int> actions;
	actions = { 5, 7, 5, 5 };
	cout << sol.trainingPlan(actions) << endl; // 7
	actions = { 12, 1, 6, 12, 6, 12, 6 };
	cout << sol.trainingPlan(actions) << endl; // 1
}