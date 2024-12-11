def f(n):
    c = 0
    while n >= 0:
        n = n - 2
        c = c + n - 2
    return c

def test_statements():
    results = []

    # Statement 1: f always returns an integer without infinite loop
    try:
        for n in range(-10, 10):
            f(n)
        results.append(True)
    except:
        results.append(False)

    # Statement 2: If input is odd, f(n-2) might be smaller than f(n)
    results.append(f(5) > f(3))

    # Statement 3: If input is even, output is also even
    results.append(all(f(n) % 2 == 0 for n in range(0, 10, 2)))

    # Statement 4: If input is odd, output is also odd
    results.append(all(f(n) % 2 != 0 for n in range(1, 10, 2)))

    # Statement 5: If n is between 4 and 100, iterations equal ⌈n/2⌉
    results.append(all(f(n) == (n // 2) * (n // 2 - 1) for n in range(4, 101)))

    # Statement 6: For any positive even n, f(n) ≥ f(n-2)
    results.append(all(f(n) >= f(n-2) for n in range(2, 10, 2)))

    # Statement 7: f(n) is non-negative integer for any integer n
    results.append(all(f(n) >= 0 for n in range(-10, 10)))

    # Statement 8: If n > 10, f(n) is positive
    results.append(all(f(n) > 0 for n in range(11, 20)))

    # Statement 9: For large enough n, f is strictly increasing
    results.append(all(f(n) < f(n+2) for n in range(10, 20, 2)))

    return results

def main():
    results = test_statements()
    for i, result in enumerate(results, 1):
        print(f"Statement {i}: {'Correct' if result else 'Incorrect'}")

if __name__ == "__main__":
    main() 