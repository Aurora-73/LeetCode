def replace_characters(input_string):
    # 将方括号替换为大括号，并将双引号替换为单引号
    result = input_string.replace('[', '{').replace(']', '}').replace('"', "'")
    return result

# 示例输入
input_string = '["example", "test", ["nested", "list"]]'
output_string = replace_characters(input_string)

print("输入字符串:", input_string)
print("输出字符串:", output_string)