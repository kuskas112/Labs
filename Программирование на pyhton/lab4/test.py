import random
class RandomizedSet:

    def __init__(self):
        self.table = {}

    def insert(self, val: int) -> bool:
        try:
            self.table[val] += 1
            return False
        except KeyError:
            self.table[val] = 1
            return True

    def remove(self, val: int) -> bool:
        try:
            self.table[val] += 1
            self.table.pop(val)
            return True
        except KeyError:
            return False
    def getRandom(self) -> int:
        randInt = random.randint(0, len(self.table.keys())-1)
        randKey = list(self.table.keys())[randInt]
        return randKey



obj = RandomizedSet()
val = 20
val2 = 30
param_1 = obj.insert(val)
param_2 = obj.insert(val2)
param_2 = obj.insert(40)
param_2 = obj.insert(50)
param_3 = obj.remove(val)
param_4 = obj.getRandom()

print(param_1, param_2, param_3, param_4)

