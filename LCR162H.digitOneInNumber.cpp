// Created: 2025-07-02
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 162. 数字 1 的个数
给定一个整数 num，计算所有小于等于 num 的非负整数中数字 1 出现的个数。
示例 1：
	输入：num = 0
	输出：0
示例 2：
	输入：num = 13
	输出：6
提示：
	0 <= num < 10^9 */

class Solution1 {
public:
	int digitOneInNumber(int num) {
		return oneCount(num);
	}

private:
	int oneCount(int num) {
		if(num <= 1) return num;                       // 递归终点: 0 1
		int digits = (int)log10(num) + 1;              // 共有多少位
		int less_pot = int(pow(10, digits - 1));       // 小于 num 的最大十的幂
		if(digits < 10 && num + 1 == less_pot * 10)    // int 型最高 10 位，*10会溢出
			return digits * less_pot;                  // 递归终点: 全是 9
		int big = num / less_pot;                      // 最高位的值
		int nine_res = (digits - 1) * (less_pot / 10); // 少一位的全是9的结果
		int res = big * nine_res;                      // 第一部分，按less_pot切分
		if(big > 1) {
			res += less_pot; // 最高位大于1，之前1xxx每个多一个1
		} else {
			res += num - less_pot + 1; // 最高位是1，剩余部分每个多一次1
		} // 处理最高位1的出现次数
		return res + oneCount(num - big * less_pot);
	}
};

/* 先考虑0 - 9, 90 - 99, 900 - 999, 9000 - 9999 的情况

    位数				
    1	1			
        1			
    2	1x	    x1		
        10	    9		
    3	1xx	    x1x	    xx1	
        100	    90	    90	
    4	1xxx	x1xx	xx1x	xxx1
        1000	900	    900	    900 
    注意这些每个1仅统计一次，没有重叠，因此 f(10 ^ n - 1) = n * (10 ^ (n - 1)) 

对于非全是9的情况，将其分割位，以441为例：

    000 - 099   f(99)
    100 - 199   f(99) + 最高位1的个数 100
    200 - 299   f(99)
    300 - 399   f(99)
    400 - 441   递归f(41)

    f(41):
    00 - 09     f(9)
    10 - 19     f(9) + 最高位1的个数 10
    20 - 29     f(9)
    30 - 39     f(9)
    40 - 41     递归f(1) = 1 

注意需要计算最高位1的出现次数*/

class Solution {
public:
	int digitOneInNumber(int num) {
		int res = 0;
		while(num >= 1) {
			int digits = (int)log10(num) + 1;              // 共有多少位
			int less_pot = int(pow(10, digits - 1));       // 小于 num 的最大十的幂
			int big = num / less_pot;                      // 最高位，不为 0
			int nine_res = (digits - 1) * (less_pot / 10); // 少一位的全是9的数的值
			res += big * nine_res;                         // 第一部分，按less_pot切分
			if(big > 1) {
				res += less_pot; // 最高位大于1，之前1xxx每个多一个1
			} else {
				res += num - less_pot + 1; // 最高位是1，剩余部分每个多一次1
			} // 处理最高位1的出现次数
			num -= big * less_pot;
		}
		return res;
	}
}; // 改递归为递推

int main() {
	Solution sol;
	int num = 441;
	cout << sol.digitOneInNumber(num) << endl;
	num = 654321;
	cout << sol.digitOneInNumber(num) << endl;
}