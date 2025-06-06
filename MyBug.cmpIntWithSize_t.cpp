// Created: 2025-05-15
#include <vector>
#include <iostream>
#include <climits>
using namespace std;

int main() {
	vector<int> nums = { 1, 2, 3, 5, 6 };
	auto get_val = [&](int i) -> int {
		try {
			return nums.at(i);
		} catch(const std::exception &e) {
			return INT_MIN; // 超边界返回最小值
		}
	};
	for(int i = -1; i <= nums.size(); ++i) {
		cout << get_val(i) << " ";
	}
}

// 为什么代码没有输出？？？？

// nums.size()是一个size_t，i是int，int与size_t比较int将会被转为size_t，-1对应最大值

/*	for(int i = -1; i <= nums.size(); ++i) {
		cout << get_val(i) << " ";
	}
会导致隐式转换的错误，
	for(int i = -1; i <= int(nums.size()); ++i) { 
		cout << get_val(i) << " ";
	}
可能会超出int范围
	for(size_t i = nums.size(); i >= 0; --i) { 
		cout << get_val(i) << " ";
	}
会导致死循环

可以使用
    // std::ssize(nums) 返回 signed 类型（ptrdiff_t），可以直接和 -1 比。
    for (auto i = -1; i <= std::ssize(nums); ++i) {
        std::cout << get_val(i) << " ";
    }

‌std::ssize‌是C++20中引入的一个新功能，它是一个模板函数，用于返回给定容器或数组的大小，
但返回的是一个有符号整数类型。std::ssize的返回类型是‌std::common_type_t<std::ptrdiff_t,
std::make_signed_t<decltype(c.size())>>‌，这意味着它会将容器的大小转换为一个有符号的整数类型‌
*/