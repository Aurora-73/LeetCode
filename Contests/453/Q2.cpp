// Created: 2025-06-06
#include "MyDateGen.h"
#include "MyUtils.hpp"

/* Q2. 统计计算机解锁顺序排列数
给你一个长度为 n 的数组 complexity。
在房间里有 n 台 上锁的 计算机，这些计算机的编号为 0 到 n - 1，
每台计算机都有一个 唯一 的密码。编号为 i 的计算机的密码复杂度为 complexity{i}。
编号为 0 的计算机密码已经 解锁，并作为根节点。其他所有计算机必须通过它或其他已经解锁的计算机来解锁，具体规则如下：
可以使用编号为 j 的计算机的密码解锁编号为 i 的计算机，其中 j 是任何小于 i 的整数，
且满足 complexity{j} < complexity{i}（即 j < i 并且 complexity{j} < complexity{i}）。
要解锁编号为 i 的计算机，你需要事先解锁一个编号为 j 的计算机，
满足 j < i 并且 complexity{j} < complexity{i}。
求共有多少种 {0, 1, 2, ..., (n - 1)} 的排列方式，
能够表示从编号为 0 的计算机（唯一初始解锁的计算机）开始解锁所有计算机的有效顺序。
由于答案可能很大，返回结果需要对 109 + 7 取余数。
注意：编号为 0 的计算机的密码已解锁，而 不是 排列中第一个位置的计算机密码已解锁。
	排列 是一个数组中所有元素的重新排列。
示例 1：
	输入： complexity = {1,2,3}
	输出： 2
	解释：
	有效的排列有：
	{0, 1, 2}
	首先使用根密码解锁计算机 0。
	使用计算机 0 的密码解锁计算机 1，因为 complexity{0} < complexity{1}。
	使用计算机 1 的密码解锁计算机 2，因为 complexity{1} < complexity{2}。
	{0, 2, 1}
	首先使用根密码解锁计算机 0。
	使用计算机 0 的密码解锁计算机 2，因为 complexity{0} < complexity{2}。
	使用计算机 0 的密码解锁计算机 1，因为 complexity{0} < complexity{1}。
示例 2：
	输入： complexity = {3,3,3,4,4,4}
	输出： 0
	解释：
	没有任何排列能够解锁所有计算机。
提示：
	2 <= complexity.length <= 10 ^ 5
	1 <= complexity{i} <= 10 ^ 9 */

class Solution {
private:
	static const int MOD = 1000000007;
	vector<long long> factorial;
	vector<long long> invFactorial;

	long long modPow(long long a, long long b) {
		long long res = 1;
		while(b > 0) {
			if(b & 1) res = res * a % MOD;
			a = a * a % MOD;
			b >>= 1;
		}
		return res;
	}

	void initFactorials(int n) {
		factorial.assign(n + 1, 1);
		invFactorial.assign(n + 1, 1);
		for(int i = 1; i <= n; i++) {
			factorial[i] = factorial[i - 1] * i % MOD;
		}
		invFactorial[n] = modPow(factorial[n], MOD - 2);
		for(int i = n; i >= 1; i--) {
			invFactorial[i - 1] = invFactorial[i] * i % MOD;
		}
	}

	long long comb(int n, int k) {
		if(k < 0 || k > n) return 0;
		return factorial[n] * invFactorial[k] % MOD * invFactorial[n - k] % MOD;
	}

public:
	int countPermutations(vector<int> &complexity) {
		int n = complexity.size();

		initFactorials(n);

		int rootComplexity = complexity[0];

		unordered_map<int, int> freqMap;
		for(int i = 1; i < n; i++) {
			int c = complexity[i];
			if(c == rootComplexity || c < rootComplexity) {
				return 0;
			}
			freqMap[c]++;
		}

		vector<int> sortedValues;
		sortedValues.reserve(freqMap.size());
		for(auto &kv : freqMap) {
			sortedValues.push_back(kv.first);
		}
		sort(sortedValues.begin(), sortedValues.end());

		long long answer = 1;
		int unlockedCount = 1;

		for(int val : sortedValues) {
			int groupSize = freqMap[val];
			long long ways
			    = comb(unlockedCount + groupSize - 1, groupSize) * factorial[groupSize] % MOD;
			answer = answer * ways % MOD;
			unlockedCount += groupSize;
		}

		return int(answer);
	}
};

int main() {
	vector<int> nums;
	nums = { 1, 2, 3 };
	cout << Solution().countPermutations(nums) << endl; // 输出 2
	nums = { 3, 3, 3, 4, 4, 4 };
	cout << Solution().countPermutations(nums) << endl; // 输出 0
}