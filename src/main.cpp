#include <M5Unified.h>
#include <stdint.h>
#define U8G2_FONT_SECTION(name) 
#include "u8g2_font_FreeSans.h"

static M5GFX &display = M5.Display;
LGFX_Sprite canvas(&display);

static const lgfx::U8g2font u8g2font1(u8g2_font_FreeSansBoldOblique92pt7b);
static const lgfx::U8g2font u8g2font2(u8g2_font_FreeSansBoldOblique40pt7b);
static const lgfx::U8g2font u8g2font3(u8g2_font_FreeSansBoldOblique42pt7b);
static const lgfx::U8g2font u8g2font4(u8g2_font_FreeSansBoldOblique32pt7b);
static const lgfx::U8g2font u8g2font5(u8g2_font_FreeSansBoldOblique18pt7ba);

static std::int32_t lcd_width;
static std::int32_t lcd_height;

void RightAlignAdj(LGFX_Sprite* disp, int val, int* x);
void DrawParameter(int idx, LGFX_Sprite* disp, int line, float val, int format);

void setup()
{
  M5.begin();

  if (display.width() < display.height())
  {
    display.setRotation(display.getRotation() ^ 3);
  }
  display.setColorDepth(16);

  lcd_width = display.width();
  lcd_height = display.height();
  canvas.setColorDepth(16);
  canvas.createSprite(lcd_width, lcd_height);
}

void loop()
{
  static float cnt = 0;
  static int idx = 6;

  canvas.clear();
  switch (idx)
  {
  case 2:
  case 3:
    DrawParameter(idx, &canvas, 0, cnt, 1);
    break;
  case 4:
    DrawParameter(idx, &canvas, 0, cnt, 1);
    DrawParameter(idx, &canvas, 1, cnt, 1);
    DrawParameter(idx, &canvas, 2, cnt, 1);
    DrawParameter(idx, &canvas, 3, cnt, 1);
    break;
  case 1:
  case 5:
  case 6:
    DrawParameter(idx, &canvas, 0, cnt, 1);
    DrawParameter(idx, &canvas, 1, cnt, 1);
    break;
  }
  canvas.pushSprite(0, 0);

  cnt += 0.1;
  if (cnt >= 30)
  {
    cnt = 0;
    idx--;
    if (idx == 0)	idx = 6;
  }

  delay(10);
}

void DrawParameter(int idx, LGFX_Sprite* disp, int line, float val, int format)
{
  char str[32];
  int rx;
  int adjval;

  dtostrf((int)(val * pow(10, format)) / (float)pow(10, format), 7, format, str);
  adjval = ((int)(val * pow(10, format)) % 10);

  disp->setTextColor(TFT_WHITE);
  disp->setTextDatum(textdatum_t::top_left);

  if ((idx == 1) || (idx == 4)) {
    disp->drawRect(0, 0, 240, 240, TFT_WHITE);
    if (idx == 1) {
      disp->setFont(&u8g2font1);
      rx = 240 - 4 - disp->textWidth(str);
      RightAlignAdj(disp, adjval, &rx);
      disp->drawString(str, rx, (line * 120) + 17);
    }
    else {
      disp->setFont(&u8g2font2);
      rx = 240 - 4 - disp->textWidth(str);
      RightAlignAdj(disp, adjval, &rx);
      disp->drawString(str, rx, (line * 60) + 2);
    }
  }
  else if ((idx == 2) || (idx == 5)) {
    disp->drawRect(0, 0, 160, 80, TFT_WHITE);
    if (idx == 2) {
      disp->setFont(&u8g2font3);
      rx = 160 - 7 - disp->textWidth(str);
      RightAlignAdj(disp, adjval, &rx);
      disp->drawString(str, rx, (line * 40) + 12);
    }
    else {
      disp->setFont(&fonts::FreeSansBoldOblique24pt7b);
      rx = 160 - 4 - disp->textWidth(str);
      RightAlignAdj(disp, adjval, &rx);
      disp->drawString(str, rx, (line * 40) + 0);
    }
  }
  else if ((idx == 3) || (idx == 6)) {
    disp->drawRect(0, 0, 128, 64, TFT_WHITE);
    if (idx == 3) {
      disp->setFont(&u8g2font4);
      rx = 128 - 8 - disp->textWidth(str);
      RightAlignAdj(disp, adjval, &rx);
      disp->drawString(str, rx, (line * 32) + 10);
    }
    else {
      disp->setFont(&fonts::FreeSansBoldOblique18pt7b);
      rx = 128 - 4 - disp->textWidth(str);
      RightAlignAdj(disp, adjval, &rx);
      disp->drawString(str, rx, (line * 32) + 2);
    }
  }
}

