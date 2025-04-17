#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<unordered_set>
#include<set>
using namespace std;

/*11. 盛最多水的容器
给定一个长度为 n 的整数数组 height 。有 n 条垂线，第 i 条线的两个端点是 (i, 0) 和 (i, height[i]) 。
找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
返回容器可以储存的最大水量。
说明：你不能倾斜容器。*/

class Solution {
public:
    int maxArea(vector<int>& height) {
        int n = height.size();
        int i = 0, j = n - 1;
        int max = 0;
        while(i < j){
            int now = (j - i) * min(height[i], height[j]);
            max = max > now ? max : now;
            if(height[i] > height[j])   j--;
            else i++;
        }
        return max;
    }
};

class Solution1 {
public:
    int maxArea(vector<int>& height) {
        int n = height.size();
        int max = INT_MIN;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(max < min(height[i] ,height[j]) * (j - i)){
                    max = min(height[i] ,height[j]) * (j - i);
                }
            }
        }
        return max;
    }
};