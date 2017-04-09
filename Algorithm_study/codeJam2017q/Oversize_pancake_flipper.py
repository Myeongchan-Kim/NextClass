
def count_result(row, K):
    result = 0
    for i, happy_side in enumerate(row):
        if not happy_side:
            # Flip.
            for target in range(K):
                if i+target >= len(row):
                    return -1
                row[i+target] = not row[i+target]
            result += 1
    return result


def problem_solve(case_num):
    (row, K) = input().split(" ")
    K = int(K)

    row = list(row)
    boolean_row = list(map(lambda x: (x == '+'), row))

    result = count_result(boolean_row, K)

    if result == -1:
        print(" Case #%d: IMPOSSIBLE" % case_num)
    else:
        print(" Case #%d: %d" % (case_num, result))

T = int(input())

for case in range(T):
    problem_solve(case + 1)