// FreeSansBoldOblique前提の右揃え調整
void RightAlignAdj(LGFX_Sprite* disp, int val, int* x)
{
  int diff = 0;
  int height = disp->fontHeight();

  switch (height)
  {
  case 89:	// u8g2_font_FreeSansBoldOblique92pt7b
    if (val == 0) diff = -5;
    if (val == 1) diff = -12;
    if (val == 2) diff = -3;
    if (val == 3) diff = -5;
    if (val == 4) diff = -7;
    if (val == 5) diff = -2;
    if (val == 6) diff = -4;
    if (val == 7) diff = +3;
    if (val == 8) diff = -4;
    if (val == 9) diff = -5;
    break;
  case 56:	// u8g2_font_FreeSansBoldOblique42pt7b
    if (val == 0) diff = +0;
    if (val == 1) diff = -4;
    if (val == 2) diff = +1;
    if (val == 3) diff = +0;
    if (val == 4) diff = -1;
    if (val == 5) diff = +2;
    if (val == 6) diff = +1;
    if (val == 7) diff = +5;
    if (val == 8) diff = +0;
    if (val == 9) diff = +0;
    break;
  case 54:	// u8g2_font_FreeSansBoldOblique40pt7b
    if (val == 0) diff = +0;
    if (val == 1) diff = -4;
    if (val == 2) diff = +1;
    if (val == 3) diff = +0;
    if (val == 4) diff = -2;
    if (val == 5) diff = +1;
    if (val == 6) diff = +0;
    if (val == 7) diff = +4;
    if (val == 8) diff = +0;
    if (val == 9) diff = -1;
    break;
  case 48:	// u8g2_font_FreeSansBoldOblique36pt7b
    if (val == 0) diff = +0;
    if (val == 1) diff = -3;
    if (val == 2) diff = +1;
    if (val == 3) diff = +0;
    if (val == 4) diff = -1;
    if (val == 5) diff = +2;
    if (val == 6) diff = +1;
    if (val == 7) diff = +4;
    if (val == 8) diff = +1;
    if (val == 9) diff = +0;
    break;
  case 42:	// u8g2_font_FreeSansBoldOblique32pt7b
    if (val == 0) diff = +0;
    if (val == 1) diff = -3;
    if (val == 2) diff = +1;
    if (val == 3) diff = +0;
    if (val == 4) diff = -1;
    if (val == 5) diff = +1;
    if (val == 6) diff = +1;
    if (val == 7) diff = +4;
    if (val == 8) diff = +0;
    if (val == 9) diff = +0;
    break;
  case 46:	// FreeSansBoldOblique24pt7b
    if (val == 1) diff = -3;
    if (val == 2) diff = +1;
    if (val == 4) diff = -1;
    if (val == 5) diff = +1;
    if (val == 7) diff = +3;
    break;
  case 35:	// FreeSansBoldOblique18pt7b
    if (val == 1) diff = -2;
    if (val == 2) diff = +1;
    if (val == 3) diff = +1;
    if (val == 5) diff = +1;
    if (val == 6) diff = +1;
    if (val == 7) diff = +3;
    if (val == 8) diff = +1;
    break;
  default:
    break;
  }

  *x += diff;
}
