#include <cstdio>
#include <algorithm>
#include <cassert>

using namespace std;

const int kMaxN = 32005;

int N, v01[kMaxN], vec[kMaxN], aux[kMaxN];

void quickSort01(int left, int right) {
  if (left == right)
    return;

  int middle = (left + right) / 2;
  
  quickSort01(left, middle);
  quickSort01(middle + 1, right);

  int p1 = 0, p2 = 0;
  
  //find first "1" from first half
  for (int i = left; i <= middle && !p1; ++i)
    if (v01[i] == 1) 
      p1 = i;
  
  //find last "0" from second half
  for (int i = right; i > middle && !p2; --i)
    if (v01[i] == 0) 
      p2 = i;
  
  //first half is full of "0" or second half is full of "1"
  if (!p1 || !p2) 
    return;

  //otherwise
  printf("%d %d\n", p1, p2);
  //reverse the vector containing "0" and "1"
  reverse(v01 + p1, v01 + p2 + 1);
  //reverse the original vector
  reverse(vec + p1, vec + p2 + 1);
}

void quickSort(int left, int right) {
  if (left == right)
    return;

  int middle = (left + right) / 2;
  
  //find out the median
  copy (vec + left, vec + right + 1, aux + left);
  sort(aux + left, aux + right + 1);
  int median = aux[middle], m = aux[left], M = aux[right];
  
  //if all elements from vec[left] to vec[right] are equal => nothing to do
  if (m == median && M == median)
    return;
  
  //make v01
  int nb0 = 0;
  for (int i = left; i <= right; ++i)
    if (m != median) {
      if (vec[i] < median)
        v01[i] = 0, ++nb0;
      else
        v01[i] = 1;
    } else {
      if (vec[i] <= median)
        v01[i] = 0, ++nb0;
      else
        v01[i] = 1;
    }
  //sort v01
  quickSort01(left, right);

  quickSort(left, left + nb0 - 1);
  quickSort(left + nb0, right);
}

int main() {
  assert(freopen("invsort.in", "r", stdin));
  assert(freopen("invsort.out", "w", stdout));

  assert(scanf("%d", &N) == 1);

  for (int i = 1; i <= N; ++i)
    assert(scanf("%d", &vec[i]) == 1);

  copy(vec + 1, vec + N + 1, aux + 1);
  sort(aux + 1, aux + N + 1);
  quickSort(1, N);

  return 0;
}
