// 2026-04-13 (¿ù)

#include <iostream>

using namespace std;

void solve(int y, int x, int order, int size);

int n, r, c;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n >> r >> c;

	int size = 1 << n;

	solve(0, 0, 0, size);
}

void solve(int y, int x, int order, int size)
{
	if (y == r && x == c)
	{
		cout << order << '\n';
		return;
	}
		
	int half = size / 2;
	if (y <= r && r < y + half)
	{
		if (x <= c && c < x + half)
			solve(y, x, order, half);
		else
			solve(y, x + half, order + half * half, half);
	}
	else
	{
		if (x <= c && c < x + half)
			solve(y + half, x, order + 2 * half * half, half);
		else
			solve(y + half, x + half, order + 3 * half * half, half);
	}
}