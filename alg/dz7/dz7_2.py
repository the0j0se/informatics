def count_ways(n, k):
    MOD = 10**9 + 7
    dp = [0] * (n + 1)
    dp[1] = 1
    current_sum = 1 
    for i in range(2, n + 1):
        dp[i] = current_sum
        current_sum = (current_sum + dp[i]) % MOD
        if i > k:
            current_sum = (current_sum - dp[i - k]) % MOD
    return dp[n]

def main():
    n, k = map(int, input().split())
    print(count_ways(n, k))

if __name__ == "__main__":
    main()