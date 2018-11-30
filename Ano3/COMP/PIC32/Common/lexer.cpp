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

bool insertChar(cmd *CmdBuffer, char Char) {
    Serial.write(Char);

    if(Char == '\r') {
        Serial.write('\n');
        CmdBuffer->Buffer[CmdBuffer->Insert] = 0;
        return true;
    }
    else {
        if(Char == 127) {
            if(CmdBuffer->Insert > 0) {
                --CmdBuffer->Insert;
            } else {
                Serial.println("Bzzz!!");
            }
        } else if(CmdBuffer->Insert < arrayCount(CmdBuffer->Buffer)-1) {
            CmdBuffer->Buffer[CmdBuffer->Insert++] = Char;
        }
    }

    return false;
}

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

            int Base = 10;
            if(Next == '0') {
                ++Cmd->Parse;
                Next = Cmd->Buffer[Cmd->Parse];

                switch(Next) {
                    case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': {
                        Base = 8;
                    } break;

                    case 'd': case 'D': {
                        Base = 10;
                        ++Cmd->Parse;
                    } break;

                    case 'x': case 'X': {
                        Base = 16;
                        ++Cmd->Parse;
                    } break;

                    default: break;
                }
            }

            while((Next = Cmd->Buffer[Cmd->Parse]) &&
                  ((Next >= '0' && Next <= '9') || (Next >= 'A' && Next <= 'Z') || (Next >= 'a' && Next <= 'z'))) {
                int Digit = Next < 'A' ? Next - '0' : (Next & ~0x20) - 'A' + 10;
                if(Digit < Base) {
                    Token.Number = Token.Number*Base + Digit;
                }
                ++Cmd->Parse;
            }

        } break;

        default: {
            Token.Type = Token_EOF;
        } break;
    }

    return Token;
}

void clearBuffer(cmd *CmdBuffer) {
    for(int I = 0; I < arrayCount(CmdBuffer->Buffer); ++I) {
        CmdBuffer->Buffer[I] = 0;
    }
    CmdBuffer->Insert = 0;
    CmdBuffer->Parse = 0;
}
