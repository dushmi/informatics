#include <cstdio>

const int L = 305;

struct Trie {
  int last;
  Trie *next[26];

  Trie() {
    last = 0;
    for (int i = 0; i < 26; ++i)
      next[i] = NULL;
  }
};

inline bool letter(char ch) {
  return (ch >= 'a' && ch <= 'z');
}

char s[L];

int Na, Nb;

Trie *r = new Trie;

void insert_trie(Trie *node, int ord, int pos) {
  if (node->last < ord - 1)
    return;

  node->last = ord;

  if (!letter(s[pos]))
    return;

  if (!node->next[s[pos] - 'a'])
    node->next[s[pos] - 'a'] = new Trie;
  
  insert_trie(node->next[s[pos] - 'a'], ord, pos + 1);
}

void change_trie(Trie *node, int pos) {
  node->last = 0;
  
  if (!letter(s[pos]))
    return;

  if (node->next[s[pos] - 'a'])
    change_trie(node->next[s[pos] - 'a'], pos + 1);
}

int query_trie(Trie *node) {
  int res = 0;
  
  if (node->last == Na)
    ++res;

  for (int i = 0; i < 26; ++i)
    if (node->next[i]) 
      res += query_trie(node->next[i]);
  
  return res;
}

int main() {
  freopen("sub.in", "r", stdin);
  freopen("sub.out", "w", stdout);

  scanf("%d\n", &Na);

  for (int i = 1; i <= Na; ++i) {
    fgets(s, sizeof(s), stdin);
    for (int j = 0; letter(s[j]); ++j)
      insert_trie(r, i, j);
  }

  scanf("%d\n", &Nb);

  for (int i = 1; i <= Nb; ++i) {
    fgets(s, sizeof(s), stdin);
    for (int j = 0; letter(s[j]); ++j)
      change_trie(r, j);
  }

  printf("%d\n", query_trie(r));

  return 0;
}
