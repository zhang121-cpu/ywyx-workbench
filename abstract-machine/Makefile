# AbstractMachine 内核和库的 Makefile

# ============================================================
# 【语法说明】Makefile 基本概念：
#  - 目标(target): 依赖列表
#        recipe（recipe 必须以 Tab 开头，不能用空格）
#  - $@ : 自动变量，代表当前"目标"的名字
#  - $< : 自动变量，代表第一个"依赖"
#  - $^ : 自动变量，代表所有"依赖"（去重）
#  - $(变量名) 或 ${变量名} : 引用一个变量
#  - .PHONY : 声明"伪目标"，即使存在同名文件也始终执行
#  - 命令前的 @ : 不打印命令本身，只打印命令的输出
# ============================================================

### 通过 `make html` 获取此 Makefile 的更可读版本（需要 python-markdown）
html:                                           # 目标 html（没有依赖，所以每次 make html 都会执行）
	cat Makefile | sed 's/^\([^#]\)/    \1/g' | markdown_py > Makefile.html
.PHONY: html                                    # 声明 html 是伪目标（即使有 html 文件也执行）

## 1. 基本设置和检查

### 默认创建裸机内核镜像
# ifeq (A, B) : 如果 A == B 则执行 ifeq 块，否则跳过。必须用 endif 结束。
# $(MAKECMDGOALS) : make 的特殊变量，值为命令行中指定的目标（如 make xxx 则值为 xxx）
ifeq ($(MAKECMDGOALS),)                         # $(MAKECMDGOALS) 为空 → 用户只敲了 make，没指定目标
  MAKECMDGOALS  = image                         # 将目标设为 image
  .DEFAULT_GOAL = image                         # 同时设置默认目标为 image
endif                                           # ifeq 块结束标记

### 当执行 `make clean/clean-all/html` 时跳过检查
# $(findstring A,B) : 在 B 中查找 A，找到则返回 A，找不到返回空串
# | 在 findstring 中只是普通字符，这里巧妙地用 | 作分隔符同时匹配三个目标
ifeq ($(findstring $(MAKECMDGOALS),clean|clean-all|html),)  # 如果目标不是 clean/clean-all/html

