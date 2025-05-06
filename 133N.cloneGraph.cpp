// Created: 2025-05-05
#include "MyUtils.h"

/*133. 克隆图
给你无向 连通 图中一个节点的引用，请你返回该图的 深拷贝（克隆）。
图中的每个节点都包含它的值 val（int） 和其邻居的列表（list[Node]）。
class Node {
    public int val;
    public List<Node> neighbors;
}*/

class Node {
public:
	int val;
	vector<Node *> neighbors;
	Node() {
		val = 0;
		neighbors = vector<Node *>();
	}
	Node(int _val) {
		val = _val;
		neighbors = vector<Node *>();
	}
	Node(int _val, vector<Node *> _neighbors) {
		val = _val;
		neighbors = _neighbors;
	}
};

class Solution1 {
public:
	Node *cloneGraph(Node *node) {
		old2new.clear();
		return dfs(node);
	}
	Node *dfs(Node *node) {
		if(!node) {
			return node;
		}
		auto it = old2new.find(node);
		if(it == old2new.end()) {
			Node *newNode = new Node(node->val, {});
			old2new[node] = newNode;
			for(auto &oldNeighbor : node->neighbors) {
				newNode->neighbors.push_back(dfs(oldNeighbor));
			}
			return newNode;
		} else {
			return it->second;
		}
	}

private:
	unordered_map<Node *, Node *> old2new;
};

class Solution2 {
public:
	Node *cloneGraph(Node *node) {
		if(!node)
			return nullptr;
		unordered_map<Node *, Node *> mp;
		queue<Node *> q;
		// 克隆起始节点，并入队
		mp[node] = new Node(node->val);
		q.push(node);
		// BFS 克隆整个图
		while(!q.empty()) {
			Node *cur = q.front();
			q.pop();
			for(Node *nei : cur->neighbors) {
				auto it = mp.find(nei);
				if(it == mp.end()) {
					auto newNode = new Node(nei->val);
					it = mp.emplace(nei, newNode).first; // emplace 返回 pair<iterator,bool>
					q.push(nei);
				}
				mp[cur]->neighbors.push_back(it->second);
			}
		}
		return mp[node];
	}
};

int main() {
	Solution1 sol1;
	Solution2 sol2;
}