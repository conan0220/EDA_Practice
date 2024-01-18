def pivot_index(arr, begin, end):
    pivot = arr[begin][1]
    left_pointer = begin + 1
    right_pointer = end

    while True:
        while left_pointer <= right_pointer and arr[left_pointer][1] <= pivot:
            left_pointer += 1
        while right_pointer >= left_pointer and arr[right_pointer][1] >= pivot:
            right_pointer -= 1
        if right_pointer < left_pointer:
            break
        else:
            arr[right_pointer], arr[left_pointer] = arr[left_pointer], arr[right_pointer]

    arr[begin], arr[right_pointer] = arr[right_pointer], arr[begin]
    return right_pointer

def quicksort(arr, begin, end):
    if begin < end:
        pi = pivot_index(arr, begin, end)
        quicksort(arr, begin, pi-1)
        quicksort(arr, pi+1, end)

# Data provided by the user
data = [754, 751, 630, 944, 139, 856, 223, 357, 620, 421, 40, 911, 61, 295, 520, 666, 62, 183, 280, 534, 356, 779]
# Creating pairs with index and value
indexed_data = list(enumerate(data))

# Applying quicksort
quicksort(indexed_data, 0, len(indexed_data) - 1)

# Extracting the sorted values
sorted_data = [val for idx, val in indexed_data]
print(sorted_data)
