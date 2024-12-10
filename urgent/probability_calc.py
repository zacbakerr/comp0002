from itertools import permutations

def shift_char(c, k):
    """Shift a character by k positions, wrapping from 'z' to 'a'"""
    return chr((ord(c) - ord('a') + k) % 26 + ord('a'))

def get_k_shagram(s, k):
    """Generate all possible k-shagrams of string s"""
    results = set()
    for perm in permutations(s):
        shifted = ''.join(shift_char(c, k) for c in perm)
        results.add(shifted)
    return results

def calculate_probability():
    s = "abcdefg"
    total_strings = 26 ** 7  # Total possible strings of length 7
    k_shagrams = set()

    # Check all k values from 0 to 25
    for k in range(26):
        k_shagrams.update(get_k_shagram(s, k))

    p = len(k_shagrams) / total_strings
    return round(1 / p)

def main():
    result = calculate_probability()
    print(f"1/p rounded to the nearest integer is: {result}")

if __name__ == "__main__":
    main() 