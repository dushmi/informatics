#include <cstdio>
#include <cassert>

double wf, hf, wp, hp;

inline double max(double x, double y) {
  return x > y ? x : y;
}

int main() {
  assert(freopen("scalecrop.in", "r", stdin));
  assert(freopen("scalecrop.out", "w", stdout));

  scanf("%lf%lf%lf%lf", &wf, &hf, &wp, &hp);

  if (wp < wf && hp < hf)
    printf("%.2lf %.2lf\n", max(hf / hp, wf / wp) * wp, max(hf / hp, wf / wp) * hp);
  else if (wp < wf) 
    printf("%.2lf %.2lf\n", wf, (wf / wp) * hp);
  else if (hp < hf)
    printf("%.2lf %.2lf\n", (hf / hp) * wp, hf);
  else
    printf("%.2lf %.2lf\n", max(hf / hp, wf / wp) * wp, max(hf / hp, wf / wp) * hp);

  return 0;
}
