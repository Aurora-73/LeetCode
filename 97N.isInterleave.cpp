// Created: 2025-05-24
#include "MyUtils.h"

/*97. 交错字符串
给定三个字符串 s1、s2、s3，请你帮忙验证 s3 是否是由 s1 和 s2 交错 组成的。
两个字符串 s 和 t 交错 的定义与过程如下，其中每个字符串都会被分割成若干 非空 子字符串：
s = s1 + s2 + ... + sn
t = t1 + t2 + ... + tm
|n - m| <= 1
交错 是 s1 + t1 + s2 + t2 + s3 + t3 + ... 或者 t1 + s1 + t2 + s2 + t3 + s3 + ...
注意：a + b 意味着字符串 a 和 b 连接。*/

class Solution1 {
public:
	bool isInterleave(const string &s1, const string &s2, const string &s3) {
		n1 = s1.size(), n2 = s2.size(), n3 = s3.size();
		if(n1 + n2 != n3) {
			return false;
		}
		return dfs(s1, s2, s3, 0, 0);
	}

private:
	int n1, n2, n3;
	bool dfs(const string &s1, const string &s2, const string &s3, int i1, int i3) {
		int i2 = i3 - i1; // 传参时可以不传 i2
		if(i1 == n1 && i2 == n2 && i3 == n3) {
			return true;
		}
		if(i1 == n1 && s2[i2] != s3[i3]) {
			return false;
		}
		if(i2 == n2 && s1[i1] != s3[i3]) {
			return false;
		}
		bool res = false;
		if(i1 != n1 && s1[i1] == s3[i3]) {
			res |= dfs(s1, s2, s3, i1 + 1, i3 + 1);
		}
		if(res) return true;
		if(i2 != n2 && s2[i2] == s3[i3]) {
			res |= dfs(s1, s2, s3, i1, i3 + 1);
		}
		return res;
	}
}; // 暴力搜索

struct myHash {
	size_t operator()(const pair<int, int> &pa) const {
		return ((size_t)pa.first << 32) ^ (size_t)pa.second;
	}
};

class Solution2 {
public:
	bool isInterleave(const string &s1, const string &s2, const string &s3) {
		n1 = s1.size(), n2 = s2.size(), n3 = s3.size();
		if(n1 + n2 != n3) {
			return false;
		}
		return dfs(s1, s2, s3, 0, 0);
	}

private:
	int n1, n2, n3;
	unordered_map<pair<int, int>, bool, myHash> memo;
	bool dfs(const string &s1, const string &s2, const string &s3, int i1, int i2) {
		int i3 = i1 + i2;
		auto it = memo.find({ i1, i2 });
		if(it != memo.end()) {
			return it->second;
		}
		if(i1 == n1 && i2 == n2 && i3 == n3) {
			return true;
		}
		if(i1 == n1 && s2[i2] != s3[i3]) {
			return false;
		}
		if(i2 == n2 && s1[i1] != s3[i3]) {
			return false;
		}
		bool res = false;
		if(i1 != n1 && s1[i1] == s3[i3]) {
			res |= dfs(s1, s2, s3, i1 + 1, i2);
		}
		if(!res && i2 != n2 && s2[i2] == s3[i3]) {
			res |= dfs(s1, s2, s3, i1, i2 + 1);
		}
		memo[{ i1, i2 }] = res;
		return res;
	}
}; // 记忆化搜索
// 提取到递推式 dp[i][j] = (i < n1 && s1[i] == s3[i + j] && dp[i + 1][j]) || (j < n2 && s2[j] ==
// s3[i + j] && dp[i][j + 1]) 想获取dp[i][j] 要先获取 dp[i + 1][j] 和 dp[i][j + 1]

