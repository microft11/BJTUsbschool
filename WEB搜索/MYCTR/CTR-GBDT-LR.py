import pandas as pd
import numpy as np
import matplotlib
import matplotlib.pyplot as plt
from sklearn.datasets import make_classification
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.ensemble import GradientBoostingClassifier, RandomForestClassifier
import xgboost as xgb
from xgboost.sklearn import XGBClassifier
from sklearn.preprocessing import OneHotEncoder
from sklearn.metrics import roc_curve, roc_auc_score, confusion_matrix, classification_report

# 1.随机生成数据集
np.random.seed(10)
X, y = make_classification(n_samples=1000, n_features=30)

# 2.切分数据
X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=223, test_size=0.5)
X_train, X_train_lr, y_train, y_train_lr = train_test_split(X_train, y_train, random_state=223, test_size=0.2)


# 4.网格搜索


# 5.训练模型
# 5.1 RandomForest + LogisticRegression
def RF_LR():
    # Rf: 训练模型
    rf = RandomForestClassifier(n_estimators=100, max_depth=4)  # n_estimators:树的数目
    rf.fit(X_train, y_train)
    rf_result = rf.apply(X_train)  # apply得到叶子节点的索引

    # onehot编码
    ohe = OneHotEncoder()
    ohe.fit(rf_result)
    # 利用RF模型获取以X_train_lr为输入的叶子节点的索引值, 并对其进行one-hot编码
    X_train_leaf_ohe = ohe.transform(rf.apply(X_train_lr))

    # LR: 训练模型
    lr = LogisticRegression(C=0.1, penalty="l2", multi_class='auto')
    lr.fit(X_train_leaf_ohe, y_train_lr)
    # LR: 预测
    y_pred = lr.predict_proba(ohe.transform(rf.apply(X_test)))[:, 1]

    # 模型评估
    fpr, tpr, _ = roc_curve(y_test, y_pred)
    auc = roc_auc_score(y_test, y_pred)
    print("RandomForest + LogisticRegression :\n", auc)
    return fpr, tpr


# 5.2 XGBoost + LogisticRegression
def XGB_LR():
    # XGBoost: 训练模型
    # nthread: 并行度
    # n_estimators: Number of boosted trees to fit 要拟合树的数目
    # colsample_bytree:Subsample ratio of columns when constructing each tree
    XGB = xgb.XGBClassifier(nthread=4, learning_rate=0.08, n_estimators=100,
                            colsample_bytree=0.5)
    XGB.fit(X_train, y_train)
    XGB_result = XGB.apply(X_train)
    # onehot编码
    ohe = OneHotEncoder()
    ohe.fit(XGB_result)
    X_train__ohe = ohe.transform(XGB.apply(X_train_lr))
    # X_train__ohe = ohe.transform(rf_result)
    # LR: 训练模型
    lr = LogisticRegression(C=0.1, penalty="l2", multi_class='auto')
    lr.fit(X_train__ohe, y_train_lr)
    # LR: 预测
    # y_pred的shape = [n_samples, n_classes]
    y_pred = lr.predict_proba(ohe.transform(XGB.apply(X_test)))[:, 1]
    # 模型评估
    fpr, tpr, _ = roc_curve(y_test, y_pred)
    auc = roc_auc_score(y_test, y_pred)
    print("XGBoost + LogisticRegression :\n", auc)
    return fpr, tpr


# 5.3 GradientBoostingClassifier+LR
def GBDT_LR():
    # GBDT: 训练模型
    # n_estimators:迭代次数
    gbdt = GradientBoostingClassifier(n_estimators=100)
    gbdt.fit(X_train, y_train)
    gbdt_result = gbdt.apply(X_train)  # 3维:shape (n_samples, n_estimators, n_classes)
    # onehot编码
    ohe = OneHotEncoder()
    ohe.fit(gbdt_result[:, :, 0])  # gbdt_result[:,:,0]获取GBDT
    # print(ohe.fit(gbdt_result[:,:,0]))
    X_train__ohe = ohe.transform(gbdt.apply(X_train_lr)[:, :, 0])
    # LR: 训练模型
    lr = LogisticRegression(C=0.1, penalty="l2", multi_class='auto')
    lr.fit(X_train__ohe, y_train_lr)
    # LR: 预测
    # y_pred的shape = [n_samples, n_classes]
    y_pred = lr.predict_proba(ohe.transform(gbdt.apply(X_test)[:, :, 0]))[:, 1]
    # 模型评估
    fpr, tpr, _ = roc_curve(y_test, y_pred)
    auc = roc_auc_score(y_test, y_pred)
    print("GBDT + LogisticRegression :\n", auc)
    return fpr, tpr


# 5.4 LR
def LR():
    # LR: 训练模型
    lr = LogisticRegression(C=0.1, penalty="l2", multi_class='auto')
    lr.fit(X_train, y_train)
    # LR: 预测
    # y_pred的shape = [n_samples, n_classes]
    y_pred = lr.predict_proba(X_test)[:, 1]
    # 模型评估
    fpr, tpr, _ = roc_curve(y_test, y_pred)
    auc = roc_auc_score(y_test, y_pred)
    print("LogisticRegression :\n", auc)
    return fpr, tpr


# 5.4 XGBoost
def XGBoost():
    # XGB: 训练模型
    XGB = xgb.XGBClassifier(nthread=4, learning_rate=0.08, n_estimators=100,
                            colsample_bytree=0.5)
    XGB.fit(X_train, y_train)
    # XGB: 预测
    y_pred = XGB.predict_proba(X_test)[:, 1]
    # 模型评估
    fpr, tpr, _ = roc_curve(y_test, y_pred)
    auc = roc_auc_score(y_test, y_pred)
    print("XGBoost :\n", auc)
    return fpr, tpr


# 主函数

if __name__ == '__main__':
    fpr_rf_lr, tpr_rf_lr = RF_LR()
    fpr_xgb_lr, tpr_xgb_lr = XGB_LR()
    fpr_gbdt_lr, tpr_gbdt_lr = GBDT_LR()
    fpr_lr, tpr_lr = LR()
    fpr_xgb, tpr_xgb = XGBoost()

    # plt.figure(1)
    plt.xlim(0, 0.2)
    plt.ylim(0.8, 1)
    plt.plot([0, 1], [0, 1], "k--")
    plt.plot(fpr_rf_lr, tpr_rf_lr, label="RF+LR")
    plt.plot(fpr_xgb_lr, tpr_xgb_lr, label="XGB+LR")
    plt.plot(fpr_gbdt_lr, tpr_gbdt_lr, label="GBDT+LR")
    plt.plot(fpr_lr, tpr_lr, label="LR")
    plt.plot(fpr_xgb, tpr_xgb, label="XGBoost")

    plt.xlabel("False positive rate")
    plt.ylabel("True positive rate")
    plt.legend(loc="best")

    plt.show()

# # gbc = GradientBoostingClassifier(loss='exponential',criterion='friedman_mse',presort='auto')
# gbc = GradientBoostingClassifier(loss='deviance',criterion='friedman_mse',presort='auto')
# gbc.fit(X_train,y_train)
#
#
# 6.测试数据
# y_pred = gbc.predict(X_test)
#
# 7. 模型检测
# print("classification report is: \n", classification_report(y_test,y_pred))
