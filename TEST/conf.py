import os
import re
from collections import defaultdict

# 获取脚本所在的目录
directory = os.path.dirname(os.path.realpath(__file__))
directory += input(f"数据目录 : {directory}")

prefix = input("数据前缀名 : ")
use_builtin_judger = input("是否使用内置评测器（on/off）: ")
use_builtin_checker = input("请输入内置检查器类型（例如：wcmp）: ")
input_suffix = input("输入文件的后缀名（如in）: ")
output_suffix = input("输出文件的后缀名（如out）: ")
time_limit = int(input("时间限制（秒）: "))
memory_limit = int(input("空间限制（MB）: "))
conf_lines = [
    f"use_builtin_judger {use_builtin_judger}\n",
    f"use_builtin_checker {use_builtin_checker}\n",
    f"input_pre {prefix}\n",
    f"output_pre {prefix}\n",
    f"input_suf {input_suffix}\n",
    f"output_suf {output_suffix}\n",
    f"time_limit {time_limit}\n",
    f"memory_limit {memory_limit}\n",
    "output_limit 64\n",
    "n_ex_tests 0\n",
    "n_sample_tests 0\n"
]

# 询问用户是否要绑定子任务
bind_subtasks = input("子任务？(on/off): ").strip()

if bind_subtasks == 'on':
    # 绑定子任务的逻辑
    connector = input("编号连接方式（- 或 _）: ")

    # 匹配文件名的正则表达式
    pattern = re.compile(f"{prefix}(\d+){connector}(\d+)\\.({input_suffix}|{output_suffix})")

    # 用于存储文件的字典，键为 x 值，值为一个字典，其中键为 y 值，值为一个列表，包含不同后缀的文件名
    files_dict = defaultdict(lambda: defaultdict(list))

    # 收集所有匹配的文件
    for filename in os.listdir(directory):
        match = pattern.match(filename)
        if match:
            x = int(match.group(1))
            y = int(match.group(2))
            files_dict[x][y].append(match.group(3))

    # 按 x 值排序，然后对每个 x 值下的 y 值排序
    sorted_x = sorted(files_dict.keys())
    n_tests = 0
    n_subtasks = 0
    print(f"\n----检测到{len(sorted_x)}个subtask----\n")

    # 用于记录每个子任务的起始和结束 id
    subtask_ends = []
    subtask_scores = []

    for x in sorted_x:
        n_subtasks += 1
        print(f"----subtask_{n_subtasks}----")
        # 为同一子任务中的所有文件分配相同的 id
        for y in sorted(files_dict[x].keys()):
            n_tests += 1
            for ext in files_dict[x][y]:
                new_filename = f"{prefix}{n_tests}.{ext}"
                os.rename(os.path.join(directory, f"{prefix}{x}{connector}{y}.{ext}"), os.path.join(directory, new_filename))
                print(f"重命名{prefix}{x}{connector}{y}.{ext}->{new_filename}")
        subtask_ends.append(n_tests)
        score = int(input(f"子任务 {x} 的分数: "))
        subtask_scores.append(score)

    # 检查所有子任务分数之和是否为100
    total_score = sum(subtask_scores)
    if total_score != 100:
        print("警告：子任务分数之和不等于100。")

    # 创建 problem.conf 文件
    conf_lines.append(f"n_tests {n_tests}\n")
    conf_lines.append(f"n_subtasks {n_subtasks}\n")

    # 添加子任务信息
    for i, (end, score) in enumerate(zip(subtask_ends, subtask_scores), 1):
        conf_lines.append(f"subtask_end_{i} {end}\n")
        conf_lines.append(f"subtask_score_{i} {score}\n")
else:
    # 不绑定子任务的逻辑
    
    # 计算 n_tests
    n_tests = len([f for f in os.listdir(directory) if f.startswith(prefix) and f.endswith(input_suffix)])
    
    # 创建 problem.conf 文件
    conf_lines.append(f"n_tests {n_tests}\n")

# 写入 problem.conf 文件
conf_path = os.path.join(directory, "problem.conf")
with open(conf_path, 'w') as conf_file:
    conf_file.writelines(conf_lines)

print(f"\n已创建于{conf_path}")