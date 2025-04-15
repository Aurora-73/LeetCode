#include <vector>
#include <unordered_map>
#include <random>

/*
实现RandomizedSet 类：
RandomizedSet() 初始化 RandomizedSet 对象
bool insert(int val) 当元素 val 不存在时，向集合中插入该项，并返回 true ；否则，返回 false 。
bool remove(int val) 当元素 val 存在时，从集合中移除该项，并返回 true ；否则，返回 false 。
int getRandom() 随机返回现有集合中的一项（测试用例保证调用此方法时集合中至少存在一个元素）。每个元素应该有 相同的概率 被返回。
你必须实现类的所有函数，并满足每个函数的 平均 时间复杂度为 O(1) 。
*/

class RandomizedSet {
private:
    std::vector<int> values;               // 存储元素的动态数组
    std::unordered_map<int, size_t> value_to_index; // 值到索引的映射
    std::mt19937 random_engine{ std::random_device{}() }; // 随机数引擎

public:
    RandomizedSet() = default;

    bool insert(int val) {
        if (value_to_index.find(val) != value_to_index.end())
            return false;

        value_to_index[val] = values.size();
        values.push_back(val);
        return true;
    }

    bool remove(int val) {
        auto it = value_to_index.find(val);
        if (it == value_to_index.end())
            return false;

        size_t index = it->second;
        int last_val = values.back();
        value_to_index[last_val] = index;
        values[index] = last_val;

        values.pop_back();
        value_to_index.erase(it);

        return true;
    }

    int getRandom() {
        std::uniform_int_distribution<size_t> dist(0, values.size() - 1);
        return values[dist(random_engine)];
    }
};

int main() {
    RandomizedSet randomizedSet = RandomizedSet();
    randomizedSet.insert(1); // 向集合中插入 1 。返回 true 表示 1 被成功地插入。
    randomizedSet.remove(2); // 返回 false ，表示集合中不存在 2 。
    randomizedSet.insert(2); // 向集合中插入 2 。返回 true 。集合现在包含 [1,2] 。
    randomizedSet.getRandom(); // getRandom 应随机返回 1 或 2 。
    randomizedSet.remove(1); // 从集合中移除 1 ，返回 true 。集合现在包含 [2] 。
    randomizedSet.insert(2); // 2 已在集合中，所以返回 false 。
    randomizedSet.getRandom(); // 由于 2 是集合中唯一的数字，getRandom 总是返回 2 。
}

/*
一开始看o(1)查找删除就直接想到哈希表，
关键怎么o(1)删除节点，还需要一个数据结构，
脑子里把所有能想到的数据结构过了一遍，
首先排除map/set(红黑树添加、删除o(logn))、
list（添加删除需遍历o(n)）、
unordered_map/unordered_set(哈希表映射，是无序的，因此无法做到随机获取等概率)、
priority_queue(优先队列只能通过堆顶top访问元素无法后续等概率获取元素，无法通过索引读数据，想想怎么获取)
，stack和queue(同优先队列)，剩下vector、deque，都行，
使用vector即可，添加只需push_back，删除需通过unordered_map找到要删除节点的索引，
和尾部元素交换即可。随机获取等概率只需要用rand()%v.size()就能等概率获取数组索引也就得到元素。
*/

/*
* 重点：
* O(1) -> unordered 作为映射
* random -> random_access -> 数组（通过和最后一个元素交换实现O(1)删除（不强调绝对的有序性））
*/