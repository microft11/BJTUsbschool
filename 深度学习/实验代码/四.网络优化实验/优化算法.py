import time
import matplotlib.pyplot as plt
import numpy as np
import torch
import torch.nn as nn
import torchvision
from torch.nn.functional import cross_entropy, binary_cross_entropy
from torch.nn import CrossEntropyLoss
from torchvision import transforms
from sklearn import metrics


# 手动实现RMSprop算法
# 初始化
def init_rmsprop(params):
    s_w1, s_b1, s_w2, s_b2 = torch.zeros(params[0].shape), torch.zeros(params[1].shape), \
                             torch.zeros(params[2].shape), torch.zeros(params[3].shape)
    return s_w1, s_b1, s_w2, s_b2


# 对每一个参数进行RMSprop法
def rmsprop(params, states, lr=0.01, gamma=0.9):
    gamma, eps = gamma, 1e-6
    for p, s in zip(params, states):
        with torch.no_grad():
            s[:] = gamma * s + (1 - gamma) * torch.square(p.grad)
            p[:] -= lr * p.grad / torch.sqrt(s + eps)
        p.grad.data.zero_()


# 手动实现Momentum算法
# 初始化
def init_momentum(params):
    v_w1, v_b1, v_w2, v_b2 = torch.zeros(params[0].shape), torch.zeros(params[1].shape), \
                             torch.zeros(params[2].shape), torch.zeros(params[3].shape)
    return v_w1, v_b1, v_w2, v_b2


# 对每一个参数进行momentum法
def sgd_momentum(params, states, lr=0.01, momentum=0.5):
    for p, v in zip(params, states):
        with torch.no_grad():
            v[:] = momentum * v - p.grad
            p[:] += lr * v
        p.grad.data.zero_()


# 手动实现Adam算法
def init_adam_states(params):
    v_w1, v_b1, v_w2, v_b2 = torch.zeros(params[0].shape), torch.zeros(params[1].shape), \
                             torch.zeros(params[2].shape), torch.zeros(params[3].shape)
    s_w1, s_b1, s_w2, s_b2 = torch.zeros(params[0].shape), torch.zeros(params[1].shape), \
                             torch.zeros(params[2].shape), torch.zeros(params[3].shape)
    return (v_w1, s_w1), (v_b1, s_b1), (v_w2, s_w2), (v_b2, s_b2)


# 根据Adam算法思想手动实现Adam
Adam_t = 0.01


def Adam(params, states, lr=0.01, t=Adam_t):
    global Adam_t
    beta1, beta2, eps = 0.9, 0.999, 1e-6
    for p, (v, s) in zip(params, states):
        with torch.no_grad():
            v[:] = beta1 * v + (1 - beta1) * p.grad
            s[:] = beta2 * s + (1 - beta2) * (p.grad ** 2)
            v_bias_corr = v / (1 - beta1 ** Adam_t)
            s_bias_corr = s / (1 - beta2 ** Adam_t)
        p.data -= lr * v_bias_corr / (torch.sqrt(s_bias_corr + eps))
    p.grad.data.zero_()
    Adam_t += 1
