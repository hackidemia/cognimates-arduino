#include <WebUSB.h>

/**
 * Creating an instance of WebUSBWebSerial will add an additional USB interface to
 * the device that is marked as vendor-specific (rather than USB CDC-ACM) and
 * is therefore accessible to the browser.
 *
 * The URL here provides a hint to the browser about what page the user should
 * navigate to to interact with the device.
 */
WebUSB WebUSBWebSerial(1 /* https:// */, "webusb.github.io/arduino/demos/rgb");

#define WebSerial WebUSBWebSerial

int message[3];
int messageIndex;

void setup() {
  while (!WebSerial) {
    ;
  }
  Serial.begin(9600);
  Serial.println("Starting IDE serial");
  WebSerial.begin(9600);
  WebSerial.write("Sketch begins. \r\n");
  WebSerial.flush();
  messageIndex = 0;
}

void loop() {
  if (WebSerial && WebSerial.available()) {
    message[messageIndex++] = WebSerial.read();
    if (messageIndex == 3) {
      Serial.println(message[0]);
      Serial.println(message[1]);
      Serial.println(message[2]);
      Serial.println("end message");
      if(message[0] == 1){
          Serial.println("inside digitalwrite");
          pinMode(message[1], OUTPUT);
          if(message[2] == 1){
            digitalWrite(message[1], HIGH);
          } else {
            digitalWrite(message[1], LOW);
          }
      } else if(message[0] == 0){
          Serial.println("inside analog write");
          pinMode(message[1], OUTPUT);
          double value = double(message[2])/100.0*255;
          analogWrite(message[1], (int)value);
      } else if(message[0] == 2){
          pinMode(message[1], INPUT);
          Serial.println("inside analog read");
          int val = analogRead(message[1]);
          Serial.println(val);
          char out_string[6];
          memset(out_string, 0, sizeof(out_string));
          sprintf(out_string, "%d", val);
          Serial.println(out_string);
          WebSerial.write(out_string);
          WebSerial.flush();
      } else if(message[0] == 3){
          pinMode(message[1], INPUT);
          Serial.println("inside digital read");
          int digital = digitalRead(message[1]);
          int val;
          if(digital == HIGH){
            val = 1;
          } else {
            val = 0;
          }
          char out_string[6];
          memset(out_string, 0, sizeof(out_string));
          sprintf(out_string, "%d", val);
          Serial.println(out_string);
          WebSerial.write(out_string);
          WebSerial.flush();
      }
     
      messageIndex = 0;
      memset(message, 0, sizeof(message));
    }
  }
}
