import os
import pandas as pd

def average_csv_files(report_folder, output_folder):
    # 创建输出文件夹如果不存在
    os.makedirs(output_folder, exist_ok=True)

    # 遍历所有时间戳文件夹
    all_data = {}

    for timestamp_folder in os.listdir(report_folder):
        folder_path = os.path.join(report_folder, timestamp_folder)
        if os.path.isdir(folder_path):
            for filename in os.listdir(folder_path):
                if filename.endswith('.csv'):
                    file_path = os.path.join(folder_path, filename)
                    # 读取 CSV 文件
                    df = pd.read_csv(file_path)

                    # 使用文件名作为键存储数据
                    if filename not in all_data:
                        all_data[filename] = []
                    all_data[filename].append(df)

    # 计算每个文件的平均值并保存
    for filename, dfs in all_data.items():
        # 假设所有 DataFrame 有相同的行数
        row_count = len(dfs[0])
        avg_data = []

        # 对每一行求平均值
        for i in range(row_count):
            row_data = [df.iloc[i] for df in dfs]
            average_row = []

            # 对每一列求平均值，保留函数名
            for column in row_data[0].index:
                if column == 'Function Name':
                    # 保留函数名不变
                    average_row.append(row_data[0][column])
                else:
                    # 计算数值列的平均值
                    numeric_values = [row[column] for row in row_data if isinstance(row[column], (int, float))]
                    average_value = sum(numeric_values) / len(numeric_values) if numeric_values else 0
                    average_row.append(average_value)

            avg_data.append(average_row)

        # 创建新的 DataFrame
        average_df = pd.DataFrame(avg_data, columns=dfs[0].columns)
        average_df['Function Name'] = average_df['Function Name'].str.replace('-gen', '-ava')  # 改名为 -ava

        # 生成输出文件路径
        output_file = os.path.join(output_folder, f"{filename.replace('.csv', '-ava.csv')}")
        
        # 保存到新文件
        average_df.to_csv(output_file, index=False, encoding='utf-8-sig')

def main():
    report_folder = 'report'
    output_folder = 'report/ava'
    
    average_csv_files(report_folder, output_folder)

if __name__ == '__main__':
    main()
