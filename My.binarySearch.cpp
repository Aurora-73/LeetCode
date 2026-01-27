#include "MyUtils.hpp"

using namespace std;
// 统一 : 区间风格：左闭右开 [l, r)

int binarySearch(const vector<int> &vec, int key) {
	int left = 0, right = vec.size(), middle; // 左闭右开, right 为 size
	while(left < right) {                     // 左闭右开 left == right 为空区间
		middle = left + (right - left) / 2;
		if(key == vec[middle]) {
			return middle;
		} else if(key < vec[middle]) {
			right = middle; // 左闭右开
		} else {
			left = middle + 1; // 注意这里仍要加1
		}
	}
	return -1;
}

int lower_bound(const vector<int> &vec, int key) {
	int left = 0, right = vec.size();
	while(left < right) {
		int mid = left + (right - left) / 2;
		if(vec[mid] < key) {
			left = mid + 1;
		} else {
			right = mid;
		}
	}
	return left;
} // 返回第一个大于等于key的元素的下标 左闭右开

int upper_bound(const vector<int> &vec, int key) {
	int left = 0, right = vec.size();
	while(left < right) {
		int mid = left + (right - left) / 2;
		if(vec[mid] <= key) {
			left = mid + 1;
		} else {
			right = mid;
		}
	}
	return left;
} // 返回第一个大于key的元素的下标 左闭右开

/* lower_bound 是第一个大于等于 key 的元素，upper_bound 是第一个大于 key 的元素。
   这样只会用到 end()，不会用到 begin() - 1。
   而如果搜索最后一个小于 key 的元素 或者 最后一个小于等于 key 的元素可能会用到 begin() - 1 */

// template <typename Cond>
// int find_first(const vector<int> &vec, Cond cond) {
// 	int left = 0, right = vec.size(); // [left, right)
// 	while(left < right) {
// 		int mid = left + (right - left) / 2;
// 		// 左边都是 false，右边都是 true
// 		if(!cond(vec[mid])) {
// 			left = mid + 1; // vec[mid] 不满足，答案在 mid+1…right
// 		} else {
// 			right = mid; // vec[mid] 满足，答案在 left…mid
// 			             // mid 满足，不舍弃（虽然在左闭右开的形式中舍弃了，但是返回时left =
// 			             // right其实没有舍弃，只是以后不在检查这个元素了）
// 		}
// 	}
// 	return left;
// } 太复杂了
// 标准格式，lower_bound是conde = [&](int val){return val >= key;}
// upper_bound是conde = [&](int val){return val > key;}
// binary_search是conde = [&](int val){return val >= key;} 且 left < n && vec[left] == key

template <typename Cond>
int find_first(const vector<int> &vec, Cond cond) {
	int left = 0, right = vec.size(); // 左闭右开
	while(left < right) {
		int mid = left + (right - left) / 2;
		// 左边都是 false，右边都是 true
		if(cond(vec[mid])) {
			// 额外判断是不是第一个满足条件的
			if(mid == 0 || !cond(vec[mid - 1])) {
				return mid; // 如果是直接返回
			} else {
				right = mid; // 如果不是，放心去掉mid
			}
		} else {
			// 标准的二分查找
			left = mid + 1;
		}
	}
	return left;
} // 返回第一个使得 cond条件为真的元素的下标, 分界线左边不满足，右边均满足，左闭右开写法

template <typename RandomIt, typename Conditon>
RandomIt my_find_first(RandomIt first, RandomIt last, Conditon cond) {
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
// binary_search是conde = [&](RandomIt::value_type val){return val >= key;} 且 first != end &&
// *first == key 更好的写法应该是 std::iterator_traits<RandomIt>::value_type，因为 RandomIt
// 可能是原生指针

int main() {
	vector<int> vec = { 0, 2, 4, 6, 8, 10 };
	int key = 5;
	cout << "left close right close " << binarySearch(vec, key) << endl;
	cout << "lower_bound STL " << lower_bound(vec.begin(), vec.end(), key) - vec.begin() << endl;
	cout << "lower_bound " << lower_bound(vec, key) << endl;
	auto cond = [&](int val) {
		return val >= key;
	};
	cout << "find_first " << find_first(vec, cond) << endl;
	key = 4;
	cout << "left close right close " << binarySearch(vec, key) << endl;
	cout << "lower_bound STL " << lower_bound(vec.begin(), vec.end(), key) - vec.begin() << endl;
	cout << "lower_bound " << lower_bound(vec, key) << endl;
	cout << "find_first " << find_first(vec, cond) << endl;
}