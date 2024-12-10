from itertools import permutations

def shift_char(c, k):
    """Shift a character by k positions, wrapping from 'z' to 'a'"""
    # Convert char to 0-25 number, add k, mod 26, convert back to char
    return chr((ord(c) - ord('a') + k) % 26 + ord('a'))

def get_k_shagram(s, k):
    """Generate all possible k-shagrams of string s"""
    results = set()
    # Step 1: Generate all permutations
    for perm in permutations(s):
        # Step 2: Shift each character by k positions
        shifted = ''.join(shift_char(c, k) for c in perm)
        results.add(shifted)
    return results

def is_k_shagram(s, t, k):
    """Check if t is a k-shagram of s"""
    return t in get_k_shagram(s, k)

def test_statement1():
    """Test if s is h-shagram of t where h = -k when t is k-shagram of s"""
    test_cases = [
        ("abc", 1),
        ("word", 2),
        ("xyz", 3),
        ("queen", 5),
        ("test", -1),
        ("sample", 25)
    ]
    
    for s, k in test_cases:
        # Get a k-shagram of s
        t = next(iter(get_k_shagram(s, k)))
        h = -k
        if not (is_k_shagram(s, t, k) and is_k_shagram(t, s, h)):
            return False, f"Failed for s={s}, k={k}, t={t}"
    return True, "All test cases passed"

def test_statement2():
    """Test if "abz" is a k-shagram of "bac" for some k"""
    # Test all possible k values
    for k in range(-26, 26):
        if is_k_shagram("bac", "abz", k):
            return True, k
    return False, None

def test_statement3():
    """Test if k must be multiple of 26 when "abba" is k-shagram of itself"""
    results = []
    # Test a wider range of k values
    for k in range(-260, 261):
        if is_k_shagram("abba", "abba", k):
            results.append(k)
    
    # Verify all results are multiples of 26
    all_multiples = all(k % 26 == 0 for k in results)
    return results, "All are multiples of 26" if all_multiples else "Not all are multiples of 26"

def test_statement4():
    """Test if k must be multiple of 26 when "anna" is k-shagram of itself"""
    results = []
    # Test a wider range of k values
    for k in range(-260, 261):
        if is_k_shagram("anna", "anna", k):
            results.append(k)
    
    # Verify all results are multiples of 26
    all_multiples = all(k % 26 == 0 for k in results)
    return results, "All are multiples of 26" if all_multiples else "Not all are multiples of 26"

def test_statement5():
    """Test if number of k-shagrams of "queen" depends on k"""
    counts = {}
    # Test more k values
    test_k_values = list(range(10)) + [25, 26, 27, -1, -26]
    for k in test_k_values:
        counts[k] = len(get_k_shagram("queen", k))
    
    # Check if all counts are the same
    all_same = len(set(counts.values())) == 1
    return counts, "Count does not depend on k" if all_same else "Count depends on k"

def test_statement6():
    """Test if no string can be a k-shagram of itself for 0 < k < 10"""
    # Test more strings including edge cases
    test_strings = [
        "a", "b", "z",  # single letters
        "ab", "yz", "aa",  # two letters
        "abc", "xyz", "aaa",  # three letters
        "abcd", "wxyz", "aaaa",  # four letters
        "queen", "pizza", "hello"  # longer words
    ]
    
    for k in range(1, 10):
        for s in test_strings:
            if is_k_shagram(s, s, k):
                return False, f"Found counterexample: string '{s}' is {k}-shagram of itself"
    return True, "No counterexamples found"

def test_statement7():
    """Test if there exists a k (0 < k < 26) where any string is a k-shagram of its k-shagrams"""
    # Test more strings including edge cases
    test_strings = [
        "a", "b", "z",  # single letters
        "ab", "yz", "aa",  # two letters
        "abc", "xyz", "aaa",  # three letters
        "word", "test", "aaaa",  # four letters
        "queen", "pizza", "hello"  # longer words
    ]
    
    for k in range(1, 26):
        valid_for_all = True
        for s in test_strings:
            # Get all k-shagrams of s
            k_shagrams = get_k_shagram(s, k)
            # For each k-shagram, check if s is a k-shagram of it
            for t in k_shagrams:
                if not is_k_shagram(t, s, k):
                    valid_for_all = False
                    break
            if not valid_for_all:
                break
        if valid_for_all:
            return True, k
    return False, None

def main():
    print("\nTesting all statements with enhanced rigor:")
    print("\nStatement 1 (s is h-shagram of t where h = -k when t is k-shagram of s):")
    print(test_statement1())
    
    print("\nStatement 2 ('abz' is k-shagram of 'bac' for some k):")
    print(test_statement2())
    
    print("\nStatement 3 (k must be multiple of 26 when 'abba' is k-shagram of itself):")
    print(test_statement3())
    
    print("\nStatement 4 (k must be multiple of 26 when 'anna' is k-shagram of itself):")
    print(test_statement4())
    
    print("\nStatement 5 (number of k-shagrams of 'queen' depends on k):")
    print(test_statement5())
    
    print("\nStatement 6 (no string can be a k-shagram of itself for 0 < k < 10):")
    print(test_statement6())
    
    print("\nStatement 7 (exists k where any string is k-shagram of its k-shagrams):")
    print(test_statement7())

if __name__ == "__main__":
    main()


