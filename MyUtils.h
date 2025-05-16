#ifndef MY_UTILS_H
#define MY_UTILS_H

// 常用标准库
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <set>
#include <climits>
#include <cassert>
#include <memory>
#include <bitset>
#include <stdexcept>
#include <cmath>
#include <cctype>
#include <limits>
#include <type_traits>
#include <functional>
using namespace std;

// ================= 输入输出加速 =================
void fast_io() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
}

// ================= 调试输出系统 =================
#define DEBUG(...)                                                                                                     \
	cerr << #__VA_ARGS__ << " = ";                                                                                     \
	_debug(__VA_ARGS__);

template <typename T>
void _debug(const T &t) {
	cerr << t << endl;
}

template <typename T, typename... Args>
void _debug(const T &t, const Args &...args) {
	cerr << t << ", ";
	_debug(args...);
}

// ================= 容器输出重载 =================
// vector
template <typename T>
ostream &operator<<(ostream &os, const vector<T> &vec) {
	os << "{";
	for(size_t i = 0; i < vec.size(); ++i) {
		os << vec[i] << (i == vec.size() - 1 ? "" : ", ");
	}
	return os << "}";
}

// pair
template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &p) {
	return os << "(" << p.first << " → " << p.second << ")";
}

// map（按有序格式输出）
template <typename K, typename V>
ostream &operator<<(ostream &os, const map<K, V> &m) {
	os << "{";
	for(auto it = m.begin(); it != m.end();) {
		os << it->first << " ⇒ " << it->second;
		if(++it != m.end()) os << ", ";
	}
	return os << "}";
}

// unordered_map（输出不保证顺序）
template <typename K, typename V>
ostream &operator<<(ostream &os, const unordered_map<K, V> &um) {
	os << "{";
	size_t count = 0;
	for(const auto &kv : um) {
		os << kv.first << " ⇒ " << kv.second;
		if(++count != um.size()) os << ", ";
	}
	return os << "}";
}

// set
template <typename T>
ostream &operator<<(ostream &os, const set<T> &s) {
	os << "{";
	for(auto it = s.begin(); it != s.end();) {
		os << *it;
		if(++it != s.end()) os << ", ";
	}
	return os << "}";
}

// unordered_set
template <typename T>
ostream &operator<<(ostream &os, const unordered_set<T> &us) {
	os << "{";
	size_t count = 0;
	for(const auto &elem : us) {
		os << elem;
		if(++count != us.size()) os << ", ";
	}
	return os << "}";
}

template <typename RandomIt, typename Cond>
RandomIt my_find_first(RandomIt first, RandomIt last, Cond cond) {
	// 要求 RandomIt 支持 last - first
	using diff_t = typename std::iterator_traits<RandomIt>::difference_type;
	diff_t len = last - first; // 区间 [first, last) 长度

	while(len > 0) {
		diff_t half = len / 2;
		RandomIt mid = first + half; // 计算中点
		if(!cond(mid)) {
			// [first..mid] 都不满足
			first = mid + 1;
			len = len - half - 1;
		} else {
			// mid 及其右侧可能满足
			len = half;
		}
	}
	// 退出时 first==last 或 *first 是第一个满足 cond 的位置
	return first;
} // 返回第一个使得 cond条件为真的元素的的迭代器, 分界线左边不满足，右边均满足，左闭右开
// 标准格式，lower_bound是conde = [&](RandomIt::value_type val){return val >= key;}
// upper_bound是conde = [&](RandomIt::value_type val){return val > key;}
// binary_search是conde = [&](RandomIt::value_type val){return val >= key;} 且 first != end && *first == key
// 更好的写法应该是 std::iterator_traits<RandomIt>::value_type，因为 RandomIt 可能是原生指针

#endif // MY_UTILS_H