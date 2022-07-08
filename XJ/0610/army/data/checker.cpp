#include <bits/stdc++.h>

const int N = 1005;

void ensure(bool x)
{
  if (!x)
  {
    std::cerr << 0 << std::endl;
    exit(0);
  }
}

int64_t distance(int x, int y)
{
  return (int64_t)(x)*x + (int64_t)(y)*y;
}

int main(int, char **argv)
{
  FILE *f_in  = fopen(argv[1], "r");
  FILE *f_out = fopen(argv[2], "r");
  FILE *f_ans = fopen(argv[3], "r");

  double ratio = 1.0;

  int t;
  fscanf(f_in, "%d", &t);
  for (int i = 0; i < t; i++)
  {
    int n;
    fscanf(f_in, "%d", &n);
    static int px[N], py[N], qx[N], qy[N];
    for (int i = 0; i < n; i++)
      fscanf(f_in, "%d%d", &px[i], &py[i]);
    for (int i = 0; i < n + 1; i++)
      fscanf(f_in, "%d%d", &qx[i], &qy[i]);
    static int64_t dis[N][N];
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n + 1; j++)
        dis[i][j] = distance(px[i] - qx[j], py[i] - qy[j]);

    static char out_s[100], ans_s[100];
    fgets(out_s, 99, f_out);
    fgets(ans_s, 99, f_ans);
    ensure(strcmp(out_s, ans_s) == 0);

    static bool vis_a[N], vis_b[N];
    std::fill(vis_a, vis_a + n, false);
    std::fill(vis_b, vis_b + n + 1, false);
    bool valid = [&] {
      if (ans_s[0] == 'I')
      {
        return true;
      }
      else
      {
        bool res = true;
        for (int i = 0; i < n; i++)
          fscanf(f_ans, "%*d%*d");
        for (int i = 0; i < n; i++)
        {
          int a, b;
          ensure(fscanf(f_out, "%d%d", &a, &b) == 2);
          a--, b--;
          if (a < 0 || a > n || b <= 0 || b > n + 1 || vis_a[a] || vis_b[b])
          {
            res = false;
          }
          else
          {
            for (int i = 0; i < n + 1; i++)
              if (!vis_b[i])
                if (dis[a][i] < dis[a][b])
                  res = false;
            vis_a[a] = true;
            vis_b[b] = true;
          }
        }
        fgets(out_s, 99, f_out);
        fgets(ans_s, 99, f_ans);
        return res;
      }
    }();

    if (!valid)
      ratio = std::min(ratio, 0.4);
  }

  std::cerr << ratio << std::endl;

  fclose(f_in);
  fclose(f_out);
  fclose(f_ans);

  return 0;
}

