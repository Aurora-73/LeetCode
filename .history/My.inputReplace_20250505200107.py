def replace_characters(input_string):
    # 将方括号替换为大括号，并将双引号替换为单引号
    result = input_string.replace('[', '{').replace(']', '}').replace('"', "'")
    return result

# 示例输入
input_string = '[["1","1","0","0","0"],["1","1","0","0","0"],["0","0","1","0","0"],["0","0","0","1","1"]]'
output_string = replace_characters(input_string)

print(output_string)