// Created: 2025-05-17
#include "MyUtils.hpp"
using namespace std;

/* 快速排序的不同写法 */

/* 单路（Lomuto）：用一个指针 i 维护 < pivot 的区间，遍历 j，最后把枢轴交换到 i。能确定枢轴最终位置（返回的索引就是枢轴位置）。实现简单但对大量重复元素或已排序序列容易退化，通常配合随机化枢轴避免最坏情况。

双路（Hoare）：用两个指针从两端向中间扫描并交换。不一定把枢轴放到它最终位置（返回的是划分点 j，但枢轴可能还在任一侧）。对元素分布更健壮（尤其是元素较少重复时），交换次数通常少于 Lomuto。

三路（Dutch / Dijkstra）：把数组分成 < pivot、== pivot、> pivot 三段（lt、i、gt 指针）。把所有等于枢轴的元素都聚到中间，返回一个范围 [lt, gt]，适合重复元素多的情况，能显著降低递归深度和比较次数。 */

std::mt19937 rng((unsigned)chrono::high_resolution_clock::now().time_since_epoch().count());

// 单路（Lomuto 分区）: 实现最简单，能确定枢轴最终位置。
int lomuto_partition(vector<int> &nums, int l, int r) {
	// 随机化枢轴：把一个随机元素放到 r
	uniform_int_distribution<int> dist(l, r);
	swap(nums[dist(rng)], nums[r]);

	int pivot = nums[r];
	int i = l; // nums[l..i-1] < pivot
	for(int j = l; j < r; ++j) {
		if(nums[j] < pivot) {
			swap(nums[i], nums[j]);
			++i;
		}
	}
	swap(nums[i], nums[r]); // 把枢轴放到 i，i 是枢轴的最终位置
	return i;
}

void quicksort_lomuto(vector<int> &nums, int l, int r) {
	if(l >= r) return;
	int p = lomuto_partition(nums, l, r);
	quicksort_lomuto(nums, l, p - 1);
	quicksort_lomuto(nums, p + 1, r);
}

// 双路（Hoare 分区）：两个指针向中间走，交换不符合两侧条件的元素；不保证枢轴在返回索引位置，但通常更少交换。
int hoare_partition(vector<int> &nums, int l, int r) {
	uniform_int_distribution<int> dist(l, r);
	int pivot = nums[dist(rng)];
	int i = l - 1;
	int j = r + 1;
	while(true) {
		do {
			++i;
		} while(nums[i] < pivot);
		do {
			--j;
		} while(nums[j] > pivot);
		if(i >= j) return j; // 返回 j 作为划分点（注意：枢轴不一定在 j）
		swap(nums[i], nums[j]);
	}
}

void quicksort_hoare(vector<int> &nums, int l, int r) {
	if(l >= r) return;
	int p = hoare_partition(nums, l, r);
	// 注意使用 p 而不是 p-1 / p+1 的细节（递归区间选择）
	quicksort_hoare(nums, l, p);
	quicksort_hoare(nums, p + 1, r);
}

// 双路（挖坑填数）：通过“覆盖赋值”在数组里来回填坑，最终 pivot 被放回某个确定的位置并返回。
int digPit_partition(vector<int> &nums, int l, int r) {
	uniform_int_distribution<int> dist(l, r);
	int p = dist(rng);
	swap(nums[l], nums[p]);

	int pivot = nums[l];
	int i = l, j = r;

	while(i < j) {
		while(i < j && nums[j] >= pivot) --j;
		nums[i] = nums[j];

		while(i < j && nums[i] <= pivot) ++i;
		nums[j] = nums[i];
	}

	nums[i] = pivot;
	return i;
}

void quicksort_digPit(vector<int> &nums, int l, int r) {
	if(l >= r) return;
	int p = digPit_partition(nums, l, r);
	quicksort_digPit(nums, l, p - 1);
	quicksort_digPit(nums, p + 1, r);
}

// 三路（Dutch national flag / Dijkstra）：把等于枢轴的元素集中在中间，适合重复元素多的场景；返回一个等于区间 [lt, gt]。
pair<int, int> three_way_partition(vector<int> &nums, int l, int r) {
	int pivot = nums[l]; // 也可随机化选择并 swap 到 l
	int lt = l;          // nums[l..lt-1] < pivot
	int i = l;           // nums[lt..i-1] == pivot
	int gt = r;          // nums[gt+1..r] > pivot
	while(i <= gt) {
		if(nums[i] < pivot) {
			swap(nums[lt++], nums[i++]);
		} else if(nums[i] > pivot) {
			swap(nums[i], nums[gt--]);
		} else {
			++i;
		}
	}
	return { lt, gt };
} // [  <  |lt|  =  |i|    ?     |gt| > ]

void quicksort_threeway(vector<int> &nums, int l, int r) {
	if(l >= r) return;
	auto [lt, gt] = three_way_partition(nums, l, r);
	quicksort_threeway(nums, l, lt - 1);
	quicksort_threeway(nums, gt + 1, r);
}

int main() {
	vector<int> nums;
	nums = { 5, 2, 3, 1, 2, 5, 4, 5, 0 };
	quicksort_lomuto(nums, 0, nums.size() - 1);
	cout << nums << endl;

	nums = { 5, 2, 3, 1, 2, 5, 4, 5, 0 };
	quicksort_hoare(nums, 0, nums.size() - 1);
	cout << nums << endl;

	nums = { 5, 2, 3, 1, 2, 5, 4, 5, 0 };
	quicksort_digPit(nums, 0, nums.size() - 1);
	cout << nums << endl;

	nums = { 5, 2, 3, 1, 2, 5, 4, 5, 0 };
	quicksort_threeway(nums, 0, nums.size() - 1);
	cout << nums << endl;
}