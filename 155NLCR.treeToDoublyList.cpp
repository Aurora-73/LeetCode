// Created: 2025-06-28
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 155. 将二叉搜索树转化为排序的双向链表
将一个 二叉搜索树 就地转化为一个 已排序的双向循环链表。
对于双向循环列表，你可以将左右孩子指针作为双向循环链表的前驱和后继指针，
第一个节点的前驱是最后一个节点，最后一个节点的后继是第一个节点。
特别地，我们希望可以 就地 完成转换操作。当转化完成以后，树中节点的左指针需要指向前驱，
树中节点的右指针需要指向后继。还需要返回链表中最小元素的指针。
示例 1：
	输入：root = {4,2,5,1,3} 
	输出：{1,2,3,4,5}
	解释：下图显示了转化后的二叉搜索树，实线表示后继关系，虚线表示前驱关系。
示例 2：
	输入：root = {2,1,3}
	输出：{1,2,3}
示例 3：
	输入：root = {}
	输出：{}
	解释：输入是空树，所以输出也是空链表。
示例 4：
	输入：root = {1}
	输出：{1}
提示：
	-1000 <= Node.val <= 1000
	Node.left.val < Node.val < Node.right.val
	Node.val 的所有值都是独一无二的
	0 <= Number of Nodes <= 2000 */

typedef TreeNode Node;

class Solution {
public:
	Node *treeToDoublyList(Node *root) {
		if(!root) return root;
		Node *prev = nullptr;
		InOrder(root, prev);
		while(root->left) {
			root = root->left;
		}
		root->left = prev;
		prev->right = root;
		return root;
	}

private:
	void InOrder(Node *now, Node *&prev) {
		if(!now) return;
		InOrder(now->left, prev);
		if(prev) {
			prev->right = now;
			now->left = prev;
		}
		prev = now;
		InOrder(now->right, prev);
	}
};

void test(vector<int> treeVal) {
	Solution sol;
	Node *root;
	root = createTree(treeVal);
	root = sol.treeToDoublyList(root);
	Node *p = root;
	if(p) {
		do {
			cout << p->val << " ";
			p = p->right;
		} while(p != root);
	}
	cout << endl;
}

int main() {
	test({ 4, 2, 5, 1, 3 });
	test({ 2, 1, 3 });
	test({});
	test({ 1 });
	return 0;
}