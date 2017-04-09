import string


def make_jamcoin(len, seed):
    half_coin = ""
    while seed != 0:
        half_coin = str(seed % 2) + half_coin
        seed //= 2
    return ("1" + half_coin.zfill(len - 2) + "1") * 2


def calc_divisor(base, jamcoin):
    half = len(jamcoin) // 2
    return int(jamcoin[0:half], base)


def problem_solve(case_num):
    (N, J) = input().split(" ")
    N = int(N)
    J = int(J)

    print("Case #%d:" % case_num)

    # make jamcoin
    for i in range(J):
        jamcoin = make_jamcoin(N//2, i)
        print(jamcoin, end=" ")
        for base in range(2, 11):
            print(calc_divisor(base, jamcoin), end=" ")
        print()


T = int(input())

for case in range(T):
    problem_solve(case+1)
