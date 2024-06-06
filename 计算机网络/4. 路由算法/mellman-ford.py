class Graph:
    def __init__(self):
        self.edges = []

    def add_edge(self, from_node, to_node, weight):
        self.edges.append((from_node, to_node, weight))

def bellman_ford(graph, start):
    distances = {start: 0}
    path = {}

    for _ in range(len(graph.edges)):
        updated = False
        for from_node, to_node, weight in graph.edges:
            if from_node in distances and (to_node not in distances or distances[from_node] + weight < distances[to_node]):
                distances[to_node] = distances[from_node] + weight
                path[to_node] = from_node
                updated = True
        if not updated:
            break

    # 检测负权重循环
    for from_node, to_node, weight in graph.edges:
        if from_node in distances and distances[from_node] + weight < distances[to_node]:
            raise ValueError("Graph contains a negative-weight cycle")

    return distances, path

# 示例使用
graph = Graph()
edges = [
    ('A', 'B', 1),
    ('A', 'C', 4),
    ('B', 'C', 2),
    ('B', 'D', 5),
    ('C', 'D', 1),
    ('D', 'E', -10)
]

for edge in edges:
    graph.add_edge(*edge)

try:
    distances, path = bellman_ford(graph, 'A')
    print("Shortest distances from A:", distances)
    print("Paths:", path)
except ValueError as e:
    print(e)
