import numpy as np
import random
import chardet
from collections import defaultdict, Counter
from sklearn.model_selection import train_test_split
from sklearn.metrics import precision_score, recall_score, f1_score
from sklearn_crfsuite import CRF

# 数据预处理
def detect_encoding(filename):
    with open(filename, 'rb') as file:
        raw_data = file.read()
    result = chardet.detect(raw_data)
    return result['encoding']

def load_data(filename, encoding=None):
    if encoding is None:
        encoding = detect_encoding(filename)
    print(f"Detected encoding: {encoding}")
    with open(filename, 'r', encoding=encoding, errors='ignore') as file:
        lines = file.readlines()
    print(f"Loaded {len(lines)} lines from {filename}")
    return lines

def tokenize(sentence):
    words_tags = sentence.strip().split()
    words = [wt.split('/')[0] for wt in words_tags]
    tags = [wt.split('/')[-1] for wt in words_tags]
    return words, tags

def preprocess_data(filename, sample_size=None):
    sentences = load_data(filename)
    if sample_size:
        sentences = random.sample(sentences, sample_size)
    
    data = []
    for sentence in sentences:
        words, tags = tokenize(sentence)
        data.append(list(zip(words, tags)))
    
    return data

# Feature Extraction
def word2features(sent, i):
    word = sent[i][0]

    features = {
        'bias': 1.0,
        'word': word,
        'word.lower()': word.lower(),
        'word[-3:]': word[-3:],
        'word[-2:]': word[-2:],
        'word.isupper()': word.isupper(),
        'word.istitle()': word.istitle(),
        'word.isdigit()': word.isdigit(),
    }
    if i > 0:
        prev_word = sent[i-1][0]
        features.update({
            '-1:word.lower()': prev_word.lower(),
            '-1:word.istitle()': prev_word.istitle(),
            '-1:word.isupper()': prev_word.isupper(),
        })
    else:
        features['BOS'] = True

    if i < len(sent)-1:
        next_word = sent[i+1][0]
        features.update({
            '+1:word.lower()': next_word.lower(),
            '+1:word.istitle()': next_word.istitle(),
            '+1:word.isupper()': next_word.isupper(),
        })
    else:
        features['EOS'] = True

    return features

def sent2features(sent):
    return [word2features(sent, i) for i in range(len(sent))]

def sent2labels(sent):
    return [label for token, label in sent]

def sent2tokens(sent):
    return [token for token, label in sent]

# 示例实验代码
data = preprocess_data('train_pd.txt')

# Splitting data into train and test sets
train_data, test_data = train_test_split(data, test_size=0.2)

X_train = [sent2features(s) for s in train_data]
y_train = [sent2labels(s) for s in train_data]

X_test = [sent2features(s) for s in test_data]
y_test = [sent2labels(s) for s in test_data]

# Train CRF model
modelfile_name = 'model_crf.utf8'  # 显式指定模型文件名编码为UTF-8
crf = CRF(
    algorithm='lbfgs',
    c1=0.1,
    c2=0.1,
    max_iterations=100,
    all_possible_transitions=True
)
crf.fit(X_train, y_train)

# Save trained model
crf.save(modelfile_name)

# Predicting
y_pred = crf.predict(X_test)

# Flatten the nested lists
y_test_flat = [label for sublist in y_test for label in sublist]
y_pred_flat = [label for sublist in y_pred for label in sublist]

# Evaluation
precision = precision_score(y_test_flat, y_pred_flat, average='weighted')
recall = recall_score(y_test_flat, y_pred_flat, average='weighted')
f1 = f1_score(y_test_flat, y_pred_flat, average='weighted')

print("Precision:", precision)
print("Recall:", recall)
print("F1 Score:", f1)
