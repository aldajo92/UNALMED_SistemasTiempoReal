#include <ZumoMotors.h>

ZumoMotors motors;

#define VALUE_SIZE 3
char c;
String command;
String values[VALUE_SIZE];

void setup() {
  Serial.begin(9600);
}

void loop() {}

////////////////////// Manage Serial Communication /////////////////////////////

void echo(String value){
  Serial.print("responding-to-");
  Serial.println(value);
}

void parseCommand(String com) {
  String middle;
  middle = com;

  for(int i = 0; i < VALUE_SIZE; i++){
    values[i] = middle.substring(0, middle.indexOf(";"));
    middle = middle.substring(middle.indexOf(";") + 1);
  }

  if(values[0] == "echo"){
    echo(values[1]);
  }else
  if(values[0] == "f"){
    forward(values[1].toInt());
  }else
  if(values[0] == "m"){
    moveM(values[1].toInt(), values[2].toInt());
  }
}

void serialEvent(){
  if (Serial.available()) {
    c = Serial.read();
    if (c == '\n') {
      parseCommand(command);
      command = "";
      Serial.flush();
    }
    else {
      command += c;
    }
  }
}

////////////////////// Manage Motors /////////////////////////////

void forward(int value){
  motors.setSpeeds(value, value);
}

void moveM(int v, int w){
  motors.setSpeeds(v+w, v-w);
}

////////////////////// Manage Tasks /////////////////////////////