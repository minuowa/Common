#pragma once
union CXColor {
    struct {
        unsigned char B;
        unsigned char G;
        unsigned char R;
        unsigned char A;
    };
    u32 Color;
    operator u32 () {
        return Color;
    }
};
static const u32 Color_Pure_White = 0XFFFFFFFF;
static const u32 Color_Pure_Black = 0X00000000;
static const u32 Color_Pure_Red = 0XFF0000FF;
static const u32 Color_Pure_Green = 0XFF00FF00;
static const u32 Color_Pure_Blue = 0X0000FFFF;

