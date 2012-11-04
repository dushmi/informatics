#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cassert>

struct Node {
  int priority, key, elem;
  bool reverse;
  Node *left, *right;

  Node() {
  }

  Node(int _key, int _priority, Node *_left, Node *_right) {
    key = _key;
    priority = _priority;
    left = _left;
    right = _right;
    reverse = 0;
    elem = (_left ? _left->elem : 0) + (_right ? _right->elem : 0);
  }
};

Node *R;

int n, m;

inline void init() {
  srand(time(0));
  R = NULL;
}

inline void reverse(Node *&r) {
  if (!r)
    return;

  if (r->left)
    r->left->reverse ^= r->reverse;
  if (r->right)
    r->right->reverse ^= r->reverse;
  
  if (r->reverse) {
    r->reverse = 0;
    Node *aux = r->left;
    r->left = r->right;
    r->right = aux;
  }
}

inline void remake(Node *&r) {
  r->elem = (r->left ? r->left->elem : 0) + (r->right ? r->right->elem : 0) + 1;
}

inline void rotLeft(Node *&r) {
  Node *aux = r->left;
  r->left = aux->right;
  aux->right = r;
  remake(r); remake(aux);
  r = aux;
}

inline void rotRight(Node *&r) {
  Node *aux = r->right;
  r->right = aux->left;
  aux->left = r;
  remake(r); remake(aux);
  r = aux;
}

inline void balance(Node *&r) {
  if (r->left && r->left->priority < r->priority)
    rotLeft(r);
  else if (r->right && r->right->priority < r->priority)
    rotRight(r);
  else
    remake(r);
}

void insert(Node *&r, int pos, int key, int priority) {
  if (!r) {
    r = new Node(key, priority, NULL, NULL);
    return;
  }

  reverse(r); reverse(r->left); reverse(r->right);

  if (pos <= (r->left ? r->left->elem : 0))
    insert(r->left, pos, key, priority);
  else
    insert(r->right, pos - 1 - (r->left ? r->left->elem : 0), key, priority);

  balance(r);
}

void erase(Node *&r) {
  if (!r->left && !r->right) {
    delete r; r = 0;
    return;
  }

  reverse(r); reverse(r->left); reverse(r->right);

  if (r->left && r->right) {
    if (r->left->priority < r->right->priority) {
      rotLeft(r); 
      erase(r->right);
    } else {
      rotRight(r);
      erase(r->left);
    }
  } else {
    if (r->left) {
      rotLeft(r);
      erase(r->right);
    } else {
      rotRight(r);
      erase(r->left);
    }
  }

  balance(r);
}

Node* find(Node *r, int pos) {
  reverse(r);
  
  if ((r->left ? r->left->elem : 0) + 1 == pos)
    return r;

  if ((r->left ? r->left->elem : 0) >= pos)
    return find(r->left, pos);
  else
    return find(r->right, pos - 1 - (r->left ? r->left->elem : 0));
}

inline int query(int pos) {
  return find(R, pos)->key;
}

inline void reverseSequence(int x, int y) {
  Node *left, *center, *right;
  
  insert(R, x - 1, 0, 0);
  left = R->left;
  
  insert(R->right, y - x + 1, 0, 0);
  right = R->right->right;
  center = R->right->left;
  
  center->reverse ^= 1;
  reverse(center);
  
  delete R->right;
  delete R;
  
  R = new Node(0, 0, left, center);
  erase(R);
  
  center = R;
  R = new Node(0, 0, center, right);
  erase(R);
}

void read() {
  assert(scanf("%d%d", &n, &m));

  for (int i = 1; i <= n; ++i)
    insert(R, i - 1, i, rand() + 1);
}

void solve() {
  int x, y, k;
  
  for (int i = 1; i <= m; ++i) {
    assert(scanf("%d%d%d", &x, &y, &k));
    reverseSequence(x, y);
    printf("%d\n", query(k));
  }
}

int main() {
  assert(freopen("rev.in", "r", stdin));
  assert(freopen("rev.out", "w", stdout));

  init();

  read();

  solve();

  return 0;
}
