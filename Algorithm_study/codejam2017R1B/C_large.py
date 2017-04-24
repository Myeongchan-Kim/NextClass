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

    # Find shortest way Floyd-Warshall
    dist_list = find_shortest_way(ways, N)

    # Set diagonal Inf
    for i in range(N):
        dist_list[i][i] = math.inf

    time_table = np.empty((N, N))
    v_func = np.vectorize(calc_time)
    for i in range(N):
        time_table[i] = v_func(list(dist_list[i]), horses[i][0], horses[i][1])

    result_table = find_shortest_way(time_table, N)
    for order in orders:
        result.append(result_table[order[0]-1][order[1]-1])

    return result


def calc_time(dist, endure, speed):
    if dist > endure:
        return math.inf
    else:
        return dist / speed


def find_shortest_way(ways, N):
    # Floyd-Warshall algorithm
    r, c = ways.shape
    if r != N or c != N:
        raise "Wrong way input"
    dist_list = np.empty((r,c))
    dist_list.fill(math.inf)
    for i in range(N):
        for j in range(N):
            dist_list[i][j] = ways[i][j]

    # shortening
    for k in range(N):
        for i in range(N):
            for j in range(N):
                dist_list[i][j] = min( dist_list[i][j], dist_list[i][k] + dist_list[k][j])
    return dist_list

if __name__ == "__main__":
    T = int(input())

    for i in range(T):
        problem(i+1)
