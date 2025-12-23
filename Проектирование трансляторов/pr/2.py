from itertools import product

EPS = "ε"


class Grammar:
    def __init__(self, productions, start):
        self.P = productions  # A -> list of RHS
        self.S = start
        self.N = set(productions.keys())

    # ----------------------------
    # УСТРАНЕНИЕ ε-ПРАВИЛ
    # ----------------------------
    def remove_epsilon_rules(self):
        nullable = set()

        # 1. Найти укорачивающие нетерминалы
        changed = True
        while changed:
            changed = False
            for A, rules in self.P.items():
                if A in nullable:
                    continue
                for r in rules:
                    if r == [EPS] or all(x in nullable for x in r):
                        nullable.add(A)
                        changed = True

        new_P = {}

        # 2. Построить новые правила
        for A, rules in self.P.items():
            new_rules = set()
            for r in rules:
                if r == [EPS]:
                    continue

                positions = [i for i, x in enumerate(r) if x in nullable]
                for mask in product([0, 1], repeat=len(positions)):
                    temp = r[:]
                    for bit, pos in zip(mask, positions):
                        if bit == 0:
                            temp[pos] = None
                    temp = [x for x in temp if x is not None]
                    if temp:
                        new_rules.add(tuple(temp))
            new_P[A] = [list(r) for r in new_rules]

        self.P = new_P

    # ----------------------------
    # УСТРАНЕНИЕ ЦЕПНЫХ ПРАВИЛ
    # ----------------------------
    def remove_chain_rules(self):
        chain = {A: set() for A in self.N}

        # 1. Цепная достижимость
        for A in self.N:
            stack = [A]
            while stack:
                X = stack.pop()
                for r in self.P.get(X, []):
                    if len(r) == 1 and r[0] in self.N:
                        if r[0] not in chain[A]:
                            chain[A].add(r[0])
                            stack.append(r[0])

        # 2. Добавить нецепные правила
        new_P = {A: [] for A in self.N}
        for A in self.N:
            for B in chain[A] | {A}:
                for r in self.P.get(B, []):
                    if not (len(r) == 1 and r[0] in self.N):
                        if r not in new_P[A]:
                            new_P[A].append(r)

        self.P = new_P

    def print(self):
        for A in self.P:
            rhs = ["".join(r) for r in self.P[A]]
            print(f"{A} → {' | '.join(rhs)}")

print("=== ТЕСТ 1: Устранение ε-правил ===")

g1 = Grammar(
    productions={
        "S": [["A", "B"]],
        "A": [["S", "A"], ["B", "B"], ["b", "B"]],
        "B": [["b"], ["a", "A"], ["ε"]]
    },
    start="S"
)

print("Исходная грамматика:")
g1.print()

g1.remove_epsilon_rules()

print("\nПосле устранения ε-правил:")
g1.print()

print("\n=== ТЕСТ 2: Устранение ε-правил ===")

g2 = Grammar(
    productions={
        "S": [["a", "A", "B"], ["b", "A"], ["ε"]],
        "A": [["a", "A", "B"], ["ε"]],
        "B": [["b", "B"], ["c"]]
    },
    start="S"
)

print("Исходная грамматика:")
g2.print()

g2.remove_epsilon_rules()

print("\nПосле устранения ε-правил:")
g2.print()

print("\n=== ТЕСТ 3: Устранение цепных правил ===")

g3 = Grammar(
    productions={
        "S": [["S", "or", "T"], ["T"]],
        "T": [["T", "and", "E"], ["E"]],
        "E": [["not", "E"], ["F"]],
        "F": [["(", "S", ")"], ["b"]]
    },
    start="S"
)

print("Исходная грамматика:")
g3.print()

g3.remove_chain_rules()

print("\nПосле устранения цепных правил:")
g3.print()

print("\n=== ТЕСТ 4: Устранение цепных правил ===")

g4 = Grammar(
    productions={
        "S": [["L", "A"], ["L", "B"]],
        "L": [["P", ":="], ["Q", ":="]],
        "A": [["F"]],
        "B": [["F"]],
        "P": [["i"]],
        "Q": [["j"]],
        "F": [["Q", "(", "i", ")"]]
    },
    start="S"
)

print("Исходная грамматика:")
g4.print()

g4.remove_chain_rules()

print("\nПосле устранения цепных правил:")
g4.print()
