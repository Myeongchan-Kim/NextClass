
import operator
# stats = {'a':1000, 'b':3000, 'c': 100}
# max(stats.iteritems(), key=operator.itemgetter(1))[0]


def find_max(pool, without=None):
    if without is None:
        return max(pool, key=pool.get)

    without_pool = pool.copy()
    without_pool.pop(without)
    return find_max(without_pool)


def only_RGY_string(pool, N):

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

    return result

def problem_solve(case_num):
    [N, R, O, Y, G, B, V] = [int(a) for a in input().split()]
    pool = {
        "R": R,
        "O": O,
        "Y": Y,
        "G": G,
        "B": B,
        "V": V,
    }

    if R < G or B < O or Y < V:
        return list("IMPOSSIBLE")

    result = []
    char = None
    if (N == O * 2 and B == O) \
        or (N == V * 2 and V == Y) \
        or (N == G * 2 and R == G):
        while sum(pool.values()) > 0:
            char = find_max(pool, char)
            result.append(char)
            pool[char] -= 1
        return result
    elif (B == O and O != 0) or (V == Y and V != 0) or (R == G and G != 0):
        return list("IMPOSSIBLE")

    RGpart = []
    BOpart = []
    YVpart = []

    if G != 0:
        RGpart = make_part_str(pool, ["R", "G"])

    if O != 0:
        BOpart = make_part_str(pool, ["B", "O"])

    if V != 0:
        YVpart = make_part_str(pool, ["Y", "V"])

    if pool["G"] > 0 or pool["O"] > 0 or pool["V"] > 0:
        return list("ERROR")

    if RGpart != []:
        pool['R'] += 1
    if BOpart != []:
        pool['B'] += 1
    if YVpart != []:
        pool['Y'] += 1

    rest_part = only_RGY_string(pool, pool['R'] + pool['B'] + pool['Y'])
    if rest_part == list("IMPOSSIBLE"):
        return list("IMPOSSIBLE")

    if RGpart != []:
        for pos, char in enumerate(rest_part):
            if char == "R":
                rest_part = rest_part[:pos] + RGpart + rest_part[pos+1:]
                break

    if BOpart != []:
        for pos, char in enumerate(rest_part):
            if char == "B":
                rest_part = rest_part[:pos] + BOpart + rest_part[pos+1:]
                break
    if YVpart != []:
        for pos, char in enumerate(rest_part):
            if char == "Y":
                rest_part = rest_part[:pos] + YVpart + rest_part[pos+1:]
                break
    return rest_part


def make_part_str(pool, chars):
    result = [chars[0]]
    pool[chars[0]] -= 1
    while pool[chars[1]] > 0:
        result += [chars[1]]
        result += [chars[0]]
        pool[chars[1]] -= 1
        pool[chars[0]] -= 1
    return result


if __name__ == "__main__":
    T = int(input())

    for i in range(T):
        result = problem_solve(i + 1)
        print("Case #%d: %s" % (i + 1, "".join(result)))
