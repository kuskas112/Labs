from copy import deepcopy

EPS = "ε"


class Grammar:
    def __init__(self, terminals, nonterminals, productions, start):
        self.T = set(terminals)
        self.N = set(nonterminals)
        self.P = productions  # dict: A -> list of right sides
        self.S = start

    def remove_barren_symbols(self):
        """Удаление бесплодных символов"""
        productive = set()

        # Шаг 1: правила вида A -> a
        changed = True
        while changed:
            changed = False
            for A in self.N:
                if A in productive:
                    continue
                for prod in self.P.get(A, []):
                    if all(symbol in self.T or symbol == EPS or symbol in productive
                           for symbol in prod):
                        productive.add(A)
                        changed = True
                        break

        # Удаляем бесплодные нетерминалы
        self.N = productive
        self.P = {
            A: [
                prod for prod in prods
                if all(symbol in self.T or symbol == EPS or symbol in productive
                       for symbol in prod)
            ]
            for A, prods in self.P.items() if A in productive
        }

    def remove_unreachable_symbols(self):
        """Удаление недостижимых символов"""
        reachable = {self.S}
        changed = True

        while changed:
            changed = False
            for A in list(reachable):
                for prod in self.P.get(A, []):
                    for symbol in prod:
                        if symbol in self.N and symbol not in reachable:
                            reachable.add(symbol)
                            changed = True

        self.N = reachable
        self.P = {A: self.P[A] for A in self.P if A in reachable}

    def reduce(self):
        """Приведение грамматики"""
        self.remove_barren_symbols()
        self.remove_unreachable_symbols()

    def print(self):
        print("Нетерминалы:", self.N)
        print("Терминалы:", self.T)
        print("Начальный символ:", self.S)
        print("Правила:")
        for A in self.P:
            rhs = ["".join(p) for p in self.P[A]]
            print(f"  {A} → {' | '.join(rhs)}")


# ======================
# ПРИМЕР ИЗ ЗАДАНИЯ №1
# ======================

grammar1 = Grammar(
    terminals={"a", "b", "c"},
    nonterminals={"A", "B", "C", "D", "E", "F", "G", "S"},
    start="S",
    productions={
        "S": [["a", "A", "b", "B"], ["E"]],
        "A": [["B", "C", "a"], ["a"]],
        "B": [["A", "C", "b"], ["b"]],
        "C": [["A"], ["B"], ["b", "A"], ["a", "B"], ["c", "C"], ["a", "E"], ["b", "E"]],
        "D": [["c"], ["F", "b"], ["F", "a"]],
        "E": [["E", "a"], ["E", "b"], ["E", "c"], ["E", "D"], ["F", "G"], ["D", "G"]],
        "F": [["B", "C"], ["A", "C"], ["D", "C"], ["E", "C"]],
        "G": [["G", "a"], ["G", "b"], ["G", "c"], ["G", "D"]],
    }
)

print("Исходная грамматика:")
grammar1.print()

grammar1.reduce()

print("\nПриведённая грамматика:")
grammar1.print()