### 打印构建信息
# $(info 文本) : 在 make 解析时直接打印信息到终端，常用于调试
$(info # Building $(NAME)-$(MAKECMDGOALS) [$(ARCH)])

### 检查：环境变量 `$ARCH` 必须在支持的列表中
# $(shell 命令) : 执行 shell 命令并返回其标准输出
# $(notdir 路径) : 去掉路径中的目录部分，只保留文件名
# $(basename 文件) : 去掉文件后缀（如 x86_64-qemu.mk → x86_64-qemu）
ARCHS = $(basename $(notdir $(shell ls $(AM_HOME)/scripts/*.mk)))  # 列出 scripts/ 下所有 .mk 文件，提取架构名
# $(filter A,B) : 从 B 中筛选出匹配模式 A 的单词
ifeq ($(filter $(ARCHS), $(ARCH)), )           # $(ARCH) 不在支持列表中 → filter 返回空
  $(error Expected $$ARCH in {$(ARCHS)}, Got "$(ARCH)")
endif

### 从 `$ARCH` 中提取指令集架构（`ISA`）和平台。例如：`ARCH=x86_64-qemu -> ISA=x86_64; PLATFORM=qemu`
# $(subst 旧,新,文本) : 文本替换，将文本中的"旧"替换为"新"
# $(word n,列表) : 取列表中的第 n 个单词（n 从 1 开始）
ARCH_SPLIT = $(subst -, ,$(ARCH))
ISA        = $(word 1,$(ARCH_SPLIT))
PLATFORM   = $(word 2,$(ARCH_SPLIT))

### 检查是否有需要构建的内容
# $(flavor 变量) : 返回变量的类型（"undefined" / "simple" / "recursive"）
ifeq ($(flavor SRCS), undefined)                # SRCS 变量未定义
  $(error Nothing to build)
endif

### 检查结束
endif                                           # 对应第 2 个 ifeq（跳过检查的 endif）

## 2. 通用编译目标

### 创建目标目录（`build/$ARCH`）
# $(shell pwd) : 执行 pwd 获取当前目录的绝对路径
WORK_DIR  = $(shell pwd)
DST_DIR   = $(WORK_DIR)/build/$(ARCH)
# $(shell mkdir -p ...) : 在 make 解析时创建目录（-p 递归创建父目录）
$(shell mkdir -p $(DST_DIR))

### 编译目标（二进制镜像或归档文件）
IMAGE_REL = build/$(NAME)-$(ARCH)
# $(abspath 路径) : 将相对路径转为绝对路径
IMAGE     = $(abspath $(IMAGE_REL))
ARCHIVE   = $(WORK_DIR)/build/$(NAME)-$(ARCH).a

### 收集要链接的文件：目标文件（`.o`）和库文件（`.a`）
# $(addprefix 前缀,列表) : 给列表中每个单词前面加上前缀
# $(addsuffix 后缀,列表) : 给列表中每个单词后面加上后缀
OBJS      = $(addprefix $(DST_DIR)/, $(addsuffix .o, $(basename $(SRCS))))
# 上面这行的含义：SRCS = "src/main.c src/foo.c"
#   → basename → "src/main src/foo"
#   → addsuffix .o → "src/main.o src/foo.o"
#   → addprefix build/x86_64-qemu/ → "build/x86_64-qemu/src/main.o ..."

# $(sort 列表) : 排序并去重
# := 是"简单展开"赋值（立即求值），= 是"递归展开"赋值（延迟求值）
LIBS     := $(sort $(LIBS) am klib)             # 确保 am 和 klib 必定在 LIBS 中
# LINKAGE 包含所有要链接的 .o 文件（.a 库文件由下方的 LIB_TEMPLATE 添加）
LINKAGE   = $(OBJS)

## 3. 通用编译标志

### （交叉）编译器，例如 mips-linux-gnu-g++
# $(CROSS_COMPILE) : 交叉编译前缀，如 mips-linux-gnu-，本地编译则为空
AS        = $(CROSS_COMPILE)gcc                 # 汇编器（用 gcc 而非 as，因为需要预处理）
CC        = $(CROSS_COMPILE)gcc                 # C 编译器
CXX       = $(CROSS_COMPILE)g++                 # C++ 编译器
LD        = $(CROSS_COMPILE)ld                  # 链接器
AR        = $(CROSS_COMPILE)ar                  # 静态库打包工具
OBJDUMP   = $(CROSS_COMPILE)objdump             # 反汇编工具
OBJCOPY   = $(CROSS_COMPILE)objcopy             # 目标文件格式转换工具
READELF   = $(CROSS_COMPILE)readelf             # ELF 文件信息查看工具

### 编译标志
# INC_PATH : 头文件搜索路径（项目 include + 各个库的 include）
INC_PATH += $(WORK_DIR)/include $(addsuffix /include/, $(addprefix $(AM_HOME)/, $(LIBS)))
# $(addprefix -I, $(INC_PATH)) : 给每个路径加上 -I 前缀
INCFLAGS += $(addprefix -I, $(INC_PATH))

ARCH_H := arch/$(ARCH).h
# -D宏名=值 : 定义 C 预处理宏，等价于在 C 代码中写 #define
# \" 用于在 Makefile 中输出字面双引号
# $(shell echo ... | tr a-z A-Z) : 将小写转为大写（如 x86_64 → X86_64）
# tr - _ : 将 - 替换为 _
CFLAGS   += -O2 -MMD -Wall -Werror $(INCFLAGS) \
            -D__ISA__=\"$(ISA)\" -D__ISA_$(shell echo $(ISA) | tr a-z A-Z)__ \
            -D__ARCH__=$(ARCH) -D__ARCH_$(shell echo $(ARCH) | tr a-z A-Z | tr - _) \
            -D__PLATFORM__=$(PLATFORM) -D__PLATFORM_$(shell echo $(PLATFORM) | tr a-z A-Z | tr - _) \
            -DARCH_H=\"$(ARCH_H)\" \
            -fno-asynchronous-unwind-tables -fno-builtin -fno-stack-protector \
            -Wno-main -U_FORTIFY_SOURCE -fvisibility=hidden
CXXFLAGS +=  $(CFLAGS) -ffreestanding -fno-rtti -fno-exceptions
ASFLAGS  += -MMD $(INCFLAGS)
# $(addprefix -T, $(LDSCRIPTS)) : 给每个链接脚本加上 -T 前缀（ld 的 -T 指定链接脚本）
LDFLAGS  += -z noexecstack $(addprefix -T, $(LDSCRIPTS))

## 4. 架构特定的配置

### 引入架构特定的配置（例如来自 `scripts/x86_64-qemu.mk`）
# -include : 包含另一个 Makefile。前面的 - 表示文件不存在也不报错
-include $(AM_HOME)/scripts/$(ARCH).mk

## 5. 编译规则

# ============================================================
# 【语法说明】模式规则 (Pattern Rules)：
#   %.o : %.c   表示"任何 .o 文件都可由同名的 .c 文件编译而来"
#   $@ = 目标（即 .o 文件）
#   $< = 第一个依赖（即 .c 文件）
#   $(realpath $<) : 将依赖转为绝对路径
#   $(dir $@) : 提取目标的目录部分
# ============================================================

### 规则（编译）：单个 `.c` -> `.o`（gcc）
# @mkdir -p ... : @ 前缀表示执行但不打印该命令本身
$(DST_DIR)/%.o: %.c
	@mkdir -p $(dir $@) && echo + CC $<
	@$(CC) -std=gnu11 $(CFLAGS) -c -o $@ $(realpath $<)

### 规则（编译）：单个 `.cc` -> `.o`（g++）
$(DST_DIR)/%.o: %.cc
	@mkdir -p $(dir $@) && echo + CXX $<
	@$(CXX) -std=c++17 $(CXXFLAGS) -c -o $@ $(realpath $<)

### 规则（编译）：单个 `.cpp` -> `.o`（g++）
$(DST_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@) && echo + CXX $<
	@$(CXX) -std=c++17 $(CXXFLAGS) -c -o $@ $(realpath $<)

### 规则（编译）：单个 `.S` -> `.o`（gcc，预处理后调用汇编器）
$(DST_DIR)/%.o: %.S
	@mkdir -p $(dir $@) && echo + AS $<
	@$(AS) $(ASFLAGS) -c -o $@ $(realpath $<)

# ifeq : 如果目标是 archive，走静态库打包；否则走 ELF 镜像链接
ifeq ($(MAKECMDGOALS),archive)
### 规则（归档）：目标文件（`*.o`）-> `ARCHIVE.a`（ar）
# ar rcs : r=替换/添加, c=创建, s=建立索引
$(ARCHIVE): $(OBJS)
	@echo + AR "->" $(shell realpath $@ --relative-to .)
	@$(AR) rcs $@ $^                     
else

# ============================================================
# 【语法说明】define ... endef : 定义多行变量/宏
#   $(1) 表示宏的第一个参数（调用时传入）
#   $$(AM_HOME) : 双 $ 转义，使得变量在宏展开时才求值
#   force : 一个永远不会存在的伪目标，确保每次都重新构建
#   -s : make 的静默模式，不打印进入/离开目录的信息
#   -C : make 的 -C 选项，先切换到指定目录再执行
# ============================================================

# $(1): 库名称（调用时传入，如 am、klib）
define LIB_TEMPLATE =                           # 定义一个名为 LIB_TEMPLATE 的宏
$$(AM_HOME)/$(1)/build/$(1)-$$(ARCH).a: force
	@$$(MAKE) -s -C $$(AM_HOME)/$(1) archive
LINKAGE += $$(AM_HOME)/$(1)/build/$(1)-$$(ARCH).a
endef                                           # 宏定义结束

### 规则（递归 make）：构建依赖库（am, klib, ...）
# $(foreach 变量,列表,操作) : 遍历列表，对每个元素执行操作
# $(call 宏名,参数) : 调用一个宏（由 define 定义），$(1)=参数
# $(eval ...) : 将文本作为 Makefile 语法求值执行
# 这三者组合：对 LIBS 中的每个库，调用 LIB_TEMPLATE 宏生成规则并执行
$(foreach lib, $(LIBS), $(eval $(call LIB_TEMPLATE,$(lib))))
endif

### 规则（链接）：目标文件（`*.o`）和库文件（`*.a`）-> `IMAGE.elf`，最终打包进镜像的 ELF 二进制文件（ld）
$(IMAGE).elf: $(LINKAGE) $(LDSCRIPTS)
	@echo \# Creating image [$(ARCH)]          
	@echo + LD "->" $(IMAGE_REL).elf
# ifneq (A,B) : 如果 A不= B
# 如果 ARCH 包含 "native"（本地编译），用 g++ 链接
ifneq ($(filter $(ARCH),native),)
	@$(CXX) -o $@ -Wl,--whole-archive $(LINKAGE) -Wl,-no-whole-archive $(LDFLAGS_CXX)
else                                            # 否则（交叉编译），用 ld 链接
	@$(LD) $(LDFLAGS) -o $@ --start-group $(LINKAGE) --end-group
endif                                           # ifneq 结束

### 规则（`#include` 依赖）：引入 gcc 通过 `-MMD` 生成的 `.d` 文件
# -MMD : gcc 编译时自动生成 .d 文件（记录源文件依赖的头文件）
# -include : 包含 .d 文件，前面的 - 表示文件不存在不报错
# 这样当头文件变化时，make 能自动检测到并重新编译相关源文件
-include $(addprefix $(DST_DIR)/, $(addsuffix .d, $(basename $(SRCS))))

## 6. 杂项

### 构建顺序控制
# 依赖链：image → image-dep → $(IMAGE).elf
# 用户执行 make image 时，会先构建 image-dep，而 image-dep 依赖 $(IMAGE).elf
image: image-dep
archive: $(ARCHIVE)
image-dep: $(IMAGE).elf
# .PHONY 可一次声明多个伪目标
.PHONY: image image-dep archive run

### 强制重新构建规则
# force 是一个没有 recipe 的目标，永远被视为"需要更新"
# 任何依赖 force 的目标都会被强制重新构建
force:
.PHONY: force

### 清理单个项目（删除 `build/`）
clean:
	rm -rf Makefile.html $(WORK_DIR)/build/
.PHONY: clean

### 清理深度2以内的所有子项目（忽略错误）
# find . -mindepth 2 -name Makefile : 查找当前目录下深度 ≥2 的所有 Makefile
# $(dir ...) : 提取每个文件路径的目录部分
CLEAN_ALL = $(dir $(shell find . -mindepth 2 -name Makefile))
clean-all: $(CLEAN_ALL) clean                   # 先清理子项目，再清理本目录
$(CLEAN_ALL):                                   # 对每个子项目目录执行 clean
# -@ : - 表示忽略错误继续执行，@ 表示不打印命令本身
	-@$(MAKE) -s -C $@ clean                 
.PHONY: clean-all $(CLEAN_ALL)
