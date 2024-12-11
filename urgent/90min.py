def successor(input):
    # Function to generate the next number in a base-3 number system
    # Input is a list representing digits in base-3 (0,1,2)
    # Returns the next number in sequence by incrementing by 1
    i = 0
    while i < len(input):
        if input[i] < 2:
            # If current digit is 0 or 1, increment it and we're done
            input[i] += 1
            break
        else:
            # If current digit is 2, set to 0 and carry over to next digit
            input[i] = 0  
            i += 1

    if i == len(input):
        # If we've carried over past the last digit, append 1 as new digit
        input.append(1)

    return input

def leq(A, B):
    # Pad shorter number with leading zeros to match lengths
    max_len = max(len(A), len(B))
    A = A + [0] * (max_len - len(A))
    B = B + [0] * (max_len - len(B))
    
    # Compare from most significant digit (right to left)
    for i in range(max_len - 1, -1, -1):
        if A[i] < B[i]:
            return True
        if A[i] > B[i]:
            return False
    
    # If we get here, numbers are equal
    return True

def tritwise_min(A, B):
    # Pad shorter number with zeros to match lengths
    max_len = max(len(A), len(B))
    a = A + [0] * (max_len - len(A))
    b = B + [0] * (max_len - len(B))
    
    # Take minimum of each digit position
    result = []
    for i in range(max_len):
        result.append(min(a[i], b[i]))
    
    # Remove trailing zeros
    while len(result) > 0 and result[-1] == 0:
        result.pop()
        
    return result if result else [0]  # Return [0] if result is empty

def f(A, B):
    # Make copies to avoid modifying inputs
    current = A.copy()
    result = current.copy()
    
    while leq(current, B):
        # Take tritwise minimum of result and current number
        result = tritwise_min(result, current)
        
        # Move to next number
        next_num = current.copy()
        successor(next_num)
        current = next_num
        
    return result
    
def f_eff(A, B):
    # Pad shorter number with zeros to match lengths
    max_len = max(len(A), len(B))
    a = A + [0] * (max_len - len(A))
    b = B + [0] * (max_len - len(B))
    
    result = []
    carry = False
    
    # Process each digit position from most significant (right) to least significant (left)
    for i in range(max_len - 1, -1, -1):
        if not carry and a[i] == b[i]:
            # If no carry and digits are same, keep that digit
            result.insert(0, a[i])
        else:
            # If digits differ or there's a carry, all numbers in between will create a 0
            result.insert(0, 0)
            if a[i] != b[i]:
                carry = True
    
    # Remove trailing zeros
    while len(result) > 0 and result[-1] == 0:
        result.pop()
        
    return result if result else [0]

def test_performance():
    import time
    import random
    
    # Test cases with increasing sizes
    test_sizes = [2, 4, 6, 8]
    
    for size in test_sizes:
        # Generate random test case of given size
        A = [random.randint(0, 2) for _ in range(size)]
        B = [random.randint(0, 2) for _ in range(size)]
        
        # Make sure A <= B
        while not leq(A, B):
            B = [random.randint(0, 2) for _ in range(size)]
        
        # Test f
        start_time = time.time()
        result1 = f(A, B)
        f_time = time.time() - start_time
        
        # Test f_eff
        start_time = time.time()
        result2 = f_eff(A, B)
        f_eff_time = time.time() - start_time
        
        print(f"\nSize {size}:")
        print(f"Input A: {A}")
        print(f"Input B: {B}")
        print(f"f() time: {f_time:.6f} seconds")
        print(f"f_eff() time: {f_eff_time:.6f} seconds")
        print(f"Speedup: {f_time/f_eff_time:.2f}x")
        print(f"Results match: {result1 == result2}")

# Run the performance test
if __name__ == "__main__":
    print(successor([2,1,0]))