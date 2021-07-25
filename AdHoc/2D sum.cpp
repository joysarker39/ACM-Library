long long arr[MAX][MAX], csum[MAX][MAX];

void init_2Dsum(int N, int M) {
    for(int i = 1; i <= M; i++)
        for(long long j = 1, rsum = 0; j <= M; j++)
            csum[i][j] = csum[i-1][j] + (rsum+=arr[i][j]);
}

long long cal_2Dsum(int si, int sj, int ei, int ej) {
    return csum[ei][ej]+csum[si-1][sj-1] - csum[ei][sj-1] - csum[si-1][ej];
}
