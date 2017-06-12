# algospot_FORTRESS.py

import os
import sys

class Circle():
    def __init__(self, x, y, r):
        self.x = x
        self.y = y
        self.r = r
        self.children = []
        self.parent = self

    def show(self):
        print("(%d, %d, %d)" % (self.x, self.y, self.r))

    def is_include(self, c):
        if ((self.x - c.x)**2 + (self.y - c.y)**2 < self.r ** 2) and c.r < self.r:
            return True
        return False

    def insert(self, c):
        for child in self.children:
            if child.is_include(c):
                child.insert(c)
                return

        for (i,child) in enumerate(self.children):
            if c.is_include(child):
                c.parent = self
                self.children = rearr_root(c , self.children)
                return

        self.children.append(c)
        c.parent = self
        return

    def height(self):
        childheight = 0
        if( len(self.children) is 0 ):
            return 0

        for child in self.children:
            childheight = max(childheight, child.height())
        return childheight + 1

    def diameter(self):
        max_d_children = 0
        max_new_dia = 0
        for child in self.children:
            max_d_children = max(max_d_children, child.diameter())

        height = self.height()

        if len(self.children) > 1:
            first_height = 0
            second_height = 0
            for child in self.children:
                tmp = sorted([first_height, second_height, child.height()])
                (first_height , second_height) = (tmp[1], tmp[2])
            max_new_dia = first_height + second_height + 2

        # self.print()
        # print("Max d in childrent : %d" % max_d_children)
        # print("Height : %d" % height)
        # print("Max new Dia : %d" % max_new_dia)
        return max(height, max_new_dia, max_d_children)


    def print(self):
        print("%d, %d, %d ,parent:(%d, %d, %d), child:%d , height:%d" % (self.x, self.y, self.r,self.parent.x,self.parent.y,self.parent.r ,len(self.children), self.height()))
        for child in self.children:
            child.print()

n = 0
root = None

def rearr_root(target, child_list):
    new_list = [target]
    for c in child_list:
        if target.is_include(c):
            target.insert(c)
        else:
            new_list.append(c)

    return new_list


def insert_tree(circle):
    global root
    if root == None:
        root = circle
    else:
        root.insert(circle)


def problem_solve(case_num):
    global n, cache,root
    root = None
    n = int(input())
    for i in range(n):
        row = input()
        row = row.split()
        x = int(row[0])
        y = int(row[1])
        r = int(row[2])
        c = Circle(x,y,r)
        insert_tree(c)

    result = root.diameter()
    print(result)


if __name__ == "__main__":
    N = int(input())
    for i in range(N) :
        problem_solve(i+1)
