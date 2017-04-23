import numpy as np
import math

cache = {}

def problem(case_num):
    N, Q = input().split()
    N = int(N)
    Q = int(Q)

    cache.clear()
    horses = []
    ways = np.empty((N,N))
    for i in range(N):
        endure, speed = [int(x)for x in input().split()]
        horses.append((endure, speed))

    for i in range(N):
        ways[i] = [int(x) for x in input().split()]
    ways = np.vectorize(lambda x: math.inf if x == -1 else x)(ways)

    orders = []
    for i in range(Q):
        from_city, to_city = [int(x) for x in input().split()]
        orders.append((from_city, to_city))

    result = solve(N, horses, ways, orders)
    result = ["%f" % x for x in result]
    print("Case #%d: %s" % (case_num, " ".join(result)))

def solve(N, horses, ways, orders):
    result = []
    for order in orders:
        start_city = order[0] - 1
        finish_city = order[1] - 1
        result.append(calculate_small(start_city, finish_city, ways, horses, horses[start_city]))
    return result

def calculate_small(start, finish, ways, horses, riding_horse):
    if start == finish:
        return 0.0
    id_str = ",".join([ str(x) for x in [start, finish, riding_horse]])
    cache_result = cache.get(id_str, False)
    if cache_result:
        return cache_result

    dist = ways[start][start+1]
    time = dist / riding_horse[1]
    if dist > riding_horse[0]:
        return math.inf

    change_result = calculate_small(start+1, finish, ways, horses, horses[start+1])
    no_change_result = calculate_small(start+1, finish, ways, horses, (riding_horse[0] - dist, riding_horse[1]))

    cache[id_str] = time + min(change_result, no_change_result)
    return cache[id_str]


if __name__ == "__main__":
    T = int(input())

    for i in range(T):
        problem(i+1)