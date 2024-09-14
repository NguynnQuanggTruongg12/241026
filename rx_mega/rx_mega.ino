void setup() {
  Serial.begin(38400);     // Khởi tạo Serial Monitor
  Serial1.begin(115200);   // Giao tiếp với ESP8266 qua Serial1 (TX1, RX1)
  Serial.println("====READY====");
}

void loop() {
  // Biến chứa dữ liệu đọc được
  static String dataString = "";

  // Nếu có dữ liệu từ Serial1 (ESP8266)
  while (Serial1.available()) {
    char c = Serial1.read();  // Đọc từng ký tự
    if (c == '\n') {  // Kết thúc chuỗi khi gặp ký tự xuống dòng
      // Tách chuỗi dữ liệu theo ký tự phân tách ';'
      int separatorIndex = dataString.indexOf(';');
      if (separatorIndex != -1) {
        // Chuyển đổi chuỗi thành số thực
        float Vx = dataString.substring(0, separatorIndex).toFloat();
        float Vw = dataString.substring(separatorIndex + 1).toFloat();
        
        // Hiển thị giá trị lên Serial Monitor
        Serial.print("Vx: ");
        Serial.print(Vx);
        Serial.print("    ");
        Serial.print("Vw: ");
        Serial.println(Vw);
      }
      dataString = "";  // Reset chuỗi dữ liệu để đọc lần tiếp theo
    } else {
      dataString += c;  // Ghép từng ký tự vào chuỗi
    }
  }
}
