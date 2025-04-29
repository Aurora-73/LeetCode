#ifndef MY_TreeNode
#define MY_TreeNode

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/**
 * 根据层序数组创建二叉树（-1 表示空节点）
 * @param values 整数数组
 * @return 树的根节点
 */
TreeNode *createTree(const std::vector<int> &values) {
	if(values.empty() || values[0] == -1)
		return nullptr;

	TreeNode *root = new TreeNode(values[0]);
	std::queue<TreeNode *> q;
	q.push(root);

	size_t i = 1;
	while(i < values.size()) {
		TreeNode *current = q.front();
		q.pop();

		// 左子节点
		if(i < values.size() && values[i] != -1) {
			current->left = new TreeNode(values[i]);
			q.push(current->left);
		}
		++i;

		// 右子节点
		if(i < values.size() && values[i] != -1) {
			current->right = new TreeNode(values[i]);
			q.push(current->right);
		}
		++i;
	}

	return root;
}

/**
 * 输出二叉树（层序遍历）
 * @param os 输出流
 * @param root 根节点
 */
void printTreeFancy(TreeNode *node, std::ostream &os, const std::string &prefix, bool isLeft, const std::string &tag) {
	if(!node) {
		os << prefix << (isLeft ? "└── " : "├── ") << "n " << tag << std::endl;
		return;
	}

	os << prefix << (isLeft ? "└── " : "├── ") << node->val << " " << tag << std::endl;

	bool hasLeft = node->left != nullptr;
	bool hasRight = node->right != nullptr;

	std::string newPrefix = prefix + (isLeft ? "    " : "│   ");

	if(hasLeft || hasRight) {
		printTreeFancy(node->left, os, newPrefix, false, " l");
		printTreeFancy(node->right, os, newPrefix, true, " r");
	}
}

// 重载 << 运算符，打印带 l/r 标签的树
std::ostream &operator<<(std::ostream &os, TreeNode *root) {
	if(!root) {
		os << "null root" << std::endl;
	} else {
		os << root->val << "  root" << std::endl;
		printTreeFancy(root->left, os, "", false, " l");
		printTreeFancy(root->right, os, "", true, " r");
	}
	return os;
}

/**
 * 释放二叉树内存
 * @param root 根节点
 */
void deleteTree(TreeNode *root) {
	if(!root)
		return;
	deleteTree(root->left);
	deleteTree(root->right);
	delete root;
}

#endif // MY_TreeNode
