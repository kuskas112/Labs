import pytest
from lab1 import *


def test_openset_not_none():
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

    path = astar(graph, start, goal)
    assert path is not None

def test_start_is_not_Node():
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

    goal = Node(3, 2)

    path = astar(graph, 24, goal)
    assert path is None

def test_end_is_not_Node():
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

    path = astar(graph, start, 33)
    assert path is None

def test_start_is_goal():
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
    goal = Node(0, 0)

    path = astar(graph, start, goal)

    assert path == [(0, 0)]

def test_node_not_in_graph():
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

    start = Node(4, 0)
    goal = Node(0, 0)

    path = astar(graph, start, goal)
    assert path == None

def test_cycle():
    graph = {
        Node(0, 0): [Node(1, 0), Node(0, 1)],
        Node(1, 0): [Node(0, 0), Node(2, 0)],
        Node(2, 0): [Node(1, 0), Node(3, 0), Node(2, 1)],
        Node(2, 1): [Node(2, 0), Node(3, 0)],
        Node(0, 1): [Node(0, 0), Node(0, 2)],
        Node(0, 2): [Node(0, 1), Node(1, 2)],
        Node(1, 2): [Node(0, 2), Node(2, 2)],
        Node(2, 2): [Node(1, 2), Node(3, 2)],
        Node(3, 0): [Node(2, 0), Node(2, 1)],
        Node(3, 2): [Node(2, 2)],
    }

    start = Node(1, 0)
    goal = Node(3, 2)

    path = astar(graph, start, goal)
    assert path == [(1, 0), (0, 0), (0, 1), (0, 2), (1, 2), (2, 2), (3, 2)]

def test_duplicates():
    graph = {
        Node(1, 0): [Node(1, 1), Node(0, 1)],
        Node(1, 1): [Node(1, 0), Node(0, 1)],
        Node(0, 1): [Node(1, 0), Node(1, 1), Node(1, 2)],
        Node(1, 2): [Node(0, 1)],
    }

    start = Node(1, 0)
    goal = Node(1, 2)

    path = astar(graph, start, goal)
    assert path == [(1, 0), (0, 1), (1, 2)]

def test_multiple_ways():
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

    path = astar(graph, start, goal)
    assert path == [(0, 0), (1, 1), (1, 2), (2, 2), (3, 2)]

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

    path = astar(graph, start, goal)
    assert path == [(0, 0), (1, 1), (1, 2), (2, 2), (3, 2)]