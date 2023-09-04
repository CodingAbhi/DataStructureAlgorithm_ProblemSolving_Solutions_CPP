def maxsubarr(arr):
    max_ending = max_till = arr[0]

    for num in arr[1:]:
        max_ending = max(num, max_ending + num)
        max_till = max(max_till, max_ending)

    return max_till


input_str = input("Enter array : ")
print(end='\n')
arr = list(map(int, input_str.split()))

result = maxsubarr(arr)
print("Max subarray sum:", result)
