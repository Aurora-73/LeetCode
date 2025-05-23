// Created: 2025-05-23
#include "MyUtils.h"

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

class Solution {
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
			int li = left_center - (half - 1);
			int ri = left_center + half;
			if(s[li] != s[ri]) {
				return;
			}
			if(half > max_half_length) {
				max_half_length = half;
				max_center = left_center;
			}
		}
	}
};
/* 中心扩散（奇数长度）
    枚举每个字符 odd_center 作为回文中心，向左右两侧同时扩散，记录能扩到的最大半径 max_half_length。
中心扩散（偶数长度）
    枚举每个「相邻字符对」 (left_center, left_center + 1) 作为回文中心，向左右扩散，
    同样用同一个 max_half_length 跟之前比较，保留最大的那种。
结果拼接
    如果最长来源于奇数中心（半径 = h），长度就是 2 * h + 1，起点是 max_center - h；
    如果最长来源于偶数中心（配对数 = h），长度就是 2 * h，起点是 max_center - h + 1。
最后取更大的一种。*/

int main() {
	Solution sol;
}