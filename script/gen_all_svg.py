import os
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

def plot_experiment_data(report_folder, svg_folder):
    # 创建 SVG 文件夹如果不存在
    os.makedirs(svg_folder, exist_ok=True)

    # 定义实验文件名关键字
    experiment_keys = ['o0', 'o1', 'o2', 'o3', 'ofast']
    data = {}

    # 遍历 report 文件夹，读取实验数据
    for filename in os.listdir(report_folder):
        if any(key in filename for key in experiment_keys) and filename.endswith('-gen-ava.csv'):
            file_path = os.path.join(report_folder, filename)
            df = pd.read_csv(file_path)
            data[filename] = df

    # 确保有数据进行绘图
    if not data:
        print("No data files found.")
        return

    # 为每个 CSV 文件中的每种数据类型生成单独的 SVG 文件夹
    for filename, df in data.items():
        # 过滤掉不需要的列
        df_filtered = df.drop(columns=['Calls', 'Self s/call', 'Total s/call', 'Function Name'], errors='ignore')
        
        # 假设最后一列是函数名称
        function_names = df.iloc[:, -1]  # 获取函数名称
        data_types = df_filtered.columns    # 获取数据类型

        # 创建以 CSV 文件名命名的文件夹
        file_folder = os.path.join(svg_folder, filename.replace('.csv', ''))
        os.makedirs(file_folder, exist_ok=True)

        for data_type in data_types:
            plt.figure(figsize=(10, 6))
            
            # 绘制每个数据类型下所有函数的实验数据
            bars = plt.bar(function_names, df_filtered[data_type], color='skyblue')

            # 使用对数坐标绘制 y 轴
            plt.yscale('log')
            plt.title(f'{data_type} Data from {filename} (Log Scale)')
            plt.xlabel('Function Name')
            plt.ylabel('Values (Log Scale)')
            plt.xticks(rotation=45)
            plt.grid(axis='y')

            # 处理文件名中的特殊字符
            safe_filename = filename.replace(' ', '_').replace('/', '_').replace('\\', '_')

            # 保存为 SVG 文件
            output_file = os.path.join(file_folder, f'{safe_filename}_{data_type}_data.svg')
            plt.tight_layout()
            plt.savefig(output_file, format='svg')
            plt.close()

def main():
    report_folder = 'report/ava'  # 假设 CSV 文件保存在这个目录下
    svg_folder = 'report/all'       # 保存 SVG 文件的目录
    plot_experiment_data(report_folder, svg_folder)

if __name__ == '__main__':
    main()
