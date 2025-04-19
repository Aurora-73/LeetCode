#include <string>
#include <vector>
#include <unordered_set>
#include <iostream>
using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> numset(nums.begin(),nums.end());
        int max = bool(nums.size());
        for(auto i : numset){
            if(numset.count(i - 1)){
                continue;
            }else{
                int max_i = 1;
                while(numset.count(i + max_i)){
                    max_i++;
                }
                max = max > max_i ? max : max_i;
            }
        }
        return max;
    }
};