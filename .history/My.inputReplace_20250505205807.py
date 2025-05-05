def replace_characters(input_string):
    # 将方括号替换为大括号，并将双引号替换为单引号
    result = input_string.replace('[', '{').replace(']', '}').replace('"', "'")
    return result

# 示例输入
input_string = 'board = [["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]]'
output_string = replace_characters(input_string)

print(output_string)