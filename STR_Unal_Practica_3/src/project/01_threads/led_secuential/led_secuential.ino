#define LED1 7
#define LED2 8
#define LED3 9

#define DELAYTIME 250

int counter = 0;
boolean led1_flag = true;
boolean led2_flag = true;
boolean led3_flag = true;

void setup(){
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
}

void loop(){
    led1_flag = !led1_flag;
    digitalWrite(LED1, led1_flag);
    if(counter % 2 == 0){
        led2_flag = !led2_flag;
        digitalWrite(LED2, led2_flag);
    };
    if(counter % 4 == 0){
        led3_flag = !led3_flag;
        digitalWrite(LED3, led3_flag);
    };
    delay(250);
    counter++;
    if (counter == 8) counter = 0;
}