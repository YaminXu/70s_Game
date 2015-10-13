//70's Arduino TV game
//by XuYaMin 2014.1.15
#include <TVout.h>
#include <fontALL.h>
TVout TV;

int rad = 2;        
float xpos, ypos;       
float  xspeed_p = 2.8;  
float  yspeed_p = -2.2;  
float  xspeed = 2.8;  
float  yspeed = -2.2;  
int wind_force=0;
float force=0.2;
int  enmey_pos=100;
int rand_pos=0;
int t=1000;
int hit=0;

void setup() {
  pinMode(3, OUTPUT);     
  TV.begin(PAL,120,96);
  TV.delay(2000);
  TV.select_font(font6x8);
  TV.print(22,24,"Monster will be back...");
  TV.tone(100, 500);
  TV.delay(1000);
  TV.tone(200, 500);
  TV.delay(1000);
  TV.tone(300, 500);
  TV.delay(1000);  
  TV.clear_screen();
  TV.select_font(font8x8);
  TV.print(12,35,"POTATO GUN !");
  TV.tone(100, 1000);
  TV.delay(1000);  
  TV.select_font(font6x8);
  TV.print(2,80,"   XuYaMin 2014");  
  TV.tone(150, 500);
  TV.delay(4000);
  TV.clear_screen();  
  xpos = 10;
  ypos = 80;
  //Serial.begin(9600);
  pinMode(2, INPUT);  
}

