// Created: 2025-06-25
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 173. 点名
某班级 n 位同学的学号为 0 ~ n-1。
点名结果记录于升序数组 records。假定仅有一位同学缺席，请返回他的学号。
示例 1：
	输入：records = {0,1,2,3,5}
	输出：4
示例 2：
	输入：records = {0, 1, 2, 3, 4, 5, 6, 8}
	输出：7
提示：
	1 <= records.length<= 10000 */

class Solution {
public:
	int takeAttendance(vector<int> &records) {
		int i = 0, j = records.size();
		while(i < j) {
			int mid = i + (j - i) / 2;
			if(records[mid] == mid) {
				i = mid + 1;
			} else {
				j = mid;
			}
		}
		return i;
	}
};

int main() {
	Solution sol;
	vector<int> records;
	records = { 0, 1, 2, 3, 5 };
	cout << sol.takeAttendance(records) << endl;
	records = { 0, 1, 2, 3, 4, 5, 6, 8 };
	cout << sol.takeAttendance(records) << endl;
}