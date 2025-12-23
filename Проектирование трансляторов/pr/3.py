EPS = "ε"


class Grammar:
    def __init__(self, productions, start):
        self.P = productions  # A -> list of RHS
        self.S = start
        self.N = list(productions.keys())

    # ----------------------------
    # УСТРАНЕНИЕ ЛЕВОЙ РЕКУРСИИ
    # ----------------------------
    def remove_left_recursion(self):
        new_P = {}

        original_nonterminals = list(self.P.keys())  # ← ТОЛЬКО исходные

        for i, Ai in enumerate(original_nonterminals):
            rules = self.P.get(Ai, [])

            # 1. Устранение косвенной левой рекурсии
            for j in range(i):
                Aj = original_nonterminals[j]
                updated_rules = []

                for r in rules:
                    if r and r[0] == Aj:
                        for gamma in new_P.get(Aj, []):
                            updated_rules.append(gamma + r[1:])
                    else:
                        updated_rules.append(r)

                rules = updated_rules

            # 2. Устранение непосредственной левой рекурсии
            alpha = []  # A → Aα
            beta = []   # A → β

            for r in rules:
                if r and r[0] == Ai:
                    alpha.append(r[1:])
                else:
                    beta.append(r)

            if alpha:
                A_prime = Ai + "'"
                while A_prime in new_P or A_prime in self.P:
                    A_prime += "'"

                new_P[Ai] = [b + [A_prime] for b in beta]
                new_P[A_prime] = [a + [A_prime] for a in alpha] + [["ε"]]
            else:
                new_P[Ai] = rules

        self.P = new_P


    def print(self):
        for A in self.P:
            rhs = ["".join(r) for r in self.P[A]]
            print(f"{A} → {' | '.join(rhs)}")


def test_left_recursion_1():
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

    g.remove_left_recursion()

    print("\nПосле устранения левой рекурсии:")
    g.print()


def test_left_recursion_2():
    print("\n=== ТЕСТ 2 ===")
    g = Grammar(
        productions={
            "S": [["a", "A", "B"], ["b", "A"], ["a"]],
            "A": [["A", "B"], ["S", "d"], ["c", "b"]],
            "B": [["B", "b"], ["c"]]
        },
        start="S"
    )

    print("Исходная грамматика:")
    g.print()

    g.remove_left_recursion()

    print("\nПосле устранения левой рекурсии:")
    g.print()


def test_left_recursion_3():
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

    g.remove_left_recursion()

    print("\nПосле устранения левой рекурсии:")
    g.print()


if __name__ == "__main__":
    test_left_recursion_1()
    test_left_recursion_2()
    test_left_recursion_3()
