// Created: 2025-04-30
#include "MyUtils.h"
#include "MyTreeNode.h"

/*106. 从中序与后序遍历序列构造二叉树
给定两个整数数组 inorder 和 postorder ，其中 inorder 是二叉树的中序遍历， 
postorder 是同一棵树的后序遍历，请你构造并返回这颗 二叉树 。*/

class Solution1 {
public:
	TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
		if(!postorder.size())
			return nullptr;
		std::vector<int>::iterator postend = postorder.end();
		return buildTreeIter(inorder.begin(), inorder.end(), postorder.begin(), postend);
	}
	TreeNode *buildTreeIter(std::vector<int>::iterator inbegin,
	                        std::vector<int>::iterator inend,
	                        std::vector<int>::iterator postbegin,
	                        std::vector<int>::iterator &postend) {
		if(inbegin == inend) {
			return nullptr;
		}
		postend--;
		auto it = find(inbegin, inend, *postend);
		if(it == inend || *it != *postend) {
			return nullptr;
		}
		TreeNode *now = new TreeNode(*postend);
		now->right = buildTreeIter(it + 1, inend, postbegin, postend); // 不是先左后右，后序遍历根的左边是右子树
		now->left = buildTreeIter(inbegin, it, postbegin, postend);
		return now;
	}
};

class Solution2 {
public:
	TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
		if(postorder.empty())
			return nullptr;
		inorder_map.clear();

		// 建立哈希表加速查找
		for(auto it = inorder.begin(); it != inorder.end(); ++it) {
			inorder_map[*it] = it;
		}
		auto postend = postorder.end();
		return buildTreeIter(inorder.begin(), inorder.end(), postorder.begin(), postend);
	}

private:
	unordered_map<int, vector<int>::iterator> inorder_map;

	TreeNode *buildTreeIter(std::vector<int>::iterator inbegin,
	                        std::vector<int>::iterator inend,
	                        std::vector<int>::iterator postbegin,
	                        std::vector<int>::iterator &postend) {
		if(inbegin == inend) {
			return nullptr;
		}
		postend--;
		auto it = inorder_map[*postend]; // 用 map 查找代替 find()
		TreeNode *now = new TreeNode(*postend);

		now->right = buildTreeIter(it + 1, inend, postbegin, postend);
		now->left = buildTreeIter(inbegin, it, postbegin, postend);
		return now;
	}
};

// 缺少 方法二：迭代

int main() {
	Solution1 sol1;
	vector<int> inorder = {9, 3, 15, 20, 7};
	vector<int> postorder = {9, 15, 7, 20, 3};
	sol1.buildTree(inorder, postorder);
}
