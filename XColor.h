#pragma once
union CXColor
{
	struct 
	{
		unsigned char B;
		unsigned char G;
		unsigned char R;
		unsigned char A;
	};
	u32 Color;
	operator u32 ()
	{
		return Color;
	}
};

