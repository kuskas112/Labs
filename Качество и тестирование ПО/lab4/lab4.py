from tkinter import *
from lab1 import *
import heapq
from math import sqrt

class Button():
    def __init__(self, x=None, y=None):
        if x is not None and y is not None:
            self.x = x
            self.y = y
        self.width = 100
        self.height = 50
        global canvas
        self.canvas = canvas
    def pointInBounds(self, x, y):
        if (
            (self.x < x < self.x + self.width) and
            (self.y < y < self.y + self.height)
        ):
            return True
        return False

    def draw(self):
        self.id = canvas.create_rectangle(self.x, self.y, self.x+self.width, self.y+self.height, fill="lightblue", outline="black")
        canvas.create_text(self.x + self.width / 2, self.y + self.height / 2, text='Далее')

class Node():
    def __init__(self, x=None, y=None):
        if x is not None and y is not None:
            self.x = x
            self.y = y
        self.size = 30
        self.neibs = set()
        self.color = 'blue'
        self.lineColor = 'black'
        self.number = None
        global canvas
        self.canvas = canvas
        self.g = float('inf')  # стоимость пути до этой вершины
        self.h = float('inf')  # эвристика (предполагаемая стоимость до цели)
        self.f = float('inf')  # суммарная стоимость f = g + h
        self.parent = None     # ссылка на предыдущего узла в пути

    def addNeib(self, node):
        if (node == self): return
        self.neibs.add(node)
        node.neibs.add(self)
    
    def pointInBounds(self, x, y):
        radius = self.size / 2
        centerX = self.x + radius
        centerY = self.y + radius
        distanceSquared = (x - centerX)**2 + (y - centerY)**2
        if (distanceSquared <= radius**2):
            return True
        return False

    def drawLineToNode(self, node):
        xFrom = self.x + self.size/2
        yFrom = self.y + self.size/2

        xTo = node.x + node.size/2
        yTo = node.y + node.size/2
        self.canvas.create_line(xFrom, yFrom, xTo, yTo, fill=self.lineColor)
    
    def drawLinesToNeibs(self):
        for neib in self.neibs:
            self.drawLineToNode(neib)
    
    def draw(self):
        self.id = self.canvas.create_oval(self.x, self.y, self.x+self.size, self.y+self.size, fill=self.color, width=1)
        if(self.number is not None):
            canvas.create_text(self.x, self.y, text=self.number)
    
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
        path.append(node)
        node = node.parent
    return path[::-1]

def astar(graph, start_node, end_node):

    if(isinstance(start_node, Node) == False or isinstance(end_node, Node) == False):
        return None

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


# Создание главного окна
root = Tk()
root.title("Lab 4")

winWidth = 600
winHeight = 500

# Создание холста для рисования
canvas = Canvas(root, width=winWidth, height=winHeight, bg="white")
canvas.pack()

nodes = []
states = [
    'Построение',
    'Выбор точек',
    'Отрисовка пути'
]
currState = 0

def drawGraph():
    global canvas
    global nodes
    for i in range(len(nodes)):
        nodes[i].draw()
    for i in range(len(nodes)):
        nodes[i].drawLinesToNeibs()
    canvas.create_rectangle(0,0,200,30,fill='white')
    canvas.create_text(100,10,text=states[currState])
    

drawGraph()
selectedNode = None

start = None
end = None
resultId = None

def on_mouse_click(event):
    global selectedNode
    global nodes
    global states
    global currState
    global button
    global start
    global end
    global resultId
    currentState = states[currState]
    if(currentState == 'Построение'):
        if(button.pointInBounds(event.x, event.y)): return
        for node in nodes:
            if (node.pointInBounds(event.x, event.y)):
                if(selectedNode):
                    selectedNode.addNeib(node)
                    selectedNode.color = 'blue'
                    selectedNode = None
                else:
                    selectedNode = node
                    node.color = 'green'
                break
        else: #no Node clicked
            newNode = Node(event.x, event.y)
            newNode.x = newNode.x - newNode.size / 2
            newNode.y = newNode.y - newNode.size / 2
            newNode.number = len(nodes) + 1
            nodes.append(newNode)
    elif(currentState == 'Выбор точек'):
        if(button.pointInBounds(event.x, event.y)): return
        for node in nodes:
            if (node.pointInBounds(event.x, event.y)):
                if(selectedNode):
                    start = selectedNode
                    end = node
                    selectedNode.color = 'blue'
                    selectedNode = None
                else:
                    selectedNode = node
                    node.color = 'green'
                break
    elif(currentState == 'Отрисовка пути'):
        graph = {node: node.neibs for node in nodes}
        path = astar(graph, start, end)
        resultId = drawResult(path)
        if path is not None:
            for node in nodes:
                if (node in path):
                    node.color = 'red'
    drawGraph()

def button_click(event):
    global states
    global currState
    global resultId
    currState = (currState + 1) % len(states)
    if(currState == 0):
        if(resultId):
            canvas.delete(resultId)
            resultId = None
        for node in nodes:
            if node.color == 'red': node.color = 'blue'
    drawGraph()

def drawResult(nodes):
    nodesNumbers = [node.number for node in nodes]
    result = ', '.join(map(str, nodesNumbers))
    return canvas.create_text(250, 15, text=f'Путь: {result}')

button = Button(500, 400)
button.draw()

canvas.tag_bind(button.id, "<Button-1>", button_click)

canvas.bind("<Button-1>", on_mouse_click)

root.mainloop()