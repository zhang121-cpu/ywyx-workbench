.PHONY: all run gdb clean latest $(ALL)

RESULT = .result
$(shell > $(RESULT))

COLOR_RED   = \033[1;31m
COLOR_GREEN = \033[1;32m
COLOR_NONE  = \033[0m

ALL = $(basename $(notdir $(shell find tests/. -name "*.c")))

all: $(addprefix Makefile., $(ALL))
	@echo "test list [$(words $(ALL)) item(s)]:" $(ALL)

$(ALL): %: Makefile.%

# Makefile.% 规则：为每个测试源文件生成一个临时 Makefile，并以其启动新的make 进程
#
# --- 自动变量（make 内置）---
#   $@ : 当前"目标"名。例如 Makefile.add-longlong
#   $< : 第一个"依赖"。例如 tests/add-longlong.c
#   $* : stem（茎），即模式中 % 匹配的部分。例如 add-longlong
#   $$ : 字面 $ 符号，传递给 shell 后变成单个 $。$${AM_HOME} → shell 看到 ${AM_HOME}
# ① 生成临时 Makefile（如 Makefile.add-longlong）
#   写入内容示例： NAME = add-longlong
#                 SRCS = tests/add-longlong.c
#                 include ${AM_HOME}/Makefile
# ② 子 make 编译 + ③ 记录结果
#   -s : 静默模式，不打印 make 进出目录信息
#   -f $@ : 指定刚生成的临时 Makefile 作为构建文件

Makefile.%: tests/%.c latest
	@/bin/echo -e "NAME = $*\nSRCS = $<\ninclude $${AM_HOME}/Makefile" > $@
	@if make -s -f $@ ARCH=$(ARCH) $(MAKECMDGOALS); then \
		printf "[%14s] $(COLOR_GREEN)PASS$(COLOR_NONE)\n" $* >> $(RESULT); \
	else \
		printf "[%14s] $(COLOR_RED)***FAIL***$(COLOR_NONE)\n" $* >> $(RESULT); \
	fi
	-@rm -f Makefile.$*

run: all
	@cat $(RESULT)
	@rm $(RESULT)

gdb: all

clean:
	rm -rf Makefile.* build/

latest:
