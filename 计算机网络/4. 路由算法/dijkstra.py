import heapq

class Graph:
    def __init__(self):
        self.edges = {}
    
    def add_edge(self, from_node, to_node, weight):
        if from_node not in self.edges:
            self.edges[from_node] = []
        self.edges[from_node].append((to_node, weight))
        if to_node not in self.edges:
            self.edges[to_node] = []
        self.edges[to_node].append((from_node, weight))  # 若是无向图

def dijkstra(graph, start):
    queue = [(0, start)]
    distances = {start: 0}
    path = {}
    
    while queue:
        (current_distance, current_node) = heapq.heappop(queue)
        
        for neighbor, weight in graph.edges.get(current_node, []):
            distance = current_distance + weight
            if neighbor not in distances or distance < distances[neighbor]:
                distances[neighbor] = distance
                heapq.heappush(queue, (distance, neighbor))
                path[neighbor] = current_node
    
    return distances, path

# 示例使用
graph = Graph()
edges = [
    ('A', 'B', 1),
    ('A', 'C', 4),
    ('B', 'C', 2),
    ('B', 'D', 5),
    ('C', 'D', 1)
]

for edge in edges:
    graph.add_edge(*edge)

distances, path = dijkstra(graph, 'A')
print("Shortest distances from A:", distances)
print("Paths:", path)
