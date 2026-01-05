// Created: 2025-12-25
#include "MyListNode.h"
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一棵二叉树，设计一个算法，创建含有某一深度上所有节点的链表（比如，若一棵树的深度为 D，则会创建出 D 个链表）。
返回一个包含所有深度的链表的数组。
示例：
输入：{1,2,3,4,5,null,7,8}
        1
       /  \ 
      2    3
     / \    \ 
    4   5    7
   /
  8
输出：{{1},{2,3},{4,5,7},{8}} */

class Solution {
public:
	vector<ListNode *> listOfDepth(TreeNode *tree) {
		if(!tree) return {};
		vector<ListNode *> res;
		queue<TreeNode *> que;
		que.push(tree);
		while(!que.empty()) {
			int size = que.size();
			ListNode dummy, *tail = &dummy;
			for(int k = 0; k < size; ++k) {
				TreeNode *curr = que.front();
				que.pop();
				tail->next = new ListNode(curr->val);
				tail = tail->next;
				if(curr->left) que.push(curr->left);
				if(curr->right) que.push(curr->right);
			}
			res.push_back(dummy.next);
		}
		return res;
	}
};

int main() {
	Solution sol;
	TreeNode *tree;
	tree = createTree({ 1, 2, 3, 4, 5, EMPTY_NODE, 7, 8 });
	cout << sol.listOfDepth(tree) << endl;
}