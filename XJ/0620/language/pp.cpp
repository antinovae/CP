int main()
{
  int n = sc.next_int();
  sc.next_int();

  std::vector<std::vector<int>> map(n, std::vector<int>(n));
  for (auto &a : map)
    for (auto &b : a)
      b = sc.next_int() - 1;

  const int kx = n / 2;

  std::vector<std::tuple<int, int, int>> ops;
  while (std::any_of(map.begin(), map.end(), [&](const std::vector<int> &a) {
    return std::any_of(
        a.begin(), a.end(), [&](int b) { return b != map[0][0]; });
  }))
  {
    std::vector<std::vector<bool>> vis(n, std::vector<bool>(n, false));
    std::vector<int>               cnt(n, 0);

    std::vector<std::pair<int, int>> con;
    std::queue<std::pair<int, int>>  que;
    que.emplace(kx, kx);
    vis[kx][kx] = true;

    while (!que.empty())
    {
      const auto [px, py] = que.front();
      que.pop();
      con.emplace_back(px, py);

      for (const auto &[dx, dy] :
           cm::array<int, 4, 2>{{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}})
      {
        int vx = px + dx, vy = py + dy;
        if (0 <= vx && vx < n && 0 <= vy && vy < n)
          if (!vis[vx][vy])
          {
            vis[vx][vy] = true;
            if (map[vx][vy] == map[px][py])
              que.emplace(vx, vy);
            else
              cnt[map[vx][vy]] += 1;
          }
      }
    }

    int vc = static_cast<int>(
        std::distance(cnt.begin(), std::max_element(cnt.begin(), cnt.end())));
    ops.emplace_back(kx, kx, vc);
    for (const auto &[px, py] : con)
      map[px][py] = vc;
  }

  ops.emplace_back(kx, kx, 0);

  freopen("language.out", "w", stdout);

  printf("%zu\n", ops.size());
  for (const auto &[px, py, pc] : ops)
    printf("%d %d %d\n", px + 1, py + 1, pc + 1);

  return 0;
}
