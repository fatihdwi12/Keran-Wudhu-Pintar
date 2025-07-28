#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#define pin_busy 5
#define pin_infrared 18
#define pin_relay 19
SoftwareSerial mySerial(16, 17);  // RX, TX
DFRobotDFPlayerMini myDFPlayer;


int interval_deteksi_tubuh = 30;  //detik
int timer = 0;

/* kode serial mp3
1. berniat
2. membasuh wajah
3. membasuh lengan
4. membasuh sebagian kepala
5. membasuh kaki
6. sistem aktif
7. silakan mendekat
8. gerakan salah
9. wudhu selesai
10. urutan salah
11.  membasuh lengan atas
12. membasuh betis
*/



void setup() {
  delay(2000);
  Serial.begin(115200);
  mySerial.begin(9600);
  
  delay(3000);
  if (!myDFPlayer.begin(mySerial)) {
    Serial.println("DFPlayer Mini tidak terdeteksi");
  }
  delay(3000);
  pinMode(pin_busy, INPUT);
  pinMode(pin_infrared, INPUT);
  pinMode(pin_relay, OUTPUT);
  digitalWrite(pin_relay, HIGH); //mati

  Serial.println("DFPlayer Mini siap!");
  myDFPlayer.volume(30);  // volume 0 - 30
  myDFPlayer.play(6);
  // for(int a = 1;a<=12;a++){
  //   Serial.println(String(a));
  //   myDFPlayer.play(a);
  //   delay(2000);
  // }
  timer = millis();
}

void loop() {

  int sensor_ir = digitalRead(pin_infrared);
  if (sensor_ir == 0) {
    timer = millis();
    digitalWrite(pin_relay, LOW);
  } else {
    digitalWrite(pin_relay, HIGH);
  }


  if (millis() - timer >= interval_deteksi_tubuh * 1000) {
    timer = millis();
    myDFPlayer.play(7);
  }



  String data = "";
  if (Serial.available()) {
    data = Serial.readStringUntil(',');
    data.trim();
    myDFPlayer.play(data.toInt());
  }

 
}
