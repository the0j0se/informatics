def solve():
    A = set(map(int, input().split()))
    B = set(map(int, input().split()))
    c = [x for x in A ^ B if x % 2]
    
    print(*c if c else "нет нечетных")

solve()