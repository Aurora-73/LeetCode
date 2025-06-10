import re

def transform_string(s: str) -> str:
    # 1. 去除版权标记
    s = s.replace("©leetcode", "")

    # 2. 去除空行
    lines = s.splitlines()
    non_empty = [line for line in lines if line.strip() != ""]

    # 3. 排除第2~5行不需要的标签 & 删除指定英文句子的行
    unwanted = {"简单", "中等", "困难", "相关标签", "premium lock icon", "相关企业"}
    pattern = r'^Create the variable named \w+ to store the input midway in the function\.$'
    cleaned = []
    for i, line in enumerate(non_empty):
        if 1 <= i <= 4 and line.strip() in unwanted:
            continue
        if re.match(pattern, line.strip()):
            continue
        cleaned.append(line)

    # 4. 基础字符替换和标点前空格去除
    text = "\n".join(cleaned)
    text = (text.replace("[", "{")
                .replace("]", "}")
                .replace("'", '"'))
    text = re.sub(r'\s+(，|。)', r'\1', text)

    # 5. 自动断句：行长>66，找最靠近中点的中文逗号/句号断行
    def break_line(line: str) -> list[str]:
        L = len(line)
        if L > 66:
            poses = [m.start() for m in re.finditer(r"[，。]", line)]
            if poses:
                mid = L // 2
                pos = min(poses, key=lambda x: abs(x - mid))
                return [line[:pos+1], line[pos+1:]]
        return [line]

    # 6. 按节缩进：标题行不缩进，标题下面的行缩进一次（已有缩进的不再重复）
    HEADERS = ("注意：", "示例 1：", "示例 2：", "示例 3：", "示例 4：", "提示：", "提示:", "示例 1:", "示例 2:", "示例 3:")
    final_lines = []
    indent_mode = False

    for raw in text.splitlines():
        for part in break_line(raw):
            stripped = part.lstrip()
            # 如果是新的标题行
            if any(stripped.startswith(h) for h in HEADERS):
                final_lines.append(stripped)
                indent_mode = True
            else:
                if indent_mode:
                    # 若已经有缩进（空格或制表符开头）则不再加
                    if part.startswith(("	", "\t")):
                        final_lines.append(part)
                    else:
                        final_lines.append("\t" + part)
                else:
                    final_lines.append(part)

    # 7. 删除结果第二行如果是“数字+分”
    if len(final_lines) >= 2 and re.fullmatch(r"\d+\s*分", final_lines[1].strip()):
        final_lines.pop(1)

    # 8. 如果最后一行以 "https://" 开头，则删除
    if final_lines and final_lines[-1].strip().startswith("https://"):
        final_lines.pop(-1)

    return "\n".join(final_lines)


if __name__ == "__main__":
    try:
        with open("Input.txt", "r", encoding="utf-8") as f:
            input_str = f.read()
    except FileNotFoundError:
        # 文件不存在则创建空文件
        with open("Input.txt", "w", encoding="utf-8") as f:
            pass
        input_str = ""
    output_str = transform_string(input_str)
    with open("Input.txt", "w", encoding="utf-8") as f:
        f.write(output_str)
