#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

#define BOTtoken "YOUR_TELEGRAM_BOT_TOKEN"
#define CHAT_ID "YOUR_TELEGRAM_CHAT_ID"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

unsigned long lastTimeBotRan;
const int botRequestDelay = 1000;

const int led1 = 2;
const int led2 = 4;
const int led3 = 5;
const int led4 = 18;
const int led5 = 19;
const int buzzer = 23;

void handleNewMessages(int numNewMessages) {
  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;

    if (chat_id != CHAT_ID) {
      bot.sendMessage(chat_id, "Unauthorized access!", "");
      continue;
    }

    if (text == "/start") {
      String welcome = "Hello! I'm your ESP32 Telegram Bot 🤖\n\n";
      welcome += "Commands:\n";
      welcome += "/led1_on or /led1_off\n";
      welcome += "/led2_on or /led2_off\n";
      welcome += "/led3_on or /led3_off\n";
      welcome += "/led4_on or /led4_off\n";
      welcome += "/led5_on or /led5_off\n";
      welcome += "/buzzer_on or /buzzer_off\n";
      bot.sendMessage(chat_id, welcome, "");
    }

    if (text == "/led1_on") { digitalWrite(led1, HIGH); bot.sendMessage(chat_id, "LED 1 is ON 💡", ""); }
    if (text == "/led1_off") { digitalWrite(led1, LOW); bot.sendMessage(chat_id, "LED 1 is OFF ❌", ""); }

    if (text == "/led2_on") { digitalWrite(led2, HIGH); bot.sendMessage(chat_id, "LED 2 is ON 💡", ""); }
    if (text == "/led2_off") { digitalWrite(led2, LOW); bot.sendMessage(chat_id, "LED 2 is OFF ❌", ""); }

    if (text == "/led3_on") { digitalWrite(led3, HIGH); bot.sendMessage(chat_id, "LED 3 is ON 💡", ""); }
    if (text == "/led3_off") { digitalWrite(led3, LOW); bot.sendMessage(chat_id, "LED 3 is OFF ❌", ""); }

    if (text == "/led4_on") { digitalWrite(led4, HIGH); bot.sendMessage(chat_id, "LED 4 is ON 💡", ""); }
    if (text == "/led4_off") { digitalWrite(led4, LOW); bot.sendMessage(chat_id, "LED 4 is OFF ❌", ""); }

    if (text == "/led5_on") { digitalWrite(led5, HIGH); bot.sendMessage(chat_id, "LED 5 is ON 💡", ""); }
    if (text == "/led5_off") { digitalWrite(led5, LOW); bot.sendMessage(chat_id, "LED 5 is OFF ❌", ""); }

    if (text == "/buzzer_on") { digitalWrite(buzzer, HIGH); bot.sendMessage(chat_id, "Buzzer is ON 🔔", ""); }
    if (text == "/buzzer_off") { digitalWrite(buzzer, LOW); bot.sendMessage(chat_id, "Buzzer is OFF 🔕", ""); }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(led1, OUTPUT); pinMode(led2, OUTPUT); pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT); pinMode(led5, OUTPUT); pinMode(buzzer, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
  client.setInsecure();
}

void loop() {
  if (millis() - lastTimeBotRan > botRequestDelay) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while (numNewMessages) {
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
}
