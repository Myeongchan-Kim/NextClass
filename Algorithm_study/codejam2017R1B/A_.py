

def problem_sovle(case_num):
    distance, horse_count = input().split()
    distance = int(distance)
    horse_count = int(horse_count)

    max_time = 0
    for i in range(horse_count):
        k, s = input().split()
        k = int(k)
        s = int(s)

        arrive_time = (distance - k) / s
        max_time = max(arrive_time, max_time)

    max_speed = distance / max_time
    print("Case #%d: %.6f" % (case_num, max_speed))

if __name__ == "__main__":
    T = int(input())

    for i in range(T):
        problem_sovle(i+1)
