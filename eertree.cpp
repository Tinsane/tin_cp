const int S = 26;
const int N = 4e5 + 10 + S;

struct eerTree
{
	struct State
	{
		int len;
		int go[S];
		int link;
		State() {}
		State(int len, int link) : len(len), link(link)
		{
			memset(go, -1, sizeof go);
		}
	} states[N];
	int st_sz;
	int cur;
	string s;
	void init(string s)
	{
		this->s = s;
		states[0] = State(-1, 0);
		states[1] = State(0, 0);
		cur = 0;
		st_sz = 2;
	}
	bool add_letter(int pos, int add)
	{
		auto c = s[pos];
		while (c != s[pos - states[cur].len - 1])
			cur = states[cur].link;
		if (states[cur].go[c] != -1)
		{
			cur = states[cur].go[c];
			return false;
		}
		auto link = states[cur].link;
		while (c != s[pos - states[link].len - 1])
			link = states[link].link;
		link = states[link].go[c];
		if (link == -1)
			link = 1;
		states[st_sz] = State(states[cur].len + 2, link);
		states[cur].go[c] = st_sz;
		cur = st_sz++;
	}
} tree;
