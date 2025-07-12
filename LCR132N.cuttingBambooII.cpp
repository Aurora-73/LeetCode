// Created: 2025-07-02
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 131. 砍竹子 I
现需要将一根长为正整数 bamboo_len 的竹子砍为若干段，每段长度均为正整数。
请返回每段竹子长度的最大乘积是多少。至少砍一次
示例 1：
	输入: bamboo_len = 12
	输出: 81
提示：
	2 <= bamboo_len<= 58 */

class Solution {
public:
	int cuttingBamboo(int n) {
		if(n <= 3) return n - 1;
		int quotient = n / 3, remainder = n % 3;
		if(remainder == 0) {
			return pow(3, quotient);
		} else if(remainder == 1) {
			return pow(3, quotient - 1) * 4;
		} else {
			return pow(3, quotient) * 2;
		}
	}
};
// 首先在实数域内考虑，设每段长度为x，则f(x) = x ^ (b / x) 取对数后求导得 x = e 时最大，因此整数仅需要考虑 2,3
// 设 3 ^ (b / 3) > 2 ^ (b / 2) 由于 2ln3 > 3ln2，因此恒成立，因此 x 为 3 时最好，接下来考虑 b 不能被 3 整除的情况
// 若余数为1，因为 2 * 2 > 3 * 1，因此借一个3的1，补为2最大。若余数为2，2 > 1 * 1，将余下的单独分为一段即可

int main() {
	Solution sol;
	int bamboo_len = 12;
	cout << sol.cuttingBamboo(bamboo_len) << endl;
}