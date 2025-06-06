// MyDateGen.cpp
#include "MyDateGen.h"
#include <algorithm>
#include <chrono>
#include <numeric>
#include <random>
#include <string>
#include <vector>

using namespace std;

vector<int> randomIntArray(int n, int minVal, int maxVal, bool ordered, bool unique) {
	vector<int> arr;
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	if(unique) {
		int range = maxVal - minVal + 1;
		if(n > range) n = range; // 防止死循环
		vector<int> pool(range);
		iota(pool.begin(), pool.end(), minVal);
		shuffle(pool.begin(), pool.end(), rng);
		arr.assign(pool.begin(), pool.begin() + n);
	} else {
		arr.resize(n);
		uniform_int_distribution<int> dist(minVal, maxVal);
		for(int i = 0; i < n; ++i) arr[i] = dist(rng);
	}
	if(ordered) {
		sort(arr.begin(), arr.end());
	}
	return arr;
}

string randomString(int n, bool ordered, bool unique) {
	string str;
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	if(unique) {
		int range = 26;          // a-z
		if(n > range) n = range; // 防止死循环
		vector<char> pool(range);
		iota(pool.begin(), pool.end(), 'a');
		shuffle(pool.begin(), pool.end(), rng);
		str.assign(pool.begin(), pool.begin() + n);
	} else {
		str.resize(n);
		uniform_int_distribution<int> dist('a', 'z');
		for(int i = 0; i < n; ++i) str[i] = dist(rng);
	}
	if(ordered) {
		sort(str.begin(), str.end());
	}
	return str;
}

vector<vector<int>> randomMatrix(int rows, int cols, int minVal, int maxVal) {
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	uniform_int_distribution<int> dist(minVal, maxVal);
	vector<vector<int>> mat(rows, vector<int>(cols));
	for(int i = 0; i < rows; ++i)
		for(int j = 0; j < cols; ++j) mat[i][j] = dist(rng);
	return mat;
}