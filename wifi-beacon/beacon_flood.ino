#include <Arduino.h>
#include <WiFi.h>
#include "esp_wifi.h"  

int c = 16;
int chr = 0;
String tmp = "";
String ph = ".'#-"; 
String text[17] = {"hevorix", "hevorix", "hevorix", "hevorix", "hevorix", "hevorix", "hevorix", "hevorix", "hevorix", "hevorix", "hevorix", "hevorix", "hevorix", "hevorix", "hevorix", "hevorix", "hevorix"};
byte channel;

uint8_t packet[128] = { 0x80, 0x00, 0x00, 0x00,
                        0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                        0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                        0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                        0xc0, 0x6c,
                        0x83, 0x51, 0xf7, 0x8f, 0x0f, 0x00, 0x00, 0x00,
                        0x64, 0x00,
                        0x01, 0x04,
                        0x00, 0x0e, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72,
                        0x01, 0x08, 0x82, 0x84,
                        0x8b, 0x96, 0x24, 0x30, 0x48, 0x6c, 0x03, 0x01,
                        0x04
                      };

void setup() {
  delay(500);
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);

  esp_wifi_init(NULL);
  esp_wifi_start();
}

void loop() {
  chr = 0;
  if (c == 17) { 
    c = 0;
  }

 
  channel = random(1, 12);
  esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);

 
  packet[10] = packet[16] = random(256);
  packet[11] = packet[17] = random(256);
  packet[12] = packet[18] = random(256);
  packet[13] = packet[19] = random(256);
  packet[14] = packet[20] = random(256);
  packet[15] = packet[21] = random(256);

  int pcount = 42; 

  for (int i = 41; i <= 52; i++) {
    packet[i] = ph[0];
  }

  tmp = String(c + 10);

  packet[38] = ph[1]; 
  packet[39] = tmp[0];
  packet[40] = tmp[1];
  packet[41] = ph[3]; 

  for (int i = 0; i < text[c].length(); i++) {
    packet[pcount] = text[c][i];
    pcount++;
  }

  for (int i = 0; i < 4; i++) {
    esp_wifi_80211_tx(WIFI_IF_STA, packet, 57, true);
  }

  c++; 
  delay(1);
}