class Solution3 {
public:
	bool isInterleave(const string &s1, const string &s2, const string &s3) {
		int n1 = s1.size(), n2 = s2.size(), n3 = s3.size();
		if(n3 != n1 + n2) return false;
		vector<vector<bool>> dp(n1 + 1, vector<bool>(n2 + 1, false));
		for(int i = n1; i >= 0; --i) {
			for(int j = n2; j >= 0; --j) {
				dp[i][j] = (i < n1 && s1[i] == s3[i + j] && dp[i + 1][j])
				    || (j < n2 && s2[j] == s3[i + j] && dp[i][j + 1])
				    || (i == n1 && j == n2); // 终点也为真 i == n1 && j == n2
			}
		}
		return dp[0][0];
	}
};

class Solution4 {
public:
	bool isInterleave(const string &s1, const string &s2, const string &s3) {
		int n1 = s1.size(), n2 = s2.size(), n3 = s3.size();
		if(n3 != n1 + n2) return false;

		vector<vector<bool>> dp(n1 + 1, vector<bool>(n2 + 1, false));
		dp[n1][n2] = true; // 终点初始化为 true

		for(int i = n1; i >= 0; --i) {
			for(int j = n2; j >= 0; --j) {
				if(i < n1 && s1[i] == s3[i + j] && dp[i + 1][j]) {
					dp[i][j] = true;
				}
				if(j < n2 && s2[j] == s3[i + j] && dp[i][j + 1]) {
					dp[i][j] = true;
				}
			}
		}
		return dp[0][0];
	}
}; /* 所以是外层循环遍历i就压缩i，外层循环遍历j就压缩j吗
ChatGPT 说：
对的，从滚动数组的「上一轮」概念来看：
如果外层循环是 i，那么每一次外层迭代就代表「上一行」完整的一维状态保存在一维数组里，因而要压缩行，也就是压缩 i 维，
如果把循环顺序颠倒，外层是 j，那「上一列」的完整状态就在一维数组里，就应该压缩列，也就是压缩 j 维，
最终原则是：
压缩那一维，就要让它在外层循环，每轮保留「上一轮」的完整状态；另一维在内层循环，用倒序（或正序）确保依赖的本轮值不会被提前覆盖。*/

class Solution5 {
public:
	bool isInterleave(string &s1, string &s2, string &s3) {
		if(s1.size() > s2.size()) {
			std::swap(s1, s2);
		} // 保持s1短于s2
		int n1 = s1.size(), n2 = s2.size(), n3 = s3.size();
		if(n3 != n1 + n2) return false;
		vector<bool> dp(n2 + 1, false);
		for(int i = n1; i >= 0; --i) {
			for(int j = n2; j >= 0; --j) {
				bool from_s1 = false;
				if(i < n1 && s1[i] == s3[i + j] && dp[j]) {
					from_s1 = true; // 这里用的 dp[j] 还是「上一行」的值
				}
				bool from_s2 = false;
				if(j < n2 && s2[j] == s3[i + j] && dp[j + 1]) {
					from_s2 = true; // dp[j+1] 是本行右侧刚更新过的 dp[i][j+1]
				}
				dp[j] = from_s1 || from_s2 || (i == n1 && j == n2);
			}
		}
		return dp[0];
	}
};

class Solution {
public:
	bool isInterleave(string &s1, string &s2, string &s3) {
		if(s1.size() > s2.size()) {
			std::swap(s1, s2);
		} // 保持s1短于s2
		int n1 = s1.size(), n2 = s2.size(), n3 = s3.size();
		if(n3 != n1 + n2) return false;
		vector<bool> dp(n2 + 1, false);
		dp[n2] = true; // 终点初始化为 true
		for(int i = n1; i >= 0; --i) {
			for(int j = n2; j >= 0; --j) {
				dp[j] = (i < n1 && s1[i] == s3[i + j] && dp[j])
				    || (j < n2 && s2[j] == s3[i + j] && dp[j + 1])
				    || (i == n1 && j == n2); // 终点也为真 i == n1 && j == n2
			}
		}
		return dp[0];
	}
};

int main() {
	Solution sol;
	string s1, s2, s3;
	s1 = "dbbc";
	s2 = "aabcca";
	s3 = "aadbbcbcac";
	cout << sol.isInterleave(s1, s2, s3);
}