#include <Arduino.h>
#include <ArduinoJson.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735>
#include <WiFi.h>
#include <SpotifyESP32.h>
#include <SPI.h>

char* SSID = "HP";
char* PASSWORD = "71213599";

const char* CLIENT_ID = "CLIENT_ID";
const char* CLIENT_SECRET = "CLIENT_SECRET";

Spotify sp(CLIENT_ID, CLIENT_SECRET);

#define TFT_CS 1
#define TFT_RST 2
#define TFT_DC 3
#define TFT_SCLK 4
#define TFT_MOSI 5

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

void setup() {
  Serial.begin(115200);
  WiFi.begin(SSID, PASSWORD);
  Serial.print("Connecting to WiFi...");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serai.print(".");
  }
  Serial.printf("\nConnected!\n");

  sp.begin();
  while(!sp.is_auth())
  {
    delay(2000)
    sp.handle_client();
  }
  Serial.println("Connected to Spotify!");

  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
  Serial.println("TFT initialized!");
  tft.fillScreen(ST77XX_BLACK)

  tft.setCursor(0,0);
  tft.write(WiFi.localIP().toString().c_str());
  delay(5000)
}

void loop() {
  tft.fillScreen(ST77XX_WHITE);

  //song info
  tft.setCursor(40,40);
  tft.setTextSize(16);
  tft.write(sp.current_track_name());
  tft.setCursor(40,80);
  tft.setTextSize(12);
  tft.write(sp.current_artist_name());

  //play icon
  tft.setcursor(140,0);
  if(sp.is_playing()) {
    tft.fillRect(140, 0, 20, 128, ST77XX_DARKGREEN);
  }
  delay(1000);
}