#include "TMath.h"
#include "CmsMapping.hpp"

Float_t GetX_Cms30x30(Int_t channel)					
{									
 //if (channel<64) channel=channel+64;
 //if (channel>64) channel=channel-64;

  const static Float_t map[128]=					
    {									
        1,
        65,
        2,
        66,
        3,
        67,
        4,
        68,
        5,
        69,
        6,
        70,
        7,
        71,
        8,
        72,
        9,
        73,
        10,
        74,
        11,
        75,
        12,
        76,
        13,
        77,
        14,
        78,
        15,
        79,
        16,
        80,
        17,
        81,
        18,
        82,
        19,
        83,
        20,
        84,
        21,
        85,
        22,
        86,
        23,
        87,
        24,
        88,
        25,
        89,
        26,
        90,
        27,
        91,
        28,
        92,
        29,
        93,
        30,
        94,
        31,
        95,
        32,
        96,
        33,
        97,
        34,
        98,
        35,
        99,
        36,
        100,
        37,
        101,
        38,
        102,
        39,
        103,
        40,
        104,
        41,
        105,
        42,
        106,
        43,
        107,
        44,
        108,
        45,
        109,
        46,
        110,
        47,
        111,
        48,
        112,
        49,
        113,
        50,
        114,
        51,
        115,
        52,
        116,
        53,
        117,
        54,
        118,
        55,
        119,
        56,
        120,
        57,
        121,
        58,
        122,
        59,
        123,
        60,
        124,
        61,
        125,
        62,
        126,
        63,
        127,
        64,
        128,
    };								

  return map[channel];						
//return channel;
}


Float_t GetX_Cmsbig(Int_t channel)
{
//const static Float_t mapped;
const static Float_t map[128]=
    {
		/*1*/64,
		/*2*/65,
		/*3*/63,
		/*4*/66,
		/*5*/62,
		/*6*/67,
		/*7*/61,
		/*8*/68,
		/*9*/60,
		/*10*/69,
		/*11*/59,
		/*12*/70,
		/*13*/58,
		/*14*/71,
		/*15*/57,
		/*16*/72,
		/*17*/56,
		/*18*/73,
		/*19*/55,
		/*20*/74,
		/*21*/54,
		/*22*/75,
		/*23*/53,
		/*24*/76,
		/*25*/52,
		/*26*/77,
		/*27*/51,
		/*28*/78,
		/*29*/50,
		/*30*/79,
		/*31*/49,
		/*32*/80,
		/*33*/48,
		/*34*/81,
		/*35*/47,
		/*36*/82,
		/*37*/46,
		/*38*/83,
		/*39*/45,
		/*40*/84,
		/*41*/44,
		/*42*/85,
		/*43*/43,
		/*44*/86,
		/*45*/42,
		/*46*/87,
		/*47*/41,
		/*48*/88,
		/*49*/40,
		/*50*/89,
		/*51*/39,
		/*52*/90,
		/*53*/38,
		/*54*/91,
		/*55*/37,
		/*56*/92,
		/*57*/36,
		/*58*/93,
		/*59*/35,
		/*60*/94,
		/*61*/34,
		/*62*/95,
		/*63*/33,
		/*64*/96,
		/*65*/32,
		/*66*/97,
		/*67*/31,
		/*68*/98,
		/*69*/30,
		/*70*/99,
		/*71*/29,
		/*72*/100,
		/*73*/28,
		/*74*/101,
		/*75*/27,
		/*76*/102,
		/*77*/26,
		/*78*/103,
		/*79*/25,
		/*80*/104,
		/*81*/24,
		/*82*/105,
		/*83*/23,
		/*84*/106,
		/*85*/22,
		/*86*/107,
		/*87*/21,
		/*88*/108,
		/*89*/20,
		/*90*/109,
		/*91*/19,
		/*92*/110,
		/*93*/18,
		/*94*/111,
		/*95*/17,
		/*96*/112,
		/*97*/16,
		/*98*/113,
		/*99*/15,
		/*100*/114,
		/*101*/14,
		/*102*/115,
		/*103*/13,
		/*104*/116,
		/*105*/12,
		/*106*/117,
		/*107*/11,
		/*108*/118,
		/*109*/10,
		/*110*/119,
		/*111*/9,
		/*112*/120,
		/*113*/8,
		/*114*/121,
		/*115*/7,
		/*116*/122,
		/*117*/6,
		/*118*/123,
		/*119*/5,
		/*120*/124,
		/*121*/4,
		/*122*/125,
		/*123*/3,
		/*124*/126,
		/*125*/2,
		/*126*/127,
		/*127*/1,
        /*128*/128,
	};

/*	
	if (channel<64) {
		mapped = channel*2 + 1;
		return mapped;
	}
	else {
	        mapped = channel*2;
                return mapped; 
	}
*/
	return map[channel];
}

