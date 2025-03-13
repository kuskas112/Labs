import heapq
from math import sqrt

class Node:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.g = float('inf')  # стоимость пути до этой вершины
        self.h = float('inf')  # эвристика (предполагаемая стоимость до цели)
        self.f = float('inf')  # суммарная стоимость f = g + h
        self.parent = None     # ссылка на предыдущего узла в пути

    def __hash__(self):
        return hash((self.x, self.y))  # Хэшируемые координаты

    def __eq__(self, other):
        return isinstance(other, Node) and self.x == other.x and self.y == other.y
    
    def __lt__(self, other):
        return self.f < other.f

def heuristic(a, b):
    """Эвклидова дистанция между двумя точками."""
    return sqrt((a.x - b.x)**2 + (a.y - b.y)**2)

def reconstruct_path(node):
    path = []
    while node is not None:
        path.append((node.x, node.y))
        node = node.parent
    return path[::-1]

def astar(graph, start_node, end_node):
    open_set = []  # Очередь с приоритетом (min-heap)
    closed_set = set()  # Множество посещенных узлов

    # Добавляем начальную вершину в очередь
    start_node.g = 0
    start_node.h = heuristic(start_node, end_node)
    start_node.f = start_node.g + start_node.h
    heapq.heappush(open_set, (start_node.f, start_node))
    
    while open_set:
        current_f, current_node = heapq.heappop(open_set)
        
        if current_node == end_node:
            return reconstruct_path(current_node)
        
        closed_set.add(current_node)
        
        for neighbor in graph.get(current_node, []):
            if neighbor in closed_set:
                continue
            
            tentative_g = current_node.g + heuristic(current_node, neighbor)
            
            if tentative_g < neighbor.g:
                neighbor.g = tentative_g
                neighbor.h = heuristic(neighbor, end_node)
                neighbor.f = neighbor.g + neighbor.h
                neighbor.parent = current_node
                
                if neighbor not in open_set:
                    heapq.heappush(open_set, (neighbor.f, neighbor))
    
    return None  # Путь не найден

if __name__ == '__main__':
    graph = {
        Node(0, 0): [Node(1, 0), Node(1, 1)],
        Node(1, 0): [Node(0, 0), Node(2, 0)],
        Node(2, 0): [Node(1, 0), Node(3, 0)],
        Node(1, 1): [Node(0, 0), Node(1, 2)],
        Node(3, 1): [Node(3, 0), Node(3, 2)],
        Node(1, 2): [Node(1, 1), Node(2, 2)],
        Node(2, 2): [Node(1, 2), Node(3, 2)],
        Node(3, 2): [Node(3, 1), Node(2, 2)],
    }

    start = Node(0, 0)
    goal = Node(3, 2)

    path = astar(graph, start, None)
    print(path)