#include <Arduino.h>
#include <stdbool.h>

enum {
    RB4 = 1 << 4, // Button 1
    RB5 = 1 << 5, // Button 2

    RG6 = 1 << 6, // Red
    RG7 = 1 << 7, // Yellow
    RG8 = 1 << 8, // Green
};

enum {
    State_Green,
    State_GreenWithButton,
    State_Yellow,
    State_Red,

    State_IntermittentMark,
    State_IntermittentOn,
    State_IntermittentOff,
};

int State;
unsigned long StateStartTime;
bool LastButton1, LastButton2;

void switchToState(int NewState) {
    State = NewState;
    StateStartTime = millis();
}

void switchToStateKeepTime(int NewState) {
    State = NewState;
}

void setup() {
    AD1PCFG = 0xFFFF; // Set all port B as digital
    TRISGCLR = RG6 | RG7 | RG8;
    LATGCLR  = RG6 | RG7 | RG8;

    switchToState(State_Green);
}

void loop() {
    unsigned long Time = millis();
    unsigned long StateDelta = Time - StateStartTime;

    // NOTE(nox): Inputs
    bool Button1 = !(PORTB & RB4);
    bool Button1Re = (Button1 && !LastButton1);
    LastButton1 = Button1;

    bool Button2 = !(PORTB & RB5);
    bool Button2Re = (Button2 && !LastButton2);
    LastButton2 = Button2;

    // NOTE(nox): Logic
    if(State == State_Green && Button1Re) {
        if(StateDelta > 4000) {
            switchToState(State_Yellow);
        } else {
            switchToStateKeepTime(State_GreenWithButton);
        }
    }
    else if(State == State_Green && StateDelta > 9000) {
        switchToState(State_Yellow);
    }
    else if(State == State_GreenWithButton && StateDelta > 4000) {
        switchToState(State_Yellow);
    }
    else if(State == State_Yellow && StateDelta > 1000) {
        switchToState(State_Red);
    }
    else if(State == State_Red && StateDelta > 5000) {
        switchToState(State_Green);
    }
    else if(State == State_IntermittentOn && StateDelta > 1000) {
        switchToState(State_IntermittentOff);
    }
    else if(State == State_IntermittentOff && StateDelta > 1000) {
        switchToState(State_IntermittentOn);
    }

    // NOTE(nox): Override
    if(Button2Re) {
        if(State > State_IntermittentMark) {
            switchToState(State_Green);
        } else {
            switchToState(State_IntermittentOn);
        }
    }

    // NOTE(nox): Output
    LATGCLR  = RG6 | RG7 | RG8;
    if(State == State_Green || State == State_GreenWithButton) {
        LATGSET = RG8;
    }
    else if(State == State_Yellow || State == State_IntermittentOn) {
        LATGSET = RG7;
    }
    else if(State == State_Red) {
        LATGSET = RG6;
    }
}
