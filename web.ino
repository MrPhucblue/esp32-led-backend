#include <WiFi.h>
#include <HTTPClient.h>

// Thông tin WiFi
const char* ssid = "Hoang Phuc Sau";         // Thay bằng tên WiFi của bạn
const char* password = "";      // Thay bằng mật khẩu WiFi của bạn

// Địa chỉ server backend đã deploy trên Render
const char* serverName = "https://esp32nhayled.onrender.com/update";

// Chân kết nối LED
const int ledPin = 2;  // GPIO2 = LED D2

bool ledState = false;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  // Kết nối WiFi
  Serial.print("Đang kết nối WiFi: ");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Đã kết nối WiFi!");
}

void loop() {
  ledState = !ledState;
  digitalWrite(ledPin, ledState);   // Nhấp nháy LED

  sendStatusToServer(ledState);     // Gửi trạng thái LED lên server

  delay(10000);  // Nhấp nháy mỗi 1 giây
}

void sendStatusToServer(bool state) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Gửi dạng query string: /update?status=0 hoặc 1
    String fullUrl = String(serverName) + "?status=" + (state ? "1" : "0");
    http.begin(fullUrl);

    int responseCode = http.POST("");  // POST body rỗng
    Serial.print("Gửi trạng thái: ");
    Serial.println(state ? "1" : "0");
    Serial.print("Phản hồi server: ");
    Serial.println(responseCode);

    http.end();
  } else {
    Serial.println("WiFi mất kết nối!");
  }
}
