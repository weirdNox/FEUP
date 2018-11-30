#include <Arduino.h>
#include <utils.cpp>
#include <lexer.cpp>
#include <timer.cpp>

enum {
    LED = 7,
};

typedef struct led_state {
    bool Light;
    int WantedPeriod;
    int UsedPeriod;
    int RemainingPeriodTime;
    int RemainingCount;
} led_state;

static cmd Cmd = {};
static led_state LedState = {};
static Timer4 Timer = {};

void __attribute__((interrupt)) timerIsr() {
    LedState.RemainingPeriodTime -= LedState.UsedPeriod;

    if(!LedState.RemainingPeriodTime) {
        LedState.Light = !LedState.Light;
        --LedState.RemainingCount;

        if(!LedState.RemainingCount) {
            Timer.stop();
        }
        else {
            LedState.RemainingPeriodTime = LedState.WantedPeriod;
            if(LedState.WantedPeriod != LedState.UsedPeriod) {
                // NOTE(nox): Workaround
                LedState.UsedPeriod = 200;
                Timer.setFrequency(1000/LedState.UsedPeriod);
            }
        }
    }
    else if(LedState.RemainingPeriodTime < LedState.UsedPeriod) {
        // NOTE(nox): Workaround
        LedState.UsedPeriod = LedState.RemainingPeriodTime;
        Timer.setFrequency(1000/LedState.UsedPeriod);
    }

    clearIntFlag(_TIMER_4_IRQ);
}

void setup() {
    Serial.begin(115200);
    Serial.println("Insert commands");
    pinMode(LED, OUTPUT);
    Timer.attachInterrupt(timerIsr);
}

void loop() {
    if(Serial.available() && insertChar(&Cmd, Serial.read())) {
        token CmdBase = nextToken(&Cmd);
        if(CmdBase.Type == Token_String) {
            if(strcmp(CmdBase.String, "version") == 0) {
                Serial.println("Butler Serial v0.0.0.1.pi");
            }
            else if(strcmp(CmdBase.String, "blink") == 0) {
                token NumberOfTimes = nextToken(&Cmd);
                token Period = nextToken(&Cmd);

                if(NumberOfTimes.Type == Token_Number && NumberOfTimes.Number > 0 &&
                   Period.Type == Token_Number && Period.Number > 0)
                {
                    LedState.WantedPeriod = Period.Number;
                    if(Period.Number > 200) {
                        // NOTE(nox): Workaround needed
                        LedState.UsedPeriod = 200;
                    }
                    else {
                        LedState.UsedPeriod = LedState.WantedPeriod;
                    }

                    LedState.RemainingPeriodTime = LedState.WantedPeriod;
                    LedState.Light = !LedState.Light;
                    LedState.RemainingCount = NumberOfTimes.Number*2-1;
                    Timer.setFrequency(1000/LedState.UsedPeriod);
                    Timer.start();
                } else {
                    Serial.println("This command should have two positive numbers as arguments");
                }
            }
            else if(strcmp(CmdBase.String, "light") == 0) {
                Timer.stop();
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

    if(LedState.Light) {
        digitalWrite(LED, HIGH);
    } else {
        digitalWrite(LED, LOW);
    }
}
