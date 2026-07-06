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

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

// this should be enough
static char buf[65536] = {};   // 随机生成的表达式会放入此缓冲区
static char code_buf[65536 + 128] = {}; // 存放拼接后的完整 C 代码（包含 buf 中的表达式），比 buf 略大以容纳代码模板的其他部分

/*被设定程序，可以输出对应表达式的计算结果，便于后续验证*/
static char *code_format =
"#include <stdio.h>\n"
"int main() { "
"  unsigned result = %s; "    
"  printf(\"%%u\", result); "  // 输出计算结果（无符号十进制）,"前面多了/是转义字符，两个%是为了在后面sprintf输出一个%
"  return 0; "
"}";

static uint32_t choose(uint32_t n) {
  return rand() % n;    // 返回 0 ~ n-1 之间的随机数
}

//生成一个随即数
static void gen_num(){
  uint32_t num = choose(1000);   //生成0~999的随机数
  char str[6];
  sprintf(str, "%uu", num);   //将随机数转换为字符串
  strcat(buf, str);          //将字符串拼接到buf中
}

//生成指定运算符
static void gen(char c){
  char str[2];
  str[0] = c;
  str[1] = '\0';
  strcat(buf, str);
}

//生成随即运算符
static void gen_rand_op(){
  switch (choose(4)) {   
    case 0: gen('+'); break;
    case 1: gen('-'); break;
    case 2: gen('*'); break;
    case 3: gen('/'); break;
  }
}

//概率生成' '放在token之间
static void gen_rand_space(){
  switch (choose(3)) {   
    case 0: gen(' '); break;
    default: break;   //不生成空格
  }
}

// 随机生成一个算术表达式，写入 buf 中
static void gen_rand_expr(int depth) {
  if (depth > 10) {      //递归深度超过10时，直接生成一个数字
    gen_num();
  } else {
    switch (choose(5)) {
      case 0: 
        gen_num(); 
        break;
      case 1: 
        gen('('); 
        gen_rand_space();
        gen_rand_expr(depth + 1); 
        gen_rand_space();
        gen(')'); 
        break;
      default: 
        gen_rand_expr(depth + 1); 
        gen_rand_space();
        gen_rand_op(); 
        gen_rand_space();
        gen_rand_expr(depth + 1); 
        break;
    }
  }
}

// 运行 /tmp/.expr，读取它打印的无符号结果到 *out
// 返回 0 表示“读取成功 + 子进程正常退出”
// 返回 -1 表示任意失败（启动失败、读失败、异常退出等）
static int run_expr_and_get_result(uint32_t *out) {
  int pipefd[2];  // 创建匿名管道：pipefd[0] 读端，pipefd[1] 写端
  if (pipe(pipefd) != 0) return -1;  //pipe作用：给数组分配管道，两元素分别对应缓存对象的读端与写段

  pid_t pid = fork();  //复制当前进程，变成两个进程一起跑，此时返回两个pid，子进程得到的pid为0,父进程获得的pid为子进程的真正pid
  if (pid < 0) {
    close(pipefd[0]);
    close(pipefd[1]);
    return -1;
  }

  if (pid == 0) {
    close(pipefd[0]);
    if (dup2(pipefd[1], STDOUT_FILENO) < 0) _exit(127); //将标准输出指向终端屏幕
    close(pipefd[1]);
    execl("/tmp/.expr", "/tmp/.expr", (char *)NULL);//将当前子进程改为/temp/.expr程序
    _exit(127);
  }

  close(pipefd[1]);

  FILE *rfp = fdopen(pipefd[0], "r");
  if (rfp == NULL) {
    close(pipefd[0]);
    int st;
    waitpid(pid, &st, 0);  //waitpid作用：等待子进程结束，回收资源
    return -1;
  }

  int read_ok = (fscanf(rfp, "%u", out) == 1);
  fclose(rfp);

  int status = 0;
  waitpid(pid, &status, 0);

  if (!read_ok) return -1;                               //如果是子进程崩溃的话，fscanf返回值就是EOF，read_ok为0
  if (WIFSIGNALED(status)) return -1;     //是否被信号杀死，被信号杀死返回非0值
  if (!WIFEXITED(status)) return -1;       //是否正常退出，正常退出返回非0值（其实就是与WIFSIGNALED(status)相反）
  if (WEXITSTATUS(status) != 0) return -1;  //提取退出码

  return 0;
}

int main(int argc, char *argv[]) {
  int seed = time(0);
  srand(seed);    //将种子设置在rand中，便于rand函数生成随机数

  int loop = 1;
  if (argc > 1) {
    sscanf(argv[1], "%d", &loop);   // 默认生成 1 条测试用例，也可通过命令行参数指定数量
  }

  int i;
  for (i = 0; i < loop; i ++) {
    buf[0] = '\0';   // 清空 buf，准备生成新的表达式
    gen_rand_expr(0);
    sprintf(code_buf, code_format, buf);

    FILE *fp = fopen("/tmp/.code.c", "w");
    assert(fp != NULL);
    fputs(code_buf, fp);   //将字符串写入临时 C 文件
    fclose(fp);

    //system作用：在 shell 中执行一条命令，等它跑完再返回     
    int ret = system("gcc /tmp/.code.c -o /tmp/.expr -Werror 2>/dev/null");  
    if (ret != 0) {
      i--;
      continue;    // 编译失败（如表达式有语法错误），跳过本次
    }

    uint32_t result;
    ret = run_expr_and_get_result(&result);
    if (ret != 0) {
      i--;
      continue;
    }

    printf("%u %s\n", result, buf);
  }
  return 0;
}
