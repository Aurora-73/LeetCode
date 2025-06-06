// Created: 2025-06-02
#include "MyUtils.hpp"
#include <cstring>
#include <random>
/*1218. 最长定差子序列
给你一个整数数组 arr 和一个整数 difference，请你找出并返回 arr 中最长等差子序列的长度，该子序列中相邻元素之间的差等于 difference。
子序列 是指在不改变其余元素顺序的情况下，通过删除一些元素或不删除任何元素而从 arr 派生出来的序列。
示例 1：
    输入：arr = [1,2,3,4], difference = 1
    输出：4
    解释：最长的等差子序列是 [1,2,3,4]。*/

class Solution1 {
public:
	int longestSubsequence(vector<int> &arr, int difference) {
		constexpr int mov = 10002, size = 2 * mov;
		int n = arr.size(), res = 1;
		array<int, size> dp; // index = val + mov
		dp.fill(0);
		for(int i = n - 1; i >= 0; --i) {
			int val = arr[i], index = val + mov, temp = index + difference; // 只找一个，不需要循环
			bool vaild = temp >= 0 && temp < 2 * mov;
			dp[index] = max((vaild ? dp[temp] : 0) + 1, dp[index]);
			res = max(res, dp[index]);
		}
		return res;
	}
}; // 值域dp

class Solution {
public:
	int longestSubsequence(vector<int> &arr, int difference) {
		memset(dp, 0, sizeof(dp));
		int n = arr.size(), res = 1, next;
		for(auto &a : arr) {
			a += mov;
			next = a - difference;
			bool vaild = next >= 0 && next < 2 * mov;
			dp[a] = max((vaild ? dp[next] : 0) + 1, dp[a]);
			res = max(res, dp[a]);
		}
		return res;
	}

private:
	static constexpr int mov = 10002, size = 2 * mov;
	static int dp[size]; // 只是声明
};

// ——— 在类外为静态成员 dp 提供定义 ———
int Solution::dp[Solution::size];

/* 在类内声明一个 static 成员变量，只是告诉编译器“这个类有这么一个静态成员”；
它并不真正为这块内存分配空间。真正的内存分配（也就是“定义”）要在类外显式写一行，
否则链接阶段找不到这块存储，就会报“未定义引用”（undefined reference）的错误。 */
// constexpr是编译器替换的，不需要类外声明
/* 类是用户自定义的一种数据类型，只描述了结构和接口。
普通成员变量的内存由对象创建时自动分配和销毁；
静态成员变量属于整个类，只存在一份，因此需要在类外显式定义一次来分配全局存储。*/

class Solution2 {
public:
	int longestSubsequence(vector<int> &arr, int difference) {
		int res = 0, temp;
		unordered_map<int, int> dp;
		for(auto &a : arr) {
			temp = dp[a - difference] + 1;
			dp[a] = temp;
			res = max(res, temp);
		}
		return res;
	}
};

int main() {
	int n = 100000;
	vector<int> arr(n);
	random_device rd;
	mt19937 gen(rd());
	int minVal = -10000, maxVal = 10000;
	uniform_int_distribution<> dis(minVal, maxVal);
	for(int i = 0; i < n; ++i) {
		arr[i] = dis(gen);
	}
	cout << Solution().longestSubsequence(arr, 5) << endl;
	cout << Solution1().longestSubsequence(arr, 5) << endl;
}