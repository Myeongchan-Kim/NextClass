
def calc_height(N, K):
    max_height = 0
    sum = 1
    while sum <= K:
        sum *= 2
        max_height += 1

    min_height = 0
    if K == 2 ** max_height - 1:
        min_height = max_height
    else:
        min_height = max_height - 1

    return max_height, min_height


def calc_remain_last(max_height, N, K):
    intervals = dict()
    intervals[N] = 1

    remain = K
    for i in range(max_height):
        new_intervals = dict()
        for key in intervals:
            new_key1 = (key-1) // 2 + (key-1) % 2
            new_key2 = (key-1) // 2
            if new_key1 not in new_intervals:
                new_intervals[new_key1] = 0
            if new_key2 not in new_intervals:
                new_intervals[new_key2] = 0
            new_intervals[new_key1] += intervals[key]
            new_intervals[new_key2] += intervals[key]
        if remain <= sum(intervals.values()):
            return intervals, remain, new_key1, new_key2
        else:
            remain -= sum(intervals.values())
        intervals = new_intervals


def problem_solve(case_num):
    (N, K) = input().split(" ")
    N = int(N)
    K = int(K)

    max_height, min_height = calc_height(N, K)

    intervals, remain, key1, key2 = calc_remain_last(max_height, N, K)

    for key in reversed(list(sorted(intervals))):
        if remain <= intervals[key]:
            key1, key2 = (key-1)//2 + (key-1)%2, (key-1)//2
            break
        else:
            remain -= intervals[key]

    # print(intervals)
    print(" Case #%d: %d %d" % (case_num, key1, key2))

T = int(input())

for case in range(T):
    problem_solve(case + 1)