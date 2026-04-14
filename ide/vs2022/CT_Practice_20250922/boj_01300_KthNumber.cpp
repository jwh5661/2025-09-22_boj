/*
* [백준 1300] K번째 수 ( G1 )
* - 훈련 날짜 : 2026-04-14 (화)
* - 알고리즘 : 이분 탐색 / 파라메트릭 서치 ( Parametric Search )
* - 1. 중간점 : mid = ( start + end ) / 2	// 기본 정수 나눗셈 ( 왼쪽 쏠림 )
* - 2. 범위 갱신 : 조건 만족 시 end = min	// 정답 후보를 챙기고 아래로 깎아내림
*/

#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	long long n, k;
	cin >> n >> k;

	long long start = 1, end = k;

	while (start < end)
	{
		long long mid = (start + end) / 2;
		long long cnt = 0;

		for (int i = 1; i <= n; i++)
			cnt += min(mid / i, (long long)n);

		if (cnt >= k)
			end = mid;
		else
			start = mid + 1;
	}

	cout << start;
}