// Created: 2025-06-30
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 165. 解密数字
现有一串神秘的密文 ciphertext，经调查，密文的特点和规则如下：
	密文由非负整数组成
	数字 0-25 分别对应字母 a-z
请根据上述规则将密文 ciphertext 解密为字母，并返回共有多少种解密结果。
示例 1：
	输入：ciphertext = 216612
	输出：6
	解释：216612 解密后有 6 种不同的形式，分别是 "cbggbc"，
	"vggbc"，"vggm"，"cbggm"，"cqgbc" 和 "cqgm" 
提示：
	0 <= ciphertext < 2^31 */

class Solution {
public:
	int crackNumber(int ciphertext) {
		const string &s = to_string(ciphertext);
		int n = s.size();
		vector<int> dp(n + 1);
		dp[n] = dp[n - 1] = 1;
		for(int i = n - 2; i >= 0; --i) {
			dp[i] = dp[i + 1];
			if(s[i] == '1' || (s[i] == '2' && s[i + 1] < '6')) {
				dp[i] += dp[i + 2];
			}
		}
		return dp[0];
	}
};

int main() {
	Solution sol;
	int ciphertext;
	ciphertext = 216612;
	cout << sol.crackNumber(ciphertext) << endl; // 6
	ciphertext = 02010302;
	cout << sol.crackNumber(ciphertext) << endl; // 1
}