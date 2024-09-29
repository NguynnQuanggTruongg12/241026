#define led A15

void setup() {
  Serial.begin(38400);     // Initialize Serial Monitor
  Serial1.begin(115200);   // Communication with ESP8266 via Serial1 (TX1, RX1)
  pinMode(led,OUTPUT);
  digitalWrite(led,0);
  Serial.println("====READY====");
}

void loop() {
  // Variable to hold the read data
  static String dataString = "";

  // If there is data from Serial1 (ESP8266)
  while (Serial1.available()) {
    char c = Serial1.read();  // Read one character at a time
    if (c == '\n') {  // End the string when a newline character is encountered
      // Split the data string based on the separator ';'
      int firstSeparator = dataString.indexOf(';');
      int secondSeparator = dataString.indexOf(';', firstSeparator + 1);
      int thirdSeparator = dataString.indexOf(';', secondSeparator + 1);
      
      if (firstSeparator != -1 && secondSeparator != -1 && thirdSeparator != -1) {
        // Convert the substrings into floating-point numbers and integers
        float Vx = dataString.substring(0, firstSeparator).toFloat();
        float Vw = dataString.substring(firstSeparator + 1, secondSeparator).toFloat();
        int internet = dataString.substring(secondSeparator + 1, thirdSeparator).toInt();
        int status = dataString.substring(thirdSeparator + 1).toInt();
        
        // Display the values on the Serial Monitor
        Serial.print("Vx: ");
        Serial.print(Vx);
        Serial.print("    ");
        Serial.print("Vw: ");
        Serial.print(Vw);
        Serial.print("    ");
        Serial.print("Internet: ");
        Serial.print(internet);
        Serial.print("    ");
        Serial.print("Status: ");
        Serial.println(status);
        
        // Check internet connection status
        if (internet == 1) {
          // Serial.println("Có internet");
          digitalWrite(led,1);  // "Có internet" means "Internet available"
        } else {
          // Serial.println("No internet");
          digitalWrite(led,1);
          delay(2000);
          digitalWrite(led,0);
          delay(500);
        }
      }
      dataString = "";  // Reset the string for the next read
    } else {
      dataString += c;  // Append the character to the string
    }
  }
}
