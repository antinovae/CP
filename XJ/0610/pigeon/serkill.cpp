#include "pigeon.h"
#include <bits/stdc++.h>

namespace MESSAGES
{

static const char *F_INPUT   = "\033[31mWA [0]\033[00m: input presentation error";
static const char *F_CLAIM   = "\033[31mWA [1]\033[00m: claim returns %d, which is out of range [1, 10^9]";
static const char *F_PIGEON  = "\033[31mWA [2]\033[00m: pigeon receives %d, which is out of range [0, 1]";
static const char *T_PIGEON  = "\033[31mWA [3]\033[00m: pigeon is called more or less than 100 times";
static const char *P_PIGEON  = "\033[31mWA [4]\033[00m: pigeon is called outside function receive";
static const char *A_RECEIVE = "\033[31mWA [5]\033[00m: receive returns %d, which is not the correct answer";
static const char *CORRECT   = "\033[32mOK\033[00m: the answer is correct, your score is %.12lf";

}; // namespace MESSAGES

template <class... T>
void ensure(bool cond, const char *message, T... param)
{
  if (!cond)
  {
    fprintf(stderr, message, param...);
    exit(1);
  }
}

int read_int(int l, int r)
{
  int  x;
  bool v = static_cast<bool>(std::cin >> x);
  ensure(v, MESSAGES::F_INPUT);
  ensure(l <= x, MESSAGES::F_INPUT);
  ensure(x < r, MESSAGES::F_INPUT);
  return x;
}

std::string read_mask(size_t n)
{
  std::string s;
  bool        v = static_cast<bool>(std::cin >> s);
  ensure(v, MESSAGES::F_INPUT);
  ensure(s.length() == n, MESSAGES::F_INPUT);
  for (char c : s)
    ensure(c == '0' || c == '1', MESSAGES::F_INPUT);
  for (size_t i = 0; i + 1 < n; i++)
    ensure(s[i] == '0' || s[i + 1] == '0', MESSAGES::F_INPUT);
  ensure(s.back() == '0', MESSAGES::F_INPUT);
  return s;
}

std::string rand_mask(size_t n)
{
  static std::mt19937 rd(std::random_device{}());

  std::string s;
  s.reserve(n);

  bool always_true = false;
  for (size_t i = 0; i < n - 1; i++)
  {
    if (always_true)
    {
      s += '0';
      always_true = false;
    }
    else
    {
      char c = '0' + (rd() % 2);
      s += c;
      if (c == '1')
        always_true = true;
      else
        always_true = false;
    }
  }
  s += '0';

  return s;
}

struct serkill_t
{
private:
  std::string      method;
  std::vector<int> bits;
  bool             can_send = false;

public:
  serkill_t() = default;
  template <class T>
  serkill_t(T &&method) : method(std::forward<T>(method))
  {
  }

  void start_send()
  {
    can_send = true;
  }

  void stop_send()
  {
    can_send = false;
    ensure(bits.size() == 100, MESSAGES::T_PIGEON);
  }

  int send_bit(int x)
  {
    ensure(can_send, MESSAGES::P_PIGEON);
    ensure(0 <= x && x <= 1, MESSAGES::F_PIGEON, x);

    size_t k = bits.size();
    ensure(k < method.size(), MESSAGES::T_PIGEON);

    if (method[k] == '0')
    {
      bits.push_back(x);
      return 0;
    }
    else
    {
      bits.push_back(!x);
      return 1;
    }
  }

  std::vector<int> get_bits()
  {
    return bits;
  }
};

serkill_t serkill;

int pigeon(int x)
{
  return serkill.send_bit(x);
}

int main()
{
  int type = read_int(0, 2);
  int t    = read_int(0, std::numeric_limits<int>::max());

  int n = claim(type);
  ensure(1 <= n && n <= 1e9, MESSAGES::F_CLAIM, n);

  for (int i = 0; i < t; i++)
  {
    int  x    = read_int(1, n + 1);
    auto mask = (type == 0) ? rand_mask(100) : read_mask(100);
    serkill   = {mask};

    serkill.start_send();
    send(n, x);
    serkill.stop_send();

    int rx = receive(n, serkill.get_bits());
    ensure(x == rx, MESSAGES::A_RECEIVE, rx);
  }

  auto score = [](int n0) -> double {
    if (n0 <= 1)
      return 0;
    else if (n0 <= 11)
      return 0.01 * (n0 - 1);
    else if (n0 <= 111)
      return 0.001 * (n0 - 11) + 0.1;
    else if (n0 <= 10111)
      return 0.00001 * (n0 - 111) + 0.2;
    else
      return 0.14 * std::log10(n0) - 0.26;
  };

  fprintf(stderr, MESSAGES::CORRECT, score(n));

  return 0;
}
