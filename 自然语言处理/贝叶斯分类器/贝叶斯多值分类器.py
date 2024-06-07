import numpy as np
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score
from sklearn.naive_bayes import MultinomialNB
from sklearn.datasets import fetch_20newsgroups

class NaiveBayesMulticlassClassifier:
    def fit(self, X, y):
        self.classes = np.unique(y)
        self.priors = np.zeros(len(self.classes))
        self.conditional_probs = np.zeros((len(self.classes), X.shape[1]))

        for idx, cls in enumerate(self.classes):
            cls_indices = np.where(y == cls)
            self.priors[idx] = len(cls_indices[0]) / len(y)
            self.conditional_probs[idx, :] = (np.sum(X[cls_indices], axis=0) + 1) / (len(cls_indices[0]) + 2)

    def predict(self, X):
        predictions = []
        for x in X:
            log_probs = []
            for idx, cls in enumerate(self.classes):
                log_prob = np.log(self.priors[idx])
                log_prob += np.sum(x * np.log(self.conditional_probs[idx, :]) + (1 - x) * np.log(1 - self.conditional_probs[idx, :]))
                log_probs.append(log_prob)
            predictions.append(self.classes[np.argmax(log_probs)])
        return np.array(predictions)

# 数据预处理与评估函数
def preprocess_and_evaluate_multiclass(data, target, test_size=0.2):
    vectorizer = CountVectorizer()
    X = vectorizer.fit_transform(data)
    y = np.array(target)

    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=test_size, random_state=42)
    
    classifier = MultinomialNB()
    classifier.fit(X_train, y_train)
    y_pred = classifier.predict(X_test)

    accuracy = accuracy_score(y_test, y_pred)
    precision = precision_score(y_test, y_pred, average='macro')
    recall = recall_score(y_test, y_pred, average='macro')
    f1 = f1_score(y_test, y_pred, average='macro')

    return accuracy, precision, recall, f1

# 测试多值分类器
newsgroups = fetch_20newsgroups(subset='all')

accuracy, precision, recall, f1 = preprocess_and_evaluate_multiclass(newsgroups.data, newsgroups.target)
print(f"Accuracy: {accuracy}")
print(f"Precision: {precision}")
print(f"Recall: {recall}")
print(f"F1 Score: {f1}")
