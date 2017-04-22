import string
from collections import deque

class cake():
    def __init__(self, cake_list, row, col):
        self.letter_list = dict()
        self.shape = (row, col)
        self.body = cake_list
        self.count_letter()

    def count_letter(self):
        for row in self.body:
            for char in row:
                value = self.letter_list.get(char, False)
                if value is False:
                    self.letter_list[char] = 1
                else:
                    self.letter_list[char] += 1


    def check_rect(self, char):
        que = deque()

        # Find first char
        cid = None
        rid = None
        for row in range(len(self.body)):
            for col in range(len(row)):
                if self.body[row][col] == char:
                    cid = col
                    rid = row
                    break

        que.append((rid, cid))
        count = 0
        while que:
            cid, rid = que.pop()
            count += 1
            if cid > 0 and self.body[rid][cid-1] == char:
                que.append(rid, cid-1)
            if rid > 0 and self.body[rid-1][cid] == char:
                que.append(rid-1, cid)
            if cid < self.shape[1]-1 and self.body[rid][cid + 1] == char:
                que.append(rid, cid + 1)
            if rid < self.shape[0]-1 and self.body[rid+1][cid] == char:
                que.append(rid+1, cid)

            # check diagonal
            if rid > 0 and cid > 0 and self.body[rid-1][cid-1] == char:
                if (self.body[rid-1][cid] == char and self.body[rid][cid-1] == char) is False:
                    return False
            if rid > 0 and cid < self.shape[1] -1 and self.body[rid-1][cid+1] == char:
                if (self.body[rid-1][cid] == char and self.body[rid][cid+1] == char) is False:
                    return False
            if rid < self.shape[0] - 1 and cid > 0 and self.body[rid + 1][cid - 1] == char:
                if (self.body[rid + 1][cid] == char and self.body[rid][cid - 1] == char) is False:
                    return False
            if rid < self.shape[0] - 1 and cid < self.shape[1]-1 and self.body[rid+1][cid+1] == char:
                if (self.body[rid+1][cid] == char and self.body[rid][cid+1] == char) is False:
                    return False

        if count != self.letter_list[char]:
            return False

        # All pass
        return True

    def check_rect_all(self):
        for key in self.letter_list:
            if self.check_rect(key) is False:
                return False
        return True


def is_complete(cake):
    # Checking all letter is filled.
    for row in cake:
        for i, char in enumerate(row):
            if char == '?':
                return False

    if cake.check_rect_all():
        return True
    else:
        return "IMPOSSIBLE"


def find_letter(cake, rid, cid):
    if is_complete(cake) == "IMPOSSIBLE":
        return False
    if is_complete(cake) is True:
        return cake
    #
    # for row in cake:
    #     for i, char in enumerate(row):
    #         if char == '?':
    #             if rid > 0:
    #                 #copy before character
    #                 cake[rid][cid] = cake[rid-1][cid]
    #                 result = find_letter(cake, rid+1, cid+1)


def fill_row(cake):
    for rid, row in enumerate(cake.body):
        cid = 0
        while cid < len(row):
            while cid + 1 < cake.shape[1] and cake.body[rid][cid+1] == '?':
                cake.body[rid][cid+1] = cake.body[rid][cid]
                cid += 1
            cid += 1

        # move backward
        cid -= 1
        while cid >= 0:
            while cid > 0 and cake.body[rid][cid-1] == '?':
                cake.body[rid][cid-1] = cake.body[rid][cid]
                cid -= 1
            cid -= 1


def fill_col(cake):
    for rid, row in enumerate(cake.body):
        for cid, col in enumerate(row):
            if rid > 0 and cake.body[rid][cid] == '?':
                cake.body[rid][cid] = cake.body[rid-1][cid]

    for rid in range(cake.shape[0]-1, -1, -1):
        for cid, col in enumerate(cake.body[rid]):
            if rid < cake.shape[0]-1 and cake.body[rid][cid] == '?':
                cake.body[rid][cid] = cake.body[rid+1][cid]



def problem_solve(case_num):
    row, col = input().split(" ")
    row = int(row)
    col = int(col)

    cake_input = []
    for r in range(row):
        cake_input.append(list(input()))

    new_cake = cake(cake_input, row, col)

    fill_row(new_cake)
    fill_col(new_cake)
    print("Case #%d:" % case_num)
    for r in range(row):
        print("".join(new_cake.body[r]))


if __name__ == "__main__":
    T = int(input())

    for case_num in range(T):
        problem_solve(case_num+1)


