/**
\brief iot-lab_M3 definition of the "eui64" bsp module.

\author Alaeddine Weslati <alaeddine.weslati@inria.fr>, January 2014.
*/

#include "string.h"
#include "eui64.h"

//=========================== defines =========================================
// stm32f103rey, 96-bit unique ID address
#define UNIQUE_ID_BASE_ADDRESS          0x1FFFF7E8	//Unique ID first 8 bytes
#define UNIQUE_ID_LAST_ADDRESS          0x1FFFF7EC	//Unique ID last 8 bytes
//=========================== variables =======================================
/* Uncomment only one of the following*/
/*MAC address as proccessor ID stored in flash*/
const uint8_t const *uid = (const uint8_t *const) UNIQUE_ID_BASE_ADDRESS;
const uint8_t const *luid = (const uint8_t *const) UNIQUE_ID_LAST_ADDRESS;

///* MAC address of node provided by user */
//const uint8_t uid[8] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x04};

//=========================== prototypes ======================================

//=========================== public ==========================================

void eui64_get(uint8_t* addressToWrite)
{
  addressToWrite[0] = (uid[0]^luid[0]);
  addressToWrite[1] = (uid[1]^luid[2]);
  addressToWrite[2] = (uid[2]^luid[4]);
  addressToWrite[3] = (uid[3]^luid[6]);
  addressToWrite[4] = (uid[4]^luid[1]);
  addressToWrite[5] = (uid[5]^luid[3]);
  addressToWrite[6] = (uid[6]^luid[5]);
  addressToWrite[7] = (uid[7]^luid[7]);
}

/* Gets proccessor 96-bytes unique id*/

void uid96_get (uint8_t* uniqueID) {
	uniqueID[0] = uid[0];
	uniqueID[1] = uid[1];
	uniqueID[2] = uid[2];
	uniqueID[3] = uid[3];
	uniqueID[4] = uid[4];
	uniqueID[5] = uid[5];
	uniqueID[6] = uid[6];
	uniqueID[7] = uid[7];
	uniqueID[8] = uid[8];
	uniqueID[9] = uid[9];
	uniqueID[10] = uid[10];
	uniqueID[11] = uid[11];

}

//=========================== private =========================================
