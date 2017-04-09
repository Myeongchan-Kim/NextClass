

def is_asend(num):
    str_num = str(num)
    sorted_char = list(map(lambda x: str(x), sorted(list(str_num))))
    result = int("".join(sorted_char))
    # print(result)
    return num == result


def find_largest_asend(num):
    while not is_asend(num):
        num -= 1
    return num


def problem_solve(case_num):
    target = int(input())
    result = int(find_largest_asend(target))

    print(" Case #%d: %d" % (case_num, result))

T = int(input())

for case in range(T):
    problem_solve(case + 1)