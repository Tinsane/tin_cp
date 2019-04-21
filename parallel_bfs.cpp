const int N = 101;
set<int> edges[N];

struct Wave
{
	set<int> used;
	int wave[N], wsi, now;
	set<int>::iterator edge;
	void init(int start)
	{
		used.clear();
		used.insert(start);
		wave[0] = start;
		wsi = 1;
		now = 0;
		edge = edges[start].begin();
	}
	bool make_step()
	{
		for (; now < wsi; ++now, edge = edges[wave[now]].begin())
			for (; edge != edges[wave[now]].end(); ++edge)
				if (used.count(*edge) == 0)
				{
					used.insert(*edge);
					wave[wsi++] = *edge;
					++edge;
					return true;
				}
		return false;
	}
};

Wave waves[2];

void parallel_bfs(int a, int b)
{
	waves[0].init(a);
	waves[1].init(b);
	while (waves[0].make_step() && waves[1].make_step());
	waves[0].make_step();
	waves[1].make_step();
}
