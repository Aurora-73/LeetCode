// Created: 2026-01-02
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/*面试题 16.05. 阶乘尾数
设计一个算法，算出 n 阶乘有多少个尾随零。
示例 1：
	输入：3
	输出：0
	解释：3! = 6, 尾数中没有零。
示例 2：
	输入：5
	输出：1
	解释：5! = 120, 尾数中有 1 个零.
	说明: 你算法的时间复杂度应为 O(log n)。*/

class Solution {
public:
	int trailingZeroes(int n) {
		int res = 0;
		while(n) {
			n /= 5;
			res += n;
		}
		return res;
	}
};
/* 方法一：优化计算
考虑 {1,n} 中质因子 p 的个数。
{1,n} 中 p 的倍数有 n1​=⌊pn​⌋ 个，这些数至少贡献出了 n1​ 个质因子 p。p2 的倍数有 n2​=⌊p2n​⌋ 个，
由于这些数已经是 p 的倍数了，为了不重复统计 p 的个数，我们仅考虑额外贡献的质因子个数，即这些数额外贡献了至少 n2​ 个质因子 p。
依此类推，{1,n} 中质因子 p 的个数为
k=1∑∞​⌊pkn​⌋
上式表明：
n 不变，p 越大，质因子个数越少，因此 {1,n} 中质因子 5 的个数不会大于质因子 2 的个数；
{1,n} 中质因子 5 的个数为
k=1∑∞​⌊5kn​⌋<k=1∑∞​5kn​=4n​=O(n)
代码实现时，由于
⌊5kn​⌋=⌊5⌊5k−1n​⌋​⌋
因此我们可以通过不断将 n 除以 5，并累加每次除后的 n，来得到答案。
Python3C++JavaC#GolangCJavaScriptclass Solution:
    def trailingZeroes(self, n: int) -> int:
        ans = 0
        while n:
            n //= 5
            ans += n
        return ans
复杂度分析
时间复杂度：O(logn)。
空间复杂度：O(1)。 */

/*k=1∑∞5kn⌋
从最直观的角度看
在 1 ~ n 里：
每 5 个数，至少有 1 个能贡献一个 5
→ ⌊n/5⌋
每 25 = 5² 个数，有 1 个能贡献 额外一个 5
→ ⌊n/25⌋
每 125 = 5³ 个数，再多贡献一个 5
→ ⌊n/125⌋
例如：
25 = 5² 本身就贡献 2 个 5
125 = 5³ 贡献 3 个 5
所以必须叠加统计。
2️⃣ 为什么不会重复计算？
你担心的点一般是这里。
⌊n/5⌋：统计的是 至少有 1 个 5
⌊n/25⌋：只统计 “第二个 5”
⌊n/125⌋：只统计 “第三个 5”
也就是说：
每一层只统计“新增加的 5”*/

int main() {
	Solution sol;
	int n;
	n = 10000;
	cout << sol.trailingZeroes(n) << endl;

	n = 4235342;
	cout << sol.trailingZeroes(n) << endl;
}