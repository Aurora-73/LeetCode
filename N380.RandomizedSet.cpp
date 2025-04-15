#include <vector>
#include <unordered_map>
#include <random>

/*
ʵ��RandomizedSet �ࣺ
RandomizedSet() ��ʼ�� RandomizedSet ����
bool insert(int val) ��Ԫ�� val ������ʱ���򼯺��в����������� true �����򣬷��� false ��
bool remove(int val) ��Ԫ�� val ����ʱ���Ӽ������Ƴ���������� true �����򣬷��� false ��
int getRandom() ����������м����е�һ�����������֤���ô˷���ʱ���������ٴ���һ��Ԫ�أ���ÿ��Ԫ��Ӧ���� ��ͬ�ĸ��� �����ء�
�����ʵ��������к�����������ÿ�������� ƽ�� ʱ�临�Ӷ�Ϊ O(1) ��
*/

class RandomizedSet {
private:
    std::vector<int> values;               // �洢Ԫ�صĶ�̬����
    std::unordered_map<int, size_t> value_to_index; // ֵ��������ӳ��
    std::mt19937 random_engine{ std::random_device{}() }; // ���������

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
    randomizedSet.insert(1); // �򼯺��в��� 1 ������ true ��ʾ 1 ���ɹ��ز��롣
    randomizedSet.remove(2); // ���� false ����ʾ�����в����� 2 ��
    randomizedSet.insert(2); // �򼯺��в��� 2 ������ true ���������ڰ��� [1,2] ��
    randomizedSet.getRandom(); // getRandom Ӧ������� 1 �� 2 ��
    randomizedSet.remove(1); // �Ӽ������Ƴ� 1 ������ true ���������ڰ��� [2] ��
    randomizedSet.insert(2); // 2 ���ڼ����У����Է��� false ��
    randomizedSet.getRandom(); // ���� 2 �Ǽ�����Ψһ�����֣�getRandom ���Ƿ��� 2 ��
}

/*
һ��ʼ��o(1)����ɾ����ֱ���뵽��ϣ��
�ؼ���ôo(1)ɾ���ڵ㣬����Ҫһ�����ݽṹ��
��������������뵽�����ݽṹ����һ�飬
�����ų�map/set(�������ӡ�ɾ��o(logn))��
list�����ɾ�������o(n)����
unordered_map/unordered_set(��ϣ��ӳ�䣬������ģ�����޷����������ȡ�ȸ���)��
priority_queue(���ȶ���ֻ��ͨ���Ѷ�top����Ԫ���޷������ȸ��ʻ�ȡԪ�أ��޷�ͨ�����������ݣ�������ô��ȡ)
��stack��queue(ͬ���ȶ���)��ʣ��vector��deque�����У�
ʹ��vector���ɣ����ֻ��push_back��ɾ����ͨ��unordered_map�ҵ�Ҫɾ���ڵ��������
��β��Ԫ�ؽ������ɡ������ȡ�ȸ���ֻ��Ҫ��rand()%v.size()���ܵȸ��ʻ�ȡ��������Ҳ�͵õ�Ԫ�ء�
*/

/*
* �ص㣺
* O(1) -> unordered ��Ϊӳ��
* random -> random_access -> ���飨ͨ�������һ��Ԫ�ؽ���ʵ��O(1)ɾ������ǿ�����Ե������ԣ���
*/