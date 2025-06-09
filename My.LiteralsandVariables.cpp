// Created: 2025-05-23
#include <chrono>
#include <iostream>
using namespace std;

char *test1() {
	return (char *)"NULL"; // 返回字符串字面量，位于只读区
}

char *test2() {
	char str[5] = "NULL";
	return (char *)str;
	// 返回局部变量！
}

void test3() {
	cout << (void *)"NULL" << endl;
}

int main() {
	char *a;
	a = test1();

	for(int i = 0; i < 4; ++i) {
		cout << a[i] << " ";
	}
	cout << endl;
	char *b;
	b = test2();
	if(b != nullptr) {
		for(int i = 0; i < 4; ++i) {
			cout << b[i] << " "; // 错误，局部变量已经被销毁
		}
		cout << endl;
	} else {
		cout << (void *)(b) << " is nullptr" << endl; // 是空指针了
	}
	cout << reinterpret_cast<void *>(a) << endl;
	const char *c = "NULL"; // 指向只读全局变量区，不用const不安全
	cout << reinterpret_cast<const void *>(c) << endl;
	test3(); // 字面量的值保存在只读取，会进行字符串字面量合并
	return 0;
}