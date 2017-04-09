
def find_max_interval(intervals):
    max_i = intervals[0]
    for interval in intervals:
        if interval[1] - interval[0] > max_i[1] - max_i[0]:
            max_i = interval

    return max_i

def find_min_interval(intervals):
    min_i = intervals[0]
    for interval in intervals:
        if interval[1] - interval[0] < min_i[1] - min_i[0]:
            min_i = interval

    return min_i

def problem_solve(case_num):
    (N, K) = input().split(" ")
    N = int(N)
    K = int(K)

    intervals = [(1, N)]
    last_interval = (N-1) // 2 + (N-1) % 2, (N - 1) // 2
    for i in range(K):
        max_interval = find_max_interval(intervals)
        new_pos = (max_interval[0] + max_interval[1]) // 2
        intervals.remove(max_interval)
        intervals.append((max_interval[0], new_pos - 1))
        intervals.append((new_pos+1, max_interval[1]))
        last_interval = (max_interval[1] - new_pos, new_pos - max_interval[0])

    print(" Case #%d: %d %d" % (case_num, last_interval[0], last_interval[1]))

T = int(input())

for case in range(T):
    problem_solve(case + 1)