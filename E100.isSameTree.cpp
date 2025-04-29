#include "MyUtils.h"
#include "MyTreeNode.h"

class Solution {
public:
	bool isSameTree(TreeNode *p, TreeNode *q) {
		if(!p && !q)
			return true;
		if(!p || !q)
			return false;
		return p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
	}
};

int main() {
	TreeNode *root = createTree({1, -1, 1, 1, 4, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13});
	cout << root << endl;
}