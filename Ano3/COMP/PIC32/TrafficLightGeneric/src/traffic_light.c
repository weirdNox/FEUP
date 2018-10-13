#include <Arduino.h>
#include <stdbool.h>

typedef enum io {
    Input_Button1,
    Input_Button2,
    Input_Count,

    Output_Red = Input_Count,
    Output_Yellow,
    Output_Green,
    Output_Count
} io;

typedef struct input_state {
    bool Enabled;
    bool Re;
    bool Last;
} input_state;

input_state Inputs[Input_Count] = {};

#define ARDUINO 0

#if ARDUINO
int PinMap[Input_Count + Output_Count] = {
    [Input_Button1] = 15,
    [Input_Button2] = 21,

    [Output_Red]    = 13,
    [Output_Yellow] = 12,
    [Output_Green]  = 11,
};

static void initPins() {
    int I;
    for(I = 0; I < Input_Count; ++I) {
        pinMode(PinMap[I], INPUT);
    }
    for(I = 0; I < Output_Count; ++I) {
        pinMode(PinMap[Input_Count + I], OUTPUT);
    }
}

static void readInputs() {
    int I;
    for(I = 0; I < Input_Count; ++I) {
        input_state *State = Inputs + I;
        State->Last = State->Enabled;
        State->Enabled = digitalRead(PinMap[I]) != HIGH;
        State->Re = (State->Enabled && !State->Last);
    }
}

inline static void writeOutput(io Output, int State) {
    digitalWrite(PinMap[Output], State ? HIGH : LOW);
}
#else
int PinMap[Input_Count + Output_Count] = {
    [Input_Button1] = 1 << 4,
    [Input_Button2] = 1 << 5,

    [Output_Red]    = 1 << 6,
    [Output_Yellow] = 1 << 7,
    [Output_Green]  = 1 << 8,
};

static void initPins() {
    int I;
    AD1PCFG = 0xFFFF; // Set all port B as digital
    for(I = 0; I < Output_Count; ++I) {
        TRISGCLR = PinMap[Input_Count + I];
        LATGCLR  = PinMap[Input_Count + I];
    }
}

static void readInputs() {
    int I;
    for(I = 0; I < Input_Count; ++I) {
        input_state *State = Inputs + I;
        State->Last = State->Enabled;
        State->Enabled = !(PORTB & PinMap[I]);
        State->Re = (State->Enabled && !State->Last);
    }
}

inline static void writeOutput(io Output, bool State) {
    if(State) {
        LATGSET = PinMap[Output];
    } else {
        LATGCLR = PinMap[Output];
    }
}
#endif

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

void switchToState(int NewState) {
    State = NewState;
    StateStartTime = millis();
}

void switchToStateKeepTime(int NewState) {
    State = NewState;
}

void setup() {
    initPins();

    switchToState(State_Green);
}

void loop() {
    unsigned long Time = millis();
    unsigned long StateDelta = Time - StateStartTime;

    // NOTE(nox): Inputs
    readInputs();

    // NOTE(nox): Logic
    if(State == State_Green && Inputs[Input_Button1].Re) {
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
    if(Inputs[Input_Button2].Re) {
        if(State > State_IntermittentMark) {
            switchToState(State_Green);
        } else {
            switchToState(State_IntermittentOn);
        }
    }

    // NOTE(nox): Output
    writeOutput(Output_Red,    0);
    writeOutput(Output_Yellow, 0);
    writeOutput(Output_Green,  0);
    if(State == State_Green || State == State_GreenWithButton) {
        writeOutput(Output_Green, 1);
    }
    else if(State == State_Yellow || State == State_IntermittentOn) {
        writeOutput(Output_Yellow, 1);
    }
    else if(State == State_Red) {
        writeOutput(Output_Red, 1);
    }

}
