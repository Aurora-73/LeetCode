// Created: 2025-06-25
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 172. 统计目标成绩的出现次数
某班级考试成绩按非严格递增顺序记录于整数数组 scores，请返回目标成绩 target 的出现次数。
示例 1：
	输入: scores = {2, 2, 3, 4, 4, 4, 5, 6, 6, 8}, target = 4
	输出: 3
示例2：
	输入: scores = {1, 2, 3, 5, 7, 9}, target = 6
	输出: 0
提示：
	0 <= scores.length <= 10^5
	-10^9<= scores{i}<= 10^9
	scores是一个非递减数组
	-10^9<= target<= 10^9 */

class Solution1 {
public:
	int countTarget(vector<int> &scores, int target) {
		auto it = equal_range(scores.begin(), scores.end(), target);
		return it.second - it.first;
	}
};

class Solution2 {
public:
	int countTarget(vector<int> &scores, int target) {
		int r = upper_bound(scores, target), l = lower_bound(scores, target);
		return r - l;
	}

private:
	int lower_bound(vector<int> &scores, int target) {
		int i = 0, j = scores.size(); // 左闭右开
		while(i < j) {
			int mid = i + (j - i) / 2;
			if(scores[mid] >= target) {
				j = mid;
			} else {
				i = mid + 1;
			}
		}
		return i;
	} // 第一个大于等于target的元素位置

	int upper_bound(vector<int> &scores, int target) {
		int i = 0, j = scores.size(); // 左闭右开
		while(i < j) {
			int mid = i + (j - i) / 2;
			if(scores[mid] > target) {
				j = mid;
			} else {
				i = mid + 1;
			}
		}
		return i;
	} // 第一个大于target的元素位置
};

class Solution3 {
public:
	int countTarget(vector<int> &scores, int target) {
		return lower_bound(scores, target + 1) - lower_bound(scores, target);
	}

private:
	int lower_bound(vector<int> &scores, int target) {
		int i = 0, j = scores.size(); // 左闭右开
		while(i < j) {
			int mid = i + (j - i) / 2;
			if(scores[mid] >= target) {
				j = mid;
			} else {
				i = mid + 1;
			}
		}
		return i;
	}
}; // 找当 target 的下界 和 target + 1 的下界 即可

int main() {
	Solution1 sol;
	vector<int> scores;
	int target;
	scores = { 2, 2, 3, 4, 4, 4, 5, 6, 6, 8 }, target = 4;
	cout << sol.countTarget(scores, target) << endl; // 3
	scores = { 1, 2, 3, 5, 7, 9 }, target = 6;
	cout << sol.countTarget(scores, target) << endl; // 0
}