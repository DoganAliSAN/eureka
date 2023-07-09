#include <Servo.h>
Servo left_front;
Servo left_back;
Servo right_front;
Servo right_back;

void setup() {
    Serial2.begin(115200);
    left_back.attach(PA0);
    left_front.attach(PA1);
    right_back.attach(PA2);
    right_front.attach(PA3);
}

char* tokens[10]; // Array to store tokens, adjust the size as needed

void loop() {
    if (Serial2.available()) {
        String data = Serial2.readStringUntil('\n');

        char charArray[data.length() + 1];

        data.toCharArray(charArray, sizeof(charArray));

        int tokenCount = 0;

        char* token = strtok(charArray, "|||");

        while (token != NULL) {
            tokens[tokenCount] = token;
            tokenCount++;
            token = strtok(NULL, "|||");
        }

        if (strcmp(tokens[0], "TESTMODE1") == 0) {
            left_back.writeMicroseconds(1000);
            left_front.writeMicroseconds(1000);
            right_back.writeMicroseconds(1000);
            right_front.writeMicroseconds(1000);
            delay(1000);
            left_back.writeMicroseconds(1150);
            left_front.writeMicroseconds(1150);
            right_back.writeMicroseconds(1150);
            right_front.writeMicroseconds(1150);
            delay(3000);
            left_back.writeMicroseconds(1000);
            left_front.writeMicroseconds(1000);
            right_back.writeMicroseconds(1000);
            right_front.writeMicroseconds(1000);
            tokens[0] = "";
        } else if (strcmp(tokens[0], "TESTMODE2") == 0) {
            String RestData = tokens[1];
            char charArray[RestData.length() + 1];

            RestData.toCharArray(charArray, sizeof(charArray));

            int tokenCount = 0;

            char* token = strtok(charArray, ",");

            while (token != NULL) {
                tokens[tokenCount] = token;
                tokenCount++;
                token = strtok(NULL, ",");
            }

            const char* motor_number = tokens[0];
            int motor_speed = atoi(tokens[1]);

            if (motor_speed < 1000) {
                motor_speed = 1000;
            }
            if (motor_speed > 2000) {
                motor_speed = 2000;
            }

            if (strcmp(motor_number, "0") == 0) {
                left_back.writeMicroseconds(1000);
                delay(500);
                left_back.writeMicroseconds(motor_speed);
            } else if (strcmp(motor_number, "1") == 0) {
                left_front.writeMicroseconds(1000);
                delay(500);
                left_front.writeMicroseconds(motor_speed);
            } else if (strcmp(motor_number, "2") == 0) {
                right_back.writeMicroseconds(1000);
                delay(500);
                right_back.writeMicroseconds(motor_speed);
            } else if (strcmp(motor_number, "3") == 0) {
                right_front.writeMicroseconds(1000);
                delay(500);
                right_front.writeMicroseconds(motor_speed);
            }
        } else if (strcmp(tokens[0], "TAKEOFF") == 0) {
            // Code for TAKEOFF
        } else if (strcmp(tokens[0], "PIDVALUES") == 0) {
            // pid değerlerini esp32nin sdcard'ına kaydediip oradan alabiliriz
        }
    }
}
