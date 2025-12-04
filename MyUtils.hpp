#ifndef MY_UTILS_H
#define MY_UTILS_H

// 常用标准库
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cctype>
#include <chrono>
#include <climits>
#include <cmath>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

// ================= 调试输出系统 =================
#define DEBUG(...)                                                                                 \
	cerr << #__VA_ARGS__ << " = ";                                                                 \
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
// pair
template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &p) {
	return os << "(" << p.first << ", " << p.second << ")";
}

// vector
template <typename T>
ostream &operator<<(ostream &os, const vector<T> &vec) {
	os << "{ ";
	for(size_t i = 0; i < vec.size(); ++i) {
		os << vec[i] << ((i == vec.size() - 1) ? "" : ", ");
	}
	return os << " }";
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

#endif // MY_UTILS_H