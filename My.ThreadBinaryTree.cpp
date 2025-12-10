#include "MyTreeNode.h"
#include "MyUtils.hpp"
using namespace std;
// 中序线索二叉树

struct ThreadNode {
	int val;
	ThreadNode *left;
	ThreadNode *right;
	bool leftIsThread;
	bool rightIsThread;

	ThreadNode(int x) :
	    val(x), left(nullptr), right(nullptr), leftIsThread(false), rightIsThread(false) { }
};

static void buildInorderThreadsHelper(ThreadNode *cur, ThreadNode *&prev) {
	if(!cur) return;
	if(!cur->leftIsThread) buildInorderThreadsHelper(cur->left, prev);

	if(prev) {
		if(prev->right == nullptr) {
			prev->right = cur;
			prev->rightIsThread = true;
		}
	}
	if(cur->left == nullptr) {
		cur->left = prev;
		cur->leftIsThread = true;
	}

	prev = cur;
	if(!cur->rightIsThread) buildInorderThreadsHelper(cur->right, prev);
}

void buildInorderThreads(ThreadNode *root) {
	ThreadNode *prev = nullptr;
	buildInorderThreadsHelper(root, prev);
}

ThreadNode *leftmost(ThreadNode *node) {
	if(!node) return nullptr;
	while(!node->leftIsThread && node->left) node = node->left;
	return node;
}

void inorderThreadTraversal(ThreadNode *root, void (*visit)(ThreadNode *)) {
	ThreadNode *cur = leftmost(root);
	while(cur) {
		visit(cur);
		// 如果右边是线索（后继），直接跳到后继
		if(cur->rightIsThread) {
			cur = cur->right;
		} else {
			// 否则进入右子树并到达该子树的最左节点
			cur = leftmost(cur->right);
		}
	}
}

void printNode(ThreadNode *node) {
	if(node) cout << node->val << " ";
}

int main() {
	// 构造一棵普通二叉树（不含线索）
	ThreadNode *a = new ThreadNode(1);
	ThreadNode *b = new ThreadNode(2);
	ThreadNode *c = new ThreadNode(3);
	ThreadNode *d = new ThreadNode(4);
	ThreadNode *e = new ThreadNode(5);

	a->left = b;
	a->right = c;
	b->left = d;
	b->right = e;

	// 构建线索（会在空指针位置填充前驱/后继，并设置标志）
	buildInorderThreads(a);

	// 用线索做中序遍历（输出应为：4 2 5 1 3）
	inorderThreadTraversal(a, printNode);
	cout << endl;

	// 注意：此处没有实现销毁/恢复原树指针（如果需要恢复成普通二叉树，需要再写反向逻辑）
	return 0;
}