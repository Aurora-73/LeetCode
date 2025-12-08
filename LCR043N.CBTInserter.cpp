// Created: 2025-12-08
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 完全二叉树是每一层（除最后一层外）都是完全填充（即，节点数达到最大，
第 n 层有 2n-1个节点）的，并且所有的节点都尽可能地集中在左侧。
设计一个用完全二叉树初始化的数据结构CBTInserter，它支持以下几种操作：
	CBTInserter(TreeNode root)使用根节点为root的给定树初始化该数据结构；
	CBTInserter.insert(int v) 向树中插入一个新节点，
节点类型为 TreeNode，值为 v。使树保持完全二叉树的状态，并返回插入的新节点的父节点的值；
	CBTInserter.get_root() 将返回树的根节点。
示例 1：
	输入：inputs = {"CBTInserter","insert","get_root"}, inputs = {{{1}},{2},{}}
	输出：{null,1,{1,2}}
示例 2：
	输入：inputs = {"CBTInserter","insert","insert","get_root"}, inputs = {{{1,2,3,4,5,6}},{7},{8},{}}
	输出：{null,3,4,{1,2,3,4,5,6,7,8}}
提示：
	最初给定的树是完全二叉树，且包含1到1000个节点。
	每个测试用例最多调用CBTInserter.insert 操作10000次。
	给定节点或插入节点的每个值都在0到5000之间。 */

class CBTInserter {
public:
	CBTInserter(TreeNode *r) : root { r } {
		que.push(root);
		while(!que.empty()) {
			p = que.front();
			que.pop();
			if(p->left) {
				que.push(p->left);
			} else {
				isLeft = true;
				return;
			}
			if(p->right) {
				que.push(p->right);
			} else {
				isLeft = false;
				return;
			}
		}
	}

	int insert(int v) {
		int res = p->val;
		auto newNode = new TreeNode(v);
		if(isLeft) {
			p->left = newNode;
		} else {
			p->right = newNode;
			p = que.front();
			que.pop();
		}
		isLeft = !isLeft;
		que.push(newNode);
		return res;
	}

	TreeNode *get_root() {
		return root;
	}

private:
	queue<TreeNode *> que;
	TreeNode *root, *p;
	bool isLeft = true;
}; // 思路类似于BFS，维护一个队列，当遇到第一个可以插入的值的时候停止BFS，需要注意insert不是正常的继续BFS

class CBTInserter1 {
public:
	CBTInserter1(TreeNode *root_) : root(root_) {
		if(!root) return; // 若不需要处理 nullptr，这行可去掉

		std::queue<TreeNode *> q;
		q.push(root);
		while(!q.empty()) {
			TreeNode *node = q.front();
			q.pop();
			// 如果 node 少于两个孩子，把它加入候选队列
			if(!(node->left && node->right)) {
				candidates.push(node);
			}
			if(node->left) q.push(node->left);
			if(node->right) q.push(node->right);
		}
	}

	int insert(int v) {
		TreeNode *newNode = new TreeNode(v);
		TreeNode *parent = candidates.front();
		if(!parent->left) {
			parent->left = newNode;
		} else {
			parent->right = newNode;
			// 父节点已满，从候选队列移除
			candidates.pop();
		}
		// 新节点可能成为未来的父节点（目前没有孩子）
		candidates.push(newNode);
		return parent->val;
	}

	TreeNode *get_root() const {
		return root;
	}

private:
	TreeNode *root = nullptr;
	std::queue<TreeNode *> candidates;
}; //候选父节点队列，保存所有 孩子数 < 2 的节点，每次插入时从队列顶端找出待插入位置的父节点值

int main() {
	auto root = createTree({ 1 });
	CBTInserter cbt(root);
	cbt.insert(2);
	cbt.insert(3);
	cout << root << endl;
}