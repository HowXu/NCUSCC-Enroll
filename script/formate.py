import os
import pandas as pd
from datetime import datetime

def parse_gprof_report(file_path):
    functions = []
    start_collecting = False
    
    with open(file_path, 'r') as f:
        lines = f.readlines()
        
        for line in lines:
            if 'Each sample counts as 0.01 seconds.' in line:
                start_collecting = True
                continue
            
            if start_collecting:
                if line.startswith('%'):  # 捕获标题行
                    continue  # 不添加标题行
                
                parts = line.split()
                # 检查列表长度是否足够
                if len(parts) >= 7 and parts[0].replace('.', '', 1).isdigit():
                    functions.append(parts)  # 保留原有信息结构
                    
    return functions

def filter_functions(functions, exclude):
    return [func for func in functions if func[-1] not in exclude]

def calculate_new_percentages(functions):
    total = sum(float(func[0]) for func in functions)  # 计算总时间
    for func in functions:
        new_percentage = (float(func[0]) / total) * 100  # 计算新的占比
        func.insert(0, round(new_percentage, 3))  # 将新占比放在第一列，并保留三位小数

def format_numbers(functions):
    for func in functions:
        for i in range(1, len(func) - 1):  # 从第二列开始格式化到倒数第二列
            func[i] = f"{float(func[i]):.3f}"

def save_to_csv(functions, output_path):
    # 添加新的列名
    new_header = ['New Percentage (%)', 'Time (%)', 'Cumulative Seconds', 'Self Seconds', 'Calls', 'Self s/call', 'Total s/call', 'Function Name']
    
    df = pd.DataFrame(functions, columns=new_header)
    df.to_csv(output_path, index=False, encoding='utf-8-sig')

def main():
    input_folder = 'analysis'
    output_folder = 'report'
    exclude_functions = ['_init', 'get_random_array_with_seed']

    os.makedirs(output_folder, exist_ok=True)
    
    # 获取当前时间戳
    timestamp = datetime.now().strftime('%Y%m%d_%H%M%S')
    timestamp_folder = os.path.join(output_folder, timestamp)
    os.makedirs(timestamp_folder, exist_ok=True)

    for filename in os.listdir(input_folder):
        if filename.endswith('.txt'):
            file_path = os.path.join(input_folder, filename)
            functions = parse_gprof_report(file_path)

            filtered_functions = filter_functions(functions, exclude_functions)
            calculate_new_percentages(filtered_functions)
            format_numbers(filtered_functions)  # 格式化数字

            # 生成输出文件名
            output_file = os.path.join(timestamp_folder, f'{os.path.splitext(filename)[0]}.csv')
            save_to_csv(filtered_functions, output_file)

if __name__ == '__main__':
    main()
