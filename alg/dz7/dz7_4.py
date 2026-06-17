def print_partitions(target, start_num, path):
    if target == 0:
        print(*path)
        return
    for num in range(start_num, target + 1):
        path.append(num)
        print_partitions(target - num, num, path)
        path.pop()

def main():
    n = int(input())
    print_partitions(n, 1, [])

if __name__ == "__main__":
    main()