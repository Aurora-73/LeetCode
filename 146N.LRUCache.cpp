#include "MyUtils.hpp"
/* 146. LRU 缓存
请你设计并实现一个满足 LRU (最近最少使用) 缓存 约束的数据结构。
实现 LRUCache 类：
	LRUCache(int capacity) 以 正整数 作为容量capacity 初始化 LRU 缓存
	int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1。
	void put(int key, int value)如果关键字key 已经存在，则变更其数据值value ；如果不存在，
则向缓存中插入该组key-value。如果插入操作导致关键字数量超过capacity，则应该 逐出 最久未使用的关键字。
函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。
示例：
	输入
	{"LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"}
	{{2}, {1, 1}, {2, 2}, {1}, {3, 3}, {2}, {4, 4}, {1}, {3}, {4}}
	输出
	{null, null, null, 1, null, -1, null, -1, 3, 4}
	解释
	LRUCache lRUCache = new LRUCache(2);
	lRUCache.put(1, 1); // 缓存是 {1=1}
	lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
	lRUCache.get(1);    // 返回 1
	lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
	lRUCache.get(2);    // 返回 -1 (未找到)
	lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
	lRUCache.get(1);    // 返回 -1 (未找到)
	lRUCache.get(3);    // 返回 3
	lRUCache.get(4);    // 返回 4
提示：
	1 <= capacity <= 3000
	0 <= key <= 10000
	0 <= value <= 10^5
	最多调用 2 * 10^5 次 get 和 put*/

struct MyListNode {
	int key;
	MyListNode *next;
	MyListNode *pre;
	MyListNode() {
		key = 0;
		next = nullptr;
		pre = nullptr;
	}
};

class LRUCache1 {
public:
	LRUCache1(int cap) : capacity(cap), head(new MyListNode()), tail(new MyListNode()) {
		tail->pre = head;
		head->next = tail;
	}

	int get(int key) {
		auto find = map.find(key);
		if(find == map.end()) {
			return -1;
		} else {
			moveToFirst(find->second.second);
			return find->second.first;
		}
	}

	void put(int key, int value) {
		auto find = map.find(key);
		if(find != map.end()) {
			find->second.first = value;
			moveToFirst(find->second.second);
			return;
		}
		MyListNode *now;
		if(map.size() < capacity) {
			now = new MyListNode();
		} else {
			now = tail->pre;
			map.erase(now->key);
		}
		now->key = key;
		map.insert(make_pair(key, make_pair(value, now)));
		moveToFirst(now);
	}

private:
	size_t capacity;
	unordered_map<int, pair<int, MyListNode *>> map; // key - (value, node)
	MyListNode *head, *tail;
	void moveToFirst(MyListNode *node) {
		if(node->pre == head) return;
		if(node->pre != nullptr) {
			node->pre->next = node->next;
		}
		if(node->next != nullptr) {
			node->next->pre = node->pre;
		}
		node->next = head->next;
		node->pre = head;
		node->next->pre = node;
		head->next = node;
	}
	~LRUCache1() {
		tail = head->next;
		while(tail) {
			delete head;
			head = tail;
			tail = tail->next;
		}
		delete head;
	}
};
// 因为需要 O(1) 级别的查找，所以需要哈希表
// 因为需要 O(1) 级别的删除，所以需要xx优先队列xx，
// 不能用优先队列，因为访问元素后要修改访问时间，优先队列只能在插入和删除时保持有序，修改无法保持
// 记录当前步数，优先队列步数最小的在最上面
// 记录最大容量，容量过大则删除

struct UDListNode {
	int key, value;
	UDListNode *prev;
	unique_ptr<UDListNode> next;
	UDListNode(int k = 0, int v = 0) : key(k), value(v), prev(nullptr), next(nullptr) { }
};

class LRUCache2 {
private:
	size_t capacity;
	unordered_map<int, UDListNode *> map;

	unique_ptr<UDListNode> head; // dummy head
	UDListNode *tail;            // dummy tail (裸指针，只接链)

public:
	LRUCache2(int cap) : capacity(cap) {
		head = make_unique<UDListNode>();
		auto tailNode = new UDListNode();
		tail = tailNode;

		head->next.reset(tail);
		tail->prev = head.get();
	}

