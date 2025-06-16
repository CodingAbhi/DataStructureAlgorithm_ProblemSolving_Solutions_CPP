def find_possible_digits(valid_patterns, faulty_display):   
    possible_digits = []
    for digit, valid_pattern in valid_patterns.items():     
        difference_count = sum(1 for original, faulty in zip(faulty_display, valid_pattern) if original != faulty)
        if difference_count <= 1:
            possible_digits.append(digit)
    return possible_digits

def solve():    
    standard_digit_patterns = [input().strip() for _ in range(3)]  
    faulty_digit_patterns = [input().strip() for _ in range(3)]   
    
    valid_patterns = {}
    for i in range(10):
        valid_patterns[i] = ''.join(standard_digit_patterns[j][i*3:(i+1)*3] for j in range(3))   
    
    faulty_number_sequences = []
    for i in range(len(faulty_digit_patterns[0]) // 3):
        faulty_display = ''.join(faulty_digit_patterns[j][i*3:(i+1)*3] for j in range(3))
        possible_digits = find_possible_digits(valid_patterns, faulty_display)
        if not possible_digits:
            print("Invalid", end='')
            return
        faulty_number_sequences.append(possible_digits) 

    from itertools import product
    total_sum = 0
    for possible_number in product(*faulty_number_sequences):
        total_sum += int(''.join(map(str, possible_number)))    
    print(total_sum, end='')

solve()
