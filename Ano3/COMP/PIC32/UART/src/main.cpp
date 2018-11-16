#include <Arduino.h>
#include <utils.cpp>
#include <lexer.cpp>

enum {
    LED = 7,
};

typedef struct led_state {
    bool Light;
    bool Blinking;
    int LastTime;
    int Period;
    int RemainingCount;
} led_state;

cmd Cmd = {};
led_state LedState = {};

void setup() {
    Serial.begin(115200);
    Serial.println("Insert commands");
    pinMode(LED, OUTPUT);
}

void loop() {
    if(Serial.available() && insertChar(&Cmd, Serial.read())) {
        token CmdBase = nextToken(&Cmd);
        if(CmdBase.Type == Token_String) {
            if(strcmp(CmdBase.String, "version") == 0) {
                Serial.println("Butler Serial v0.0.0.1.pi");
            }
            else if(strcmp(CmdBase.String, "blink") == 0) {
                token Arg1 = nextToken(&Cmd);
                token Arg2 = nextToken(&Cmd);

                if(Arg1.Type == Token_Number && Arg2.Type == Token_Number &&
                   Arg1.Number > 0 && Arg2.Number > 0)
                {
                    LedState.Blinking = true;
                    LedState.Light = !LedState.Light;
                    LedState.LastTime = millis();
                    LedState.Period = Arg2.Number/2;
                    LedState.RemainingCount = Arg1.Number*2-1;
                } else {
                    Serial.println("This command should have two positive numbers as arguments");
                }
            }
            else if(strcmp(CmdBase.String, "light") == 0) {
                LedState.Blinking = false;
                LedState.Light = !LedState.Light;
            }
            else {
                Serial.println("Command not recognized! :(");
            }
        }
        else {
            Serial.println("The first part of a command should be a string.");
        }

        clearBuffer(&Cmd);
    }

    if(LedState.Blinking && (millis() - LedState.LastTime) > LedState.Period) {
        LedState.LastTime = millis();
        LedState.Light = !LedState.Light;
        --LedState.RemainingCount;

        if(!LedState.RemainingCount) {
            LedState.Blinking = false;
        }
    }

    if(LedState.Light) {
        digitalWrite(LED, HIGH);
    } else {
        digitalWrite(LED, LOW);
    }
}
