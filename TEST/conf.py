import os
import re
from collections import defaultdict
from collections import Counter

# 获取脚本所在的目录
directory = os.path.dirname(os.path.realpath(__file__))
directory += input(f"数据目录 : {directory}")

# 获取数据前缀名
prefix = input("数据前缀名 : ")
title = prefix + "_"
input_suffix = "in"
print(f"默认输入文件后缀名: {input_suffix}")

# 匹配后缀名的正则表达式
suffix_pattern = re.compile(f"^{prefix}.+?\\.(\w+)$")

# 计数每个后缀的出现次数，忽略 '.in' 后缀
suffix_count = Counter(re.search(suffix_pattern, filename).group(1) for filename in os.listdir(directory) if re.search(suffix_pattern, filename) and re.search(suffix_pattern, filename).group(1) != 'in')

# 找出出现次数最多的后缀（除了 '.in'）
output_suffix,_ = suffix_count.most_common(1)[0]
print(f"检测到输出文件后缀名: {output_suffix}")

time_limit = int(input("时间限制（秒）: "))
memory_limit = int(input("空间限制（MB）: "))
conf_lines = [
    "use_builtin_judger on\n",
    "use_builtin_checker wcmp\n",
    f"input_pre {title}\n",
    f"output_pre {title}\n",
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
    # 匹配连接方式的正则表达式
    link_pattern = re.compile(f"^{prefix}\d+(.+?)\d+\\.in$")

    # 计数每个连接方式的出现次数
    link_count = Counter(re.search(link_pattern, filename).group(1) for filename in os.listdir(directory) if re.search(link_pattern, filename))

    # 找出出现次数最多的连接方式
    connector,_ = link_count.most_common(1)[0]
    print(f"\n检测到连接方式: {connector}")

    # 匹配文件名的正则表达式
    pattern = re.compile(f"^{prefix}(\d+){connector}(\d+)\\.({input_suffix}|{output_suffix})$")

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
    print(f"\n----检测到{len(sorted_x)}个subtask----")

    # 用于记录每个子任务的起始和结束 id
    subtask_ends = []
    subtask_scores = []

    for x in sorted_x:
        n_subtasks += 1
        print(f"\n----subtask_{n_subtasks}----")
        # 为同一子任务中的所有文件分配相同的 id
        for y in sorted(files_dict[x].keys()):
            n_tests += 1
            for ext in files_dict[x][y]:
                new_filename = f"{title}{n_tests}.{ext}"
                os.rename(os.path.join(directory, f"{prefix}{x}{connector}{y}.{ext}"), os.path.join(directory, new_filename))
                print(f"重命名{prefix}{x}{connector}{y}.{ext}->{new_filename}")
        subtask_ends.append(n_tests)
        score = int(input(f"子任务 {x} 的分数: "))
        subtask_scores.append(score)

    # 检查所有子任务分数之和是否为100
    total_score = sum(subtask_scores)
    if total_score != 100:
        print("\n警告：子任务分数之和不等于100！！！")

    # 创建 problem.conf 文件
    conf_lines.append(f"n_tests {n_tests}\n")
    conf_lines.append(f"n_subtasks {n_subtasks}\n")

    # 添加子任务信息
    for i, (end, score) in enumerate(zip(subtask_ends, subtask_scores), 1):
        conf_lines.append(f"subtask_end_{i} {end}\n")
        conf_lines.append(f"subtask_score_{i} {score}\n")
else:
    # 不绑定子任务的逻辑

    # 匹配文件名的正则表达式
    pattern = re.compile(f"{prefix}(\d+)\\.({input_suffix}|{output_suffix})")

    # 用于存储文件的字典，键为 x 值，包含不同后缀的文件名
    files_dict = defaultdict(list)

    # 收集所有匹配的文件
    for filename in os.listdir(directory):
        match = pattern.match(filename)
        if match:
            x = int(match.group(1))
            files_dict[x].append(match.group(2))

    # 按 x 值排序，然后对每个 x 值下的 y 值排序
    sorted_x = sorted(files_dict.keys())
    n_tests = 0
    print(f"\n----检测到{len(sorted_x)}个test----\n")

    for x in sorted_x:
        n_tests += 1
        for ext in files_dict[x]:
            new_filename = f"{title}{n_tests}.{ext}"
            os.rename(os.path.join(directory, f"{prefix}{x}.{ext}"), os.path.join(directory, new_filename))
            print(f"重命名{prefix}{x}.{ext}->{new_filename}")
    
    # 创建 problem.conf 文件
    conf_lines.append(f"n_tests {n_tests}\n")

# 写入 problem.conf 文件
conf_path = os.path.join(directory, "problem.conf")
with open(conf_path, 'w') as conf_file:
    conf_file.writelines(conf_lines)

print(f"\n已创建于{conf_path}")
