struct Edge
{
	int to;
	int flow;
	int cap;
	Edge() {}
	Edge(int to, int cap) : to(to), flow(), cap(cap) {}
};

const int N = 1e4 + 10;
int n, m;
Edge edges[10 * N];
vector<int> inds[N];
int height[N];
int excess[N];
int best[N], maxh, bsi;

void prepush()
{
	height[0] = n + 1;
	for(auto i : inds[0])
	{
		auto& e = edges[i];
		excess[e.to] = e.flow = e.cap;
		edges[i ^ 1].flow = -e.flow;
	}
	while(true)
	{
		// choose
		if (bsi == 0)
		{
			for (int i = 1; i < n - 1; ++i)
				if (excess[i] > 0)
				{
					if (bsi > 0 || height[i] > height[best[0]])
						bsi = 0;
					if (bsi == 0 || height[best[0]] == height[i])
						best[bsi++] = i;
				}
		}
		if (bsi == 0)
			break;
		// push
		while(bsi > 0)
		{
			auto v = best[--bsi];
			bool pushed = false;
			for(auto i : inds[v])
			{
				auto& e = edges[i];
				if (e.flow == e.cap || height[e.to] != height[v] - 1)
					continue;
				int delta = min(excess[v], e.cap - e.flow);
				e.flow += delta;
				edges[i ^ 1].flow -= delta;
				excess[v] -= delta;
				excess[e.to] += delta;
				pushed = true;
				if (excess[v] == 0)
					break;
			}
			// lift
			if (!pushed)
			{
				height[v] = INF;
				for (auto i : inds[v])
					if (edges[i].flow < edges[i].cap)
						height[v] = min(height[v], height[edges[i].to] + 1);
				if (height[v] > height[best[0]])
					break;
			}
		}
	}
}
