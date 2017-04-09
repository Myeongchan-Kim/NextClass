import string


def problem_solve(case_num):
    N = int(input())
    pool = [False] * 10
    for i in range(1, 99):
        digit = str(N * i)
        for char in digit:
            pool[int(char)] = True
        if pool.count(True) == 10:
            print("Case #%d: %d" % (case_num, N * i))
            return
    print("Case #%d: %s" % (case_num, "INSOMNIA"))


T = int(input())

for case in range(T):
    problem_solve(case + 1)
