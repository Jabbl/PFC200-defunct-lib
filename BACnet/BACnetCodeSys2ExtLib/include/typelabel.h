#pragma once

#include <stdbool.h>


/** Get the string for the given key item in the list of typelabels.
@param key [in] Key to search for
@return The string value if successfull, otherwise NULL.
*/
const char* typelabel_get_item(const char* key);

/** Refetch the typelabels from the controller.
@return Returns "true" if successful, "false" if failed.
*/
bool typelabel_refresh(void);

/** Gets the Model Name of the current Wago controller.
@return Returns the model name if successful, otherwise NULL.
*/
static inline const char* typelabel_get_model_name(void)
{
	return typelabel_get_item("ORDER");
}

/** Gets the MAC address of the current Wago controller.
@return Returns the model name if successful, otherwise NULL.
*/
static inline const char* typelabel_get_mac(void)
{
	return typelabel_get_item("MAC");
}

/** Gets the Unique Identifier serial number of the current Wago controller.
 NOTE: Only works on PFC200 G2 controllers such as 8212. Returns NULL on 8202.
@return Returns the model name if successful, otherwise NULL.
*/
static inline const char* typelabel_get_unique_identifier(void)
{
	return typelabel_get_item("UII");
}


// ** Example command **
// /etc/config-tools/get_typelabel_value -a

// ** Example data **
// MAC=00:30:DE:42:52:46
// DEVCONF=0x000C
// DISPLAYRES_V=0
// DISPLAYRES_H=0
// DISPLAYORIENTATION=0
// OPERATINGCOUNTER=0
// BLIDX=11
// PSN=750-8206
// WAGONR=1094724
// WAGONRSTR=WAGO
// VENDORID=0x1006
// DEVICEID=0x1209
// SIGN=0xb0346636
// MAXTERM=0
// TARGETID=38504
// SYSDESC=WAGO 750-8212 PFC200 G2 2ETH RS
// ORDER=750-8212
// BA=1820886
// HWIDX=01
// PRGDATE=20180122T082343
// MARKING=PFC
// DESCR=WAGO 750-8212 PFC200 G2 2ETH RS
// UII=37SUN31564010207508212+0000000000001111
// LICENSES=426EFC85B477D09FEF96456268108B8ADCA7A6BDF1BD432511D7D798D8F6D34C588790EED18D654EE7F84FE1C5BD8F7F5A99B4BF04B0526FA1FFE14FD17774BA4A2CDB99DBD5D68ED7E44F9E0CB2AB1374537C66E3C3FC7001C1E96FA517E4CBB1D004F759EADEB77F0A9ECCD889C546
