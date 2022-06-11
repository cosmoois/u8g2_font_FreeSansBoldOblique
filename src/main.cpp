#include <M5Unified.h>
#include <stdint.h>
#define U8G2_FONT_SECTION(name) 
#include "u8g2_font_FreeSans.h"

static M5GFX &display = M5.Display;
LGFX_Sprite canvas(&display);

static const lgfx::U8g2font u8g2font92(u8g2_font_FreeSansBoldOblique92pt7b);
static const lgfx::U8g2font u8g2font40(u8g2_font_FreeSansBoldOblique40pt7b);
static const lgfx::U8g2font u8g2font42(u8g2_font_FreeSansBoldOblique42pt7b);
static const lgfx::U8g2font u8g2font32(u8g2_font_FreeSansBoldOblique32pt7b);
static const lgfx::U8g2font u8g2font18a(u8g2_font_FreeSansBoldOblique18pt7ba);

void DrawParameter(int idx, LGFX_Sprite* disp, int line, float val, int format);

void setup()
{
  M5.begin();

  if (display.width() < display.height())
  {
    display.setRotation(display.getRotation() ^ 3);
  }
  display.setColorDepth(16);

  int lcd_width = display.width();
  int lcd_height = display.height();
  canvas.setColorDepth(16);
  canvas.createSprite(lcd_width, lcd_height);
}

void loop()
{
  static float cnt = 0;
  static int idx = 1;

  canvas.clear();
  switch (idx)
  {
  case 2:
  case 3:
    DrawParameter(idx, &canvas, 0, cnt, 1);
    break;
  case 4:
    DrawParameter(idx, &canvas, 0, cnt,      2);
    DrawParameter(idx, &canvas, 1, cnt,      1);
    DrawParameter(idx, &canvas, 2, cnt * 10, 0);
    DrawParameter(idx, &canvas, 3, cnt,      0);
    break;
  case 1:
  case 5:
  case 6:
    DrawParameter(idx, &canvas, 0, cnt, 1);
    DrawParameter(idx, &canvas, 1, cnt, 0);
    break;
  }
  canvas.pushSprite(0, 0);

  cnt += 0.1;
  if (cnt >= 25)
  {
    cnt = 0;
    idx++;
    if (idx > 6)	idx = 1;
  }

  // unsigned long timecnt;
  // do {
  //   timecnt = millis();
  // } while (timecnt % 1000 != 0);
}

void DrawParameter(int idx, LGFX_Sprite* disp, int line, float val, int format)
{
  String Str_set;
  char str[32];
  int num_size;   // 数字フォント基準幅（フォント毎に固定：調整不可）
  int dot_size;   // 小数点フォント幅（フォント毎に固定：調整不可）
  int x_adj;      // x軸右寄せ調整値（フォント毎に固定：調整不可）

  int rx;         // 右寄せ位置（サンプルとしてディスプレイの右端を指定）
  int line_space; // 行間隔（サンプルとしてディスプレイを１，２，４等分する値を指定）
  int y_offset;   // Y軸オフセット（サンプルとして行の中央になるように指定）

  if (format == 0) {
    Str_set = String((int)val);
  } else {
    Str_set = String(val, format);
  }
  Str_set.toCharArray(str, sizeof(str));

  disp->setTextColor(TFT_WHITE);
  disp->setTextDatum(textdatum_t::top_left);

  if ((idx == 1) || (idx == 4)) {
    disp->drawRect(0, 0, 240, 240, TFT_YELLOW);
    rx = 240;
    if (idx == 1) {
      disp->setFont(&u8g2font92); num_size = 65;  dot_size = 32;  x_adj = 17;
      line_space = 120;
      y_offset = 16;
    }
    else {
      disp->setFont(&u8g2font40); num_size = 40;  dot_size = 20;  x_adj = 12;
      line_space = 60;
      y_offset = 4;
    }
  }
  else if ((idx == 2) || (idx == 5)) {
    disp->drawRect(0, 0, 160, 80, TFT_YELLOW);
    rx = 160;
    if (idx == 2) {
      disp->setFont(&u8g2font42); num_size = 42;  dot_size = 21;  x_adj = 12;
      line_space = 0; // １行のみ表示のためダミー値をセット
      y_offset = 13;
    }
    else {
      disp->setFont(&fonts::FreeSansBoldOblique24pt7b); num_size = 26;  dot_size = 13;  x_adj = 7;
      line_space = 40;
      y_offset = 1;
    }
  }
  else if ((idx == 3) || (idx == 6)) {
    disp->drawRect(0, 0, 128, 64, TFT_YELLOW);
    rx = 128;
    if (idx == 3) {
      disp->setFont(&u8g2font32); num_size = 32;  dot_size = 16;  x_adj = 9;
      line_space = 0; // １行のみ表示のためダミー値をセット
      y_offset = 11;
    }
    else {
      disp->setFont(&fonts::FreeSansBoldOblique18pt7b); num_size = 19;  dot_size = 9;   x_adj = 4;
      line_space = 32;
      y_offset = 2;
    }
  }

  disp->drawString(str, rx - (strlen(str) * num_size) - (format ? 0 : dot_size) + x_adj, (line * line_space) + y_offset);
}
