class Jar:

    cookies = []

    def __init__(self, capacity=12):
        if capacity < 0:
            raise ValueError
        else:
            cookies = [capacity]

    def __str__(self):
        ...

    def deposit(self, n):
        ...

    def withdraw(self, n):
        ...

    @property
    def capacity(self):
        ...

    @property
    def size(self):
        ...