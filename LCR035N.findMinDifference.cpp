// Created: 2025-12-04
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个 24 小时制（小时:分钟 "HH:MM"）的时间列表，找出列表中任意两个时间的最小时间差并以分钟数表示。
示例 1：
	输入：timePoints = {"23:59","00:00"}
	输出：1
示例 2：
	输入：timePoints = {"00:00","23:59","00:00"}
	输出：0
提示：
	2 <= timePoints <= 2 * 10^4
	timePoints{i} 格式为 "HH:MM" */

class Solution1 {
public:
	int findMinDifference(vector<string> &timePoints) {
		set<int> s;
		for(auto &str : timePoints) {
			if(!s.insert(str2min(str)).second) {
				return 0;
			} // 有重复时间，结果为0
		}
		int res = *s.begin() + (24 * 60) - *s.rbegin(), before = *s.begin();
		auto it = s.begin();
		for(++it; it != s.end(); ++it) {
			res = min(res, *it - before);
			before = *it;
		}
		return res;
	}

private:
	int str2min(string &str) {
		return (str[0] - '0') * 10 * 60 + (str[1] - '0') * 60 + (str[3] - '0') * 10
		    + (str[4] - '0');
	}
}; // 使用set保存，因为set本身自动是有序的

class Solution2 {
public:
	int findMinDifference(vector<string> &timePoints) {
		vector<int> vals;
		int n = timePoints.size();
		vals.resize(n);
		for(int i = 0; i < n; ++i) {
			vals[i] = str2min(timePoints[i]);
		}
		std::sort(vals.begin(), vals.end());
		int res = vals[0] + (24 * 60) - vals.back(), before = vals[0];
		for(int i = 1; i < n; ++i) {
			res = min(res, vals[i] - before);
			before = vals[i];
		}
		return res;
	}

private:
	int str2min(string &str) {
		return (str[0] - '0') * 10 * 60 + (str[1] - '0') * 60 + (str[3] - '0') * 10
		    + (str[4] - '0');
	}
}; // vector有序数组的排序并不会比set红黑树的插入慢

class Solution {
public:
	int findMinDifference(vector<string> &timePoints) {
		int n = timePoints.size();
		if(n <= 1) return 0;
		if(n > 1440) return 0; // 鸽巢原理，必定有重复元素

		array<bool, 1440> seen {}; // vector<bool> 是位压缩更慢
		for(const auto &s : timePoints) {
			int m = toMin(s);
			if(seen[m]) return 0; // 重复
			seen[m] = 1;
		}

		int first = -1, prev = -1, ans = numeric_limits<int>::max();
		for(int i = 0; i < 1440; ++i) {
			if(!seen[i]) continue;
			if(first == -1) first = i;
			if(prev != -1) ans = min(ans, i - prev);
			prev = i;
		} // 结束时prev就是最后一个时间
		ans = min(ans, first + 1440 - prev);
		return ans;
	}

private:
	inline int toMin(const string &t) noexcept {
		return (t[0] - '0') * 600 + (t[1] - '0') * 60 + (t[3] - '0') * 10 + (t[4] - '0');
	}
}; // 使用位压缩，因为一共只有1440个时间

int main() {
	Solution sol;
	vector<string> timePoints;
	timePoints = { "01:01", "02:01" };
	cout << sol.findMinDifference(timePoints) << endl;
	timePoints = { "23:59", "00:00", "00:10", "10:00" };
	cout << sol.findMinDifference(timePoints) << endl;
	timePoints = { "00:00", "23:59", "00:00" };
	cout << sol.findMinDifference(timePoints) << endl;
}