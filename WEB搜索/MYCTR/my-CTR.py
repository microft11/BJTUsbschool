import numpy as np
import pandas as pd
from sklearn.preprocessing import LabelEncoder
from sklearn.feature_extraction.text import CountVectorizer
from scipy.sparse import hstack, csr_matrix, issparse
from scipy.sparse import vstack
import torch
import torch.nn as nn
import torch.optim as optim

# 解析news.txt文件
with open('news.txt', 'r', encoding='utf-8') as file:
    lines = file.readlines()

# 存储新闻数据的列表
news_list = []

current_news = {}  # 用于存储当前新闻的字典
for line in lines:
    line = line.strip().split('\t')
    if line:  # 如果行不为空
        current_news = {'News ID': line[0], 'Category': line[1], 'Title': line[3]}  # 提取News ID, Category, 和 Title
        news_list.append(current_news)

# print(news_list)

# 转换新闻数据为DataFrame
news_data = pd.DataFrame(news_list)

# 假设train_data包含用户点击历史等信息
train_data = pd.read_csv('train_behaviors.txt', delimiter='\t', header=None,
                         names=['Impression ID', 'User ID', 'Time', 'History', 'Impressions'])

# 假设test_data包含测试数据
test_data = pd.read_csv('test_behaviors.txt', delimiter='\t', header=None,
                        names=['Impression ID', 'User ID', 'Time', 'History'])
# test_data = pd.read_csv('test_behaviors.txt', delimiter='\t', header=None,
#                         names=['Impression ID', 'User ID', 'Time', 'History', 'Impressions'])

print("end1")

# 特征工程步骤
# 1. 处理用户点击历史
train_data['History'] = train_data['History'].apply(lambda x: str(x))  # 将数据转换为字符串
train_data['History'] = train_data['History'].apply(lambda x: x.split(' '))  # 将历史点击分割成列表

print("end2")

# 2. 处理新闻类别和标题
# 使用LabelEncoder将类别和标题转化为数值特征
label_encoder = LabelEncoder()
news_data['Category_encoded'] = label_encoder.fit_transform(news_data['Category'])
news_data['Title_encoded'] = label_encoder.fit_transform(news_data['Title'])

print("end3")

# 3. 文本特征处理
# 使用CountVectorizer将新闻标题转化为词袋模型的特征向量
vectorizer = CountVectorizer()
news_title_features = vectorizer.fit_transform(news_data['Title'])

print("end4")


# 4. 合并特征
# 根据用户点击历史中的新闻ID匹配新闻特征
# 修改生成特征向量的部分
def generate_history_features(history):
    max_history_length = 1  # 选择最近的10个历史新闻
    history = history[:max_history_length]  # 限制历史新闻数量
    features = []

    for news_id in history:
        # 添加新闻ID的打印语句
        print(f"Processing news ID: {news_id}")

        # 查找匹配的新闻特征
        matching_features = news_title_features[news_data.index[news_data['News ID'] == news_id]]

        # 添加到特征列表中
        features.append(matching_features)

    return features


# 根据用户点击历史中的新闻ID匹配新闻标题特征
train_data['History_features'] = train_data['History'].apply(generate_history_features)

# train_data['History_features'] = train_data['History'].apply(
#     lambda history: [news_title_features[news_data.index[news_data['News ID'] == news_id]].toarray() for news_id in
#                      history])

print(test_data.columns)
# 假设test_data包含测试数据
test_data['History'] = test_data['History'].apply(lambda x: x.split(' '))  # 将历史点击分割成列表

print("end5")


# 进行与训练数据相同的特征工程处理，包括新闻类别和标题的编码等

# 定义CTR预测模型
class CTRModel(nn.Module):
    def __init__(self, input_dim, hidden_dim, output_dim):
        super(CTRModel, self).__init__()
        self.fc1 = nn.Linear(input_dim, hidden_dim)
        self.relu = nn.ReLU()
        self.fc2 = nn.Linear(hidden_dim, output_dim)
        self.sigmoid = nn.Sigmoid()

    def forward(self, x):
        x = self.fc1(x)
        x = self.relu(x)
        x = self.fc2(x)
        x = self.sigmoid(x)
        return x


# 创建模型实例
input_dim = 100  # 输入特征维度
hidden_dim = 64  # 隐层维度
output_dim = 1  # 输出维度

model = CTRModel(input_dim, hidden_dim, output_dim)

# 定义损失函数和优化器
criterion = nn.BCELoss()  # 二元交叉熵损失
optimizer = optim.Adam(model.parameters(), lr=0.001)

print(train_data)


# 创建 train_labels 列，根据 Impressions 列设定值
def set_click_label(impressions):
    impressions = impressions.split()  # 将 Impressions 按空格分割成列表
    for impression in impressions:
        if impression.startswith('N'):
            return 1
    return 0


train_data['train_labels'] = train_data['Impressions'].apply(set_click_label)

# 输出 train_data
print(train_data)

train_labels = train_data['train_labels']

# 数据预处理和清洗（根据需要）
print("end6")

