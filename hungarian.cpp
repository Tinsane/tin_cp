const int N = 110;
int n;
int a[N][N];
int rpot[N], cpot[N];
int way[N], match[N];
int minv[N];
bool used[N];

void hungarian()
{
	for (int i = 1; i <= n; ++i)
	{
		match[0] = i;
		int col = 0;
		fill(minv, minv + n + 1, INF);
		fill(used, used + n + 1, false);
		do
		{
			used[col] = true;
			int row = match[col];
			int delta = INF;
			int next;
			for (int j = 1; j <= n; ++j)
			{
				if (used[j])
					continue;
				int cur = a[row][j] - rpot[row] - cpot[j];
				if(cur < minv[j])
				{
					minv[j] = cur;
					way[j] = col;
				}
				if (minv[j] < delta)
				{
					delta = minv[j];
					next = j;
				}
			}
			for (int j = 0; j <= n; ++j)
				if (used[j])
					rpot[match[j]] += delta, cpot[j] -= delta;
				else
					minv[j] -= delta;
			col = next;
		} while (match[col] != 0);
		do
		{
			int prev = way[col];
			match[col] = match[prev];
			col = prev;
		} while (col != 0);
	}
}
