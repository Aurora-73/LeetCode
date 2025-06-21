// Created: 2025-06-21
#include "MyDateGen.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 72. 编辑距离
给你两个单词word1 和word2， 请返回将word1转换成word2 所使用的最少操作数。
你可以对一个单词进行如下三种操作：
	插入一个字符
	删除一个字符
	替换一个字符
示例1：
    输入：word1 = "horse", word2 = "ros"
    输出：3
    解释：
    horse -> rorse (将 "h" 替换为 "r")
    rorse -> rose (删除 "r")
    rose -> ros (删除 "e")
示例2：
	输入：word1 = "intention", word2 = "execution"
	输出：5
	解释：
	intention -> inention (删除 "t")
	inention -> enention (将 "i" 替换为 "e")
	enention -> exention (将 "n" 替换为 "x")
	exention -> exection (将 "n" 替换为 "c")
	exection -> execution (插入 "u")
提示：
	0 <= word1.length, word2.length <= 500
	word1 和 word2 由小写英文字母组成 */

class Solution1 {
public:
	int minDistance(string &word1, string &word2) {
		int n1 = word1.size(), n2 = word2.size();
		vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1));
		// dp[i][j] 表示 word1 的前 i 位到 word2 的前 j 位的编辑距离
		for(int i = 0; i <= n1; ++i) dp[i][0] = i;
		for(int j = 0; j <= n2; ++j) dp[0][j] = j;
		for(int i = 1; i <= n1; ++i) {
			for(int j = 1; j <= n2; ++j) {
				if(word1[i - 1] == word2[j - 1]) { // 注意前x位的下标为x - 1
					dp[i][j] = dp[i - 1][j - 1];
				} else {
					dp[i][j] = min({ dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1] }) + 1;
				}
			}
		}
		return dp.back().back();
	}
};

class Solution {
public:
	int minDistance(string &word1, string &word2) {
		if(word1.size() < word2.size()) std::swap(word1, word2);
		int n1 = word1.size(), n2 = word2.size();
		vector<int> curr(n2 + 1);
		for(int j = 0; j <= n2; ++j) curr[j] = j;
		for(int i = 1; i <= n1; ++i) {
			int diga = curr[0]; // 不是初始化为 0
			curr[0] = i;        // 需要初始化
			for(int j = 1; j <= n2; ++j) {
				int temp = curr[j];
				if(word1[i - 1] == word2[j - 1]) { // 注意前x位的下标为x - 1
					curr[j] = diga;
				} else {
					curr[j] = min({ curr[j], curr[j - 1], diga }) + 1;
				}
				diga = temp;
			}
		}
		return curr.back();
	}
}; // 滚动数组优化

int main() {
	Solution sol;
	string word1, word2;
	word1 = "horse", word2 = "ros";
	cout << sol.minDistance(word1, word2) << endl; // 3
	word1 = "intention", word2 = "execution";
	cout << sol.minDistance(word1, word2) << endl; // 5
}