# DPI-C 示例 Makefile
# 使用方法：make        编译并运行
#          make clean  清理

VERILATOR = verilator
VFLAGS    = --cc --exe --build -Wall --trace

all: build

# Verilator 会：
#   1. 读取 top.v，发现 import "DPI-C" 的函数 add
#   2. 自动生成 Vtop__Dpi.h（声明 add 的头文件）
#   3. 把 driver.cpp（add 的实现）和生成的 C++ 代码一起编译
build:
	$(VERILATOR) $(VFLAGS) top.v driver.cpp dpi_func.cpp
	./obj_dir/Vtop

clean:
	rm -rf obj_dir wave.fst
