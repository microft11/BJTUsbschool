import numpy as np
from collections import defaultdict, Counter
import chardet
import random

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

def preprocess_train_data(filename, sample_size=None):
    sentences = load_data(filename)
    if sample_size:
        sentences = sentences[:sample_size]
    
    print("Sample sentences from data:")
    for i in range(min(5, len(sentences))):
        print(sentences[i].encode('gbk', errors='ignore').decode('gbk'))
    
    data = []
    for sentence in sentences:
        words, tags = tokenize(sentence)
        if words and tags:
            data.append(list(zip(words, tags)))
        else:
            print(f"Skipping sentence: {sentence.strip().encode('gbk', errors='ignore').decode('gbk')}")

    print(f"Processed {len(data)} sentences from {filename}")
    return data

# 处理数据，计算词频
def process_data(data):
    word_counts = Counter()
    for sentence in data:
        words, tags = sentence
        for word, tag in zip(words, tags):
            word_counts[word] += 1
    return word_counts

# 构建词表（词典）
def build_vocab(word_counts):
    return {word: freq for word, freq in word_counts.most_common()}

# 计算初始概率，转移概率，发射概率
def train_hmm(data):
    transition_counts = defaultdict(lambda: defaultdict(int))
    emission_counts = defaultdict(lambda: defaultdict(int))
    state_counts = defaultdict(int)
    
    for words, tags in data:
        prev_state = None
        for word, state in zip(words, tags):
            state_counts[state] += 1
            emission_counts[state][word] += 1
            if prev_state:
                transition_counts[prev_state][state] += 1
            prev_state = state
    
    total_states = sum(state_counts.values())
    initial_prob = {state: count / total_states for state, count in state_counts.items()}
    
    transition_prob = defaultdict(dict)
    for prev_state, next_states in transition_counts.items():
        total = sum(next_states.values())
        for next_state, count in next_states.items():
            transition_prob[prev_state][next_state] = count / total
    
    emission_prob = defaultdict(dict)
    for state, emissions in emission_counts.items():
        total = sum(emissions.values())
        for word, count in emissions.items():
            emission_prob[state][word] = count / total
    
    # 输出训练信息
    print("Initial Probability:")
    for state, prob in initial_prob.items():
        print(f"{state}: {prob}")

    print("\nTransition Probability:")
    for prev_state, next_states in transition_prob.items():
        for next_state, prob in next_states.items():
            print(f"{prev_state} -> {next_state}: {prob}")

    # print("\nEmission Probability:")
    # for state, emissions in emission_prob.items():
    #     for word, prob in emissions.items():
    #         print(f"{state} emits {word}: {prob}")
    
    return initial_prob, transition_prob, emission_prob


# Viterbi算法进行分词
def viterbi(obs, states, start_p, trans_p, emit_p):
    if not obs:
        return []
    
    V = [{}]
    path = {}

    # Initialize base cases (t == 0)
    for y in states:
        V[0][y] = start_p.get(y, 0) * emit_p[y].get(obs[0], 0)
        path[y] = [y]

    # Run Viterbi for t > 0
    for t in range(1, len(obs)):
        V.append({})
        new_path = {}

        for y in states:
            prob, state = max((V[t-1][y0] * trans_p[y0].get(y, 0) * emit_p[y].get(obs[t], 0), y0) for y0 in states)
            V[t][y] = prob
            new_path[y] = path[state] + [y]

        path = new_path

    # Find the final most probable path
    n = len(obs) - 1
    prob, state = max((V[n][y], y) for y in states)
    return path[state]

# 性能评估
def evaluate(predicted, actual):
    correct = sum(p == a for p, a in zip(predicted, actual))
    total_predicted = len(predicted)
    total_actual = len(actual)

    precision = correct / total_predicted if total_predicted else 0
    recall = correct / total_actual if total_actual else 0
    f_measure = 2 * precision * recall / (precision + recall) if precision + recall else 0
    
    return precision, recall, f_measure

def preprocess_train_data(filename, sample_size=None):
    sentences = load_data(filename)
    if sample_size:
        sentences = random.sample(sentences, sample_size)
    
    data = []
    for sentence in sentences:
        words, tags = tokenize(sentence)
        data.append((words, tags))
    
    return data

# 分割数据集为训练集和测试集
def split_data(data, split_ratio=0.75):
    split_index = int(len(data) * split_ratio)
    train_data = data[:split_index]
    test_data = data[split_index:]
    return train_data, test_data


all_data = preprocess_train_data('train_pd.txt', sample_size=1000)
train_data, test_data = split_data(all_data)

word_counts = process_data(train_data)
vocab = build_vocab(word_counts)
initial_prob, transition_prob, emission_prob = train_hmm(train_data)

# 预测测试数据
obs = [word for sentence, _ in test_data for word in sentence]
actual_tags = [tag for _, tags in test_data for tag in tags]
states = ['B', 'I']
predicted_tags = viterbi(obs, states, initial_prob, transition_prob, emission_prob)

# 评估性能
precision, recall, f_measure = evaluate(predicted_tags, actual_tags)
print("Precision:", precision)
print("Recall:", recall)
print("F-measure:", f_measure)
