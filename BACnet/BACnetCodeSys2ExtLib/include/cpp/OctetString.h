/********************************************************************
* Copyright (C) 2019 PowerTech Engineering AS <post@pt-eng.no>
*
* This code may not be distributed, used or sold without explicit
* written permission from PowerTech Engineering AS.
*********************************************************************/

#pragma once

#include <stdint.h>
#include <string.h>

// Constants
constexpr size_t octetstring_max_bytes = 255; // 255 octets is probably way too much...

class OctetString
{
public:
	// Initialize with empty string
	OctetString() :
		length(0)
	{
		this->string[0] = 0;
	}

	// Intialize from characterstring
	OctetString(const char* value)
	{
		this->Write_FromString(value);
	}

	// Initialize from octet-buffer
	OctetString(const uint8_t* value, size_t value_length)
	{
		this->Overwrite(value, value_length);
	}

	// Copy between octetstrings
	OctetString(const OctetString& copy)
	{
		// Verify that the length is valid
		if (copy.length <= octetstring_max_bytes)
		{
			// Copy from source to us
			memcpy(this->string, copy.string, copy.length);
		}
	}

	// Assignment
	OctetString& operator=(const OctetString& copy)
	{
		// Verify that the length is valid
		if (copy.length <= octetstring_max_bytes)
		{
			// Copy from source to us
			memcpy(this->string, copy.string, copy.length);
		}

		return *this;
	}

	bool operator==(const OctetString& rhs) const
	{
		// Check that specified lengths are equal
		bool equal = this->length == rhs.length;

		if (equal)
		{
			// Check that the strings themselves are equal
			for (size_t i = 0; i < this->length; i++)
			{
				if (this->string[i] != rhs.string[i])
				{
					equal = false;
					break;
				}
			}
		}

		// Return the result
		return equal;
	}

	inline bool operator!=(const OctetString& rhs) const { return !(*this == rhs); }

	// Get a pointer to the octetstring
	inline const uint8_t* Get_String() const { return this->string; }

	// Get current length of the octetstring
	inline size_t Get_Length() const { return this->length; }

	// Get a single octet from position 'pos' in octetstring
	inline uint8_t Get_Octet(size_t pos) 
	{ 
		if (pos <= this->length)
			return this->string[pos];
		else 
			return 0; 
	}

	// Append data to the existing octetstring
	inline void Append(const uint8_t* value, size_t value_size)
	{
		if (this->length + value_size <= octetstring_max_bytes)
		{
			memcpy(&this->string[this->length], value, value_size);
		}
	}

	// Overwrite the existing data in octetstring
	inline void Overwrite(const uint8_t* value, size_t value_size)
	{
		if (value_size <= octetstring_max_bytes)
		{
			memcpy(this->string, value, value_size);
			this->length = value_size;
		}
	}

	/** Read an alphanumeric string and put it's values into the octetstring
	@param string [in] - String to be read
	@return - False if max size reached
	*/
	bool Write_FromString(const char* string);

private:
	// Storage for values
	uint8_t string[octetstring_max_bytes];

	// Current length of string
	size_t length;
};
