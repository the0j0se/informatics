def main():
    A = [int(x) for x in input().split()[:5]]
    B = [int(x) for x in input().split()[:5]]
    
    c1 = sum(1 for x in A if x < 0)
    c2 = sum(1 for x in B if x < 0)
    
    if c1 <= c2:
        print(A, B)
    else:
        print(B, A)
main()