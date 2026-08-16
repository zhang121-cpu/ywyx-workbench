#include <stdio.h>
#include <stdlib.h>

#include "Vtop.h"
#include "verilated.h"
#include "verilated_fst_c.h"    // 如果使用 FST 格式

#define PMEM_SIZE 65536*4

static uint8_t pmem[PMEM_SIZE] = {0};

// 这里可以添加代码来加载程序到内存中
static void load_program() {
    FILE *file = fopen("npc/npc.bin","rb");

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    fread(pmem, sizeof(uint8_t), file_size/sizeof(uint8_t), file);
    fclose(file);
}

static uint32_t pmem_read(uint32_t addr, int len) {
    if (addr >= sizeof(pmem)) {
        printf("pmem_read: addr out of range: 0x%x\n", addr);
        exit(-1);
    }
    u_int32_t data = 0;
    for (int i = 0; i < len; i++) {
        data |= pmem[addr + i] << (i * 8);                               //每个数组元素中只存储一个字节的数据，低位在前，高位在后
    }
    return data;
}

static void pmem_write(uint32_t addr, uint32_t data, int len) {
    if (addr >= sizeof(pmem)) {
        printf("pmem_write: addr out of range: 0x%x\n", addr);
        exit(-1);
    }
    for (int i = 0; i < len; i++) {
        pmem[addr + i] = (data >> (i * 8)) & 0xff;               //每个数组元素中只存储一个字节的数据，低位在前，高位在后
    }
}

static void single_cycle() {
    top->clk = 0; 
    top->eval();
    top->clk = 1; 
    top->eval();
}

static void reset(int n) {
    top->rst = 1;
    while (n -- > 0) single_cycle();
    top->rst = 0;
}

int main(int argc, char** argv) {
    VerilatedContext* contextp = new VerilatedContext;
    contextp->commandArgs(argc, argv);
    Vtop* top = new Vtop{contextp};

    contextp->traceEverOn(true);              // 启用跟踪

    // 创建波形文件对象
    VerilatedFstC* tfp = new VerilatedFstC;   // FST 格式

    // 将 top 模块的信号写入波形，跟踪深度为 99（跟踪深度：从顶层模块开始向下追踪多少层子模块的信号）
    top->trace(tfp, 99);
    tfp->open("wave.fst");                    // 生成 wave.fst

    // 将载入程序到内存中，并开始复位
    load_program();

    reset(10);

    while(1) {
        // 取指阶段
        top->instruction = pmem_read(top->pc_state, 4);             //pc每次从内存中读取4个字节的指令
        top->eval();

        // 数据访存（LSU 需要）
        if (top->m_ren) {                          // 读操作
            int len = (top->m_size == 0) ? 1 :     // lb
                      (top->m_size == 1) ? 2 :     // lh
                      4;                          // lw
            top->m_rdata = pmem_read(top->m_addr, len);
            top->eval();  // 更新 m_rdata 后重新求值
        }
        if (top->m_wen) {                          // 写操作
            int len = (top->m_size == 0) ? 1 :     // sb
                      (top->m_size == 1) ? 2 :     // sh
                      4;                          // sw
            pmem_write(top->m_addr, top->m_wdata, len);
        }

        single_cycle();
    }

    tfp->close();
    delete tfp;
    delete top;
    delete contextp;
    return 0;
}
