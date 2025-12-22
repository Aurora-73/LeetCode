// Created: 2025-12-22
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 如果交换字符串X 中的两个不同位置的字母，使得它和字符串Y 相等，那么称 X 和 Y 两个字符串相似。
如果这两个字符串本身是相等的，那它们也是相似的。
例如，"tars" 和 "rats" 是相似的 (交换 0 与 2 的位置)；"rats" 和 "arts" 也是相似的，
但是 "star" 不与 "tars"，"rats"，或 "arts" 相似。
总之，它们通过相似性形成了两个关联组：{"tars", "rats", "arts"} 和 {"star"}。注意，
"tars" 和 "arts" 是在同一组中，即使它们并不相似。形式上，对每个组而言，要确定一个单词在组中，只需要这个词和该组中至少一个单词相似。
给定一个字符串列表 strs。列表中的每个字符串都是 strs 中其它所有字符串的一个字母异位词。
请问 strs 中有多少个相似字符串组？
字母异位词（anagram），一种把某个字符串的字母的位置（顺序）加以改换所形成的新词。
示例 1：
	输入：strs = {"tars","rats","arts","star"}
	输出：2
示例 2：
	输入：strs = {"omv","ovm"}
	输出：1
提示：
	1 <= strs.length <= 300
	1 <= strs{i}.length <= 300
	strs{i} 只包含小写字母。
	strs 中的所有单词都具有相同的长度，且是彼此的字母异位词。 */

class Solution {
public:
	int numSimilarGroups(vector<string> &strs) {
		int n = strs.size(), res = 0;
		parents.assign(n, -1);
		for(int i = 0; i < n; ++i) {
			for(int j = i + 1; j < n; ++j) {
				int pi = Find(i), pj = Find(j);
				if(pi != pj) {
					if(isSimilar(strs[i], strs[j])) {
						UnionP(pi, pj);
					}
				}
			}
		}
		for(int p : parents) {
			if(p == -1) {
				++res;
			}
		}
		return res;
	}

private:
	vector<int> parents;
	bool isSimilar(string &str1, string &str2) {
		int diff = 0, ns = str1.size();
		for(int i = 0; i < ns; ++i) {
			if(str1[i] != str2[i]) {
				if(++diff > 2) return false; // 提前剪枝
			}
		}
		return diff == 2 || diff == 0;
	} // strs 中的所有单词都具有相同的长度，且是彼此的字母异位词。
	int Find(int index) {
		if(parents[index] == -1) return index;
		return parents[index] = Find(parents[index]);
	}
	void UnionP(int pi, int pj) {
		if(pi != pj) {
			parents[pj] = pi;
		}
	}
}; // 并查集

int main() {
	Solution sol;
	vector<string> strs;
	strs = { "tars", "rats", "arts", "star" };
	cout << sol.numSimilarGroups(strs) << endl;

	strs = { "omv", "ovm" };
	cout << sol.numSimilarGroups(strs) << endl;
}