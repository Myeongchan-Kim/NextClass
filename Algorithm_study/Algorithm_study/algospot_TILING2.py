# TILING in Algospo.com
# Paul MC Kim

import os
import sys

MOD = 1000000007
n = 0
cache = []

def fibo(i):
    if i <= 1:
        return i
    global cache, MOD
    if cache[i] >= 0 :
        return cache[i]
    else:
        cache[i] = (fibo(i-1) + fibo(i-2)) % MOD
        return cache[i]

def problem_solve(case_num):
    global n, cache
    n = int(input())
    cache = [-1,] * (n+2)
    # print(cache)
    print(fibo(n+1))

if __name__ == "__main__":
    N = int(input())
    for i in range(N) :
        problem_solve(i+1)
