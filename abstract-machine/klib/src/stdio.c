#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

#define BUF_SIZE 32

int printf(const char *fmt, ...) {
  panic("Not implemented");
}

//将可变参数按照 fmt 格式化输出到 out 中，返回写入的字符数（不含 \0）
int vsprintf(char *out, const char *fmt, va_list ap) {
  char *p = out;
  while (*fmt) {
    if (*fmt == '%') {
      fmt++;                                          // 跳过 %
      switch (*fmt) {
        case 'd': {                              // 整数
          int num = va_arg(ap, int);
          char buf[BUF_SIZE];
          itoa(num, buf, 10);       // 将整数转换为字符串
          char *s = buf;                    // 工作指针指向 buf，避免后面buf无法自增的问题
          while (*s)  *p++ = *s++;
          fmt++;
          break;
        }
        case 'c':{                                 // 字符
          *p = (char)va_arg(ap, int);    //c语言中...会默认对char进行int类型的提升
          p++;
          fmt++;
          break;
        }
        case 's':{                                 // 字符串
          char *s = va_arg(ap, char *);
          if (s == NULL) 
            panic("空指针!");            // NULL不能读取内容，如果字符串为 NULL，则报错
          while (*s) *p++ = *s++;
          fmt++;
          break;
        }
        case '%':{                                 // 字符 %
          *p = '%';
          p++;
          fmt++;
          break;
        }
        default: {                              // 未知格式，直接输出
          *p = '%';
          p++;
          *p = *fmt;
          p++;
          fmt++;
          break;
        }
      }
    }
    else {
      *p++ = *fmt++;  
    }
  }
  *p = '\0';
  return p - out;
}

//将可变参数按照 fmt 格式化输出到 out 中，返回写入的字符数（不含 \0）
//与vsprintf不同的是，sprintf使用...而不是va_list
int sprintf(char *out, const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  int ret = vsprintf(out, fmt, ap);
  va_end(ap);
  return ret;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
