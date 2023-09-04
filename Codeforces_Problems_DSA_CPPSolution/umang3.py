def missing_number(nums):
    n = len(nums)
    total_sum = n * (n + 1) // 2
    actual_sum = sum(nums)
    missing_number = total_sum - actual_sum
    return missing_number


input_str = input("Enter the array of numbers: ")
print(end='\n')
nums = list(map(int, input_str.split()))
missednum = missing_number(nums)
print("The missing number is:", missednum)
