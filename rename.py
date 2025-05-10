import os
import re

def rename_files_in_directory(directory):
    # 遍历目录中的所有文件
    for filename in os.listdir(directory):
        # 检查文件是否以 N、E 或 H 开头，并符合命名规则
        match = re.match(r"^(N|E|H)(\d+)\.(.+)\.cpp$", filename)
        if match:
            # 提取难度等级、题号和题目名称
            difficulty = match.group(1)
            number = match.group(2)
            title = match.group(3)
            
            # 构造新的文件名
            new_filename = f"{number}{difficulty}.{title}.cpp"
            
            # 获取完整路径
            old_path = os.path.join(directory, filename)
            new_path = os.path.join(directory, new_filename)
            
            # 重命名文件
            os.rename(old_path, new_path)
            print(f"Renamed: {filename} -> {new_filename}")
        else:
            print(f"Skipped: {filename}")

# 指定目标目录
target_directory = r"e:\Code\LeeCode"
rename_files_in_directory(target_directory)