# 训练模型
num_epochs = 10
for epoch in range(num_epochs):
    optimizer.zero_grad()
    # # train_features = train_data['History_features'].apply(lambda x: csr_matrix(x))
    # train_features = train_data['History_features'].apply(lambda x: csr_matrix(np.array(x)))
    # # 合并稀疏矩阵成一个大的稀疏矩阵
    # merged_features = hstack(train_features.tolist())
    # # 将合并的稀疏矩阵转换为 PyTorch 张量
    # train_features_tensor = torch.tensor(merged_features.toarray(), dtype=torch.float32)

    # 定义一个函数来处理每个元素，将非零稀疏矩阵转化为 csr_matrix，其他情况保持不变
    def process_sparse_matrix(x):
        if issparse(x):
            return x
        else:
            # 如果 x 是一个数组并且包含至少一个非零元素
            if isinstance(x, np.ndarray) and np.count_nonzero(x) > 0:
                return csr_matrix(x)
            else:
                return None  # 或者返回其他默认值


    # # Convert each sparse matrix element to a CSR matrix
    # train_features = train_data['History_features'].apply(process_sparse_matrix)
    # # Filter out None values
    # train_features = train_features[train_features.apply(lambda x: x is not None)]
    # # Convert train_features to a list of CSR matrices
    # train_features_list = list(train_features)
    # # Convert the list of CSR matrices to a 2-D numpy array
    # train_features_array = np.vstack(train_features_list)
    # # Use vstack to stack the sparse matrices
    # merged_features = vstack(train_features_array)
    # # Convert the merged sparse matrix to a PyTorch tensor
    # train_features_tensor = torch.tensor(merged_features.toarray(), dtype=torch.float32)

    # Convert each sparse matrix element to a CSR matrix
    train_features = train_data['History_features'].apply(process_sparse_matrix)
    # Filter out None values
    train_features = train_features[train_features.apply(lambda x: x is not None)]

    # Check if there are any valid CSR matrices in the list
    if not train_features.empty:
        # Convert train_features to a list of CSR matrices
        train_features_list = list(train_features)
        # Convert the list of CSR matrices to a 2-D numpy array
        train_features_array = np.vstack(train_features_list)
        # Use vstack to stack the sparse matrices
        merged_features = vstack(train_features_array)
        # Convert the merged sparse matrix to a PyTorch tensor
        train_features_tensor = torch.tensor(merged_features.toarray(), dtype=torch.float32)
    else:
        # Handle the case where there are no valid CSR matrices
        print("No valid CSR matrices found in train_features")

    # outputs = model(train_features)
    train_features = train_features.astype(np.float32)
    print(train_features.values)
    outputs = model(torch.tensor(train_features.values, dtype=torch.float32))
    loss = criterion(outputs, torch.tensor(train_labels.values, dtype=torch.float32))
    loss.backward()
    optimizer.step()
    print(f'Epoch [{epoch + 1}/{num_epochs}], Loss: {loss.item():.4f}')


# 使用模型进行预测
# 对测试数据进行相同的特征处理并转化为张量
# 在测试数据上进行相同的特征处理并转化为PyTorch张量
def process_sparse_matrix(x):
    if issparse(x):
        return x
    else:
        # 如果 x 是一个数组并且包含至少一个非零元素
        if isinstance(x, np.ndarray) and np.count_nonzero(x) > 0:
            return csr_matrix(x)
        else:
            return None  # 或者返回其他默认值


test_features = test_data['History_features'].apply(process_sparse_matrix)  # 使用与训练数据相同的处理方法
test_features = test_features[test_features.apply(lambda x: x is not None)]  # 过滤掉None值

# 检查是否有有效的CSR矩阵
if not test_features.empty:
    # 将测试数据特征转化为PyTorch张量
    test_features_list = list(test_features)
    test_features_array = np.vstack(test_features_list)
    test_features_tensor = torch.tensor(test_features_array, dtype=torch.float32)
else:
    print("No valid CSR matrices found in test_features")

# 使用模型进行预测
predictions = model(test_features_tensor)
#
# test_features = test_data['History_features']  # 假设这是测试数据特征
# test_features = torch.tensor(test_features, dtype=torch.float32)
# predictions = model(test_features)  # 进行CTR预测
print("end7")

# 假设predictions是模型对测试数据的预测结果
# 假设predictions是一个张量


# 假设predictions是一个张量
predictions = predictions.detach().numpy().flatten()  # 将张量转化为NumPy数组

# 假设test_data包含测试数据
test_data['Prediction'] = predictions  # 将预测结果添加到测试数据中
test_data['Rank'] = test_data.groupby('Impression ID')['Prediction'].rank(ascending=True).astype(int)  # 计算排名

# 创建提交文件的内容
submission_lines = []
for _, row in test_data.iterrows():
    submission_lines.append(f"{row['Impression ID']} {row['Rank']}")

# 保存为.txt文件
with open('submission.txt', 'w') as file:
    file.write('\n'.join(submission_lines))
