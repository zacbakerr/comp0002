def shift_string(s, k):
    """Shift each character in string s by k positions (modulo 26)"""
    return ''.join(chr((ord(c) - ord('a') + k) % 26 + ord('a')) for c in s)

def is_k_shagram(s1, s2, k):
    """Check if s2 is a k-shagram of s1"""
    return ''.join(sorted(s2)) == ''.join(sorted(shift_string(s1, k)))

def word_weight(s):
    """Calculate the weight of a string (positions in alphabet starting from 0)"""
    return sum(ord(c) - ord('a') for c in s)

def find_max_weight():
    """Find the maximum weight among strings that have a k-shagram in selected_strings"""
    # Load all strings from the file
    with open('selected_strings.txt', 'r') as f:
        strings = [line.strip() for line in f if line.strip()]
    
    # Keep track of strings that have k-shagrams
    valid_strings = set()
    
    # For each string, check if it has a k-shagram in the list
    total = len(strings)
    # Create dictionary mapping sorted strings to original strings
    sorted_map = {}
    for i, s in enumerate(strings):
        sorted_s = ''.join(sorted(s))
        if sorted_s not in sorted_map:
            sorted_map[sorted_s] = []
        sorted_map[sorted_s].append(s)
    
    # For each string, check if any of its k-shifts match another string
    for i, s in enumerate(strings):
        sorted_s = ''.join(sorted(s))
        
        # Try each shift value
        for k in range(1, 26):
            # Get sorted version of shifted string
            shifted = shift_string(s, k)
            sorted_shifted = ''.join(sorted(shifted))
            
            # If we find a match, add both strings
            if sorted_shifted in sorted_map:
                valid_strings.add(s)
                valid_strings.update(sorted_map[sorted_shifted])
                break
                
        if s in valid_strings:
            continue
    
    print("Progress: 100%")
    # If no valid strings found, return 0
    if not valid_strings:
        return 0
    
    # Calculate weights of all valid strings and find maximum
    weights = [word_weight(s) for s in valid_strings]
    return max(weights)

def main():
    max_weight = find_max_weight()
    print(f"Maximum weight: {max_weight}")

if __name__ == "__main__":
    main() 