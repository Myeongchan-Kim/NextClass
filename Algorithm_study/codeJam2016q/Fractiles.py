
def pick_students(K, C, S):
    students = []
    check = 0
    for i in range(1, S+1):
        pos = 1
        for c in range(1, C+1):
            pos += K ** (c-1) * check
            check += 1
            # print("K, C, c, check, pos = %d, %d, %d, %d, %d" % (K, C, c, check, pos))
            if check >= K:
                students.append(pos)
                return students
        if pos <= (K ** C):
            students.append(pos)
    return students

def problem_solve(case_num):
    (K, C, S) = input().split(" ")
    K = int(K)
    C = int(C)
    S = int(S)

    check = C * S
    students = pick_students(K, C, S)
    print("Case #%d:" % case_num, end=" ")
    if check < K:
        print("IMPOSSIBLE")
    else :
        print(" ".join(map(str, students)))


T = int(input())

for case in range(T):
    problem_solve(case+1)
