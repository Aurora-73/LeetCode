// Created: 2026-01-04
#include "MyUtils.hpp"
#include <list> // 双向链表
// #ifdef MY_UTILS_H

/* 设计和构建一个“最近最少使用”缓存，该缓存会删除最近最少使用的项目。
缓存应该从键映射到值(允许你插入和检索特定键对应的值)，并在初始化时指定最大容量。当缓存被填满时，它应该删除最近最少使用的项目。
它应该支持以下操作： 获取数据 get 和 写入数据 put。
获取数据 get(key) - 如果密钥 (key) 存在于缓存中，则获取密钥的值（总是正数），否则返回 -1。
写入数据 put(key, value) - 如果密钥不存在，则写入其数据值。如果存在，更新数据值。
当缓存容量达到上限时，它应该在写入新数据之前删除最近最少使用的数据值，从而为新的数据值留出空间。
示例：
LRUCache cache = new LRUCache( 2  );
cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // 返回  1
cache.put(3, 3);    // 该操作会使得密钥 2 作废
cache.get(2);       // 返回 -1 (未找到)
cache.put(4, 4);    // 该操作会使得密钥 1 作废
cache.get(1);       // 返回 -1 (未找到)
cache.get(3);       // 返回  3
cache.get(4);       // 返回  4 */

struct LRUListNode {
	unordered_map<int, pair<int, LRUListNode *>>::iterator iter;
	LRUListNode *next = nullptr, *prev = nullptr;
};

class LRUCache1 {
public:
	LRUCache1(int cap) : capacity(cap) {
		mapp.reserve(cap * 2); // 初始分配足够多的桶，避免rehash导致迭代器失效
	}

	int get(int key) {
		auto it = mapp.find(key);
		if(it != mapp.end()) {
			moveToBack((it->second).second);
			return (it->second).first;
		}
		return -1;
	}

	void put(int key, int value) {
		auto pa = mapp.insert({ key, { value, new LRUListNode } });
		LRUListNode *curr = pa.first->second.second;
		if(!pa.second) {
			pa.first->second.first = value; // <-- 需要更新 value
			moveToBack(curr);
			return;
		}
		curr->iter = pa.first;
		tail->next = curr;
		curr->prev = tail;
		tail = curr;
		if(mapp.size() > capacity) {
			LRUListNode *delNode = dummy.next;
			if(delNode == tail) tail = &dummy;
			mapp.erase(delNode->iter);
			if(delNode->next) delNode->next->prev = delNode->prev;
			dummy.next = delNode->next;
			delete delNode;
		}
	}

	void moveToBack(LRUListNode *curr) {
		if(curr == tail) return;
		curr->prev->next = curr->next;
		if(curr->next) curr->next->prev = curr->prev;
		tail->next = curr;
		curr->prev = tail;
		curr->next = nullptr;
		tail = curr;
	}

private:
	unordered_map<int, pair<int, LRUListNode *>> mapp;
	LRUListNode dummy, *tail = &dummy;
	int capacity;
}; // 一个map用于保存数据，一个list用于实现LRU，这两个数据结构要产生关联

class LRUCache {
private:
	unsigned capacity;
	list<pair<int, int>> LRU_list; // 双向链表：最近使用在前
	unordered_map<int, list<pair<int, int>>::iterator> mp;

	void move_to_begin(list<pair<int, int>>::iterator it) {
		if(it == LRU_list.begin()) return;
		LRU_list.splice(LRU_list.begin(), LRU_list, it);
	}

public:
	LRUCache(int capacity) : capacity(capacity) { }

	int get(int key) {
		auto it = mp.find(key);
		if(it == mp.end()) return -1;
		// 访问即更新为最近使用：移动到链表头
		move_to_begin(it->second);
		return it->second->second;
	}

	void put(int key, int value) {
		auto it = mp.find(key);
		if(it != mp.end()) {
			// key 已存在：更新 value，并移动到头部
			it->second->second = value;
			move_to_begin(it->second);
			return;
		}

		// key 不存在：如果容量满了，淘汰最久未使用（尾部）
		if(LRU_list.size() == capacity) {
			mp.erase(LRU_list.back().first);
			LRU_list.pop_back();
		}

		// 插入新节点到头部
		LRU_list.emplace_front(key, value);
		mp[key] = LRU_list.begin();
	}
}; // list作为键值对载体，map实现查找

