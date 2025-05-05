#include<map>
#include<iostream>

using namespace std;

int main(){
    map<int, string> m;
    m[1] = "string";
    if(auto it = m.find(1); it != m.end()){
        cout << it -> second << endl;
    } 
    // 最好的写法，C++17之前声明要单独写
    if(m.count(1)){
        cout << m.at(1) << endl;
    }
    // if(m.contains(1)){
    //     cout << m.at(1) << endl;
    // } C++ 20
    // 简单的写法，实际上查找了两次，会有性能开销
    // 但是at不会修改m，可以用于const的map
    if(m.find(1) != m.end()){
        cout << m[1] << endl; 
    }
    // 不建议这么写
    // 1、实际上又进行了一次查找，性能开销
    // 2、m[1]存在修改m的可能，无法使用在const的map上
}