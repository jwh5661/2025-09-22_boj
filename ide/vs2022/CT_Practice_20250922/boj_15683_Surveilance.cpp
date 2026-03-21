// 2026-03-20 (±Ý)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void backtrack(int depth);
void shoot_ray(int x, int y, int dir, int& temp_blank);

int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { -1, 1, 0, 0 };
int rotations[6] = { 0, 4, 2, 4, 4, 1 };
int cctv2[2][2] = { {0, 1}, {2, 3} };
int cctv3[4][2] = { {0, 2}, {1, 3}, {2, 1}, {3, 0} };
int cctv4[4][3] = { {0, 2, 1}, {1, 3, 0}, {2, 1, 3}, {3, 0, 2} };
int n, m;
int cctv_num, blanks, ans, stamp;
vector<vector<int>> office;
vector<pair<int, int>> cctv_location;
vector<int> type;
vector<int> state;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n >> m;

	office = vector<vector<int>>(n, vector<int>(m, 0));
	cctv_location.reserve(8);
	type.reserve(8);
	blanks = 0;
	ans = 1e9;
	stamp = 7;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> office[i][j];

			if (office[i][j] == 0)
				blanks++;
			else if (office[i][j] != 6)
			{
				cctv_location.emplace_back(i, j);
				type.push_back(office[i][j]);
			}
		}
	}

	cctv_num = (int)type.size();
	state = vector<int>(cctv_num, -1);

	backtrack(0);

	cout << ans << '\n';
}

void backtrack(int depth)
{
	if (depth == cctv_num)
	{
		int temp_blank = blanks;
		stamp++;
		for (int i = 0; i < cctv_num; i++)
		{
			int cur_type = type[i];

			switch (cur_type)
			{
			case 1:
			{
				shoot_ray(cctv_location[i].first, cctv_location[i].second, state[i], temp_blank);
				break;
			}
			case 2:
			{
				for (int direction : cctv2[state[i]])
					shoot_ray(cctv_location[i].first, cctv_location[i].second, direction, temp_blank);
				break;
			}
			case 3:
			{
				for (int direction : cctv3[state[i]])
					shoot_ray(cctv_location[i].first, cctv_location[i].second, direction, temp_blank);
				break;
			}
			case 4:
			{
				for (int direction : cctv4[state[i]])
					shoot_ray(cctv_location[i].first, cctv_location[i].second, direction, temp_blank);
				break;
			}
			case 5:
			{
				for (int direction : {0, 1, 2, 3})
					shoot_ray(cctv_location[i].first, cctv_location[i].second, direction, temp_blank);
				break;
			}
			}
		}
		ans = min(ans, temp_blank);
		return;
	}
	int current_cctv_type = type[depth];
	for (int i = 0; i < rotations[current_cctv_type]; i++)
	{
		state[depth] = i;

		backtrack(depth + 1);

		state[depth] = -1;
	}
}

void shoot_ray(int x, int y, int dir, int& temp_blank)
{
	int nx = x + dx[dir];
	int ny = y + dy[dir];

	while ((nx >= 0 && nx < n && ny >= 0 && ny < m) && office[nx][ny] != 6)
	{
		if (office[nx][ny] == 0 ||
			(office[nx][ny] != stamp && office[nx][ny] > 6))
		{
			temp_blank--;
			office[nx][ny] = stamp;
		}
		nx += dx[dir];
		ny += dy[dir];
	}
}