import torch
from torch.utils import data
from d2l import torch as d2l
from torch import nn


# def synthetic_data(w, b, num_examples):
#     X = torch.normal(0, 1, (num_examples, len(w)))
#     y = torch.matmul(X, w.float().reshape((-1, 1))) + b.float()
#     y += torch.normal(0, 0.01, y.shape)
#     return X, y
#
#
# true_w = torch.tensor([2, -3, 4], dtype=torch.float)  # Ensure true_w is of type float
# true_b = 4.2
# features, labels = d2l.synthetic_data(true_w, true_b, 1000)

def synthetic_data(w, b, num_examples):
    X = torch.normal(0, 1, (num_examples, len(w)))
    y = torch.matmul(X, w.reshape((-1, 1))) + b
    y += torch.normal(0, 0.01, y.shape)
    return X, y


true_w = torch.tensor([2, -3, 4], dtype=torch.float)
true_b = 4.2
features, labels = synthetic_data(true_w, true_b, 1000)


def load_array(data_array, batch_size, is_train=True):
    dataset = data.TensorDataset(*data_array)
    return data.DataLoader(dataset, batch_size, shuffle=is_train)


batch_size = 10
data_iter = load_array((features, labels), batch_size)

net = nn.Sequential(nn.Linear(3, 1))  # Change input size to 3 to match your data
net[0].weight.data.normal_(0, 0.01)
net[0].bias.data.fill_(0)  # Use data instead of fill_

# Define loss function
loss = nn.MSELoss()

# Define optimization algorithm
trainer = torch.optim.SGD(net.parameters(), lr=0.03)

# Training
num_epochs = 3
for epoch in range(num_epochs):
    for X, y in data_iter:
        l = loss(net(X), y)
        trainer.zero_grad()
        l.backward()
        trainer.step()
    l = loss(net(features), labels)
    print(f'epoch {epoch + 1}, loss {l.item():f}')

w = net[0].weight.data
print('Estimated w:', w)

b = net[0].bias.data
print('Estimated b:', b)
