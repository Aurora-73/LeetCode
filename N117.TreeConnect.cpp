// Created: 2025-04-30
#include "MyUtils.h"

/*117. 填充每个节点的下一个右侧节点指针 II
给定一个二叉树：
填充它的每个 next 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next 指针设置为 NULL 。
初始状态下，所有 next 指针都被设置为 NULL 。*/
struct Node {
	int val;
	Node *left;
	Node *right;
	Node *next;
};

class Solution1 {
public:
	Node *connect(Node *root) {
		if(!root)
			return root;
		queue<Node *> q;
		Node *prev = nullptr;
		q.push(root);
		int nowlevel = 1, nextlevel = 0, count = 0;
		while(!q.empty()) {
			Node *now = q.front();
			q.pop();
			if(now->left) {
				q.push(now->left);
				nextlevel++;
			}
			if(now->right) {
				q.push(now->right);
				nextlevel++;
			}
			if(prev) {
				prev->next = now;
			}
			prev = now;
			count++;
			if(count == nowlevel) {
				nowlevel = nextlevel;
				nextlevel = 0; // 不要忘记重置
				count = 0;
				prev = nullptr;
			}
		}
		return root;
	}
};

class Solution2 {
public:
	Node *connect(Node *root) {
		if(!root)
			return root;
		queue<Node *> q;
		q.push(root);
		while(!q.empty()) {
			int levelSize = q.size();
			Node *prev = nullptr;
			for(int i = 0; i < levelSize; ++i) {
				Node *now = q.front();
				q.pop();
				if(now->left)
					q.push(now->left);
				if(now->right)
					q.push(now->right);
				if(prev)
					prev->next = now;
				prev = now;
			} // 每次处理一整层的，这样可以直接用 q.size() 获取本层节点数
		}
		return root;
	}
};

class Solution {
public:
	Node *connect(Node *root) {
		Node *LevelBegin = root;
		while(LevelBegin) {
			Node *now = LevelBegin, *prev = nullptr;
			LevelBegin = nullptr;
			while(now) {
				if(now->left) {
					if(prev) {
						prev->next = now->left;
					}
					prev = now->left;
					if(!LevelBegin) {
						LevelBegin = now->left;
					}
				}
				if(now->right) {
					if(prev) {
						prev->next = now->right;
					}
					prev = now->right;
					if(!LevelBegin) {
						LevelBegin = now->right;
					}
				}
				now = now->next;
			}
		}
		return root;
	}
}; // 每次处理当前层的下一层，由于当前层已经在之前处理过了，因此可以直接使用next在本层之间跳转

int main() {}