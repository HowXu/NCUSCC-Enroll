import os
import pandas as pd

def merge_functions_in_csv(file_path):
    df = pd.read_csv(file_path)

    # 合并 bubble_sort 和 swap
    bubble_swap_df = df[df['Function Name'].isin(['bubble_sort', 'swap'])]
    if not bubble_swap_df.empty:
        bubble_swap_merged = bubble_swap_df.sum(numeric_only=True).to_frame().T
        bubble_swap_merged['Function Name'] = 'bubble_sort'  # 改名为 bubble_sort
    else:
        bubble_swap_merged = pd.DataFrame(columns=df.columns)
        bubble_swap_merged['Function Name'] = ['bubble_sort']

    # 合并 heapify 和 heap_sort
    heap_df = df[df['Function Name'].isin(['heapify', 'heap_sort'])]
    if not heap_df.empty:
        heap_merged = heap_df.sum(numeric_only=True).to_frame().T
        heap_merged['Function Name'] = 'heap_sort'  # 改名为 heap_sort
    else:
        heap_merged = pd.DataFrame(columns=df.columns)
        heap_merged['Function Name'] = ['heap_sort']

    # 合并其他函数，排除以 test 开头的函数
    others_df = df[~df['Function Name'].str.startswith('test') &
                   ~df['Function Name'].isin(['bubble_sort', 'swap', 'heapify', 'heap_sort'])]
    if not others_df.empty:
        others_merged = others_df.sum(numeric_only=True).to_frame().T
        others_merged['Function Name'] = 'fib_heap_sort'  # 改名为 fib_heap_sort
    else:
        others_merged = pd.DataFrame(columns=df.columns)
        others_merged['Function Name'] = ['fib_heap_sort']

    # 合并所有结果
    final_df = pd.concat([bubble_swap_merged, heap_merged, others_merged], ignore_index=True)

    # 生成新的文件名
    base_name = os.path.splitext(os.path.basename(file_path))[0]
    output_file = os.path.join(os.path.dirname(file_path), f"{base_name}-gen.csv")
    
    # 保存到新文件
    final_df.to_csv(output_file, index=False, encoding='utf-8-sig')

def main():
    report_folder = 'report'
    
    # 遍历所有时间戳文件夹
    for timestamp_folder in os.listdir(report_folder):
        folder_path = os.path.join(report_folder, timestamp_folder)
        if os.path.isdir(folder_path):
            for filename in os.listdir(folder_path):
                if filename.endswith('.csv'):
                    file_path = os.path.join(folder_path, filename)
                    merge_functions_in_csv(file_path)

if __name__ == '__main__':
    main()
