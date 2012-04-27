#include <cstdio>
#include <cstdlib>
#include <ctime>

const int inf = 0x3f3f3f3f;

struct Node {
  int key, priority;
  Node *left, *right;

  Node() {
  }

  Node(int _key, int _priority, Node *_right, Node *_left) {
    key = _key;
    priority = _priority;
    left = _left;
    right = _right;
  }
};

Node *R, *nil;

void init(Node *&R) {
  srand(time(0));
  R = nil = new Node(0, 0, NULL, NULL);
}

bool search(Node *n, int key) {
  if (n == nil) 
    return 0;
  
  if (key == n->key)
    return 1;

  if (key < n->key)
    return search(n->left, key);

  return search(n->right, key);
}

void rotleft(Node *&n) {
  Node *aux = n->left;
  n->left = aux->left;
  aux->left = n;
  n = aux;
}

void rotright(Node *&n) {
  Node *aux = n->right;
  n->right = aux->left;
  aux->left = n;
  n = aux;
}

void balance(Node *&n) {
  if (n->left->priority > n->priority)
    rotleft(n);
  else if (n->right->priority > n->priority)
    rotright(n);
}

void insert(Node *&n, int key, int priority) {
  if (n == nil) {
    n = new Node(key, priority, nil, nil);
    return;
  }

  if (key < n->key)
    insert(n->left, key, priority);
  else if (key > n->key)
    insert(n->right, key, priority);

  balance(n);
}

void erase(Node *&n, int key) {
  if (n == nil)
    return;

  if (key < n->key)
    erase(n->left, key);
  else if (key > n->key)
    erase(n->right, key);
  else {
    if (n->left == nil && n->right == nil) {
      delete n;
      n = nil;
    } else {
      (n->left->priority > n->right->priority) ? rotleft(n) : rotright(n);
      erase(n, key);
    }
  }
}

void split(Node *&R, Node *&Ts, Node *&Tg, int key) {
  insert(R, key, inf);
  Ts = R->left;
  Tg = R->right;
  delete R;
  R = nil;
}

void join(Node *&R, Node *&Ts, Node *&Tg, int key) {
  R = new Node(key, 0, Ts, Tg);
  erase(R, R->key);
}

int main() {
  //insert(R, key, rand() + 1);
  return 0;
}

