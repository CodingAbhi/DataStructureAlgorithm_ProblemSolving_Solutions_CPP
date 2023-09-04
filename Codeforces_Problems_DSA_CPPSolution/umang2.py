def reverse_str(input_str):
    if len(input_str) == 0:
        return ""
    else:
        return input_str[-1] + reverse_str(input_str[:-1])


input_str = input("Enter a string: ")
print(end='\n')

reversed_str = reverse_str(input_str)

print("Reversed string:", reversed_str)
