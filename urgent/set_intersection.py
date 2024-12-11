def f(n):
    num_iterations = 0
    c = 0
    while n >= 0:
        n = n - 2
        c = c + n - 2;
        num_iterations += 1
    return num_iterations

for i in range(4,100):
    print(f(i), i)