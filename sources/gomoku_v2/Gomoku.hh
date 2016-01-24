#ifndef GOMOKU_HH_
#define	GOMOKU_HH_

typedef unsigned char	pawn;

const pawn		gl_empty = 0b00000000;
const pawn		gl_player_1 = 0b00000001;
const pawn		gl_player_2 = 0b00000010;
const pawn		gl_player_part = 0b00000011;

const pawn		gl_interest_part = 0b11111100;

const pawn		gl_interest_d5 = 0b10000000;
const pawn		gl_interest_d4 = 0b01000000;
const pawn		gl_interest_d3 = 0b00100000;
const pawn		gl_interest_d2 = 0b00010000;
const pawn		gl_interest_d1 = 0b00001000;
const pawn		gl_interest = 0b00000100;

const int		gl_infini = 1000000000;

#define			BIT(a, b) (((a&b) == b)?true:false)
#define			PAWN(a, b) (((a&3) == (b&3)) ?true:false)
#define			MAX(a, b) ((a >= b)?a:b)
#define			PERCENT(a, b) (a*100/b)
#define			OPLAYER(a) (((a & gl_player_part) == gl_player_1)?gl_player_2:gl_player_1)

#define			DEPTHINTEREST(a) ((a > 0 && a < 6)?(gl_interest<<a):0)

#define			BOOLTOINT(a) ((a == true)?0:1)

#define			IFIIS(a, b) (((b & gl_player_part) == gl_empty)?a:0)
#endif
