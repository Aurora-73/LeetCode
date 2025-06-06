// Created: 2025-05-17
#include "MyUtils.hpp"
using namespace std;

/*常见的排序算法*/

void insertSort(vector<int> &vec) {
	int n = vec.size();
	for(int i = 1; i < n; ++i) {
		int temp = vec[i];
		int j = i;
		while(j > 0 && vec[j - 1] > temp) {
			vec[j] = vec[j - 1];
			--j;
		}
		vec[j] = temp;
	}
}

template <typename BidirectionalIterator>
void insertSort(BidirectionalIterator begin, BidirectionalIterator end) {
	using ValueType = typename std::iterator_traits<BidirectionalIterator>::value_type;

	for(auto it = begin; it != end; ++it) {
		ValueType temp = std::move(*it);
		auto insertPos = it;

		while(insertPos != begin && *(std::prev(insertPos)) > temp) {
			*insertPos = std::move(*(std::prev(insertPos)));
			--insertPos;
		}

		*insertPos = std::move(temp);
	}
}

void selectSort(vector<int> &vec) {
	int n = vec.size();
	for(int i = 0; i < n; ++i) {
		int min_index = i;
		for(int j = i + 1; j < n; ++j) {
			if(vec[j] < vec[min_index]) {
				min_index = j;
			}
		}
		std::swap(vec[i], vec[min_index]);
	}
}

template <typename ForwardIterator>
void selectSort(ForwardIterator begin, ForwardIterator end) {
	for(auto it1 = begin; it1 != end; ++it1) {
		ForwardIterator min = it1;
		for(auto it2 = std::next(it1); it2 != end; ++it2) {
			if(*it2 < *min) {
				min = it2;
			}
		}
		if(min != it1) {
			std::swap(*it1, *min);
		}
	}
}

// QuickSort
class QuickSort1 {
public:
	void operator()(vector<int> &vec) {
		_quickSort(vec, 0, int(vec.size()) - 1);
	}

private:
	void _quickSort(vector<int> &vec, int left, int right) {
		if(left >= right) return;
		int pivotPos = partition(vec, left, right);
		_quickSort(vec, left, pivotPos - 1);
		_quickSort(vec, pivotPos + 1, right);
	}

	int partition(vector<int> &vec, int left, int right) {
		std::swap(vec[left], vec[left + rand() % (right - left + 1)]);
		int pivot = vec[left];
		while(left < right) {
			while(left < right && vec[right] >= pivot) --right;
			vec[left] = vec[right];
			while(left < right && vec[left] <= pivot) ++left;
			vec[right] = vec[left];
		}
		vec[left] = pivot;
		return left;
	}
};

template <typename RandomAccessIterator>
class QuickSort {
public:
	void operator()(RandomAccessIterator begin, RandomAccessIterator end) {
		if(end - begin <= 1) return;
		auto pivotPos = partition(begin, end);
		(*this)(begin, pivotPos);   // 左闭右开
		(*this)(pivotPos + 1, end); // 左闭右开
	}

private:
	RandomAccessIterator partition(RandomAccessIterator left, RandomAccessIterator right) {
		size_t ra = rand() % (right - left);
		std::swap(*left, *(left + ra));
		auto pivot = std::move(*left);
		--right;
		while(left < right) {
			while(left < right && *right >= pivot) --right;
			*left = std::move(*right);
			while(left < right && *left <= pivot) ++left;
			*right = std::move(*left);
		}
		*left = std::move(pivot);
		return left;
	}
};

template <typename RandomIt>
void quickSort(RandomIt first, RandomIt last) {
	auto len = std::distance(first, last);
	if(len <= 1) return;

	// 随机选一个枢轴，放到 first
	static thread_local std::mt19937_64 eng { std::random_device {}() };
	std::uniform_int_distribution<decltype(len)> dist(0, len - 1);
	RandomIt pivotIt = std::next(first, dist(eng));
	std::iter_swap(first, pivotIt);

	using Value_Type = typename std::iterator_traits<RandomIt>::value_type;
	Value_Type pivot = *first;

	// left、right 两头扫描
	RandomIt left = first, right = std::prev(last);

	while(left < right) {

		while(left < right && *right >= pivot) --right;
		*left = std::move(*right);

		while(left < right && *left <= pivot) ++left;
		*right = std::move(*left);
	}

	*left = std::move(pivot);

	quickSort(first, left);           // 左闭右开
	quickSort(std::next(left), last); // 左闭右开
}

// HeapSort

// MergeSort

int main() {
	vector<int> t = {};
	QuickSort1()(t);
	vector<int> vec { 1, 4, 2, 7, 3, 5, 0 };
	// selectSort(vec.begin(), vec.end());
	QuickSort<vector<int>::iterator>()(vec.begin(), vec.end());
	cout << vec << endl;
	int aaa[] = { 1, 4, 2, 7, 3, 5, 0 };
	selectSort(aaa, aaa + 7);
	for(auto &a : aaa) {
		cout << a << " ";
	}
	cout << endl;
}