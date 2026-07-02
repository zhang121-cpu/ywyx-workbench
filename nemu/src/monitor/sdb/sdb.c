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

#include <isa.h>
#include <cpu/cpu.h>
#include <memory/vaddr.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "sdb.h"

static int is_batch_mode = false;

void init_regex();
void init_wp_pool();

/* We use the `readline' library to provide more flexibility to read from stdin. */
static char* rl_gets() {
  static char *line_read = NULL;

  if (line_read) {
    free(line_read);
    line_read = NULL;
  }

  line_read = readline("(nemu) ");

  if (line_read && *line_read) {
    add_history(line_read);
  }

  return line_read;
}

static int cmd_c(char *args) {
  cpu_exec(-1);
  return 0;
}


static int cmd_q(char *args) {
  nemu_state.state = NEMU_QUIT;
  return -1;
}


static int cmd_help(char *args);
static int cmd_si(char *args);
static int cmd_info(char *args);
static int cmd_x(char *args);
static int cmd_p(char *args) ;static struct {
  const char *name;
  const char *description;
  int (*handler) (char *);
} cmd_table [] = {
  { "help", "Display information about all supported commands", cmd_help },
  { "c", "Continue the execution of the program", cmd_c },
  { "q", "Exit NEMU", cmd_q },
  { "si", "Execute N instrution ", cmd_si },
  { "info", "Print register state or watchpoint information", cmd_info },
  { "x", "Scan memory", cmd_x },
  {"p", "Evaluate expression", cmd_p},


  /* TODO: Add more commands */

};

#define NR_CMD ARRLEN(cmd_table)

static int cmd_help(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

  if (arg == NULL) {
    /* no argument given */
    for (i = 0; i < NR_CMD; i ++) {
      printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  }
  else {
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(arg, cmd_table[i].name) == 0) {
        printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        return 0;
      }
    }
    printf("Unknown command '%s'\n", arg);
  }
  return 0;
}

static int cmd_si(char *args) {
  /* extract the first argument */
  char *num = strtok(NULL, " ");

  if (num == NULL) {
    /* no argument given */
    cpu_exec(1);
    }
  else {
    cpu_exec(atoi(num));
  }
  return 0;
}

static int cmd_info(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");

  if (arg == NULL) {
    printf("Please specify the type of information to display: 'r' for registers, 'w' for watchpoints.\n");
    return 0;
  }

  if (strcmp(arg, "r") == 0) {
    isa_reg_display();
  // } else if (strcmp(arg, "w") == 0) {
  //   wp_display();
  } else {
    printf("Unknown info command '%s'. Use 'info r' for registers or 'info w' for watchpoints.\n", arg);
  }
  return 0;
}

static int cmd_x(char *args){
  /* extract the first argument */
  char *num = strtok(NULL, " ");
  char *addr_str = strtok(NULL, " ");

  if (num == NULL || addr_str == NULL) {
    printf("Please specify the printed instruction's num and address.\n");
    return 0;
  }

  vaddr_t addr = strtoul(addr_str, NULL, 0);        //可自动识别并转换包括0x十六进制在内的各种进制

  for (int i = 0; i < atoi(num); i++){
    if (i % 4 == 0) printf("0x%08x:", addr + i * 4);        //每4条指令重新打印1行地址
    printf("  0x%08x", vaddr_read(addr + i * 4, 4));
    if (i % 4 == 3) printf("\n");                                             //每4条指令换行                                                                                                    
    if (atoi(num) - 1 == i && i % 4 != 3) printf("\n");  //最后1行指令不足4条时换行
  }
  return 0;
}

static int cmd_p(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");

  if (arg == NULL) {
    printf("Please input the expression.\n");
    return 0;
  }

  bool success = true;
  word_t result = expr(args, &success);
  if (success) {
    printf("%u\n", result);
  } else {
    printf("Invalid expression: %s\n", args);
  }
  return 0;
}

//用于测试expr函数的正确性
static void expr_test() {
  FILE *fp = fopen("input", "r");
  if (fp == NULL) {
    printf("Can not open 'input'\n");
    return;
  }

  char line[65536];
  int line_no = 0;
  int pass = 0, fail = 0;

  while (fgets(line, sizeof(line), fp) != NULL) {
    line_no++;

    // 跳过空行
    if (line[0] == '\n' || line[0] == '\0') continue;

    // 解析 "期望结果 表达式"
    unsigned int expected;
    char expr_str[65536];
    if (sscanf(line, "%u %[^\n]", &expected, expr_str) != 2) {
      printf("Line %d: parse error: %s", line_no, line);
      continue;
    }

    // 用 NEMU 的 expr 求值
    bool success;
    word_t result = expr(expr_str, &success);

    // 比较
    if (!success) {
      printf("\033[31mFAIL\033[0m Line %d: %s (expr() returned false)\n", line_no, expr_str);
      fail++;
    } else if (result != expected) {
      printf("\033[31mFAIL\033[0m Line %d: %s\n  Expected: %u, Got: %u\n",
                line_no, expr_str, expected, result);
      fail++;
    } else {
      pass++;
      printf("PASS Line %d: %s = %u\n", line_no, expr_str, result);
    }
  }

  fclose(fp);
  printf("\n=== Test Summary ===\n");
  printf("Total: %d, Pass: %d, Fail: %d\n", pass + fail, pass, fail);
}

void sdb_set_batch_mode() {
  is_batch_mode = true;
}

void sdb_mainloop() {
  if (is_batch_mode) {
    //cmd_c(NULL);
    expr_test(); 
    return;
  }

  for (char *str; (str = rl_gets()) != NULL; ) {
    char *str_end = str + strlen(str);

    /* extract the first token as the command */
    char *cmd = strtok(str, " ");
    if (cmd == NULL) { continue; }

    /* treat the remaining string as the arguments,
     * which may need further parsing
     */
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end) {
      args = NULL;
    }

#ifdef CONFIG_DEVICE
    extern void sdl_clear_event_queue();
    sdl_clear_event_queue();
#endif

    int i;
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(cmd, cmd_table[i].name) == 0) {
        if (cmd_table[i].handler(args) < 0) { return; }
        break;
      }
    }

    if (i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
  }
}

void init_sdb() {
  /* Compile the regular expressions. */
  init_regex();

  /* Initialize the watchpoint pool. */
  init_wp_pool();
}
