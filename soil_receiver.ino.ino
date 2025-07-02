clude <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";

int soilValue = 0;

void setup() {
  Serial.begin(9600);

  // OLED setup
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Waiting for data...");
  display.display();

  // NRF24 setup
  radio.begin();
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    radio.read(&soilValue, sizeof(soilValue));
    Serial.print("Received Soil Moisture: ");
    Serial.println(soilValue);

    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.println("Soil Moisture");
    display.setTextSize(2);
    display.setCursor(0, 20);
    display.print(soilValue);
    display.display();
  }
  delay(1000);
}
