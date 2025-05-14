#include <iostream>
#include <vector>

using namespace std;

int binarySearch1(const vector<int> &vec, int key) {
	int i = 0, j = vec.size() - 1, middle; // 左闭右闭
	while(i <= j) {
		middle = i + (j - i) / 2;
		if(key == vec[middle]) {
			return middle;
		} else if(key < vec[middle]) {
			j = middle - 1;
		} else {
			i = middle + 1;
		}
	}
	return -1;
}

int binarySearch2(const vector<int> &vec, int key) {
	int i = 0, j = vec.size(), middle; // 左闭右开, j 为 size
	while(i < j) { // 左闭右开 i == j 为空区间
		middle = i + (j - i) / 2;
		if(key == vec[middle]) {
			return middle;
		} else if(key < vec[middle]) {
			j = middle; // 左闭右开
		} else {
			i = middle + 1; // 注意这里仍要加1
		}
	}
	return -1;
}

int main() {
	vector<int> vec = { 0, 2, 4, 6, 8, 10 };
	int key;
	while(cin >> key) {
		cout << "left close right close " << binarySearch1(vec, key) << endl;
		cout << "left close right open  " << binarySearch2(vec, key) << endl;
	}
}