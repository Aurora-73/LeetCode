// Created: 2026-01-01
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 编写一个函数，不用临时变量，直接交换numbers = {a, b}中a与b的值。
示例：
输入: numbers = {1,2}
输出: {2,1}
提示：
	numbers.length == 2
	-2147483647 <= numbers{i} <=2147483647 */

// 异或的性质
class Solution {
public:
	vector<int> swapNumbers(vector<int> &numbers) {
		numbers[0] = numbers[0] ^ numbers[1];
		numbers[1] = numbers[0] ^ numbers[1];
		numbers[0] = numbers[0] ^ numbers[1];
		return numbers;
	}
};
/* 自反性：a^a=0
    零元：a^0=a
    交换律和结合律：顺序无所谓
    可逆性：a^b = c⟹a = b^c */

// 因此 a = a ^ b #= a ^ b
// b = a ^ b #= a ^ b ^ b = a
// a = a ^ b #= a ^ b ^ a = b
// "#=" 是 "值是" 的意思

int main() {
	Solution sol;
	vector<int> numbers;
	numbers = { 1, 2 };
	cout << sol.swapNumbers(numbers) << endl;

	numbers = { 123123, 312312 };
	cout << sol.swapNumbers(numbers) << endl;
}