	~LRUCache2() = default;

	void moveToFront(UDListNode *node) {
		// 从当前位置摘除（它的 prev 和 next 必须都在）
		UDListNode *prevNode = node->prev;
		unique_ptr<UDListNode> moving = std::move(prevNode->next);
		prevNode->next = std::move(moving->next);
		if(prevNode->next) {
			prevNode->next->prev = prevNode;
		}

		// 插入到 head 后面
		moving->next = std::move(head->next);
		if(moving->next) {
			moving->next->prev = moving.get();
		}
		moving->prev = head.get();
		head->next = std::move(moving);
	}

	void removeTail() {
		UDListNode *oldTail = tail->prev;
		UDListNode *prev = oldTail->prev;
		map.erase(oldTail->key);

		prev->next = std::move(oldTail->next); // move 掉 oldTail（原来指向 tail）
		tail->prev = prev;
	}

	int get(int key) {
		auto it = map.find(key);
		if(it == map.end()) return -1;
		moveToFront(it->second);
		return it->second->value;
	}

	void put(int key, int value) {
		auto it = map.find(key);
		if(it != map.end()) {
			it->second->value = value;
			moveToFront(it->second);
			return;
		}

		if(map.size() >= capacity) {
			removeTail();
		}

		auto newNode = make_unique<UDListNode>(key, value);
		newNode->next = std::move(head->next);
		if(newNode->next) {
			newNode->next->prev = newNode.get();
		}
		newNode->prev = head.get();
		map[key] = newNode.get();
		head->next = std::move(newNode);
	}
};

class LRUCache {
public:
	LRUCache(int cap) {
		root = new ListNode;
		tile = root;
		capacity = cap;
		mp.reserve(10000);
	}

	int get(int key) {
		auto it = mp.find(key);
		if(it == mp.end()) return -1;
		ListNode *p = it->second;
		moveToBack(p);
		return p->value;
	}

	void put(int key, int value) {
		auto it = mp.find(key);
		if(it == mp.end()) {
			tile->next = new ListNode;
			tile->next->prev = tile;
			tile = tile->next;
			tile->key = key;
			tile->value = value;
			mp[key] = tile;
			if(mp.size() > capacity) {
				auto delNode = root->next;
				mp.erase(delNode->key);
				delNode->next->prev = delNode->prev;
				delNode->prev->next = delNode->next;
				delete delNode;
			} // capacity >= 1，所以tile不为delNode
		} else {
			it->second->value = value;
			moveToBack(it->second);
		}
	}

private:
	struct ListNode {
		ListNode *next = nullptr, *prev = nullptr;
		int key, value;
	};
	int capacity;
	ListNode *root, *tile; // 最后访问的放在最后面
	unordered_map<int, ListNode *> mp;
	void moveToBack(ListNode *p) {
		if(p != tile) {
			p->next->prev = p->prev;
			p->prev->next = p->next;
			tile->next = p;
			p->prev = tile;
			p->next = nullptr;
			tile = p;
		}
	}
};

int main() {
	LRUCache lru(2);
	lru.put(1, 1);
	lru.put(2, 2);
	cout << lru.get(1) << endl;
	lru.put(3, 3);
	cout << lru.get(2) << endl;
	lru.put(4, 4);
	cout << lru.get(1) << endl;
	cout << lru.get(3) << endl;
	cout << lru.get(4) << endl;

	int cap;
	cout << "请输入缓存容量：";
	cin >> cap;
	LRUCache cache(cap);

	cout << "操作说明：" << endl;
	cout << "1 key         表示 get(key)" << endl;
	cout << "2 key value   表示 put(key, value)" << endl;
	cout << "0             表示退出" << endl;

	int op;
	while(true) {
		cout << "> ";
		cin >> op;
		if(op == 0) break;
		if(op == 1) {
			int key;
			cin >> key;
			int val = cache.get(key);
			cout << "get(" << key << ") = " << val << endl;
		} else if(op == 2) {
			int key, value;
			cin >> key >> value;
			cache.put(key, value);
			cout << "put(" << key << ", " << value << ")" << endl;
		} else {
			cout << "未知操作类型！请输入 0 / 1 / 2" << endl;
		}
	}
	return 0;
}
