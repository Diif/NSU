#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 10001

typedef struct Node_ {
  char* val;
  struct Node_* next;
} Node;

Node* push(Node* tail, char* val_to_add);
Node* ReadLinesAndGetList();
void PrintList(Node* head);
void FreeList(Node* head);

Node* push(Node* tail, char* val_to_add) {
  if (tail) {
    tail->next = (Node*)malloc(sizeof(Node));
    Node* p = tail->next;
    p->next = NULL;
    int len = strlen(val_to_add) + 1;
    if (len) {
      p->val = (char*)malloc(sizeof(char) * (len));
      strcpy(p->val, val_to_add);
    } else {
      p->val = NULL;
    }
    return p;
  } else {
    tail = (Node*)malloc(sizeof(Node));
    tail->next = NULL;
    int len = strlen(val_to_add) + 1;
    if (len) {
      tail->val = (char*)malloc(sizeof(char) * len);
      strcpy(tail->val, val_to_add);
    } else {
      tail->val = NULL;
    }
    return tail;
  }
}

int main() {
  Node* head = ReadLinesAndGetList();
  printf("---------OUT---------\n");
  PrintList(head);
  FreeList(head);
}

Node* ReadLinesAndGetList() {
  Node *head = NULL, *tail = NULL;
  char buf[MAX_LEN];
  int end_was_found = 0;
  while (fgets(buf, MAX_LEN, stdin)) {
    if (buf[0] == '.') {
      end_was_found = 1;
      break;
    }
    if (!head) {
      head = tail = push(tail, buf);
    } else {
      tail = push(tail, buf);
    }
  }
  if (!end_was_found) {
    FreeList(head);
    exit(EXIT_FAILURE);
  }
  return head;
}

void PrintList(Node* head) {
  while (head) {
    printf("%s", head->val);
    head = head->next;
  }
}

void FreeList(Node* head) {
  Node* p_next;
  if (head) {
    while (head) {
      p_next = head->next;
      if (head->val) {
        free(head->val);
      }
      free(head);
      head = p_next;
    }
  }
}