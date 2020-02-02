#include <SPI.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)


int temperaturemod=0;   //    .123
int temperature=0;    //       123

const int chartSize = 84;

int chart[chartSize];

int Max,Min;

void setup()   
{
  pinMode(13, OUTPUT);

  mlx.begin();
  display.begin();
  display.setContrast(50);

  display.display(); // show splashscreen
  delay(200);
  display.clearDisplay();   // clears the screen and buffer
}

void loop() 
{
  display.clearDisplay();
  display.setCursor(0,0);
  
  temperature = mlx.readObjectTempC();
  temperaturemod = round(mlx.readObjectTempC()*10)%10;
  if (temperaturemod<0)
  temperaturemod*=-1
  
   
 
  display.setTextColor(BLACK);
  
  
  display.setTextSize(1);
  display.print(mlx.readAmbientTempC());
  display.print("C"); // sensor temperature

  //display.setTextSize(1);
  float voltage  = analogRead(0) * 5.0/1023;
   //float voltage = map(analogRead(0), 0, 1024, 0, 5);
  display.setCursor(54,0);
  display.setCursor(54,0);
  display.print(voltage);
  display.print("V"); // battery voltage

  display.setCursor(0,9);
  display.setTextSize(2);
  display.print(temperature);
  display.print(".");
  display.print(temperaturemod);  // MOd without fckin '-10.-8C'
  display.print("C"); //ir temperature
  
  insertToIndex(temperature);
  drawChart();
  
  display.display();
  delay(100);
}

void insertToIndex(int temp)
{
  for (int i=chartSize-1; i>0; i--)
    chart[i]=chart[i-1];

  chart[0]= temp;
}

void drawChart()
{  
  Max=chart[0];
  Min=chart[0];
  
  for (int i=1; i<chartSize; i++)
  {
    if (chart[i]> Max) Max=chart[i];
    if (chart[i]< Min) Min=chart[i];
  }
  
  for (int i=0; i<chartSize; i++) 
  {
   display.drawLine(chartSize-1-i,47, 83-i,  map(chart[i], Min, Max, 47, 24), BLACK); //<23
  }
}
