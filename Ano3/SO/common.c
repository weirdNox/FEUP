#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#define arrayCount(Arr) (sizeof(Arr) / sizeof(*(Arr)))

#define staticAssert(Expr, ...) typedef char STATIC_ASSERTION__[(Expr)?1:-1]
#if !NDEBUG
#define assert(Expr) if(!(Expr)) { abort(); }
#else
#define assert(Expr) (void)(0)
#endif
#define invalidCodePath() assert(!"Invalid code path")
#define invalidCase(Case) case Case: { assert(!"Invalid case"); } break
#define invalidDefaultCase() default: { assert(!"Invalid default case"); } break

typedef    int8_t  s8;
typedef   uint8_t  u8;
typedef   int16_t s16;
typedef  uint16_t u16;
typedef   int32_t s32;
typedef  uint32_t u32;
typedef   int64_t s64;
typedef  uint64_t u64;
typedef     float r32;
typedef    double r64;
typedef        s8  b8;
typedef       s16 b16;
typedef       s32 b32;
typedef       s64 b64;

typedef    size_t midx;
typedef  intptr_t sptr;
typedef uintptr_t uptr;

int stringLength(char *String) {
    int Length = 0;
    for(; *String; ++String, ++Length) {}
    return Length;
}

typedef struct {
    char *At;
    midx RemainingSize;
} format_destination;

midx formatStringList(char *Buff, midx BuffSize, char *Format, va_list Args) {
    char *At = Buff;
    char *BuffEnd = Buff + BuffSize;

    while(At < BuffEnd) {
        char Char = *Format++;
        if(Char == 0) {
            goto End;
        }
        else if(Char == '%') {
            Char = *Format++;
            switch(Char) {
                case 0: {
                    goto End;
                } break;

                case '%': {
                    *At++ = '%';
                } break;

                case 'd': {
                    int Number = va_arg(Args, int);
                    char TempBuffer[64];
                    char *Temp = TempBuffer;
                    do {
                        int Digit = Number % 10;
                        *Temp++ = '0' + Digit;
                        Number /= 10;
                    } while(Number);

                    int DigitsRemaining = Temp - TempBuffer;
                    while(DigitsRemaining && At < BuffEnd) {
                        *At++ = TempBuffer[--DigitsRemaining];
                    }
                } break;

                default: {
                    *At++ = '?';
                } break;
            }
        }
        else {
            *At++ = Char;
        }
    }

  End:;
    if(At < BuffEnd) {
        At[0] = 0;
    }
    else {
        *--At = 0;
    }

    midx WrittenSize = At - Buff;
    return WrittenSize;
}

// NOTE(nox): The return value does not include the null terminator
midx formatString(char *Buff, midx BuffSize, char *Format, ...) {
    va_list Args;
    va_start(Args, Format);

    midx WrittenSize = formatStringList(Buff, BuffSize, Format, Args);

    va_end(Args);

    return WrittenSize;
}
