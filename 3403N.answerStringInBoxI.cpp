// Created: 2025-06-04
#include "MyUtils.h"

/* 3403. 从盒子中找出字典序最大的字符串 I
给你一个字符串 word 和一个整数 numFriends。
Alice 正在为她的 numFriends 位朋友组织一个游戏。游戏分为多个回合，在每一回合中：
word 被分割成 numFriends 个 非空 字符串，且该分割方式与之前的任意回合所采用的都 不完全相同 。
所有分割出的字符串都会被放入一个盒子中。
在所有回合结束后， 找出盒子中字典序最大的 字符串 。
示例 1：
    输入: word = "dbca", numFriends = 2
    输出: "dbc"
    解释: 
    所有可能的分割方式为：
        "d" 和 "bca"。
        "db" 和 "ca"。
        "dbc" 和 "a"。
提示:
    1 <= word.length <= 5 * 103
    word 仅由小写英文字母组成。
    1 <= numFriends <= word.length*/

class Solution1 {
public:
	string answerString(const string &word, int numFriends) {
		// | 前面的 |  需要的 | 后面的 | len(前面的) + len(后面的) + 1 >= numFriends
		// 满足这个的前提下寻找字典序最大的元素，先找到最大的字典序的开头，然后尽可能的往后延伸
		if(numFriends == 1) return word;
		int maxChar = INT_MIN;
		unsigned n = word.size();
		vector<unsigned> maxIndexs;
		for(unsigned i = 0; i < n; ++i) {
			if(word[i] > maxChar) {
				maxChar = word[i];
				maxIndexs.clear();
				maxIndexs.push_back(i);
			} else if(word[i] == maxChar) {
				maxIndexs.push_back(i);
			}
		}
		int length = 1;
		while(maxIndexs.size() > 1) {
			int maxNext = INT_MIN;
			vector<unsigned> oldIndexs = std::move(maxIndexs);
			for(auto i : oldIndexs) {
				if(i + length >= n) {
					continue; // 不可能不同的开头都超过边界，超了直接删
				}
				if(word[i + length] > maxNext) {
					maxNext = word[i + length];
					maxIndexs.clear();
					maxIndexs.push_back(i);
				} else if(word[i + length] == maxNext) {
					maxIndexs.push_back(i);
				}
			}
			++length;
		}
		return word.substr(maxIndexs[0], n - numFriends + 1);
	}
};

class Solution2 {
public:
	string answerString(string word, int numFriends) {
		if(numFriends == 1) {
			return word;
		}
		int n = word.size();

		std::string_view res; // string_view 不需要拷贝 比 string 快的多
		for(int i = 0; i < n; ++i) {
			int len = std::min(n - numFriends + 1, n - i);
			std::string_view cur(word.data() + i, len);
			if(cur > res) res = cur;
		}
		return std::string(res);
	}
};

class Solution3 {
public:
	string answerString(const string &word, int numFriends) {
		if(numFriends == 1) return word;
		int n = word.size();
		int maxIndexs = -1;
		vector<long double> dp(n + 1, 0.0);
		long double max_val = -1.0;

		// —— 第一段：当 i >= numFriends-1 时，把整个后缀当作候选
		constexpr double offset = 26.0;
		constexpr double rate = ((26 + offset) * 1000000.0);
		for(int i = n - 1; i > numFriends - 2; --i) {
			dp[i] = (dp[i + 1] * 1000000.0 + (word[i] - 'a' + offset) * rate) / rate;
			// + offset 防止太小，提高精度
			if(dp[i] >= max_val) {
				max_val = dp[i];
				maxIndexs = i;
			}
		}

		// —— 第二段：当 i < numFriends-1 时，只能取到 j = n - numFriends -1 + i
		// 这一段的子串
		for(int i = numFriends - 2; i >= 0; --i) {
			int j = n - numFriends - 1 + i;
			// 正确的 “ 尾巴 ” 值：把 dp[j] 右移 (j - i) 位，也就是 dp[j] / 30 ^ (j - i)
			long double tail
			    = (j < 0 ? 0.0
			             : ((word[j] - 'a' + offset) * 1000000.0 / pow(26.0 + offset, j - i + 1)));
			dp[i] = (dp[i + 1] * 1000000.0 + (word[i] - 'a' + offset) * rate - tail) / rate;
			if(dp[i] >= max_val) {
				max_val = dp[i];
				maxIndexs = i;
			}
		}
		return word.substr(maxIndexs, n - numFriends + 1);
	}
}; // 计算每个位置开头的 字符串 的字典值

class Solution {
public:
	string answerString(const string &s, int k) {
		if(k == 1) {
			return s;
		}
		int n = s.size();
		int i = 0, j = 1;
		while(j < n) {
			int k = 0;
			while(j + k < n && s[i + k] == s[j + k]) {
				k++;
			}
			// k != 0 则 s[j + 1], s[j + 2], ..., s[j + k] 都和 s[i] 相等
			if(j + k < n && s[i + k] < s[j + k]) {
				int t = i;
				i = j;
				j = max(j + 1, t + k + 1);
			} else {
				j += k + 1;
			}
		}
		return s.substr(i, n - max(k - 1, i));
	}
};

int main() {
	Solution sol;
	cout << sol.answerString("qaoaamq", 6) << endl;
	cout << sol.answerString(
	    "dbfhwjevzfdbfahwjefahfaajlbhffrahwjefahfaajsgregrgrgsefefwaefdwadeawdcaavczxcczhahwbxjefah"
	    "faajlbhwjefahfaajlffrsgrjefzazzhzegrgrgsefefaajlffrahwjefahfaajsgrfahwjefahfaajgrgahwjefah"
	    "faajrgszzeahwjefahfaajfeahwjefahfaajfwaefdwadezzzzzzzzzzawdca",
	    16)
	     << endl;
	cout << sol.answerString("gggg", 4) << endl;
	cout << sol.answerString("dbca", 2) << endl;
	cout << sol.answerString("idfi", 2) << endl;
}