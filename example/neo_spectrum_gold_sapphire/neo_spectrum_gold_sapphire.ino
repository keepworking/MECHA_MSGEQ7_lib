#include <MSGEQ7.h>
#include <Adafruit_NeoPixel.h>
#define MIN_K_value 100
#define MAX_K_value 200
int K_value = 100;
MSGEQ7 eq;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(40, 6, NEO_GRB + NEO_KHZ800);

uint32_t color_map[40] =
{ 
  0x00efef00,0x00efef00,0x00efef00,0x00efef00,0x00efef00,0x00efef00,0x00efef00,0x005050af,
  0x00efef00,0x00efef00,0x00efef00,0x00efef00,0x00efef00,0x00efef00,0x00efef00,0x005050af,
  0x00efef00,0x00efef00,0x00efef00,0x00efef00,0x00efef00,0x00efef00,0x00efef00,0x005050af,
  0x00efef00,0x00efef00,0x00efef00,0x00efef00,0x00efef00,0x00efef00,0x00efef00,0x005050af,
  0x00efef00,0x00efef00,0x00efef00,0x00efef00,0x00efef00,0x00efef00,0x00efef00,0x005050af
}
;

void setup() {
  eq.init();
  pixels.begin();
  pixels.clear();
}
int cnt = 0;
void loop() {
  eq.poll();
  int max_v = 0;
  pixels.clear();
  for(int i = 0;i < 7;i++){
    int l = eq.getLValue(i);
    int r = eq.getRValue(i);
    int v = (l<r? r:l);
    max_v = (v>max_v? v:max_v);
    for(int j = 0;j < 5;j++){
      if(v > K_value*(5-j)){
        on_pixel(i+(8*j));
      }
    }
  }
  for(int j = 0;j < 5;j++){
    if(max_v > K_value*(5-j)){
      on_pixel(7+(8*j));
    }
  }
  K_value = constrain(max_v/5,MIN_K_value,MAX_K_value);
  pixels.show();
  delay(100);
}

void on_pixel(int index){
   pixels.setPixelColor(index, color_map[index]);
}


