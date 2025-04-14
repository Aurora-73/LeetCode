#include <iostream>
#include <vector>

using namespace std;

int main(){
    string str;
    str += "Hell" + 'o';
    cout << str <<endl;
    cout << "Hell" + 'o' << endl;
    cout << typeid("Hell" + 'o').name() << endl; // PKc 表示 const char*
    long long aaa = reinterpret_cast<long long>("Hell");
    long long bbb = reinterpret_cast<long long>("Hell" + 'o');
    cout << aaa << " " << bbb << endl;
    cout << char(bbb - aaa) << endl;
    cout << "Hell" << 'o' << endl;
}

/*关键点："Hell" + 'o' 的意思是什么？
"Hell" 是一个 const char*，指向以 \0 结尾的字符数组。
'o' 是一个字符（char），本质是一个整数值（ASCII码）——也就是 111。
"Hell" + 'o' 相当于 (const char*)("Hell" + 111) // 指针 + 偏移
*/