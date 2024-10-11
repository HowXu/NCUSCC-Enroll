import os
import pandas as pd
import matplotlib.pyplot as plt

def plot_single_function_data(report_folder, single_folder):
    # 创建单个 SVG 文件夹如果不存在
    if not os.path.exists(single_folder):
        os.mkdir(single_folder)

    # 定义实验文件名关键字
    experiment_keys = ['o0', 'o1', 'o2', 'o3', 'ofast']
    data = {}

    # 遍历 report 文件夹，读取实验数据
    for filename in os.listdir(report_folder):
        if any(key in filename for key in experiment_keys) and filename.endswith('-gen-ave.csv'):
            file_path = os.path.join(report_folder, filename)
            df = pd.read_csv(file_path)
            data[filename] = df

    # 确保有数据进行绘图
    if not data:
        print("No data files found.")
        return

    # 收集每个函数的数据，排除特定函数
    exclude_functions = ['_init', 'get_random_array_with_seed']
    functions = set()

    for df in data.values():
        # 找到所有函数名，排除不需要的函数
        filtered_functions = df.iloc[:, -1][~df.iloc[:, -1].str.startswith(tuple(exclude_functions), na=False) &
                                             ~df.iloc[:, -1].str.startswith('test', na=False)]
        functions.update(filtered_functions)

    # 为每个函数生成图表
    for function in functions:
        function_data = {key: [] for key in data.keys()}  # 存储每个实验的数据

        for filename, df in data.items():
            # 查找当前函数的数据
            func_row = df[df.iloc[:, -1] == function]
            if not func_row.empty:
                # 获取该函数的数值列，排除指定列
                function_values = func_row.iloc[0, :-1]  # 取出所有列但最后一列（函数名）
                
                # 存储有效数据
                function_data[filename] = function_values.values

        # 创建函数的文件夹
        safe_function_name = function.replace(' ', '_')  # 替换空格为下划线
        func_folder = os.path.join(single_folder, safe_function_name)

        if not os.path.exists(func_folder):
            os.mkdir(func_folder)

        # 绘制每种数据类型的图表
        index = 0
        for data_type in function_values.index:  # 遍历所有数据类型
            if 's/call' in data_type:
                index += 1  # 跳过包含 's/call' 的数据类型
                continue

            plt.figure(figsize=(12, 8))  # 增加图形高度

            # 生成 x 轴标签和 y 值
            x_labels = list(function_data.keys())
            y_values = []
            index += 1
            for exp in x_labels:
                # 确保我们只获取有数据的实验

                if function_data[exp].size > 0:
                    # 死全家Ai还得你爸自己来 我操你吗连个index都处理不好
                    y_values.append(function_data[exp][index])  # 获取第一个值
                else:
                    y_values.append(0)  # 如果没有数据，填充为0

            # 绘制数据
            plt.bar(x_labels, y_values, color='skyblue')

            plt.title(f'{data_type} Data for {function}')
            plt.xlabel('Experiments')
            plt.ylabel('Values')
            plt.xticks(rotation=45)
            plt.grid(axis='y')

            # 设置 y 轴范围
            min_value = min(y_values)
            max_value = max(y_values)

            plt.ylim(max(0.1, min_value * 0.9), max_value * 2)  # 增加 y 轴的最大值以增强对比

            # 自定义 y 轴刻度
            if max_value - min_value < 10:  # 根据需要调整这个阈值
                plt.yticks(range(0, int(max_value * 2) + 1, max(1, int(max_value * 0.1))))  # 自定义刻度

            # 尝试保存图表
            output_file = os.path.join(func_folder, f'{safe_function_name}_{data_type}_data.svg')
            try:
                plt.tight_layout()
                plt.savefig(output_file, format='svg')
            except Exception as e:
                print(f"Error saving file {output_file}: {e}")
            finally:
                plt.close()

def main():
    report_folder = 'report/average'  # 假设 CSV 文件保存在这个目录下
    single_folder = 'report/single'  # 保存单个函数 SVG 文件的目录
    plot_single_function_data(report_folder, single_folder)

if __name__ == '__main__':
    main()
