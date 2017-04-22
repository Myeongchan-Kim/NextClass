
class FenwickTree():
    def __init__(self, max_size):
        self.tree = [0,] * (max_size + 1)

    def add(self, pos, val):
        while pos < len(self.tree):
            self.tree[pos] += val
            pos += (pos & -pos)

    def sum(self, pos):
        result = 0
        while pos > 0:
            result += self.tree[pos]
            pos &= pos-1
        return result

def make_list():
    from sys import stdin
    _ = int(stdin.readline())
    A_list = [int(a) for a in stdin.readline().split()]

    rank_table = dict()
    for i, ele in enumerate(sorted(A_list)):
        rank_table[ele] = i + 1

    return [rank_table[e] for e in A_list]

if __name__ == "__main__":
    C = int(input())
    for i in range(C):
        new_list = make_list()
        max = 50001
        tree = FenwickTree(max)
        result = 0
        for ele in new_list:
            result += (tree.sum(max) - tree.sum(ele))
            tree.add(ele, 1)
        print(result)
