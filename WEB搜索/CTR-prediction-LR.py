# 1.导入数据并进行简单的数据探索
import os

data_path = os.path.join(".", "train_small.csv")
import pandas as pd

ctr_data1 = pd.read_csv(data_path)
# 2.数据的简单描述信息
print(ctr_data1.shape)
# print ctr_data.head()
# print ctr_data.describe()
print(ctr_data1.columns)
print("=" * 100)
training_Set = ctr_data1.drop(['id', 'site_id', 'app_id', 'device_id', 'device_ip', 'site_domain',
                               'site_category', 'app_domain', 'app_category', 'device_model'], axis=1)
ctr_data = training_Set.values  # numpy--ndarry
# 2.对数据进行处理和分析
from sklearn.model_selection import train_test_split

X = ctr_data[:, 1:]
print(X.shape)
y = ctr_data[:, 0]
print(y.shape)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.22, random_state=33)
print(X_train.shape)
print(y_train.shape)
# #3.引入机器学习算法
from sklearn.linear_model import LogisticRegression

# lr=LogisticRegression()
#           0       0.83      1.00      0.91     18240
#           1       0.00      0.00      0.00      3760
#
# avg / total       0.69      0.83      0.75     22000
lr = LogisticRegression(C=0.1, penalty='l1')
#              precision    recall  f1-score   support
#
#           0       0.83      1.00      0.91     18240
#           1       0.40      0.00      0.00      3760
#
# avg / total       0.76      0.83      0.75     22000
lr.fit(X_train, y_train)
# #4.模型预测
y_pred = lr.predict(X_test)
print(y_pred)
# # #5.模型校验
print(lr.score(X_train, y_train))
print(lr.score(X_test, y_test))
from sklearn.metrics import confusion_matrix

print(confusion_matrix(y_test, y_pred))
from sklearn.metrics import classification_report

print(classification_report(y_test, y_pred))
# #6.保存模型
# from sklearn.externals import joblib
#
# joblib.dump(lr, filename="Ctr_Predict.pkl")
# #8.按照要求写入对应的csv文件
import numpy as np
import pandas as pd

ctr_data2 = pd.read_csv("test.csv")
ctr_data3 = ctr_data2.drop(['click', 'site_id', 'app_id', 'device_id', 'device_ip', 'site_domain',
                            'site_category', 'app_domain', 'app_category', 'device_model'], axis=1)
print(ctr_data3)
ids = ctr_data3.values[0:, 0]
y_pred_test = lr.predict(ctr_data3.values[0:, 1:])
# # # print ids
submit = np.concatenate((ids.reshape(len(ids), 1), y_pred_test.reshape(len(y_pred_test), 1)), axis=1)
df = pd.DataFrame(submit)
df.to_csv("submit.csv", header=['id', 'click'], index=False)
