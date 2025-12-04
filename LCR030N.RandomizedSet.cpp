// Created: 2025-12-03
#include "MyUtils.hpp"
#include <random>
// #ifdef MY_UTILS_H

/* 设计一个支持在平均时间复杂度 O(1)下，执行以下操作的数据结构：
	insert(val)：当元素 val 不存在时返回 true，并向集合中插入该项，否则返回 false。
	remove(val)：当元素 val 存在时返回 true，并从集合中移除该项，否则返回 false。
	getRandom：随机返回现有集合中的一项。每个元素应该有相同的概率被返回。
示例 1：
	输入: inputs = {"RandomizedSet", "insert", "remove", "insert", "getRandom", "remove", "insert", "getRandom"}
	{{}, {1}, {2}, {2}, {}, {1}, {2}, {}}
	输出: {null, true, false, true, 2, true, false, 2}
	解释:
	RandomizedSet randomSet = new RandomizedSet();  // 初始化一个空的集合
	randomSet.insert(1); // 向集合中插入 1， 返回 true 表示 1 被成功地插入
	randomSet.remove(2); // 返回 false，表示集合中不存在 2 
	randomSet.insert(2); // 向集合中插入 2 返回 true，集合现在包含 {1,2} 
	randomSet.getRandom(); // getRandom 应随机返回 1 或 2 
	randomSet.remove(1); // 从集合中移除 1 返回 true。集合现在包含 {2} 
	randomSet.insert(2); // 2 已在集合中，所以返回 false 
	randomSet.getRandom(); // 由于 2 是集合中唯一的数字，getRandom 总是返回 2 
提示：
	-2^31<= val <= 231- 1
	最多进行 2 * 10^5 次insert， remove 和 getRandom 方法调用
	当调用getRandom 方法时，集合中至少有一个元素 */

class RandomizedSet {
public:
	/** Initialize your data structure here. */
	RandomizedSet() {
		gen.seed(rd());
	}

	/** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
	bool insert(int val) {
		auto pair = map.insert({ val, vec.size() });
		if(pair.second) {
			vec.push_back(val);
			return true;
		} else {
			return false;
		}
	}

	/** Removes a value from the set. Returns true if the set contained the specified element. */
	bool remove(int val) {
		auto it = map.find(val);
		if(it == map.end()) {
			return false;
		} else {
			vec[it->second] = vec.back();
			map[vec.back()] = it->second;
			vec.pop_back();
			map.erase(it);
			return true;
		}
	} // 删除元素就是用vector的最后一个元素替代该元素，然后将数组长度-1

	/** Get a random element from the set. */
	int getRandom() {
		std::uniform_int_distribution<size_t> dist(0, vec.size() - 1);
		return vec[dist(gen)];
	}

private:
	std::random_device rd;
	std::mt19937 gen;
	unordered_map<int, int> map;
	vector<int> vec;
};
// 因为需要O(1)时间插入删除，所以需要一个set或者map
// 因为需要获取随机元素，所以需要vector
// 使用map保存 值->下标 的映射
// 通过将数组最后一个元素赋值给指定元素的位置，然后将数组长度-1来删除元素

int main() {
	RandomizedSet rs;
	rs.insert(0);
	rs.insert(1);
	rs.remove(0);
	rs.insert(2);
	rs.remove(1);
	cout << rs.getRandom() << endl;
}