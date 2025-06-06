#include "MyUtils.hpp"

/**
 * @brief 模板化并查集（Union-Find）结构
 * 支持泛型元素，包含路径压缩与按秩合并优化。
 * @tparam T 元素类型，需支持拷贝和哈希（如 int、string 等）
 */
template <typename T>
class UnionFind {
private:
	/// 每个元素的父节点映射
	std::unordered_map<T, T> parent;
	/// 每个根节点的秩（近似树高）
	std::unordered_map<T, int> rank;

public:
	/**
		 * @brief 添加一个新元素到并查集
		 * 如果该元素已存在则无操作。
		 * @param x 要添加的元素
		 */
	void add(const T &x) {
		if(parent.find(x) == parent.end()) {
			parent[x] = x;
			rank[x] = 0;
		}
	}

	/**
		 * @brief 查找元素所在集合的根（带路径压缩）
		 * 若该元素不存在则自动加入。
		 * @param x 待查找的元素
		 * @return T 所属集合的根元素
		 */
	T find(const T &x) {
		if(parent.find(x) == parent.end()) {
			parent[x] = x;
			rank[x] = 0;
			return x;
		}
		if(parent[x] != x) parent[x] = find(parent[x]);
		return parent[x];
	}

	/**
	 * @brief 合并两个元素所在的集合（按秩合并）
	 * 自动添加未出现的元素。
	 * @param x 元素 x
	 * @param y 元素 y
	 */
	void unite(const T &x, const T &y) {
		T rootX = find(x);
		T rootY = find(y);
		if(rootX == rootY) return;

		if(rank[rootX] < rank[rootY]) {
			parent[rootX] = rootY;
		} else if(rank[rootX] > rank[rootY]) {
			parent[rootY] = rootX;
		} else {
			parent[rootY] = rootX;
			rank[rootX]++;
		}
	}

	/**
	 * @brief 判断两个元素是否属于同一个集合
	 * @param x 元素 x
	 * @param y 元素 y
	 * @return true 如果在同一个集合中
	 * @return false 否则
	 */
	bool connected(const T &x, const T &y) {
		return find(x) == find(y);
	}
};

class UnionFindSimple {
public:
	explicit UnionFindSimple(size_t s) : parent(s, -1) { }

	// 查找根（带路径压缩）
	size_t Find(size_t i) {
		if(parent[i] < 0) return i;
		return parent[i] = Find(parent[i]);
	}

	// 合并两个集合，返回新根
	size_t Union(size_t i, size_t j) {
		size_t rooti = Find(i), rootj = Find(j);
		if(rooti == rootj) return rooti;

		if(-parent[rooti] > -parent[rootj]) {
			parent[rooti] += parent[rootj];
			parent[rootj] = rooti;
			return rooti;
		} else {
			parent[rootj] += parent[rooti];
			parent[rooti] = rootj;
			return rootj;
		}
	}

	// 判断是否连通
	bool Connected(size_t i, size_t j) {
		return Find(i) == Find(j);
	}

	// 获取集合大小
	int Size(size_t i) {
		return -parent[Find(i)];
	}

private:
	std::vector<int> parent; // 负值表示集合大小，正值表示父节点索引
};

int main() {
	UnionFind<std::string> uf;

	// 添加元素（也可以在 unite 时自动添加）
	uf.add("a");
	uf.add("b");
	uf.add("c");
	uf.add("d");

	// 合并一些集合
	uf.unite("a", "b");
	uf.unite("c", "d");

	// 判断是否连通
	std::cout << std::boolalpha;
	std::cout << "a and b connected: " << uf.connected("a", "b") << "\n"; // true
	std::cout << "a and c connected: " << uf.connected("a", "c") << "\n"; // false

	// 合并更多集合
	uf.unite("b", "c");

	std::cout << "a and d connected: " << uf.connected("a", "d") << "\n"; // true

	return 0;
}
