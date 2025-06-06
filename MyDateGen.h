// MyDateGen.h
#ifndef DATA_GEN_H
#define DATA_GEN_H
#include <string>
#include <vector>

/**
 * 创建随机的 vector<int>
 * @param n 元素个数
 * @param minVal 最小值
 * @param maxVal 最大值
 * @param ordered 是否有序
 * @param unique 是否唯一
 */
std::vector<int> randomIntArray(
    int n, int minVal, int maxVal, bool ordered = false, bool unique = false);

/**
 * 创建随机的小写字母字符串
 * @param n 元素个数
 * @param ordered 是否有序
 * @param unique 元素是否唯一
 */
std::string randomString(int n, bool ordered = false, bool unique = false);

/**
 * 创建随机的二维矩阵
 * @param rows 行数
 * @param cols 列数
 * @param minVal 最小值
 * @param maxVal 最大值
 */
std::vector<std::vector<int>> randomMatrix(int rows, int cols, int minVal, int maxVal);

#endif // DATA_GEN_H