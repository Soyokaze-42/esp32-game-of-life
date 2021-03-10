/* Arduino ESP32 game of life For Heltec WiFi Kit 32
 * 2/28/21
*/

#include <U8g2lib.h> //display

#define for_x for (u8g2_uint_t x = 0; x < w; x++)
#define for_y for (u8g2_uint_t y = 0; y < h; y++)
#define for_xy for_x for_y

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, 15, 4, 16);

const uint8_t h = 32;
const uint8_t w = 64;

void setup() {
  //Serial.begin(9600);
  randomSeed(analogRead(17));

  // enable the oled screen
  u8g2.begin();
}

void loop (){
  bool univ[h][w];
	for_xy univ[y][x] = random(9) == 1 ? 1 : 0;
	while (1) {
		//show
    u8g2.clearBuffer();
	  for_y {
		  for_x {
        if (univ[y][x] > 0){
          //u8g2.drawPixel(x,y);
          u8g2.drawPixel(x*2,y*2);
          u8g2.drawPixel(x*2+1,y*2);
          u8g2.drawPixel(x*2,y*2+1);
          u8g2.drawPixel(x*2+1,y*2+1);
        }
  	  }
    }
	  u8g2.sendBuffer();
    //end show

		//evolve
    bool new_u[h][w];
 
	  for_y for_x {
		  int n = 0;
		  for (int y1 = y - 1; y1 <= y + 1; y1++)
			  for (int x1 = x - 1; x1 <= x + 1; x1++)
				  if (univ[(y1 + h) % h][(x1 + w) % w])
					  n++;
 
		  if (univ[y][x]) n--;
		  new_u[y][x] = (n == 3 || (n == 2 && univ[y][x]));
	  }
	  for_y for_x univ[y][x] = new_u[y][x];
    //end evolve
		//usleep(50000);
	}
}