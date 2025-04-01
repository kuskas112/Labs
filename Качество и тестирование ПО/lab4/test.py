from lab1 import astar
from lab1 import Node
import tkinter as tk
from math import sqrt
import heapq
class PathFindingGUI(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("A* Search Algorithm")
        self.geometry("500x500")  # Размер окна

        # Создаем канвас для отображения графа
        self.canvas = tk.Canvas(self, width=400, height=400, bg="white")
        self.canvas.pack(fill=tk.BOTH, expand=True)

        # Кнопки для запуска алгоритма и очистки экрана
        self.start_button = tk.Button(self, text="Start", command=self.run_astar)
        self.clear_button = tk.Button(self, text="Clear", command=self.clear_canvas)
        self.start_button.pack(side=tk.LEFT)
        self.clear_button.pack(side=tk.RIGHT)

        # Графические элементы для отображения путей
        self.path_lines = []

        # Словарь графа
        self.graph = {}

    def run_astar(self):
        # Пример графа
        nodes = {
            (1, 0): [(0, 1)],
            (0, 1): [(1, 0)],
        }

        start = Node(1, 0)
        goal = Node(1, 2)

        # Запускаем алгоритм A*
        path = astar(nodes, start, goal)
        if path:
            # Отображаем путь на экране
            for i in range(len(path) - 1):
                x1, y1 = path[i]
                x2, y2 = path[i+1]
                line = self.canvas.create_line(x1 * 50 + 25, y1 * 50 + 25, x2 * 50 + 25, y2 * 50 + 25, fill="blue")
                self.path_lines.append(line)
        else:
            print("Путь не найден.")

    def clear_canvas(self):
        for line in self.path_lines:
            self.canvas.delete(line)
        self.path_lines = []

# Запуск приложения
gui = PathFindingGUI()
gui.mainloop()