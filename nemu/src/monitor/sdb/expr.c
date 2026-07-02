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

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>

enum {
  TK_SPACE= 256, TK_EQ, TK_DEC, TK_UNSIGNED,

  /* TODO: Add more token types */

};

static struct rule {
  const char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */

  {"[0-9]+", TK_DEC},      // decimal number
  {"\\+", '+'},         // plus
  {"\\-", '-'},         // minus
  {"\\*", '*'},         // multiply
  {"\\/", '/'},         // divide
  {"\\(", '('},         // left parenthesis
  {"\\)", ')'},         // right parenthesis
  {" +", TK_SPACE},    // spaces
  {"u", TK_UNSIGNED},    // unsigned suffix
  {"==", TK_EQ},        // equal
};

#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

typedef struct token {
  int type;
  char str[32];
} Token;

static Token tokens[65536] __attribute__((used)) = {};
static int nr_token __attribute__((used))  = 0;

//检查表达式是否有不是别的token类型的字符
static bool make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        //Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
          //  i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;

        /*将识别出的token写入结构体tokens中，同时将nr_tokens加1*/
        switch (rules[i].token_type) {
          case TK_DEC:
            Assert(substr_len < 32, "token too long: %.*s", substr_len, substr_start);  //避免token过长导致溢出
            tokens[nr_token].type = TK_DEC;
            strncpy(tokens[nr_token].str, substr_start, substr_len);
            tokens[nr_token].str[substr_len] = '\0';
            nr_token++;
            break;
          case '+':case '-':case '*':case '/':case '(':case ')':
            tokens[nr_token].type = rules[i].token_type;
            nr_token++;
            break;
          case TK_SPACE:case TK_UNSIGNED:
            break;
          case TK_EQ:
            tokens[nr_token].type = rules[i].token_type;
            nr_token++;
            break;
          
          default: panic("请在make_token函数中添加新的token类型的处理逻辑");
        }

        break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }

  return true;
}

//检查表达式中是否有括号不匹配导致的错误
static void check_brackets(void) {
  int depth = 0;
  for (int i = 0; i < nr_token; i++) {
    if (tokens[i].type == '(') {
      depth++;
    } else if (tokens[i].type == ')') {
      depth--;
    }
    if (depth < 0) {
      panic("括号不匹配：位置 %d 处多余的 ')'", i);
    }
  }
  if (depth > 0) {
    panic("括号不匹配：存在 %d 个未闭合的 '('", depth);
  }
}

//检查是否是一组对应的括号表达式
static bool check_parentheses(int p, int q){
  if (tokens[p].type != '(' || tokens[q].type != ')') {
    return false;
  }

  int count = 0;
  for (int i = p; i < q ; i++){
    if (tokens[i].type == '(') {
      count++;
    } else if (tokens[i].type == ')') {
      count--;
    }
    if (count == 0) {
      return false;
    }
  }

  return true;
}

//找到主运算符，返回其在tokens数组中的位置
static int main_operator(int p, int q) {
  int op = -1;
  int min_precedence = 100;   //运算符优先级，初始值为一个较大的数，确保任何运算符的优先级都小于它
  int parentheses_depth = 0;  //括号深度，初始值为0，表示当前不在任何括号内

  for (int i = p; i <= q; i++) {
    if (tokens[i].type == '(') {
      parentheses_depth++;
    } else if (tokens[i].type == ')') {
      parentheses_depth--;
    } else if (parentheses_depth == 0) { // 主运算符一定要在括号外部
      int precedence;
      switch (tokens[i].type) {
        case '+':case '-':
          precedence = 1;
          break;
        case '*':case '/':
          precedence = 2;
          break;
        default:
          continue;  //跳过非运算符token 
      }

      if (precedence <= min_precedence) {
        min_precedence = precedence;
        op = i;
      }
    }
  }

  return op;
}

//计算对应表达式值
static word_t eval(int p, int q) {
  if (p > q) {
    panic("表达式错误");
  }
  else if (p == q) {
    Assert(tokens[p].type == TK_DEC, "表达式错误");
    return atoi(tokens[p].str);
  }
  else if (check_parentheses(p, q) == true) {
    return eval(p + 1, q - 1);
  }
  else {
    int op = main_operator(p, q) ; //找到主运算符位置
    word_t val1 = eval(p, op - 1);
    word_t val2 = eval(op + 1, q);

    switch (tokens[op].type) {
      case '+': return val1 + val2;
      case '-': return val1 - val2;
      case '*': return val1 * val2;
      case '/': return val1 / val2;
      default: panic("请在eval函数中添加运算符的运算逻辑");
    }
  }
}

//表达式词法分析，语法分析，计算表达式值
word_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }

  check_brackets();

  *success = true;
  return eval(0, nr_token - 1);
}
