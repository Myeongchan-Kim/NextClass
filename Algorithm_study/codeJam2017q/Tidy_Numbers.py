
def find_largest_asend(num):
    str_num = str(num)

    for i, char in enumerate(str_num):
        if i+1 >= len(str_num):
            break
        if int(char) <= int(str_num[i+1]):
            continue
        str_num = str(int(str_num[:i+1]) - 1) + ("9" * (len(str_num)-i-1))
        str_num = find_largest_asend(str_num)
    return str_num


def problem_solve(case_num):
    target = int(input())
    result = int(find_largest_asend(target))

    print(" Case #%d: %d" % (case_num, result))

T = int(input())

for case in range(T):
    problem_solve(case + 1)