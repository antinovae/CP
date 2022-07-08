int get(std::vector<int> &p, int u)
{
  if (p[u] == u)
    return u;
  else
  {
    p[u] = get(p, p[u]);
    return p[u];
  }
}
 
struct node_t
{
  node_t *f    = nullptr;
  node_t *s[2] = {nullptr, nullptr};
 
  int id;
  int len;
  int occ        = 0;
  int occ_assign = 1;
 
  int                 sum;
  std::pair<int, int> min_len;
  std::pair<int, int> min_lp;
 
  void push_up()
  {
    sum     = len;
    min_len = {len, id};
    min_lp  = {len + occ, id};
    if (s[0] != nullptr)
    {
      sum ^= s[0]->sum;
      min_len = std::min(min_len, s[0]->min_len);
      min_lp  = std::min(min_lp, s[0]->min_lp);
    }
    if (s[1] != nullptr)
    {
      sum ^= s[1]->sum;
      min_len = std::min(min_len, s[1]->min_len);
      min_lp  = std::min(min_lp, s[1]->min_lp);
    }
  }
 
  void push_occ_assign(int val)
  {
    occ_assign = val;
    occ        = val;
    min_lp     = {min_len.first + val, min_len.second};
  };
 
  void push_down()
  {
    if (occ_assign != -1)
    {
      if (s[0] != nullptr)
        s[0]->push_occ_assign(occ_assign);
      if (s[1] != nullptr)
        s[1]->push_occ_assign(occ_assign);
      occ_assign = -1;
    }
  }
 
  bool is_root() const
  {
    return f == nullptr || (f->s[0] != this && f->s[1] != this);
  }
 
  bool get_son() const
  {
    return f->s[1] == this;
  }
 
  void push()
  {
    if (!is_root())
      f->push();
    push_down();
  }
 
  void rotate()
  {
    node_t *uu = this, *ff = uu->f, *aa = ff->f;
    bool    ss = get_son();
    if (!ff->is_root())
      aa->s[ff->get_son()] = uu;
    ff->f     = uu;
    ff->s[ss] = uu->s[!ss];
    uu->f     = aa;
    uu->s[!ss] = ff;
    if (ff->s[ss] != nullptr)
      ff->s[ss]->f = ff;
    ff->push_up();
    uu->push_up();
  }
 
  void splay()
  {
    push();
    while (!is_root())
    {
      if (f->is_root())
      {
        rotate();
        break;
      }
      else
      {
        if (f->get_son() == get_son())
          f->rotate();
        else
          rotate();
        rotate();
      }
    }
  }
 
  void access()
  {
    node_t *uu = this, *ss = nullptr;
    while (uu != nullptr)
    {
      uu->splay();
      uu->s[1] = ss;
      uu->push_up();
      ss = uu;
      uu = uu->f;
    }
  }
};
 
constexpr int len_invalid = 1 << 25;
 
int main()
{
  int n  = sc.next_int();
  int op = sc.next_int();
 
  std::vector<node_t> p(n + 1);
  std::vector<int>    f(n + 1);
  std::vector<int>    s;
 
  f[0]     = -1;
  p[0].id  = 0;
  p[0].len = 0;
  p[0].push_up();
 
  int     ans     = 0;
  int64_t ans_sum = 0;
  for (int i = 0; i < n; i++)
  {
    int c = static_cast<uint8_t>(sc.next_char());
    if (op == 1)
      c = (c + ans) % 26;
    s.push_back(c);
 
    int u = i + 1;
    f[u]  = 0;
    for (int v = f[i]; v >= 0; v = f[v])
      if (s[v] == s[i])
      {
        f[u] = v + 1;
        break;
      }
 
    asee(u, f[u]);
 
    p[u].id  = u;
    p[u].len = u;
    p[u].push();
    p[u].f = &p[f[u]];
    p[u].access();
 
    while (true)
    {
      p[u].splay();
      see(p[u].s[0], p[u].s[1]);
      see(p[u].min_lp);
      if (p[u].min_lp.first < u)
      {
        int v = p[u].min_lp.second;
        see("mark", v);
        p[v].splay();
        p[v].len = len_invalid;
        p[v].push_up();
      }
      else
      {
        break;
      }
    }
 
    p[u].push_occ_assign(u);
 
    ans = (p[u].sum ^ u) & (len_invalid - 1);
    see(ans);
    ans_sum += ans;
  }
 
  fprintf(out, "%" SCNi64 "\n", ans_sum);
 
  return 0;
}
