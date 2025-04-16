#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

/*167. 两数之和 II - 输入有序数组
给你一个下标从 1 开始的整数数组 numbers ，该数组已按 非递减顺序排列  ，请你从数组中找出满足相加之和等于目标数 target 的两个数。如果设这两个数分别是 numbers[index1] 和 numbers[index2] ，则 1 <= index1 < index2 <= numbers.length 。
以长度为 2 的整数数组 [index1, index2] 的形式返回这两个整数的下标 index1 和 index2。
你可以假设每个输入 只对应唯一的答案 ，而且你 不可以 重复使用相同的元素。
你所设计的解决方案必须只使用常量级的额外空间。
*/

class Solution1 {
private:
int binarySearch(const vector<int> &vec, int key, int i, int j){
    int middle; // from i to j all_close [i, j]
    while(i <= j){
        middle = i + (j - i) / 2;
        if(key == vec[middle]){
            return middle;
        } else if (key < vec[middle]){
            j = middle - 1;
        } else {
            i = middle + 1;
        }
    }
    return -1; 
}
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int i = 0;
        for(int i = 0; i < numbers.size(); i++){
            int need_index = binarySearch(numbers, target - numbers[i], i+1, numbers.size() - 1);
            if(need_index != -1){
                return {i , need_index};
            }
        }
    }
};

class Solution2 {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
       int i = 0, j = numbers.size() - 1;
       while(true){
            if(numbers[i] + numbers[j] == target){
                return {i, j};
            }else if(numbers[i] + numbers[j] > target){
                j--;
            }else{
                i++;
            }
       }
    }
};
