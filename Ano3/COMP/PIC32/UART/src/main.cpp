#include <Arduino.h>

#define arrayCount(A) (sizeof(A)/sizeof(*A))

enum {
    LED = 7,
};

typedef enum token_type {
    Token_EOF,
    Token_String,
    Token_Number,

    Token_Count
} token_type;

typedef struct token {
    token_type Type;
    union {
        char String[10];
        int Number;
    };
} token;

typedef struct cmd {
    char Buffer[20];
    ptrdiff_t Insert;
    ptrdiff_t Parse;
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

token nextToken(cmd *Cmd) {
    token Token = {};

    char Next;
    while((Next = Cmd->Buffer[Cmd->Parse]) && (Next == ' ' || Next == '\n' || Next == '\t' || Next == '\v'))
    {
        ++Cmd->Parse;
    }

    switch(Next = Cmd->Buffer[Cmd->Parse]) {
        case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h': case 'i': case 'j':
        case 'k': case 'l': case 'm': case 'n': case 'o': case 'p': case 'q': case 'r': case 's': case 't':
        case 'u': case 'v': case 'w': case 'x': case 'y': case 'z': {
            Token.Type = Token_String;

            int Length = 0;
            Token.String[Length++] = Next;
            ++Cmd->Parse;

            while(Length < arrayCount(Token.String)-1 &&
                  (Next = Cmd->Buffer[Cmd->Parse]) && Next >= 'a' && Next <= 'z')
            {
                Token.String[Length++] = Next;
                ++Cmd->Parse;
            }

            Token.String[Length] = 0;
        } break;

        case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': {
            Token.Type = Token_Number;

            while((Next = Cmd->Buffer[Cmd->Parse]) && Next >= '0' && Next <= '9') {
                Serial.println(Next);
                Token.Number = Token.Number*10 + (Next - '0');
                ++Cmd->Parse;
            }

        } break;

        default: {
            Token.Type = Token_EOF;
        } break;
    }

    return Token;
}

void setup() {
    Serial.begin(115200);
    Serial.println("Insert commands");
    pinMode(LED, OUTPUT);
}

void loop() {
    if(Serial.available()) {
        char Char = Serial.read();
        Serial.write(Char);

        if(Char == '\r') {
            Cmd.Buffer[Cmd.Insert] = 0;
            Serial.write('\n');

            token CmdBase = nextToken(&Cmd);
            if(CmdBase.Type == Token_String) {
                if(strcmp(CmdBase.String, "version") == 0) {
                    Serial.println("Butler Serial v0.0.0.1.pi");
                } else if(strcmp(CmdBase.String, "blink") == 0) {
                    token Arg1 = nextToken(&Cmd);
                    token Arg2 = nextToken(&Cmd);

                    if(Arg1.Type == Token_Number && Arg2.Type == Token_Number &&
                       Arg1.Number > 0 && Arg2.Number > 0)
                    {
                        LedState.Blinking = true;
                        LedState.Light = !LedState.Light;
                        LedState.LastTime = millis();
                        LedState.Period = Arg2.Number;
                        LedState.RemainingCount = Arg1.Number*2;
                    } else {
                        Serial.println("This command should have two positive numbers as arguments");
                    }
                } else if(strcmp(CmdBase.String, "light") == 0) {
                    LedState.Blinking = false;
                    LedState.Light = !LedState.Light;
                } else {
                    Serial.println("Command not recognized! :(");
                }
            } else {
                Serial.println("The first part of a command should be a string.");
            }

            for(int I = 0; I < arrayCount(Cmd.Buffer); ++I) {
                Cmd.Buffer[I] = 0;
            }
            Cmd.Insert = 0;
            Cmd.Parse = 0;
        } else {
            if(Char == 127) {
                if(Cmd.Insert > 0) {
                    --Cmd.Insert;
                } else {
                    Serial.println("Bzzz!!");
                }
            } else if(Cmd.Insert < arrayCount(Cmd.Buffer)-1) {
                Cmd.Buffer[Cmd.Insert++] = Char;
            }
        }
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
