  #include <Adafruit_GFX.h>
  #include <Adafruit_SSD1306.h>
  #include <Wire.h>
  #define SCREEN_WIDTH 128 // OLED display width, in pixels
  #define SCREEN_HEIGHT 64 // OLED display height, in pixels
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

  // Button pins
  const int measureb = 15;
  const int plusb = 14;
  const int minusb = 16;
  
  // Variables
  float volts;
  float microamps;
  float lux;
  float aperture[] = {1.4,2.0,2.8,4.0,5.6,8.0,11.0,16.0,22.0};
  int aindex = 0;
  int shutterspd[] = {30,15,8,4,2,1,2,4,8,15,30,60,125,250,500,1000};
  int iso[] = {50,100,200,400,800,1600,3200,6400};
  int isoindex = 0;
  int ev = 0;
  int x;
  int count;
  int firstcheck;

void setup() {
  Serial.begin(115200);
  
  pinMode(measureb, INPUT_PULLUP);
  pinMode(plusb, INPUT_PULLUP);
  pinMode(minusb, INPUT_PULLUP);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  display.clearDisplay();
  display.setRotation(2);
}

void loop() {
  volts = analogRead(A1) * 5.0 / 1024.0;
  microamps = 1000000 * (volts / 10000.0); // 10k resistor onboard
  lux = microamps * 2.0;

  x = 2.5;
  ev = 0;
  while (lux > x + (x/2)){
    x = x * 2;
    ev++;
  }

  //Button Commands
  if (digitalRead(measureb) == LOW){// Take Measurement
    if (digitalRead(plusb) == LOW){ // +1 stop ISO
      if (isoindex < 7){
        isoindex++;
      }
    } 

    if (digitalRead(minusb) == LOW){ // -1 stop ISO
      if (isoindex > 0){
        isoindex--;
      }
    }

    firstcheck = 1; // To show lines on first boot
    count = ev - 1; // First ISO entry is 50 iso, 1 stop under normal
    count = count + isoindex; // Account for ISO
    count = count - aindex; // Aperture 0 is F/1.4 | 1 sec exp. at EV1 with ISO 100
    count = count + 4; // Because 1s is in Array[5]
  }
  
  if (digitalRead(measureb) == HIGH){// Only increase if measure button isn't pressed
    if (digitalRead(plusb) == LOW){
      if (aindex < 8){
        if (count > 0){
        aindex++;
        count--;
        }
      }
    }

    if (digitalRead(minusb) == LOW){
      if (aindex > 0){
        if (count < 15){
        aindex--;
        count++;
        }
      }
    }
  }

  // Header text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Shutter Speed:");
  display.setTextSize(2);
  display.setCursor(112, 0);
  display.print("A");
  
  // Shutter Speed
  display.setTextSize(3);
  display.setCursor(0, 12);
  if (count <= 5){
    if (firstcheck == 0) {
      display.print("----");
    }
    else {
      display.print(shutterspd[count]);
      display.print("s");
    }
  }
  else{
    if (firstcheck == 0) {
      display.print("----");
    }
    else {
      display.print("1/");
      display.print(shutterspd[count]);
      display.print("s");
    }
  }
  
  // Display Aperture, ISO and EV/LUX
  display.setTextSize(1);
  display.setCursor(0,40);
  display.print("APERTURE: ");
  display.print(aperture[aindex],1);
  display.setCursor(0, 48);
  display.print("ISO: ");
  display.print(iso[isoindex]);
  display.setCursor(0, 56);
  display.print("IEV/LUX: ");
  display.print(ev);
  display.print(" / ");
  display.print(lux);
  display.display();
  display.clearDisplay(); 
  delay(75);
}
