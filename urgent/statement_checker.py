from itertools import permutations
from collections import defaultdict

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

def is_k_shagram(s1, s2, k):
    """Check if s2 is a k-shagram of s1"""
    return s2 in get_k_shagram(s1, k)

def word_weight(s):
    """Calculate the weight of a string (positions in alphabet starting from 0)"""
    return sum(ord(c) - ord('a') for c in s)

def load_selected_strings():
    """Load strings from the file"""
    with open('selected_strings.txt', 'r') as f:
        return set(line.strip() for line in f if line.strip())

def check_statement1(selected_strings):
    """Check if all k-shagrams of length-1 words are in selected_strings"""
    length_1_words = {s for s in selected_strings if len(s) == 1}
    for word in length_1_words:
        for k in range(26):
            k_shagrams = get_k_shagram(word, k)
            if not all(shagram in selected_strings for shagram in k_shagrams):
                return False
    return True

def check_statement2():
    """Check if 'urgent' is a 13-shagram of 'gather'"""
    return is_k_shagram('gather', 'urgent', 13)

def check_statement3():
    """Check if 'accepts' is a k-shagram of 'courage' for some k"""
    for k in range(26):
        if is_k_shagram('courage', 'accepts', k):
            return True, k
    return False, None

def check_statement4():
    """Check if distinct 4-shagrams of 'while' are 96"""
    all_shagrams = set()
    for k in range(26):
        all_shagrams.update(get_k_shagram('while', 4))
    return len(all_shagrams) == 96, len(all_shagrams)

def check_statement5(selected_strings):
    """Check if exactly two strings in selected_strings have 'while' as 4-shagram"""
    count = 0
    for s in selected_strings:
        if is_k_shagram('while', s, 4):
            count += 1
    return count == 2, count

def check_statement6(selected_strings):
    """Check if 'supporters' has highest weight among length-10 strings"""
    len_10_strings = {s for s in selected_strings if len(s) == 10}
    weights = {s: word_weight(s) for s in len_10_strings}
    max_weight_word = max(weights.items(), key=lambda x: x[1])[0]
    return max_weight_word == 'supporters', max_weight_word

def main():
    selected_strings = load_selected_strings()
    
    print("\nChecking all statements:")
    
    # Statement 1
    result1 = check_statement1(selected_strings)
    print(f"\n1. All k-shagrams of length-1 words are in selected_strings: {result1}")
    
    # Statement 2
    result2 = check_statement2()
    print(f"\n2. 'urgent' is a 13-shagram of 'gather': {result2}")
    
    # Statement 3
    result3, k = check_statement3()
    print(f"\n3. 'accepts' is a k-shagram of 'courage': {result3}")
    if result3:
        print(f"   Found k = {k}")
    
    # Statement 4
    result4, count = check_statement4()
    print(f"\n4. Distinct 4-shagrams of 'while' are 96: {result4}")
    print(f"   Actual count: {count}")
    
    # Statement 5
    result5, count = check_statement5(selected_strings)
    print(f"\n5. Exactly two strings have 'while' as 4-shagram: {result5}")
    print(f"   Actual count: {count}")
    
    # Statement 6
    result6, max_word = check_statement6(selected_strings)
    print(f"\n6. 'supporters' has highest weight among length-10 strings: {result6}")
    print(f"   Word with highest weight: {max_word}")

if __name__ == "__main__":
    main() 