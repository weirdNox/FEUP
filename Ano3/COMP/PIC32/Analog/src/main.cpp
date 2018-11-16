#include <Arduino.h>
#include <utils.cpp>
#include <lexer.cpp>

cmd Cmd = {};

void setup() {
    Serial.begin(115200);
}

void loop() {
    if(Serial.available() && insertChar(&Cmd, Serial.read())) {
        token Name = nextToken(&Cmd);
        if(Name.Type == Token_String) {
            if(strcmp(Name.String, "analog") == 0) {
                token Channel = nextToken(&Cmd);
                if(Channel.Type == Token_Number) {
                    if(Channel.Number >= 0 && Channel.Number <= 11) {
                        Serial.print("Channel ");
                        Serial.print(Channel.Number);
                        Serial.print(" has value ");
                        Serial.println(analogRead(Channel.Number));
                    }
                    else {
                        Serial.println("Channel should be between 0 and 11 (inclusive)");
                    }
                }
                else {
                    Serial.println("Expected format: analog [channel number]");
                }
            }
            else if(strcmp(Name.String, "dim") == 0) {
                token Pin = nextToken(&Cmd);
                token Intensity = nextToken(&Cmd);
                if(Pin.Type == Token_Number && Intensity.Type == Token_Number) {
                    if(Pin.Number == 3 || Pin.Number == 5 || Pin.Number == 6 || Pin.Number == 9 ||
                       Pin.Number == 10)
                    {
                        if(Intensity.Number >= 0 && Intensity.Number <= 100) {
                            analogWrite(Pin.Number, Intensity.Number*255/100);
                        }
                        else {
                            Serial.println("Intensity should be 0<=I<=100");
                        }
                    }
                    else {
                        Serial.println("Pin number not available to output PWM");
                    }
                } else {
                    Serial.println("Expected format: dim [pin number] [intensity %]");
                }
            }
            else if(strcmp(Name.String, "motor") == 0) {
                // TODO(nox): Implement this
                Serial.println("This command is not yet implemented :'(");
            }
            else {
                Serial.print("Command ");
                Serial.print(Name.String);
                Serial.println(" not found!");
            }
        }
        else {
            Serial.println("The first part of a command should be its name");
        }

        clearBuffer(&Cmd);
    }
}
