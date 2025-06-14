// Created: 2025-05-23
#include "MyUtils.hpp"

/*  5. 最长回文子串
给你一个字符串 s，找到 s 中最长的 回文 子串。
示例 1：
    输入：s = "babad"
    输出："bab"
    解释："aba" 同样是符合题意的答案。
示例 2：
    输入：s = "cbbd"
    输出："bb"  */

class Solution1 {
public:
	string longestPalindrome(const string &s) {
		int max_length = 1, max_begin = 0;
		for(int i = 0; i < s.size() - max_length; ++i) {
			for(int j = s.size() - 1; j >= i + max_length; --j) {
				if(isPalindrome(s, i, j)) {
					if(j - i + 1 > max_length) {
						max_length = j - i + 1;
						max_begin = i;
					}
					break;
				}
			}
		}
		return s.substr(max_begin, max_length);
	}

private:
	inline bool isPalindrome(const string &s, int i, int j) {
		while(i < j) {
			if(s[i] != s[j]) {
				return false;
			}
			++i, --j;
		}
		return true;
	}
}; // 剪枝 ( 90ms )

class Solution2 {
public:
	string longestPalindrome(const string &s) {
		int n = s.size(), max_len = 1, begin = 0;
		vector<vector<bool>> dp(n, vector<bool>(n, false));

		for(int i = n - 1; i >= 0; --i) {
			dp[i][i] = true; // 单字符回文
			for(int j = i + 1; j < n; ++j) {
				if(s[i] == s[j]) {
					if(j - i < 3) {
						dp[i][j] = true; // "aa", "aba"
					} else {
						dp[i][j] = dp[i + 1][j - 1]; // 中间必须回文
					}
				}
				if(dp[i][j] && (j - i + 1) > max_len) {
					max_len = j - i + 1;
					begin = i;
				}
			}
		}

		return s.substr(begin, max_len);
	}
}; /* 动态规划 (179ms)
边界条件：
    i == j：单个字符一定是回文。
    j - i < 2（即子串长度为 2）时，只要 s[i] == s[j]，就是回文。
    否则，如果 s[i] == s[j] && dp[i+1][j-1]，说明当前两端字符相等且中间子串也为回文。
遍历顺序：
    外层 i 从大到小（即从后往前）
    内层 j 从 i 到 n-1
    这样保证 dp[i+1][j-1] 总是已经被计算过，避免使用未初始化的状态，符合动态规划的状态依赖顺序。*/

class Solution3 {
public:
	string longestPalindrome(const string &s) {
		n = s.size();
		for(int odd_center = 0; odd_center < n - max_half_length; ++odd_center) {
			dfs_odd(s, odd_center);
		}
		int begin = max_center - max_half_length;
		int length = max_half_length * 2 + 1;
		// max_half_length = (length - 1) / 2; // 取一个略小于奇数情况长度的半的值 (已经是了)
		for(int left_center = max_half_length; left_center < n - max_half_length - 1;
		    ++left_center) {
			dfs_even(s, left_center);
		}
		if(max_half_length * 2 > length) {
			begin = max_center - max_half_length + 1;
			length = max_half_length * 2;
		}
		return s.substr(begin, length);
	}

private:
	int max_half_length = 0, max_center = 0, n;
	void dfs_odd(const string &s, int center) {
		int max_extend = min(center, n - center - 1);
		for(int half = 1; half <= max_extend; ++half) {
			if(s[center - half] != s[center + half]) {
				break;
			}
			if(half > max_half_length) {
				max_half_length = half;
				max_center = center;
			}
		}
	}
	void dfs_even(const string &s, int left_center) {
		int max_extend = min(left_center + 1, n - left_center - 1);
		for(int half = 1; half <= max_extend; ++half) {
			if(s[left_center - half + 1] != s[left_center + half]) {
				return;
			}
			if(half > max_half_length) {
				max_half_length = half;
				max_center = left_center;
			}
		}
	}
};
/* 中心扩散 带剪枝 (0ms)
    （奇数长度）枚举每个字符 odd_center 作为回文中心，向左右两侧同时扩散，记录能扩到的最大半径
max_half_length。 （偶数长度）枚举每个「相邻字符对」 (left_center, left_center + 1)
作为回文中心，向左右扩散， 同样用同一个 max_half_length 跟之前比较，保留最大的那种。 结果拼接
    如果最长来源于奇数中心（半径 = h），长度就是 2 * h + 1，起点是 max_center - h；
    如果最长来源于偶数中心（配对数 = h），长度就是 2 * h，起点是 max_center - h + 1。
最后取更大的一种。*/

class Solution4 {
public:
	string longestPalindrome(const string &s) {
		int n = s.size();
		if(n < 2) return s;

		int start = 0, maxLen = 1;
		// lambda：从 l,r 向两边扩散，更新最长回文
		auto expand = [&](int l, int r) {
			// 一直扩到越界或两边字符不等
			while(l >= 0 && r < n && s[l] == s[r]) {
				--l;
				++r;
			}
			// 此时 (l+1 … r-1) 是回文，长度 = r-l-1
			int len = r - l - 1;
			if(len > maxLen) {
				maxLen = len;
				start = l + 1;
			}
		};

		for(int i = 0; i < n; ++i) {
			expand(i, i);     // 奇数长度回文，以 i 为中心
			expand(i, i + 1); // 偶数长度回文，以 i,i+1 为中心
		}
		return s.substr(start, maxLen);
	}
}; // 中心扩散，统一写法，没有剪枝 (8ms)

int main() {
	Solution3 sol;
}