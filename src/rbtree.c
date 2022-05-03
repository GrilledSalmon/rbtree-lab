#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed
  node_t *nil = (node_t *)malloc(sizeof(node_t)); // nil노드 생성
  nil->color = RBTREE_BLACK;
  p->nil = p->root = nil;

  return p;
}

/* 수정할 RBtree와 서브트리의 루트(x)를 받아옴 */
void left_rotate(rbtree *t, node_t *x) {
  node_t *y = x->right;
  x->right = y->left;
  if (y->left != t->nil)
    y->left->parent = x;
  
  y->parent = x->parent;

  if (x->parent == t->nil)
    t->root = y;
  else if (x == x->parent->left)
    x->parent->left = y;
  else
    x->parent->right = y;

  y->left = x;
  x->parent = y;
}

// left_rotate에서 left, right 자리만 바꿔서 만듦
void right_rotate(rbtree *t, node_t *x) {
  node_t *y = x->left;
  x->left = y->right;
  if (y->right != t->nil)
    y->right->parent = x;
  
  y->parent = x->parent;

  if (x->parent == t->nil)
    t->root = y;
  else if (x == x->parent->right)
    x->parent->right = y;
  else
    x->parent->left = y;

  y->right = x;
  x->parent = y;
}

void post_order_delete(rbtree *t, node_t *node) { // 후위순회로 노드들 지워줌
  if (node != t->nil){
    post_order_delete(t, node->left);
    post_order_delete(t, node->right);
    free(node);
  }
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  post_order_delete(t, t->root); // 딸려 있는 노드 전체 free
  free(t->nil); // nil노드 free
  free(t); // 트리 free
}

void rbtree_insert_fixup(rbtree *t, node_t *z) {
  node_t *y = NULL; // 삼촌
  while (z->parent->color == RBTREE_RED) {
    if (z->parent == z->parent->parent->left) {
      y = z->parent->parent->right;
      if (y->color == RBTREE_RED) {
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_BLACK;
        z = z->parent->parent;
      }
      else {
        if (z == z->parent->right) {
          z = z->parent;
          left_rotate(t, z);
        }
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        right_rotate(t, z->parent->parent);
      }
    }
    else {
      y = z->parent->parent->left;
      if (y->color == RBTREE_RED) {
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_BLACK;
        z = z->parent->parent;
      }
      else {
        if (z == z->parent->left) {
          z = z->parent;
          left_rotate(t, z);
        }
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        right_rotate(t, z->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
}


node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  node_t *z = (node_t *)malloc(sizeof(node_t)); // 삽입할 노드
  z->color = RBTREE_RED;
  z->key = key;
  z->left = z->right = t->nil;

  node_t *y = t->nil; // 삽입될 노드의 부모
  node_t *x = t->root; // temp..?
  
  while (x != t->nil){
    y = x;
    if (z->key < x->key)
      x = x->left;
    else
      x = x->right;
  }
  z->parent = y; // 부모 관계 설정
  if (y==t->nil)
    t->root = z;
  else if (z->key < y->key)
    y->left = z;
  else
    y->right = z;
  
  rbtree_insert_fixup(t, z);

  return z; // 삽입된 노드의 포인터
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  node_t *x = t->root; // 찾은 노드를 가리키는 포인터
  while (x != t->nil && x->key != key) {
    if (x->key > key)
      x = x->left;
    else
      x = x->right;
  }
  if (x == t->nil) // 찾고자하는 key가 없는 경우
    return NULL;
  return x;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  node_t *p = t->nil; // x의 부모
  node_t *x = t->root;

  while (x != t->nil) {
    p = x;
    x = x->left;
  }

  return p;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  node_t *p = t->nil; // x의 부모
  node_t *x = t->root;

  while (x != t->nil) {
    p = x;
    x = x->right;
  }
  
  return p;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}
