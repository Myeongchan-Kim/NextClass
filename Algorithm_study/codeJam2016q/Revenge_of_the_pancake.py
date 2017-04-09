import string


def problem_solve(case_num):
    cake_stack = input()
    result = 0
    for i, char in enumerate(cake_stack):
        if i+1 < len(cake_stack) and cake_stack[i] != cake_stack[i+1]:
            result += 1
    if cake_stack[-1] == '-':
        result += 1
    print("Case #%d: %d" % (case_num, result))

T = int(input())

for case in range(T):
    problem_solve(case+1)