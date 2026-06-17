def find_min_max(arr, left, right):
    if left == right:
        return arr[left], arr[left]
    
    if left + 1 == right:
        if arr[left] < arr[right]:
            return arr[left], arr[right]
        return arr[right], arr[left]
    
    mid = (left + right) // 2
    min1, max1 = find_min_max(arr, left, mid)
    min2, max2 = find_min_max(arr, mid + 1, right)
    
    final_min = min(min1, min2)
    final_max = max(max1, max2)
    
    return final_min, final_max


def main():
    nums = [5, 7, 2, 4, 9, 6]
    mn, mx = find_min_max(nums, 0, len(nums) - 1)
    print(f"The minimum array element is {mn}")
    print(f"The maximum array element is {mx}")
if __name__ == "__main__":
    main()