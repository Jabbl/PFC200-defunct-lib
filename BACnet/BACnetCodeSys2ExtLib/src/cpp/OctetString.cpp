/********************************************************************
* Copyright (C) 2019 PowerTech Engineering AS <post@pt-eng.no>
*
* This code may not be distributed, used or sold without explicit
* written permission from PowerTech Engineering AS.
*********************************************************************/

#include "cpp/OctetString.h"
#include <stdlib.h>
#include <ctype.h>


/** Read an alphanumeric string and put it's values into the octetstring
@param string [in] - String to be read
@return - False if max size reached
*/
bool OctetString::Write_FromString(const char* input_string)
{
	bool status = false; // Return value
	this->length = 0; // Empty the value by resetting length

	// Empty string means nothing to decode
	if (input_string[0] == 0)
	{
		status = true;
	}
	else
	{
		// Temporary values
		size_t pos = 0;
		char hex_string[3] = "";

		// Search through the entire string
		while (input_string[pos] != 0)
		{
			// Verify that the character is alphanumeric
			if (!isalnum(input_string[pos]))
			{
				pos++;
				continue;
			}

			// Verify that the next character exists and is alphanumeric
			if (input_string[pos + 1] == 0 || !isalnum(input_string[pos + 1]))
			{
				break;
			}

			// Move the values to a short string
			hex_string[0] = input_string[pos];
			hex_string[1] = input_string[pos + 1];

			// Check length
			if (this->length <= octetstring_max_bytes)
			{
				// Transfer value to octetstring
				this->string[this->length] = (uint8_t)strtol(hex_string, NULL, 16);;
				++this->length;
				
				// Minimum one pair has been successfully converted
				status = true;
			}
			else
			{
				status = false;
				break;
			}
			
			// Check next pair
			pos += 2;
		}
	}

	// String searched
	return status;
}