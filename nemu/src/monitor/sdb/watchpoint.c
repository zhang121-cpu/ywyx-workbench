/***************************************************************************************
* Copyright (c) 2014-2024 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include "sdb.h"

#define NR_WP 32

typedef struct watchpoint {
  int NO;
  struct watchpoint *next;
  char expr[32];
  word_t value;
} WP;

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
  }

  head = NULL;
  free_ = wp_pool;
}

WP* new_wp() {
  if (free_ == NULL) {
    panic("无剩余的可用监视点");
  }

  WP *new = free_;
  free_ = free_-> next;     //从free_链表中中取出一个监视点并将其放入head中
  new -> next = head;           //将该监视点放在head链表的最前端
  head = new;                          

  return new;
}

void free_wp(WP *wp) {
  if (head == NULL) {
    panic("所有监视点都已放入空闲链表");
  }

  if (head == wp) {
    head = head -> next;         //如果head对应监视点就是目标，将head指向下一个监视点
  } else {
    WP *new = head;
    while (new -> next != wp && new -> next != NULL)    
      new = new -> next;      //遍历head链表找到目标监视点的前一个监视点，并对其处理
    if (new -> next == wp) 
      new -> next = wp -> next;
    else
      panic("链表中没有该监视点");
    }
  
  wp -> next = free_;     //将被移除的件事典放入free_链表的最前端
  free_ = wp;
}

//显示所有监视点信息
void wp_display(){
  if (head == NULL) {
    printf("没有监视点\n");
    return;
  } else {
    WP *new = head;
    printf("监视点列表：\n");
    printf("监视点编号\t监视点表达式\t监视点值\n");
    while  (new != NULL) {
      printf("%d\t%s\t%u\n", new -> NO, new -> expr, new -> value);
      new = new -> next;
    }    
    return;
  }
}

