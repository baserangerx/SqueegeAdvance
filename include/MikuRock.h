#include <gba_types.h>

#define rgbToColour(rgb) 	((RGB5(((rgb>>16) & 0xFF)/8,((rgb>>8) & 0xFF)/8,((rgb) & 0xFF)/8)))

static u32 sprite_data[8*5] = {

	//Miku Rock
	0x000cfe00,
	0x0799bfd0,
	0x46889bea,
	0x4678899a,
	0x34777898,
	0x53477642,
	0x55466350,
	0x01333100,

	// APPLE
    0x00000000,
    0x00000000,
    0x22000000,
    0x22220000,
    0x22222000,
    0x12222100,
    0x22222100,
    0x22222100,

    0x00000000,
    0x00000030,
    0x00000232,
    0x00022223,
    0x00222223,
    0x00222223,
    0x02224222,
    0x02222442,

    0x22222100,
    0x22222100,
    0x22222100,
    0x22221100,
    0x22111100,
    0x11111000,
    0x11100000,
    0x00000000,

    0x02222222,
    0x02222222,
    0x00222222,
    0x00222222,
    0x00022222,
    0x00002222,
    0x00000111,
    0x00000000

	//END OF APPLE
	};


static u16 pallet_data[] = {
	rgbToColour(0x000000),
	rgbToColour(0x2d2c2a),
	rgbToColour(0x343432),
	rgbToColour(0x41403e),
	rgbToColour(0x4f4e4c),
	rgbToColour(0x066a72),
	rgbToColour(0x5e5d5b),
	rgbToColour(0x6b6a68),
	rgbToColour(0x777674),
	rgbToColour(0x848381),
	rgbToColour(0x999896),
	rgbToColour(0x34c2de),
	rgbToColour(0x48c7e2),
	rgbToColour(0x59d8ff),
	rgbToColour(0x5cdaf4),
	rgbToColour(0x4fe9ff)

};
