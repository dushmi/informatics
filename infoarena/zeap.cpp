#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <set>

using namespace std;

const int INF = 0x3f3f3f3f;

struct treap {
    int key, priority;
    treap *left, *right;

    treap(int _key, int _priority, treap *_left, treap *_right) {
        key = _key;
        priority = _priority;
        left = _left;
        right = _right;
    }
} *R, *nil;

char s[20];

multiset <int> diff;

inline int min(int x, int y) {
    return x < y ? x : y;
}

void init() {
    srand(time(0));
    R = nil = new treap(0, 0, NULL, NULL);
}

void rotleft(treap *&node) {
    treap *aux = node->left;
    node->left = aux->right;
    aux->right = node;
    node = aux;
}

void rotright(treap *&node) {
    treap *aux = node->right;
    node->right = aux->left;
    aux->left = node;
    node = aux;
}

void balance(treap *&node) {
    if (node->left->priority > node->priority)
        rotleft(node);
    else if (node->right->priority > node->priority)
        rotright(node);
}

void insert(treap *&node, int key, int priority) {
    if (node == nil) {
        node = new treap(key, priority, nil, nil);
        return;
    }

    if (key < node->key) 
        insert(node->left, key, priority);
    else
        insert(node->right, key, priority);

    balance(node);
}

void erase(treap *&node, int key) {
    if (node == nil) 
        return;

    if (key < node->key)
        erase(node->left, key);
    else if (key > node->key) 
        erase(node->right, key);
    else {
        if (node->left == nil && node->right == nil) {
            delete node;
            node = nil;
        } else {
            (node->left->priority > node->right->priority) ? rotleft(node) : rotright(node);
            erase(node, key);
        }
    }
}

bool search(treap *&node, int key) {
    if (node == nil)
        return 0;

    if (key < node->key)
        return search(node->left, key);
    
    if (key > node->key)
        return search(node->right, key);

    return 1;
}

int getNumber(char *s) {
    int x = 0;

    while ('0' <= *s && *s <= '9')
        x = x * 10 + (*s++) - '0';
    
    return x;
}

int min(treap *&node) {
    if (node == nil)
        return INF;

    if (node->left != nil)
        return min(node->left);

    return node->key;
}

int max(treap *&node) {
    if (node == nil)
        return 0;

    if (node->right != nil)
        return max(node->right);

    return node->key;
}

int prev(treap *&node, int key) {
    if (node == nil)
        return 0;

    if (key < node->key)
        return prev(node->left, key);

    if (key > node->key)
        return max(node->key, prev(node->right, key));

    return max(node->left);
}

int next(treap *&node, int key) {
    if (node == nil)
        return INF;

    if (key < node->key)
        return min(node->key, next(node->left, key));
    
    if (key > node->key)
        return next(node->right, key);

    return min(node->right);
}

int main() {
    assert(freopen("zeap.in", "r", stdin));
    assert(freopen("zeap.out", "w", stdout));

    init();

    while (fgets(s, sizeof(s), stdin)) {
        if (s[0] == 'I') {
            int x = getNumber(s + 2);
            bool ans = search(R, x);
            if (!ans) {
                insert(R, x, rand() + 1);
                int x1 = prev(R, x), x2 = next(R, x);
                multiset <int>::iterator it = diff.find(x2 - x1);
                if (it != diff.end()) 
                    diff.erase(it);
                if (x1 != 0)
                    diff.insert(x - x1);
                if (x2 != INF)
                    diff.insert(x2 - x);
            }

            continue;
        } 

        if (s[0] == 'S') {
            int x = getNumber(s + 2);
            bool ans = search(R, x);
            if (!ans)
                printf("-1\n");
            else {
                int x1 = prev(R, x), x2 = next(R, x);
                multiset <int>::iterator it;
                if (x1 != 0) {
                    it = diff.find(x - x1);
                    if (it != diff.end())
                        diff.erase(it);
                }
                if (x2 != INF) {
                    it = diff.find(x2 - x);
                    if (it != diff.end())
                        diff.erase(it);
                }
                if (x1 != 0 && x2 != INF)
                    diff.insert(x2 - x1);
                erase(R, x);
            }

            continue;
        }

        if (s[0] == 'C') {
            printf("%d\n", search(R, getNumber(s + 2)));
        
            continue;
        }

        if (s[0] == 'M' && s[1] == 'I') {
            if (diff.empty())
                printf("%d\n", -1);
            else 
                printf("%d\n", *diff.begin());
            
            continue;
        }

        int x1 = max(R), x2 = min(R);
        if (x1 == x2 || x1 == 0 || x1 == INF || x2 == 0 || x2 == INF)
            printf("-1\n");
        else
            printf("%d\n", x1 - x2);
    }

    return 0;
}
