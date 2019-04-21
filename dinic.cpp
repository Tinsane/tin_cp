struct Edge
{
	int to, rev, flow, cap;
	Edge(int to, int cap) : to(to), cap(cap), flow() {}
	int left() const
	{
		return cap - flow;
	}
};

struct Dinic
{
	int vcnt;
	vector<Edge> go[N];
	vector<Edge>::iterator its[N];
	int d[N];
	int q[N];
	int qsz;

	void add_edge(int a, int b, int cap)
	{
		go[a].emplace_back(b, cap);
		go[b].emplace_back(a, cap);
		go[a].back().rev = go[b].size() - 1;
		go[b].back().rev = go[a].size() - 1;
	}

	bool bfs(int s, int t)
	{
		fill(d, d + vcnt, -1);
		d[s] = 0;
		qsz = 0;
		q[qsz++] = s;
		for (int i = 0; i < qsz; ++i)
		{
			auto v = q[i];
			for (auto e : go[v])
				if (e.left() > 0 && d[e.to] == -1)
				{
					d[e.to] = d[v] + 1;
					q[qsz++] = e.to;
				}
		}
		return d[t] != -1;
	}

	int dfs(int v, int t, int flow)
	{
		if (v == t || flow == 0)
			return flow;
		for (auto& it = its[v]; it != go[v].end(); ++it)
		{
			auto to = it->to;
			if (d[to] != d[v] + 1)
				continue;
			auto d = dfs(to, t, min(flow, it->left()));
			if (d > 0)
			{
				it->flow += d;
				go[to][it->rev].flow -= d;
				return d;
			}
		}
		return 0;
	}

	int calc_flow(int s, int t)
	{
		int flow = 0;
		while (bfs(s, t))
		{
			for (int i = 0; i < vcnt; ++i)
				its[i] = go[i].begin();
			while (true)
			{
				int pushed = dfs(s, t, INF);
				if (!pushed)
					break;
				flow += pushed;
			}
		}
		return flow;
	}
} dinic;