int main() {
	LRUCache *lurc;
	vector<string> operator_list { "LRUCache",
		"put",
		"put",
		"get",
		"put",
		"get",
		"put",
		"get",
		"get",
		"get",
		"put",
		"put",
		"get",
		"put",
		"get",
		"put",
		"get",
		"get",
		"get",
		"put",
		"put",
		"get",
		"put",
		"get",
		"put",
		"get",
		"get",
		"get",
		"put",
		"put",
		"get",
		"put",
		"get",
		"put",
		"get",
		"get",
		"get",
		"put",
		"put",
		"get",
		"put",
		"get",
		"put",
		"get",
		"get",
		"get",
		"put",
		"put",
		"get",
		"put",
		"get",
		"put",
		"get",
		"get",
		"get",
		"put",
		"put",
		"get",
		"put",
		"get",
		"put",
		"get",
		"get",
		"get",
		"put",
		"put",
		"get",
		"put",
		"get",
		"put",
		"get",
		"get",
		"get",
		"put",
		"put",
		"get",
		"put",
		"get",
		"put",
		"get",
		"get",
		"get",
		"put",
		"put",
		"get",
		"put",
		"get",
		"put",
		"get",
		"get",
		"get",
		"put",
		"put",
		"get",
		"put",
		"get",
		"put",
		"get",
		"get",
		"get" };
	vector<vector<int>> data_list { { 2 },
		{ 1, 1 },
		{ 2, 2 },
		{ 1 },
		{ 3, 3 },
		{ 2 },
		{ 4, 4 },
		{ 1 },
		{ 3 },
		{ 4 },
		{ 1, 1 },
		{ 2, 2 },
		{ 1 },
		{ 3, 3 },
		{ 2 },
		{ 4, 4 },
		{ 1 },
		{ 3 },
		{ 4 },
		{ 1, 1 },
		{ 2, 2 },
		{ 1 },
		{ 3, 3 },
		{ 2 },
		{ 4, 4 },
		{ 1 },
		{ 3 },
		{ 4 },
		{ 1, 1 },
		{ 2, 2 },
		{ 1 },
		{ 3, 3 },
		{ 2 },
		{ 4, 4 },
		{ 1 },
		{ 3 },
		{ 4 },
		{ 1, 1 },
		{ 2, 2 },
		{ 1 },
		{ 3, 3 },
		{ 2 },
		{ 4, 4 },
		{ 1 },
		{ 2 },
		{ 3 },
		{ 1, 1 },
		{ 11, 2 },
		{ 1 },
		{ 32, 32 },
		{ 2 },
		{ 4, 4 },
		{ 1 },
		{ 3 },
		{ 4 },
		{ 11, 1 },
		{ 22, 2 },
		{ 11 },
		{ 31, 3 },
		{ 2 },
		{ 14, 4 },
		{ 1 },
		{ 3 },
		{ 4 },
		{ 1, 1 },
		{ 22, 2 },
		{ 1 },
		{ 31, 33 },
		{ 12 },
		{ 41, 34 },
		{ 1 },
		{ 3 },
		{ 4 },
		{ 1, 1 },
		{ 12, 22 },
		{ 1 },
		{ 3, 3 },
		{ 2 },
		{ 4, 4 },
		{ 1 },
		{ 3 },
		{ 4 },
		{ 1, 1 },
		{ 2, 2 },
		{ 1 },
		{ 3, 3 },
		{ 2 },
		{ 42, 34 },
		{ 1 },
		{ 3 },
		{ 4 },
		{ 1, 1 },
		{ 2, 2 },
		{ 11 },
		{ 3, 3 },
		{ 22 },
		{ 40, 14 },
		{ 1 },
		{ 3 },
		{ 4 } };
	vector<int> results { 0,
		0,
		0,
		1,
		0,
		-1,
		0,
		-1,
		3,
		4,
		0,
		0,
		1,
		0,
		-1,
		0,
		-1,
		3,
		4,
		0,
		0,
		1,
		0,
		-1,
		0,
		-1,
		3,
		4,
		0,
		0,
		1,
		0,
		-1,
		0,
		-1,
		3,
		4,
		0,
		0,
		1,
		0,
		-1,
		0,
		-1,
		-1,
		3,
		0,
		0,
		1,
		0,
		-1,
		0,
		-1,
		-1,
		4,
		0,
		0,
		1,
		0,
		-1,
		0,
		-1,
		-1,
		-1,
		0,
		0,
		1,
		0,
		-1,
		0,
		-1,
		-1,
		-1,
		0,
		0,
		1,
		0,
		-1,
		0,
		-1,
		3,
		4,
		0,
		0,
		1,
		0,
		-1,
		0,
		-1,
		3,
		-1,
		0,
		0,
		-1,
		0,
		-1,
		0,
		-1,
		3,
		-1 };

	assert(operator_list.size() == data_list.size());
	assert(results.size() == data_list.size());
	for(int i = 0, n = data_list.size(); i < n; ++i) {
		string &op = operator_list[i];
		if(op == "LRUCache")
			lurc = new LRUCache(data_list[i][0]);
		else if(op == "put") {
			assert(lurc != nullptr);
			lurc->put(data_list[i][0], data_list[i][1]);
		} else if(op == "get") {
			assert(lurc != nullptr);
			int ans = lurc->get(data_list[i][0]);
			if(ans != results[i]) {
				cout << "i=" << i << " expect=" << results[i] << " got=" << ans << endl;
			}
		}
	}
}