void loop() 
{
  float deg;   
  float wind_show=0;
  TV.clear_screen();
  xspeed=xspeed+ (float(wind_force)-50.0)*0.0004;
  yspeed=yspeed+force;
  xpos = xpos +  xspeed  ;
  ypos = ypos +  yspeed  ;
  TV.draw_line(0,95,120,95,1);  
  TV.draw_rect(1,90,14,5,WHITE);
  TV.draw_line(10,78,18,95,1);  
  deg=(analogRead(A0)*0.0005)+2.62;
  xspeed_p =  sin( deg )*6;  
  yspeed_p =  cos( deg )*6;
  TV.draw_line(5,95-5, (xspeed_p*4)+5,(yspeed_p*4)+95-5, 1);  
  TV.draw_line(5,95-5, (xspeed_p*4)+5,(yspeed_p*4)+95-5, 1); 
  if(ypos<1||ypos>90||xpos<1||xpos>119)
  {
    if(ypos<95)
    {
      if (wind_force%5==0)
        TV.print(enmey_pos-25,82,"ZZzz.");
      TV.draw_line(xpos,ypos,xpos-10,ypos-6,1); 
      TV.draw_line(xpos,ypos,xpos+10,ypos-6,1); 
      TV.draw_line(xpos,ypos,xpos-5,ypos-6,1); 
      TV.draw_line(xpos,ypos,xpos+5,ypos-6,1); 
      TV.draw_line(xpos,ypos,xpos,ypos-8,1); 
      TV.tone(100, 100);
      wind_force=random(100);
    }
    //TV.noTone();
    xspeed=yspeed=0;
    xpos = 1;
    ypos = 95;
    //Serial.println(ypos);
    TV.draw_circle(3, 86, 2,WHITE);
    if(digitalRead(2)==0)
    {
      t=1000;
      xspeed=xspeed_p;
      yspeed=yspeed_p;
      (enmey_pos--)+20;
      TV.draw_circle(3, 86, 2,0);
    }
  }
  else
  {
    TV.tone(t, 20);
  }
  TV.draw_line(enmey_pos,74,enmey_pos+15,74,WHITE);
  TV.draw_line(enmey_pos+15,74,enmey_pos+15,94,WHITE);
  TV.draw_line(enmey_pos,94,enmey_pos+15,94,WHITE);
  TV.draw_line(enmey_pos,90,enmey_pos,94,WHITE);
  TV.draw_line(enmey_pos,90,enmey_pos+10,87,WHITE);
  TV.draw_line(enmey_pos,84,enmey_pos+10,87,WHITE);
  TV.draw_line(enmey_pos,74,enmey_pos,84,WHITE);
  TV.draw_circle(enmey_pos+5,79,2,WHITE);  
  TV.draw_line(enmey_pos+3,74,enmey_pos+3,68,WHITE);
  TV.draw_line(enmey_pos+6,74,enmey_pos+6,68,WHITE);
  TV.draw_line(enmey_pos+9,74,enmey_pos+9,68,WHITE);
  TV.draw_line(enmey_pos+12,74,enmey_pos+12,68,WHITE);
  TV.draw_circle((uint8_t)xpos, (uint8_t)ypos, (uint8_t)rad,WHITE);
  if(xpos>enmey_pos-5 && xpos<enmey_pos+15&&ypos>82)
  {
    if(wind_force%5==0)
      TV.print(enmey_pos+3,58,"oh!");
    else if(wind_force%5==1)
      TV.print(enmey_pos,56,"@#!!!");
    else if(wind_force%5==2)
      TV.print(enmey_pos-2,58,"ku..pa..");    
    TV.tone(100, 50);
    TV.draw_rect(1,1,119,95,WHITE,INVERT);
    TV.delay(50);
    TV.tone(300, 50);
    TV.draw_rect(1,1,119,95,WHITE);
    TV.delay(50);
    TV.tone(100, 50);
    TV.draw_rect(1,1,119,95,WHITE,INVERT);
    TV.delay(50);
    TV.tone(300, 20);
    TV.draw_rect(1,1,119,95,WHITE);
    TV.delay(50);
    //TV.clear_screen();
    hit++;
    wind_force=random(100);
  }
  TV.draw_line(1,4,30,4,WHITE);
  TV.draw_rect(30-((deg-2.6)*50),1,3,6,WHITE);
  TV.select_font(font6x8);
  TV.print(48,0,"life");
  for(unsigned char i=0;i<(20-hit);i++)  
  {
    TV.draw_line(80+i*2,0,80+i*2,5,WHITE);
  }
  TV.select_font(font6x8);
  TV.print(0,28,"wind");
  wind_show=map(wind_force,0,100,30,90);
  if (wind_show>60)
  { 
    TV.draw_line(wind_show,30,60,30,WHITE);
    TV.draw_line(wind_show,30,wind_show-3,27,WHITE);
    TV.draw_line(wind_show,30,wind_show-3,33,WHITE);
  }
  else
  {
    TV.draw_line(wind_show,30,60,30,WHITE);
    TV.draw_line(wind_show,30,wind_show+3,27,WHITE);
    TV.draw_line(wind_show,30,wind_show+3,33,WHITE);
  }
  if(enmey_pos<20)
  {
    TV.print(0,63,"&%papa..@.#."); 
    TV.tone(300, 150);
    TV.draw_rect(1,1,119,95,WHITE,INVERT);
    TV.delay(150);
    TV.tone(500, 150);
    TV.draw_rect(1,1,119,95,WHITE);
    TV.delay(150);
    TV.tone(300, 150);
    TV.draw_rect(1,1,119,95,WHITE,INVERT);
    TV.delay(150);
    TV.tone(500, 150);
    TV.draw_rect(1,1,119,95,WHITE);
    TV.delay(150);
    TV.select_font(font6x8);
    TV.clear_screen();
    TV.print(30,44,"GAME OVER");
    TV.delay(5500);
    TV.clear_screen();
  }
  if(hit>5)
  {
    TV.draw_line(enmey_pos+8,74,enmey_pos+15,91,WHITE);
  }
  if(hit>10)
  {
    TV.draw_line(enmey_pos+15,74,enmey_pos+12,88,WHITE);
  }
  if(hit>15)
  {
    TV.draw_line(enmey_pos+2,78,enmey_pos+5,85,WHITE);
  }
  if(hit>20)
  {   
    TV.print(0,63,"win!"); 
    TV.tone(500, 500);
    TV.delay(500);
    TV.draw_rect(1,1,119,95,WHITE,INVERT);
    TV.tone(600, 500);
    TV.delay(500);
    TV.tone(800, 500);
    TV.delay(500);
    TV.tone(1000, 500);

    TV.select_font(font6x8);
    TV.clear_screen();
    TV.print(30,44,"GOOD JOB!");
    TV.delay(5500);
  }
  t=t-5;
  TV.delay(30);
}



