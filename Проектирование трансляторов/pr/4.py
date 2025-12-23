EPS = "ε"


class Grammar:
    def __init__(self, productions, start):
        self.P = productions
        self.S = start
        self.N = set(productions.keys())
        self.counter = 0

    def new_nonterminal(self):
        self.counter += 1
        return f"X{self.counter}"

    # ----------------------------
    # ШАГ 1–2 предполагаются выполненными ранее
    # (ε и цепные правила устранены)
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
        
    # ----------------------------
    # ЗАМЕНА ТЕРМИНАЛОВ В ДЛИННЫХ ПРАВИЛАХ
    # ----------------------------
    def replace_terminals(self):
        new_P = {}
        terminal_map = {}

        for A, rules in self.P.items():
            new_P.setdefault(A, [])
            for r in rules:
                if len(r) == 1:
                    new_P[A].append(r)
                else:
                    new_r = []
                    for sym in r:
                        if sym.islower() or sym in ["or", "and", "not", "(", ")"]:
                            if sym not in terminal_map:
                                X = self.new_nonterminal()
                                terminal_map[sym] = X
                                new_P[X] = [[sym]]
                            new_r.append(terminal_map[sym])
                        else:
                            new_r.append(sym)
                    new_P[A].append(new_r)

        self.P = new_P

    # ----------------------------
    # РАЗБИЕНИЕ ПРАВИЛ ДЛИНЫ > 2
    # ----------------------------
    def binarize(self):
        new_P = {}

        for A, rules in self.P.items():
            new_P.setdefault(A, [])
            for r in rules:
                if len(r) <= 2:
                    new_P[A].append(r)
                else:
                    current = r
                    prev = A
                    while len(current) > 2:
                        X = self.new_nonterminal()
                        new_P.setdefault(prev, []).append([current[0], X])
                        prev = X
                        current = current[1:]
                    new_P.setdefault(prev, []).append(current)

        self.P = new_P

    def to_cnf(self):
        self.replace_terminals()
        self.binarize()

    def print(self):
        for A in self.P:
            rhs = [" ".join(r) for r in self.P[A]]
            print(f"{A} → {' | '.join(rhs)}")



def is_cnf(grammar):
    for A, rules in grammar.P.items():
        for r in rules:
            # A → a
            if len(r) == 1:
                if not r[0].islower() and r[0] not in ["or", "and", "not", "(", ")"]:
                    return False
            # A → BC
            elif len(r) == 2:
                if not (r[0].isupper() and r[1].isupper()):
                    return False
            else:
                return False
    return True

def test_cnf_1():
    print("\n=== ТЕСТ 1 ===")

    g = Grammar(
        productions={
            "S": [["S", "a", "A"], ["A", "A"], ["b"]],
            "A": [["A", "S", "a"], ["A", "d"], ["c"]]
        },
        start="S"
    )

    print("Исходная грамматика:")
    g.print()

    g.to_cnf()

    print("\nГрамматика в НФХ:")
    g.print()

    print("\nПроверка НФХ:", is_cnf(g))

def test_cnf_2():
    print("\n=== ТЕСТ 2 ===")

    g = Grammar(
        productions={
            "S": [["a", "A", "B"], ["b", "A"], ["a"]],
            "A": [["A", "B"], ["B"], ["c", "b"]],
            "B": [["B", "b"], ["c"]]
        },
        start="S"
    )

    print("Исходная грамматика:")
    g.print()

    g.to_cnf()

    print("\nГрамматика в НФХ:")
    g.print()

    print("\nПроверка НФХ:", is_cnf(g))


def test_cnf_3():
    print("\n=== ТЕСТ 3 ===")

    g = Grammar(
        productions={
            "S": [["S", "or", "T"], ["T"]],
            "T": [["T", "and", "E"], ["E"]],
            "E": [["not", "E"], ["F"]],
            "F": [["(", "S", ")"], ["b"]]
        },
        start="S"
    )

    print("Исходная грамматика:")
    g.print()

    g.to_cnf()

    print("\nГрамматика в НФХ:")
    g.print()

    print("\nПроверка НФХ:", is_cnf(g))


if __name__ == "__main__":
    test_cnf_1()
    test_cnf_2()
    test_cnf_3()
