
#include <Adafruit_NeoPixel.h>
#define PIN 6
#define led_no 60
 
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);
int led_array [led_no][3];
int r;
int g;
int b;

void movelong() {
  
}

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(25544);
  Serial.begin(9600);
}


int whip(int r,int g,int b) {
  for (int n=1; n<led_no; n++)
  {
    strip.setPixelColor(n, r, g, b);
    strip.show();
    delay(1);
    Serial.print("on loop");
  }
}

void writetopixel(){
  for (int n=0; n<led_no; n++)
  {
   strip.setPixelColor(n,led_array[n][0] ,led_array[n][1], led_array[n][2]); 
  }
  strip.show();
  }

void shift(){
  for (int n=led_no; n>0; n--)
  {
      led_array[n][1]= led_array[n-1][1];
      led_array[n][2]= led_array[n-1][2];
      led_array[n][0] = led_array[n-1][0];
  } 
}

void hue(int h)//max  for h  =  768  120 r,g,b
{
  if (h < 256)
  {
    r = h;
    g = 255 - h;
    b = 0;
  }
  else if (h > 255 && h < 512)
  {
   h = h-255;
   b = h;
   r = 255-(h);
   g = 0 ;
  }
  else if (h > 511 )
  {
   h = h-511;
   g = h;
   b = 255-(h);
   r = 0 ;
  }
  
}


void loop() {
  // put your main code here, to run repeatedly:
  
  
  for (int n=0; n<led_no; n++)
  {
      led_array[n][1]= 0;
      led_array[n][2]= 0;
      led_array[n][0] = 0;
  } 
  writetopixel();
  for (int n=1; n<768; n++)
  { 
    hue((n*10)%768);
    led_array[0][1]= r;
    led_array[0][2]= b;
    led_array[0][0] = g;
    shift();
    writetopixel();
    delay(10);
  }
  Serial.print("ok");
  /*
  whip(255,0,0);
  whip(0,255,0);
  whip(0,255,255);
  */
    

}
