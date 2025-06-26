// MyTreeNode.cpp
#include "MyTreeNode.h"

using namespace std;

TreeNode *createTree(const std::vector<int> &values) {
	if(values.empty() || values[0] == EMPTY_NODE) return nullptr;

	TreeNode *root = new TreeNode(values[0]);
	std::queue<TreeNode *> q;
	q.push(root);

	size_t i = 1;
	while(i < values.size()) {
		TreeNode *current = q.front();
		q.pop();

		// 左子节点
		if(i < values.size() && values[i] != EMPTY_NODE) {
			current->left = new TreeNode(values[i]);
			q.push(current->left);
		}
		++i;

		// 右子节点
		if(i < values.size() && values[i] != EMPTY_NODE) {
			current->right = new TreeNode(values[i]);
			q.push(current->right);
		}
		++i;
	}

	return root;
}

void printTreeFancy(TreeNode *node,
    std::ostream &os,
    const std::string &prefix,
    bool isLeft,
    const std::string &tag) {
	if(!node) {
		os << prefix << (isLeft ? "└── " : "├── ") << "null " << tag << std::endl;
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

void deleteTree(TreeNode *root) {
	if(!root) return;
	deleteTree(root->left);
	deleteTree(root->right);
	delete root;
}