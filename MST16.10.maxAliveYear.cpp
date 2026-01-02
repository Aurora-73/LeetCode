// Created: 2026-01-02
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定 N 个人的出生年份和死亡年份，第 i 个人的出生年份为 birth{i}，
死亡年份为 death{i}，实现一个方法以计算生存人数最多的年份。
你可以假设所有人都出生于 1900 年至 2000 年（含 1900 和 2000 ）之间。如果一个人在某一年的任意时期处于生存状态，
那么他应该被纳入那一年的统计中。例如，生于 1908 年、死于 1909 年的人应当被列入 1908 年和 1909 年的计数。
如果有多个年份生存人数相同且均为最大值，输出其中最小的年份。
示例：
输入：
    birth = {1900, 1901, 1950}
    death = {1948, 1951, 2000}
输出： 1901
提示：
	0 < birth.length == death.length <= 10000
	birth{i} <= death{i} */

class Solution1 {
public:
	int maxAliveYear(vector<int> &birth, vector<int> &death) {
		int n = birth.size();
		array<int, 101> cnt {};
		for(int i = 0; i < n; ++i) {
			for(int j = birth[i]; j <= death[i]; ++j) {
				++cnt[j - 1900];
			}
		}
		int res = 0, max_cnt = -1;
		for(int i = 0; i < 101; ++i) {
			if(max_cnt < cnt[i]) {
				max_cnt = cnt[i];
				res = i + 1900;
			}
		}
		return res;
	} // O(100n)
}; // 直接用cnt数组标记每个时间的存活人口，然后求最大值

class Solution2 {
public:
	int maxAliveYear(vector<int> &birth, vector<int> &death) {
		ranges::sort(birth), ranges::sort(death);
		vector<int>::iterator left = death.begin();
		int n = birth.size(), res = 0, max_cnt = 0;
		for(int i = 0; i < n; ++i) {
			if(i < n - 1 && birth[i] == birth[i + 1]) continue;
			left = lower_bound(left, death.end(), birth[i]);
			int curr = (i + 1) - (left - death.begin());
			if(curr > max_cnt) {
				max_cnt = curr;
				res = birth[i];
			}
		}
		return res;
	}
}; // 二分查找解法，类似于2251H.fullBloomFlowers，二分查找方法，在数值非常分散的情况下好用，在本题不好用

class Solution3 {
public:
	int maxAliveYear(vector<int> &birth, vector<int> &death) {
		map<int, int> increment;
		int n = birth.size();
		for(int i = 0; i < n; ++i) {
			++increment[birth[i]];
			--increment[death[i] + 1];
		}
		int res = 0, max_cnt = 0, curr = 0;
		for(auto [year, inc] : increment) {
			curr += inc;
			if(curr > max_cnt) {
				max_cnt = curr;
				res = year;
			}
		}
		return res;
	}
}; // 差分数组，这里使用map，可以处理任意范围的出生死亡日期

class Solution {
public:
	int maxAliveYear(vector<int> &birth, vector<int> &death) {
		array<int, 102> increment {};
		int n = birth.size();
		for(int i = 0; i < n; ++i) {
			++increment[birth[i] - 1900];
			--increment[death[i] - 1900 + 1];
		}
		int res = 0, max_cnt = 0, curr = 0;
		for(int i = 0; i < 101; ++i) {
			curr += increment[i];
			if(curr > max_cnt) {
				max_cnt = curr;
				res = i + 1900;
			}
		}
		return res;
	} // O(n + 100)
}; // 不是记录每个年份的实际人口，而是记录每个年份的增长人口，然后在遍历的时候利用前缀和求当时的人口
/* 值域很小（固定范围）：优先用固定长度差分数组 + 前缀和，时间 O(n + R)，R 很小（本题 R=101）——最快且最简单。
值域大但问点与区间都很多：用事件排序（差分+扫描线），O((n+m) log(n+m))，常数小，通用。
只想写短代码，且 n 和 m 都 ≤ 5e4：用排序 + 二分，O(n log n + m log n)，实现最简洁且面试友好。
需要处理任意时间范围且想避免排序事件的常数开销：也可以用 map 做差分（但 map 常数较大），或先合并重复 start / end 再二分。*/

int main() {
	Solution sol;
	vector<int> birth, death;
	birth = { 1927,
		1954,
		1903,
		1928,
		1956,
		1929,
		1929,
		1928,
		1958,
		1902,
		1953,
		1912,
		1923,
		1937,
		1915,
		1942,
		1964,
		1954,
		1924,
		1936,
		1963,
		1950,
		1904,
		1931,
		1951,
		1953,
		1922,
		1970,
		1986,
		1947,
		1911,
		1965,
		1913,
		1920,
		1947,
		1962,
		1903,
		1905,
		1978,
		1974,
		1950,
		1921,
		1929,
		1901,
		1925,
		1929,
		1951,
		1944,
		1945 },
	death = { 1987,
		1992,
		1967,
		1997,
		1963,
		1970,
		1944,
		1986,
		1997,
		1937,
		1971,
		1982,
		1980,
		1992,
		1995,
		1992,
		1991,
		1964,
		1985,
		1938,
		1975,
		1964,
		1975,
		1961,
		1995,
		1985,
		1946,
		1989,
		1999,
		1994,
		1956,
		1984,
		1999,
		1966,
		1950,
		1993,
		1960,
		1939,
		1990,
		1975,
		1982,
		1921,
		1964,
		1998,
		1969,
		1970,
		1965,
		1973,
		1958 };
	cout << sol.maxAliveYear(birth, death) << endl;

	birth = { 1900, 1901, 1950 };
	death = { 1948, 1951, 2000 };
	cout << sol.maxAliveYear(birth, death) << endl;

	birth = { 1900, 1941, 1950, 1961, 1971, 1980, 1950 };
	death = { 1948, 1951, 2000, 2000, 2000, 2000, 2000 };
	cout << sol.maxAliveYear(birth, death) << endl;
}