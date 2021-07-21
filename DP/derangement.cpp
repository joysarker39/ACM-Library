/// derangement Code
long long dp[MAX];
long long derangement(long long N) {
    if(N == 1) return 0LL;
    if(N == 2 or N == 0) return 1LL;
    if(dp[N]) return dp[N];
    return dp[N] = (N-1) * (derangement(N-1) + derangement(N-2));
}
