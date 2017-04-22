
import operator
# stats = {'a':1000, 'b':3000, 'c': 100}
# max(stats.iteritems(), key=operator.itemgetter(1))[0]


def find_max(pool, without=None):
    if without is None:
        return max(pool, key=pool.get)

    without_pool = pool.copy()
    without_pool.pop(without)
    return find_max(without_pool)

def problem_sovle(case_num):
    [N, R, O, Y, G, B, V] = [int(a) for a in input().split()]
    pool = {
        "R": R,
        "Y": Y,
        "B": B,
    }

    # only R, G, B
    result = [""] * N
    max_char = find_max(pool)
    pos = 0
    while pool[max_char] > 0:
        if pos >= N:
            result = list("IMPOSSIBLE")
            break
        result[pos] = max_char
        pool[max_char] -= 1
        pos += 2

    if result[0] == result[-1]:
        result = list("IMPOSSIBLE")

    if result != list("IMPOSSIBLE"):
        for i, ele in enumerate(result):
            if ele == "":
                char = find_max(pool)
                result[i] = char
                pool[char] -= 1
                if pool[char] < 0:
                    result = list("IMPOSSIBLE")
                    break

    print("Case #%d: %s" % (case_num, "".join(result)))

if __name__ == "__main__":
    T = int(input())

    for i in range(T):
        problem_sovle(i+1)
