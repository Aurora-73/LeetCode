// Created: 2025-05-13
#include "MyUtils.h"

/*按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。
n 皇后问题 研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。
给你一个整数 n ，返回所有不同的 n 皇后问题 的解决方案。
每一种解法包含一个不同的 n 皇后问题 的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。*/
// 先看 52H.totalNQueens

class Solution1 {
public:
	vector<vector<string>> solveNQueens(int n) {
		this->n = n;
		allOne = (1 << n) - 1; // 低 n 位全部置 1，用于限位
		board.assign(n, string(n, '.')); // 初始化棋盘
		res.clear();
		dfs(0, 0, 0, 0);
		return res;
	}

private:
	int n; // 棋盘大小
	int allOne; // (1<<n)-1，掩码
	vector<string> board; // 当前回溯的棋盘
	vector<vector<string>> res; // 存放所有解

	// row：当前行号
	// cols：已被占用的列
	// ld：已被主对角线（↙）占用的位置
	// rd：已被副对角线（↘）占用的位置
	void dfs(int row, int cols, int ld, int rd) {
		if(row == n) {
			res.emplace_back(board);
			return;
		}
		// 计算当前行所有可放位置的掩码
		int avail = allOne & ~(cols | ld | rd);
		while(avail) {
			// 取最低位的 1
			int p = avail & -avail;
			avail -= p;

			// 计算当前列的索引
			int colIndex = __builtin_ctz(p);

			// 放置皇后
			board[row][colIndex] = 'Q';
			// 递归到下一行
			dfs(row + 1, cols | p, (ld | p) << 1, (rd | p) >> 1);
			// 回溯
			board[row][colIndex] = '.';
		}
	}
}; // 使用位运算代替visited数组

class Solution2 {
public:
	vector<vector<string>> solveNQueens(int nn) {
		vector<vector<string>> res;
		n = nn;
		temp.resize(nn, string(nn, '.'));
		res.reserve(array<int, 9> { 1, 0, 0, 2, 10, 4, 40, 92, 352 }[nn - 1]);
		dfs(res, 0);
		return res;
	}

private:
	size_t n;
	bitset<17> line, right, left = 0;
	vector<string> temp;
	// 分别表示该列，右侧斜线，左侧斜线是否有元素
	void dfs(vector<vector<string>> &res, size_t i) {
		if(i == n) {
			res.emplace_back(temp);
			return;
		}
		for(size_t j = 0; j < n; j++) {
			size_t l = i + j, r = n - 1 + i - j;
			if(!line[j] && !right[r] && !left[l]) { // 不能用是否为 Q 代替line，因为line是一整列，如果代替需要逐个比较
				temp[i][j] = 'Q';
				line.set(j), left.set(l), right.set(r);
				dfs(res, i + 1);
				temp[i][j] = '.';
				line.reset(j), left.reset(l), right.reset(r);
			}
		}
	}
}; // 使用bitset

/*为什么 return std::move(res); 会阻止 NRVO？
当你写成：
return std::move(res);
你明确把本该做「就地构造」的对象当作一个要被“移动”（move）的临时对象来处理了。根据 C++ 标准和大多数编译器的实现细节：
NRVO 只发生在直接 return 局部变量名; 的情况下，而且这个局部变量必须是函数内定义的、未被当作其它用途（例如别名逃逸）使用的“命名返回值”。
一旦你把它包裹进 std::move(...)，编译器就认为你要做一次显式的“移动构造”操作，而不再把它当作会被就地构造的特殊情况。
因此，NRVO 路径被“跳过”，编译器要么做一次标准的移动构造（但往往也能优化掉拷贝，但不是 NRVO），要么最坏退回到拷贝构造（如果类型不可移动）。
换句话说，std::move 在这里告诉编译器：“我不需要你帮我就地构造，给我把这个变量当作右值去移动吧”，从而破坏了编译器识别「这个局部变量可以直接当作返回值就地构造」的机会。
什么是 NRVO（命名返回值优化）？
背景
在 C++ 早期，函数返回一个大对象时，通常要经历一次拷贝构造：
在被调用函数中，先在自己的栈上构造一个局部对象 A；
return A; 时把 A 拷贝到一个临时对象；
调用者再把这个临时对象拷贝到接收对象上；
最后临时对象析构、A 析构。
这会产生至少一次甚至两次拷贝，效率很低。
RVO 与 NRVO
RVO（Return Value Optimization）：当你直接 return MyType{...};（返回一个临时对象字面量）时，编译器可以把那个临时对象直接构造到调用者的目标内存上，省去任何拷贝。
NRVO（Named RVO）：当你 return var;，而 var 是一个在函数里命名的局部变量，且符合一系列限制（只有一个返回点、生命周期未逃逸等），编译器同样可以把 var 就地构造到调用者的空间。
这两种优化在实践中合称为“返回值优化”（RVO/NRVO）。
优化效果
零拷贝：返回对象时不再产生额外的拷贝／移动构造调用。
更少分配：如果对象内部有动态分配（如 std::vector），就地构造也可以减少一次内部缓冲区的重新分配。
更高性能：大对象、多次调用场景下性能提升明显。
何时会失效
以下写法会阻止编译器应用 NRVO：
使用 std::move 或 static_cast<MyType&&> 强制把返回值当右值。
返回成员变量或全局变量（NRVO 只对局部变量生效）。
函数有多个不同的 return var; 分支，并且编译器不确定哪一个能统一优化。
返回的局部变量在返回前“逃逸”出函数作用域（例如把地址 &var 存到了别处），编译器就不能保证安全就地构造。*/

int main() {
	Solution1 sol1;
	Solution2 sol2;
}