#include <amtest.h>

#define FPS 30
#define N   32                                       // 网格 32×32

static inline uint32_t pixel(uint8_t r, uint8_t g, uint8_t b) {
  return (r << 16) | (g << 8) | b;                   // RGB 合成 24 位色
}
static inline uint8_t R(uint32_t p) { return p >> 16; } // 取红色分量
static inline uint8_t G(uint32_t p) { return p >> 8; }  // 取绿色分量
static inline uint8_t B(uint32_t p) { return p; }       // 取蓝色分量

static uint32_t canvas[N][N];                        // 每个格子的颜色
static int used[N][N];                               // 螺旋填充标记

static uint32_t color_buf[32 * 32];                  // 单色填充缓冲区

void redraw() {                                      // 将 canvas 绘制到屏幕
  int w = io_read(AM_GPU_CONFIG).width / N;
  int h = io_read(AM_GPU_CONFIG).height / N;
  int block_size = w * h;
  assert((uint32_t)block_size <= LENGTH(color_buf));

  int x, y, k;                                              //y为行号，x为列号
  for (y = 0; y < N; y ++) {
    for (x = 0; x < N; x ++) {
      for (k = 0; k < block_size; k ++) {
        color_buf[k] = canvas[y][x];
      }
      io_write(AM_GPU_FBDRAW, x * w, y * h, color_buf, w, h, false); // 画一个格子
    }
  }
  io_write(AM_GPU_FBDRAW, 0, 0, NULL, 0, 0, true);  // 刷新屏幕
}

static uint32_t p(int tsc) {
  int b = tsc & 0xff;
  return pixel(b * 6, b * 7, b);                     // 随时间变化的颜色
}

void update() {                                      // 更新 canvas 内容（螺旋填色）
  static int tsc = 0;
  static int dx[4] = {0, 1, 0, -1};                  // 四个方向: 右、下、左、上
  static int dy[4] = {1, 0, -1, 0};                  //x为行号，y为列号

  tsc ++;

  for (int i = 0; i < N; i ++)
    for (int j = 0; j < N; j ++) {
      used[i][j] = 0;                                // 重置标记
    }

  int init = tsc * 1;
  canvas[0][0] = p(init); used[0][0] = 1;
  int x = 0, y = 0, d = 0;                          // 从 (0,0) 开始螺旋
  for (int step = 1; step < N * N; step ++) {
    for (int t = 0; t < 4; t ++) {
      int x1 = x + dx[d], y1 = y + dy[d];
      if (x1 >= 0 && x1 < N && y1 >= 0 && y1 < N && !used[x1][y1]) {
        x = x1; y = y1;
        used[x][y] = 1;
        canvas[x][y] = p(init + step / 2);
        break;                                       // 找到下一格，退出方向搜索
      }
      d = (d + 1) % 4;                               // 撞墙/已填，换方向
    }
  }
}

void video_test() {
  unsigned long last = 0;
  unsigned long fps_last = 0;
  int fps = 0;

  while (1) {
    unsigned long upt = io_read(AM_TIMER_UPTIME).us / 1000; // 当前毫秒数
    if (upt - last > 1000 / FPS) {                            // 到帧间隔了
      update();
      redraw();
      last = upt;
      fps ++;
    }
    if (upt - fps_last > 1000) {
      // display fps every 1s
      printf("%d: FPS = %d\n", upt, fps);                    // 每秒打印帧率
      fps_last = upt;
      fps = 0;
    }
  }
}
