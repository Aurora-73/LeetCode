// Created: 2025-06-17
#include "MyDateGen.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 763. 划分字母区间
给你一个字符串 s。
我们要把这个字符串划分为尽可能多的片段，同一字母最多出现在一个片段中。例如，字符串"ababcc" 能够被分为 {"abab", "cc"}，
但类似{"aba", "bcc"} 或{"ab", "ab", "cc"} 的划分是非法的。
注意，划分结果需要满足：将所有划分结果按顺序连接，得到的字符串仍然是 s。
返回一个表示每个字符串片段的长度的列表。
示例 1：
	输入：s = "ababcbacadefegdehijhklij"
	输出：{9,7,8}
	解释：
	划分结果为 "ababcbaca"、"defegde"、"hijhklij"。
	每个字母最多出现在一个片段中。
	像 "ababcbacadefegde", "hijhklij" 这样的划分是错误的，因为划分的片段数较少。 
示例 2：
	输入：s = "eccbbbbdec"
	输出：{10}
提示：
	1 <= s.length <= 500
	s 仅由小写英文字母组成 */

class Solution1 {
public:
	vector<int> partitionLabels(string &s) {
		int n = s.size();
		vector<pair<int, int>> MinMaxPos(
		    26, { numeric_limits<int>::max(), numeric_limits<int>::min() });
		for(int i = 0; i < n; ++i) {
			auto &[minPos, maxPos] = MinMaxPos[s[i] - 'a'];
			minPos = min(minPos, i);
			maxPos = max(maxPos, i);
		}
		ranges::sort(MinMaxPos);
		vector<int> res;
		int begin = 0, end = -1; // 左闭右闭
		for(int i = 0; i < 26 && MinMaxPos[i].first != numeric_limits<int>::max(); ++i) {
			if(end < MinMaxPos[i].first) {
				if(end != -1) {
					res.push_back(end - begin + 1);
				}
				begin = MinMaxPos[i].first;
				end = MinMaxPos[i].second;
			} else {
				end = max(end, MinMaxPos[i].second);
			}
		}
		res.push_back(end - begin + 1);
		return res;
	}
};
// 首先记录每个字母的最小和最大下标，排序后使用 "56. 合并区间" 类似的算法解决。
// 注意这里不要用map，因为只有26个字母，而且后面需要 区间数组

class Solution {
public:
	vector<int> partitionLabels(const string &s) {
		int n = s.size();
		vector<int> last(26, -1);
		// 1. 记录每个字母最后出现的位置
		for(int i = 0; i < n; ++i) {
			last[s[i] - 'a'] = i;
		}
		vector<int> res;
		int start = 0, end = 0;
		// 2. 一次遍历，贪心合并
		for(int i = 0; i < n; ++i) {
			end = max(end, last[s[i] - 'a']);
			if(i == end) {
				res.push_back(end - start + 1);
				start = i + 1;
			}
		}
		return res;
	}
};
// 贪心算法

int main() {
	Solution sol;
	string s;
	s = "ababcbacadefegdehijhklij";
	cout << sol.partitionLabels(s) << endl; // {9,7,8}
	s = "eccbbbbdec";
	cout << sol.partitionLabels(s) << endl; // {10}
}