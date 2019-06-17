/********************************************************************
* Copyright (C) 2019 PowerTech Engineering AS <post@pt-eng.no>
*
* This code may not be distributed, used or sold without explicit
* written permission from PowerTech Engineering AS.
*********************************************************************/

#include "cpp/appDataValue2.h"

//AppDataValue2& AppDataValue2::operator=(const AppDataValue2 & copy)
//{
//	// Make sure there are no residual values in our value
//	this->Clear_Values();
//
//	// For primitive values, we can copy the entire union
//	if (copy.application_tag == APPLICATION_TAG_NULL ||
//		copy.application_tag == APPLICATION_TAG_BOOLEAN ||
//		copy.application_tag == APPLICATION_TAG_UNSIGNED_INT ||
//		copy.application_tag == APPLICATION_TAG_SIGNED_INT ||
//		(copy.application_tag == APPLICATION_TAG_OCTET_STRING && this->application_value.Octet_String.choice == 0) ||
//		(copy.application_tag == APPLICATION_TAG_CHARACTER_STRING && !this->application_value.Character_String) ||
//		(copy.application_tag == APPLICATION_TAG_BIT_STRING && this->application_value.Bit_String.choice == 0) ||
//		copy.application_tag == APPLICATION_TAG_ENUMERATED ||
//		copy.application_tag == APPLICATION_TAG_DATE ||
//		copy.application_tag == APPLICATION_TAG_TIME ||
//		copy.application_tag == APPLICATION_TAG_OBJECT_ID ||
//		copy.application_tag == APPLICATION_TAG_DATETIME)
//	{
//		this->application_value = copy.application_value;
//	}
//
//	// For the remaining values, we need to do other shit
//	else
//	{
//		if (copy.application_tag == APPLICATION_TAG_OCTET_STRING)
//		{
//			this->application_value.Octet_String.big = new OctetString(*copy.application_value.Octet_String.big);
//			this->application_value.Octet_String.choice = 1;
//		}
//
//		else if (copy.application_tag == APPLICATION_TAG_CHARACTER_STRING)
//		{
//			this->application_value.Character_String = new CharacterString(*copy.application_value.Character_String);
//		}
//
//		else if (copy.application_tag == APPLICATION_TAG_BIT_STRING)
//		{
//			this->application_value.Bit_String.big = new BitString(*copy.application_value.Bit_String.big);
//			this->application_value.Bit_String.choice = 1;
//		}
//
//		else if (copy.application_tag == APPLICATION_TAG_ARRAY || copy.application_tag == APPLICATION_TAG_LIST)
//		{
//			this->application_value.List = new ValueList(*copy.application_value.List);
//		}
//		// TODO PHE: Other shit
//		;
//	}
//
//	// Copy the application tag
//	this->application_tag = copy.application_tag;
//
//	return *this;
//}
//
//bool AppDataValue2::operator==(const AppDataValue2 & rhs) const
//{
//	// Check that the tags are equal
//	if (this->application_tag != rhs.application_tag)
//		return false;
//
//	// Compare each value individually
//	switch (this->application_tag)
//	{
//		case APPLICATION_TAG_NULL:
//			return true;
//
//		case APPLICATION_TAG_BOOLEAN:
//			return (this->application_value.Boolean == rhs.application_value.Boolean);
//
//		case APPLICATION_TAG_UNSIGNED_INT:
//			return (this->application_value.Unsigned_Int == rhs.application_value.Unsigned_Int);
//
//		case APPLICATION_TAG_SIGNED_INT:
//			return (this->application_value.Signed_Int == rhs.application_value.Signed_Int);
//
//		case APPLICATION_TAG_REAL:
//			return (this->application_value.Real == rhs.application_value.Real);
//
//		case APPLICATION_TAG_DOUBLE:
//			return (this->application_value.Double == rhs.application_value.Double);
//
//		case APPLICATION_TAG_OCTET_STRING:			
//			if (this->application_value.Octet_String.choice == rhs.application_value.Octet_String.choice)
//			{
//				if (this->application_value.Octet_String.choice == 0)
//				{
//					return strcmp((char*)this->application_value.Octet_String.small, (char*)rhs.application_value.Octet_String.small);
//				}
//				else
//				{
//					return *this->application_value.Octet_String.big == *rhs.application_value.Octet_String.big;
//				}
//			}
//			else
//			{
//				return false;
//			}
//
//
//		case APPLICATION_TAG_CHARACTER_STRING:
//			if (this->application_value.Character_String && rhs.application_value.Character_String)
//				return (*this->application_value.Character_String == *rhs.application_value.Character_String);
//			else
//				return (this->application_value.Character_String == rhs.application_value.Character_String);
//
//		case APPLICATION_TAG_BIT_STRING:
//			if (this->application_value.Bit_String.choice == rhs.application_value.Bit_String.choice)
//			{
//				if (this->application_value.Bit_String.choice == 0)
//				{
//					return strcmp((char*)this->application_value.Bit_String.small, (char*)rhs.application_value.Bit_String.small);
//				}
//				else
//				{
//					return *this->application_value.Bit_String.big == *rhs.application_value.Bit_String.big;
//				}
//			}
//			else
//			{
//				return false;
//			}
//
//		case APPLICATION_TAG_ENUMERATED:
//			return (this->application_value.Enumerated == rhs.application_value.Enumerated);
//
//		case APPLICATION_TAG_DATE:
//			return (this->application_value.DateTime.year == rhs.application_value.DateTime.year &&
//				this->application_value.DateTime.month == rhs.application_value.DateTime.month &&
//				this->application_value.DateTime.day == rhs.application_value.DateTime.day &&
//				this->application_value.DateTime.weekday == rhs.application_value.DateTime.weekday);
//
//		case APPLICATION_TAG_TIME:
//			return (this->application_value.DateTime.hour == rhs.application_value.DateTime.hour &&
//				this->application_value.DateTime.minute == rhs.application_value.DateTime.minute &&
//				this->application_value.DateTime.second == rhs.application_value.DateTime.second &&
//				this->application_value.DateTime.hundredths == rhs.application_value.DateTime.hundredths);
//
//		case APPLICATION_TAG_OBJECT_ID:
//			return (this->application_value.Object_Id.object_type == rhs.application_value.Object_Id.object_type &&
//				this->application_value.Object_Id.object_instance == rhs.application_value.Object_Id.object_instance);
//
//		case APPLICATION_TAG_ARRAY:
//		case APPLICATION_TAG_LIST:
//			return (*this->application_value.List == *rhs.application_value.List);
//
//		default:
//			break;
//	}
//
//	// Not comparable (yet?)
//	return false;
//}




/** Empty this value
*/
void AppDataValue2::Clear_Values()
{
	// 'Big' Octet strings need to be deleted
	if (this->application_tag == APPLICATION_TAG_OCTET_STRING)
	{
		if (this->Octet_String.choice == 1)
		{
			delete (OctetString*)this->Octet_String.value;
		}

		this->Octet_String.size = 0;
		this->Octet_String.choice = 0;
		this->Octet_String.value = 0;
	}

	//// 'Big' Character strings need to be deleted
	//else if (this->application_tag == APPLICATION_TAG_CHARACTER_STRING)
	//{
	//	if (this->application_value.Character_String)
	//	{
	//		delete this->application_value.Character_String;
	//	}
	//}

	//// 'Big' Bit strings need to be deleted
	//else if (this->application_tag == APPLICATION_TAG_BIT_STRING)
	//{
	//	if (this->application_value.Bit_String.choice == 1)
	//	{
	//		delete this->application_value.Bit_String.big;
	//	}

	//	this->application_value.Bit_String.size = 0;
	//	this->application_value.Bit_String.choice = 0;
	//	this->application_value.Bit_String.big = 0;
	//}

	//// Lists and 'arrays' are allocated and need to be deleted
	//else if (this->application_tag == APPLICATION_TAG_ARRAY || this->application_tag == APPLICATION_TAG_LIST)
	//{
	//	delete this->application_value.List;
	//}

	// The rest of the values are safe to overwrite
	this->application_value.clear();
	this->application_tag = APPLICATION_TAG_NONE;
}


/** Assume value is bool and return it
@return - Value from data if application tag is Boolean, false if not
*/
bool AppDataValue2::Get_Bool() const
{
	if (this->application_tag == APPLICATION_TAG_BOOLEAN)
	{
		return this->application_value.Boolean;
	}
	return false;
}


/** Verify that value is boolean before returning it
@param output_value - Value from data if application tag is correct
@return - Wether the application tag matches the requested value
*/
bool AppDataValue2::Get_Bool(bool & output_value) const
{
	if (this->application_tag == APPLICATION_TAG_BOOLEAN)
	{
		output_value = this->application_value.Boolean;
		return true;
	}
	return false;
}


/** Assume value is unsigned and return it
@return - Value from data if application tag is Unsigned_Int, 0 if not
*/
uint32_t AppDataValue2::Get_Unsigned() const
{
	if (this->application_tag == APPLICATION_TAG_UNSIGNED_INT)
	{
		return this->application_value.Unsigned_Int;
	}
	return 0;
}


/** Verify that value is an unsigned integer before returning it
@param output_value - Value from data if application tag is correct
@return - Wether the application tag matches the requested value
*/
bool AppDataValue2::Get_Unsigned(uint32_t & output_value) const
{
	if (this->application_tag == APPLICATION_TAG_UNSIGNED_INT)
	{
		output_value = this->application_value.Unsigned_Int;
		return true;
	}
	return false;
}


/** Assume value is signed and return it
@return - Value from data if application tag is Signed_Int, 0 if not
*/
int32_t AppDataValue2::Get_Signed() const
{
	if (this->application_tag == APPLICATION_TAG_SIGNED_INT)
	{
		return this->application_value.Signed_Int;
	}
	return 0;
}


/** Verify that value is a signed integer before returning it
@param output_value - Value from data if application tag is correct
@return - Wether the application tag matches the requested value
*/
bool AppDataValue2::Get_Signed(int32_t & output_value) const
{
	if (this->application_tag == APPLICATION_TAG_SIGNED_INT)
	{
		output_value = this->application_value.Signed_Int;
		return true;
	}
	return false;
}


/** Assume value is real and return it
@return - Value from data if application tag is Real, 0 if not
*/
float AppDataValue2::Get_Real() const
{
	if (this->application_tag == APPLICATION_TAG_REAL)
	{
		return this->application_value.Real;
	}
	return 0;
}


/** Verify that value is real before returning it
@param output_value - Value from data if application tag is correct
@return - Wether the application tag matches the requested value
*/
bool AppDataValue2::Get_Real(float & output_value) const
{
	if (this->application_tag == APPLICATION_TAG_REAL)
	{
		output_value = this->application_value.Real;
		return true;
	}
	return false;
}


/** Assume value is double and return it
@return - Value from data if application tag is Double, empty if not
*/
double AppDataValue2::Get_Double() const
{
	if (this->application_tag == APPLICATION_TAG_DOUBLE)
	{
		return this->application_value.Double;
	}
	return 0;
}


/** Verify that value is double before returning it
@param output_value - Value from data if application tag is correct
@return - Wether the application tag matches the requested value
*/
bool AppDataValue2::Get_Double(double & output_value) const
{
	if (this->application_tag == APPLICATION_TAG_DOUBLE)
	{
		output_value = this->application_value.Double;
		return true;
	}
	return false;
}


/** Assume value is octetstring and return it
@return - Value from data if application tag is Octetstring, empty if not
*/
OctetString AppDataValue2::Get_OctetString() const
{
	OctetString output;

	if (this->application_tag == APPLICATION_TAG_OCTET_STRING)
	{
		if (this->Octet_String.choice == 0)
		{
			output.Overwrite((uint8_t*)&this->Octet_String.value, this->Octet_String.size);
		}
		else
		{
			output = *(OctetString*)this->Octet_String.value;
		}
	}
	return output;
}


/** Verify that value is octet string before returning it
@param output_value - Value from data if application tag is correct
@return - Wether the application tag matches the requested value
*/
bool AppDataValue2::Get_OctetString(OctetString & output_value) const
{
	if (this->application_tag == APPLICATION_TAG_OCTET_STRING)
	{
		if (this->Octet_String.choice == 0)
		{
			output_value.Overwrite((uint8_t*)&this->Octet_String.value, this->Octet_String.size);
		}
		else
		{
			output_value = *(OctetString*)this->Octet_String.value;
		}
		return true;
	}
	return false;
}


///** Assume value is characterstring and return it
//@return - Value from data if application tag is Characterstring, empty if not
//*/
//CharacterString AppDataValue2::Get_CharacterString() const
//{
//	CharacterString output;
//
//	if (this->application_tag == APPLICATION_TAG_CHARACTER_STRING)
//	{
//		if (this->application_value.Character_String)
//		{
//			output = *this->application_value.Character_String;
//		}
//		else
//		{
//			output.Clear();
//		}
//	}
//	return output;
//}
//
//
///** Verify that value is character string before returning it
//@param output_value - Value from data if application tag is correct
//@return - Wether the application tag matches the requested value
//*/
//bool AppDataValue2::Get_CharacterString(CharacterString & output_value) const
//{
//	if (this->application_tag == APPLICATION_TAG_CHARACTER_STRING)
//	{
//		if (this->application_value.Character_String)
//		{
//			output_value = *this->application_value.Character_String;
//		}
//		else
//		{
//			output_value.Clear();
//		}
//		return true;
//	}
//	return false;
//}
//
//
///** Assume value is bitstring and return it
//@return - Value from data if application tag is Bitstring, 0 if not
//*/
//BitString AppDataValue2::Get_BitString() const
//{
//	BitString output;
//
//	if (this->application_tag == APPLICATION_TAG_BIT_STRING)
//	{
//		if (this->application_value.Bit_String.choice == 0)
//		{
//			output.Set(*this->application_value.Bit_String.small, this->application_value.Bit_String.size);
//		}
//		else
//		{
//			output = *this->application_value.Bit_String.big;
//		}
//	}
//	return output;
//}
//
//
///** Verify that value is bit string before returning it
//@param output_value - Value from data if application tag is correct
//@return - Wether the application tag matches the requested value
//*/
//bool AppDataValue2::Get_BitString(BitString & output_value) const
//{
//	if (this->application_tag == APPLICATION_TAG_BIT_STRING)
//	{
//		if (this->application_value.Bit_String.choice == 0)
//		{
//			output_value.Set(*this->application_value.Bit_String.small, this->application_value.Bit_String.size);
//		}
//		else
//		{
//			output_value = *this->application_value.Bit_String.big;
//		}
//		return true;
//	}
//	return false;
//}


/** Assume value is enumerated and return it
@return - Value from data if application tag is Enumerated, 0 if not
*/
uint32_t AppDataValue2::Get_Enumerated() const
{
	if (this->application_tag == APPLICATION_TAG_ENUMERATED)
	{
		return this->application_value.Enumerated;
	}
	return 0;
}


/** Verify that value is enumerated before returning it
@param output_value - Value from data if application tag is correct
@return - Wether the application tag matches the requested value
*/
bool AppDataValue2::Get_Enumerated(uint32_t & output_value) const
{
	if (this->application_tag == APPLICATION_TAG_ENUMERATED)
	{
		output_value = this->application_value.Enumerated;
		return true;
	}
	return false;
}


///** Assume value is Date and return it
//@return - Value from data if application tag is Date or DateTime, wildcard if not
//*/
//Date AppDataValue2::Get_Date() const
//{
//	if (this->application_tag == APPLICATION_TAG_DATE || this->application_tag == APPLICATION_TAG_DATETIME)
//	{
//		return Date(this->application_value.DateTime.year, this->application_value.DateTime.month,
//			this->application_value.DateTime.day, this->application_value.DateTime.weekday);
//	}
//	return Date();
//}
//
//
///** Verify that value is Date or DateTime before returning it
//@param output_value - Value from data if application tag is correct
//@return - Wether the application tag matches the requested value
//*/
//bool AppDataValue2::Get_Date(Date & output_value) const
//{
//	if (this->application_tag == APPLICATION_TAG_DATE)
//	{
//		output_value.Set(this->application_value.DateTime.year, this->application_value.DateTime.month,
//			this->application_value.DateTime.day, this->application_value.DateTime.weekday);
//		return true;
//	}
//	return false;
//}
//
//
///** Assume value is Time and return it
//@return - Value from data if application tag is Time or DateTime, wildcard if not
//*/
//Time AppDataValue2::Get_Time() const
//{
//	if (this->application_tag == APPLICATION_TAG_DATE || this->application_tag == APPLICATION_TAG_DATETIME)
//	{
//		return Time(this->application_value.DateTime.hour, this->application_value.DateTime.minute,
//			this->application_value.DateTime.second, this->application_value.DateTime.hundredths);
//	}
//	return Time();
//}
//
//
///** Verify that value is Time before returning it
//@param output_value - Value from data if application tag is correct
//@return - Wether the application tag matches the requested value
//*/
//bool AppDataValue2::Get_Time(Time & output_value) const
//{
//	if (this->application_tag == APPLICATION_TAG_TIME)
//	{
//		output_value.Set(this->application_value.DateTime.hour, this->application_value.DateTime.minute,
//			this->application_value.DateTime.second, this->application_value.DateTime.hundredths);
//		return true;
//	}
//	return false;
//}
//
//
///** Assume value is Object Identifier and return it
//@return - Value from data if application tag is Object Identifier, wildcard if not
//*/
//ObjectIdentifier AppDataValue2::Get_Object_ID() const
//{
//	if (this->application_tag == APPLICATION_TAG_OBJECT_ID)
//	{
//		return ObjectIdentifier(this->application_value.Object_Id.object_type, this->application_value.Object_Id.object_instance);
//	}
//	return ObjectIdentifier();
//}
//
//
///** Verify that value is Object Identifier before returning it
//@param output_value - Value from data if application tag is correct
//@return - Wether the application tag matches the requested value
//*/
//bool AppDataValue2::Get_Object_ID(ObjectIdentifier & output_value) const
//{
//	if (this->application_tag == APPLICATION_TAG_OBJECT_ID)
//	{
//		output_value.Set(this->application_value.Object_Id.object_type, this->application_value.Object_Id.object_instance);
//		return true;
//	}
//	return false;
//}
//
//
///** Assume value is DateTime and return it
//@return - Value from data if application tag is DateTime, wildcard if not
//*/
//DateTime AppDataValue2::Get_DateTime() const
//{
//	if (this->application_tag == APPLICATION_TAG_DATETIME)
//	{
//		return DateTime(this->application_value.DateTime.year, this->application_value.DateTime.month,
//			this->application_value.DateTime.day, this->application_value.DateTime.weekday,
//			this->application_value.DateTime.hour, this->application_value.DateTime.minute,
//			this->application_value.DateTime.second, this->application_value.DateTime.hundredths);
//	}
//	return DateTime();
//}
//
//
///** Verify that value is DateTime before returning it
//@param output_value - Value from data if application tag is correct
//@return - Wether the application tag matches the requested value
//*/
//bool AppDataValue2::Get_DateTime(DateTime & output_value) const
//{
//	if (this->application_tag == APPLICATION_TAG_DATETIME)
//	{
//		output_value.Set(this->application_value.DateTime.year, this->application_value.DateTime.month,
//			this->application_value.DateTime.day, this->application_value.DateTime.weekday,
//			this->application_value.DateTime.hour, this->application_value.DateTime.minute,
//			this->application_value.DateTime.second, this->application_value.DateTime.hundredths);
//		return true;
//	}
//	return false;
//}
//
//
///** Assume value is an array and return it
//@return - Pointer to list if application tag is Array, wildcard if not
//*/
//ValueList * AppDataValue2::Get_Array() const
//{
//	if (this->application_tag == APPLICATION_TAG_ARRAY)
//		return this->application_value.List;
//	else
//		return nullptr;
//}
//
//
///** Verify that value is an Array before returning it
//@param output_value - Value from data if application tag is correct
//@return - Wether the application tag matches the requested value
//*/
//bool AppDataValue2::Get_Array(ValueList * output_value) const
//{
//	(void)output_value;
//	if (this->application_tag == APPLICATION_TAG_ARRAY)
//	{
//		output_value = this->application_value.List;
//		return true;
//	}
//	output_value = nullptr;
//	return false;
//}
//
//
///** Assume value is a list and return it
//@return - Pointer to list if application tag is List, wildcard if not
//*/
//ValueList * AppDataValue2::Get_List() const
//{
//	if (this->application_tag == APPLICATION_TAG_LIST)
//		return this->application_value.List;
//	else
//		return nullptr;
//}
//
//
///** Verify that value is a List before returning it
//@param output_value - Value from data if application tag is correct
//@return - Wether the application tag matches the requested value
//*/
//bool AppDataValue2::Get_List(ValueList * output_value) const
//{
//	(void)output_value;
//	if (this->application_tag == APPLICATION_TAG_LIST)
//	{
//		output_value = this->application_value.List;
//		return true;
//	}
//	output_value = nullptr;
//	return false;
//}
//

void AppDataValue2::Set_Null()
{
	// Clear previous values and set tag
	this->Clear_Values();
	this->application_tag = APPLICATION_TAG_NULL;
}


void AppDataValue2::Set_Boolean(bool input_value)
{
	// Clear previous values, set value and tag
	this->Clear_Values();
	this->application_value.Boolean = input_value;
	this->application_tag = APPLICATION_TAG_BOOLEAN;
}


void AppDataValue2::Set_Unsigned(uint32_t input_value)
{
	// Clear previous values, set value and tag
	this->Clear_Values();
	this->application_value.Unsigned_Int = input_value;
	this->application_tag = APPLICATION_TAG_UNSIGNED_INT;
}


void AppDataValue2::Set_Signed(int32_t input_value)
{
	// Clear previous values, set value and tag
	this->Clear_Values();
	this->application_value.Signed_Int = input_value;
	this->application_tag = APPLICATION_TAG_SIGNED_INT;
}


void AppDataValue2::Set_Real(float input_value)
{
	// Clear previous values, set value and tag
	this->Clear_Values();
	this->application_value.Real = input_value;
	this->application_tag = APPLICATION_TAG_REAL;
}


void AppDataValue2::Set_Double(double input_value)
{
	// Clear previous values, set value and tag
	this->Clear_Values();
	this->application_value.Double = input_value;
	this->application_tag = APPLICATION_TAG_DOUBLE;
}


void AppDataValue2::Set_Octet_String(OctetString & input_value)
{
	this->Clear_Values();
	if (input_value.Get_Length() > 4)
	{
		this->new_octet_string((OctetString*)this->Octet_String.value, input_value);
		this->Octet_String.choice = 1;
	}
	else
	{
		memcpy((uint8_t*)&this->Octet_String.value, input_value.Get_String(), input_value.Get_Length());
		this->Octet_String.size = input_value.Get_Length();
		this->Octet_String.choice = 0;
	}

	this->application_tag = APPLICATION_TAG_OCTET_STRING;
}


//void AppDataValue2::Set_Character_String(CharacterString & input_value)
//{
//	this->Clear_Values();
//	if (input_value.Get_Length())
//		this->application_value.Character_String = new CharacterString(input_value);
//	else
//		this->application_value.Character_String = nullptr;
//
//	this->application_tag = APPLICATION_TAG_CHARACTER_STRING;
//}
//
//
//void AppDataValue2::Set_Character_String(const char * input_value)
//{
//	this->Clear_Values();
//	if (input_value)
//		this->application_value.Character_String = new CharacterString(input_value);
//	else
//		this->application_value.Character_String = nullptr;
//
//	this->application_tag = APPLICATION_TAG_CHARACTER_STRING;
//}
//
//
//void AppDataValue2::Set_Bit_String(BitString & input_value)
//{
//	this->Clear_Values();
//	if (input_value.Get_Bytes_Used() > 4)
//	{
//		this->application_value.Bit_String.big = new BitString(input_value);
//		this->application_value.Bit_String.choice = 1;
//	}
//	else
//	{
//		memcpy(this->application_value.Bit_String.small, input_value.Get_String(), input_value.Get_Bytes_Used());
//		this->application_value.Bit_String.size = input_value.Get_Bytes_Used();
//		this->application_value.Bit_String.choice = 0;
//	}
//
//	this->application_tag = APPLICATION_TAG_BIT_STRING;
//}


void AppDataValue2::Set_Enumerated(uint32_t input_value)
{
	// Clear previous values, set value and tag
	this->Clear_Values();
	this->application_value.Enumerated = input_value;
	this->application_tag = APPLICATION_TAG_ENUMERATED;
}


//void AppDataValue2::Set_Date(const Date & input_value)
//{
//	// Clear previous values, set value and tag
//	this->Clear_Values();
//	this->application_value.DateTime.year = input_value.Get_Year();
//	this->application_value.DateTime.month = input_value.Get_Month();
//	this->application_value.DateTime.day = input_value.Get_Day();
//	this->application_value.DateTime.weekday = input_value.Get_Weekday();
//	this->application_tag = APPLICATION_TAG_DATE;
//}
//
//
//void AppDataValue2::Set_Date(uint16_t year, uint8_t month, uint8_t day, uint8_t weekday)
//{
//	// Clear previous values, set value and tag
//	this->Clear_Values();
//	this->application_value.DateTime.year = year;
//	this->application_value.DateTime.month = month;
//	this->application_value.DateTime.day = day;
//	this->application_value.DateTime.weekday = weekday;
//	this->application_tag = APPLICATION_TAG_DATE;
//}
//
//
//void AppDataValue2::Set_Time(Time & input_value)
//{
//	// Clear previous values, set value and tag
//	this->Clear_Values();
//	this->application_value.DateTime.hour = input_value.Get_Hour();
//	this->application_value.DateTime.minute = input_value.Get_Minute();
//	this->application_value.DateTime.second = input_value.Get_Second();
//	this->application_value.DateTime.hundredths = input_value.Get_Hundredths();
//	this->application_tag = APPLICATION_TAG_TIME;
//}
//
//
//void AppDataValue2::Set_Time(uint8_t hour, uint8_t minute, uint8_t second, uint8_t hundredth)
//{
//	// Clear previous values, set value and tag
//	this->Clear_Values();
//	this->application_value.DateTime.hour = hour;
//	this->application_value.DateTime.minute = minute;
//	this->application_value.DateTime.second = second;
//	this->application_value.DateTime.hundredths = hundredth;
//	this->application_tag = APPLICATION_TAG_TIME;
//}
//
//
//void AppDataValue2::Set_Object_ID(ObjectIdentifier & input_value)
//{
//	// Clear previous values, set value and tag
//	this->Clear_Values();
//	this->application_value.Object_Id.object_type = input_value.Get_Type();
//	this->application_value.Object_Id.object_instance = input_value.Get_Instance();
//	this->application_tag = APPLICATION_TAG_OBJECT_ID;
//}
//
//
//void AppDataValue2::Set_Object_ID(uint16_t type, uint32_t instance)
//{
//	// Clear previous values, set value and tag
//	this->Clear_Values();
//	this->application_value.Object_Id.object_type = type;
//	this->application_value.Object_Id.object_instance = instance;
//	this->application_tag = APPLICATION_TAG_OBJECT_ID;
//}
//
//
//void AppDataValue2::Set_DateTime(DateTime & input_value)
//{
//	// Clear previous values, set value and tag
//	this->Clear_Values();
//	this->application_value.DateTime.year = input_value.Get_Year();
//	this->application_value.DateTime.month = input_value.Get_Month();
//	this->application_value.DateTime.day = input_value.Get_Day();
//	this->application_value.DateTime.weekday = input_value.Get_Weekday();
//	this->application_value.DateTime.hour = input_value.Get_Hour();
//	this->application_value.DateTime.minute = input_value.Get_Minute();
//	this->application_value.DateTime.second = input_value.Get_Second();
//	this->application_value.DateTime.hundredths = input_value.Get_Hundredth();
//	this->application_tag = APPLICATION_TAG_DATETIME;
//}
//
//
//void AppDataValue2::Set_DateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t weekday, uint8_t hour, uint8_t minute, uint8_t second, uint8_t hundredth)
//{
//	// Clear previous values, set value and tag
//	this->Clear_Values();
//	this->application_value.DateTime.year = year;
//	this->application_value.DateTime.month = month;
//	this->application_value.DateTime.day = day;
//	this->application_value.DateTime.weekday = weekday;
//	this->application_value.DateTime.hour = hour;
//	this->application_value.DateTime.minute = minute;
//	this->application_value.DateTime.second = second;
//	this->application_value.DateTime.hundredths = hundredth;
//	this->application_tag = APPLICATION_TAG_DATETIME;
//}
//
//
//void AppDataValue2::Set_List()
//{
//	this->Clear_Values();
//	this->application_value.List = new ValueList();
//	this->application_tag = APPLICATION_TAG_LIST;
//}
//
//
//void AppDataValue2::Set_List(const ValueList& input_list)
//{
//	this->Clear_Values();
//	this->application_value.List = new ValueList(input_list);
//	this->application_tag = APPLICATION_TAG_LIST;
//}
//
//
//void AppDataValue2::Set_Array()
//{
//	this->Clear_Values();
//	this->application_value.List = new ValueList();
//	this->application_tag = APPLICATION_TAG_ARRAY;
//}
//
//
//void AppDataValue2::Set_Array(const ValueList & input_array)
//{
//	this->Clear_Values();
//	this->application_value.List = new ValueList(input_array);
//	this->application_tag = APPLICATION_TAG_ARRAY;
//}
//
//
///** Write application data value to apdu
//@param value [in] - Application data value to write
//@return - False if write failed (for any reason)
//*/
//bool AppDataValue2::Apdu_Encode(ApduWriteBuffer& write_buffer) const
//{
//	// General functions
//	switch (this->Get_Tag())
//	{
//		case APPLICATION_TAG_NULL:
//			return write_buffer.Write_Null();
//
//		case APPLICATION_TAG_BOOLEAN:
//			return write_buffer.Write_Boolean(this->Get_Bool());
//
//		case APPLICATION_TAG_UNSIGNED_INT:
//			return write_buffer.Write_Unsigned(this->Get_Unsigned());
//
//		case APPLICATION_TAG_SIGNED_INT:
//			return write_buffer.Write_Signed(this->Get_Signed());
//
//		case APPLICATION_TAG_REAL:
//			return write_buffer.Write_Real(this->Get_Real());
//
//		case APPLICATION_TAG_DOUBLE:
//			return write_buffer.Write_Double(this->Get_Double());
//
//		case APPLICATION_TAG_OCTET_STRING:
//		{
//			OctetString current_octetstring(this->Get_OctetString());
//			return write_buffer.Write_OctetString(current_octetstring);
//		}
//
//		case APPLICATION_TAG_CHARACTER_STRING:
//		{
//			CharacterString current_string(this->Get_CharacterString());
//			return write_buffer.Write_CharacterString(current_string);
//		}
//
//		case APPLICATION_TAG_BIT_STRING:
//		{
//			BitString current_bitstring(this->Get_BitString());
//			return write_buffer.Write_BitString(current_bitstring);
//		}
//
//		case APPLICATION_TAG_ENUMERATED:
//			return write_buffer.Write_Enumerated(this->Get_Enumerated());
//
//		case APPLICATION_TAG_DATE:
//		{
//			// Fetch an instance of the stored date value
//			Date current_date(this->Get_Date());
//			return write_buffer.Write_Date(current_date);
//		}
//
//		case APPLICATION_TAG_TIME:
//		{
//			// Fetch an instance of the stored time value
//			Time current_time(this->Get_Time());
//			return write_buffer.Write_Time(current_time);
//		}
//
//		case APPLICATION_TAG_OBJECT_ID:
//		{
//			ObjectIdentifier current_object(this->Get_Object_ID());
//			return write_buffer.Write_ObjectID(current_object);
//		}
//
//		default:
//			break;
//	}
//
//	// Object-specific functions
//	switch (this->Get_Tag())
//	{
//		case APPLICATION_TAG_DATETIME:
//		{
//			// Fetch an instance of the object
//			DateTime var(this->Get_DateTime());
//
//			// Use the object-specific encoding function
//			return var.Apdu_Encode(write_buffer);
//		}
//
//		case APPLICATION_TAG_LIST:
//		case APPLICATION_TAG_ARRAY:
//			return this->application_value.List->Apdu_Encode(write_buffer);
//			
//		default:
//			break;
//	}
//
//	// TODO: The rest isn't done yet
//	return false;
//}
//
//
///** Write application data value to apdu with context tag
//@param data [in] - Application data value to write
//@param context_tag [in] - Context tag to encode with
//@return - False if write failed (for any reason)
//*/
//bool AppDataValue2::Apdu_Encode(ApduWriteBuffer& write_buffer, uint8_t context_tag) const
//{
//	// Primitive values
//	switch (this->Get_Tag())
//	{
//		case APPLICATION_TAG_NULL:
//			return write_buffer.Write_Null();
//
//		case APPLICATION_TAG_BOOLEAN:
//			return write_buffer.Write_Boolean(this->Get_Bool(), context_tag);
//
//		case APPLICATION_TAG_UNSIGNED_INT:
//			return write_buffer.Write_Unsigned(this->Get_Unsigned(), context_tag);
//
//		case APPLICATION_TAG_SIGNED_INT:
//			return write_buffer.Write_Signed(this->Get_Signed(), context_tag);
//
//		case APPLICATION_TAG_REAL:
//			return write_buffer.Write_Real(this->Get_Real(), context_tag);
//
//		case APPLICATION_TAG_DOUBLE:
//			return write_buffer.Write_Double(this->Get_Double(), context_tag);
//
//		case APPLICATION_TAG_OCTET_STRING:
//		{
//			OctetString current_octetstring = this->Get_OctetString();
//			return write_buffer.Write_OctetString(current_octetstring, context_tag);
//		}
//
//		case APPLICATION_TAG_CHARACTER_STRING:
//		{
//			CharacterString current_string = this->Get_CharacterString();
//			return write_buffer.Write_CharacterString(current_string, context_tag);
//		}
//
//		case APPLICATION_TAG_BIT_STRING:
//		{
//			BitString current_bitstring = this->Get_BitString();
//			return write_buffer.Write_BitString(current_bitstring, context_tag);
//		}
//
//		case APPLICATION_TAG_ENUMERATED:
//			return write_buffer.Write_Enumerated(this->Get_Enumerated(), context_tag);
//
//		case APPLICATION_TAG_DATE:
//		{
//			Date current_date = this->Get_Date();
//			return write_buffer.Write_Date(current_date, context_tag);
//		}
//
//		case APPLICATION_TAG_TIME:
//		{
//			Time current_time = this->Get_Time();
//			return write_buffer.Write_Time(current_time, context_tag);
//		}
//
//		case APPLICATION_TAG_OBJECT_ID:
//		{
//			ObjectIdentifier current_object = this->Get_Object_ID();
//			return write_buffer.Write_ObjectID(current_object, context_tag);
//		}
//
//		default:
//			break;
//	}
//
//	// TODO: The rest isn't done yet
//
//	return false;
//}
//
//DateRange AppDataValue2::Get_DateRange()
//{
//	DateRange output_value;
//
//	if (this->application_tag == APPLICATION_TAG_DATERANGE)
//	{
//		output_value.from.Set(this->application_value.DateRange.from_year, this->application_value.DateRange.from_month,
//			this->application_value.DateRange.from_day, this->application_value.DateRange.from_weekday);
//
//		output_value.to.Set(this->application_value.DateRange.to_year, this->application_value.DateRange.to_month,
//			this->application_value.DateRange.to_day, this->application_value.DateRange.to_weekday);
//	}
//
//	return output_value;
//}
//
//bool AppDataValue2::Get_DateRange(DateRange & output_value)
//{
//	if (this->application_tag == APPLICATION_TAG_DATERANGE)
//	{
//		output_value.from.Set(this->application_value.DateRange.from_year, this->application_value.DateRange.from_month,
//			this->application_value.DateRange.from_day, this->application_value.DateRange.from_weekday);
//
//		output_value.to.Set(this->application_value.DateRange.to_year, this->application_value.DateRange.to_month,
//			this->application_value.DateRange.to_day, this->application_value.DateRange.to_weekday);
//
//		return true;
//	}
//
//	return false;
//}
//
//void AppDataValue2::Set_DateRange(const DateRange & input_value)
//{
//	this->Clear_Values();
//	this->application_value.DateRange.from_year = input_value.from.Get_Year();
//	this->application_value.DateRange.from_month = input_value.from.Get_Month();
//	this->application_value.DateRange.from_day = input_value.from.Get_Day();
//	this->application_value.DateRange.from_weekday = input_value.from.Get_Weekday();
//
//	this->application_value.DateRange.to_year = input_value.to.Get_Year();
//	this->application_value.DateRange.to_month = input_value.to.Get_Month();
//	this->application_value.DateRange.to_day = input_value.to.Get_Day();
//	this->application_value.DateRange.to_weekday = input_value.to.Get_Weekday();
//
//	this->application_tag = APPLICATION_TAG_DATERANGE;
//}
//
//void AppDataValue2::Set_DateRange(const Date & from_date, const Date & to_date)
//{
//	this->Clear_Values();
//	this->application_value.DateRange.from_year = from_date.Get_Year();
//	this->application_value.DateRange.from_month = from_date.Get_Month();
//	this->application_value.DateRange.from_day = from_date.Get_Day();
//	this->application_value.DateRange.from_weekday = from_date.Get_Weekday();
//
//	this->application_value.DateRange.to_year = to_date.Get_Year();
//	this->application_value.DateRange.to_month = to_date.Get_Month();
//	this->application_value.DateRange.to_day = to_date.Get_Day();
//	this->application_value.DateRange.to_weekday = to_date.Get_Weekday();
//
//	this->application_tag = APPLICATION_TAG_DATERANGE;
//}
//
//WeekAndDay AppDataValue2::Get_WeekAndDay()
//{
//	WeekAndDay output_value;
//
//	if (this->application_tag == APPLICATION_TAG_WEEKANDDAY)
//	{
//		output_value.Set(this->application_value.WeekAndDay.month, this->application_value.WeekAndDay.week_of_month, this->application_value.WeekAndDay.day_of_week);
//	}
//
//	return output_value;
//}
//
//bool AppDataValue2::Get_WeekAndDay(WeekAndDay & output_value)
//{
//	if (this->application_tag == APPLICATION_TAG_DATERANGE)
//	{
//		output_value.Set(this->application_value.WeekAndDay.month, this->application_value.WeekAndDay.week_of_month, this->application_value.WeekAndDay.day_of_week);
//
//		return true;
//	}
//
//	return false;
//}
//
//void AppDataValue2::Set_WeekAndDay(const WeekAndDay & input_value)
//{
//	this->Clear_Values();
//	this->application_value.WeekAndDay.month = input_value.Get_Month();
//	this->application_value.WeekAndDay.week_of_month = input_value.Get_WeekOfMonth();
//	this->application_value.WeekAndDay.day_of_week = input_value.Get_WeekOfMonth();
//	this->application_tag = APPLICATION_TAG_WEEKANDDAY;
//}
//
//void AppDataValue2::Set_WeekAndDay(uint8_t month, uint8_t week_of_month, uint8_t day_of_week)
//{
//	this->Clear_Values();
//	this->application_value.WeekAndDay.month = month;
//	this->application_value.WeekAndDay.week_of_month = week_of_month;
//	this->application_value.WeekAndDay.day_of_week = day_of_week;
//	this->application_tag = APPLICATION_TAG_WEEKANDDAY;
//}
//
//bool AppDataValue2::Get_CalendarEntry(CalendarEntry & output_value)
//{
//	if (this->application_tag == APPLICATION_TAG_DATE)
//	{
//		Date set_value(this->Get_Date());
//		output_value.Set_Date(set_value);
//
//		return true;
//	}
//
//	else if (this->application_tag == APPLICATION_TAG_DATERANGE)
//	{
//		DateRange set_value(this->Get_DateRange());
//		output_value.Set_DateRange(set_value.from, set_value.to);
//
//		return true;
//	}
//
//	else if (this->application_tag == APPLICATION_TAG_WEEKANDDAY)
//	{
//		WeekAndDay set_value(this->Get_WeekAndDay());
//		output_value.Set_WeekAndDay(set_value);
//
//		return true;
//	}
//
//	else
//	{
//		return false;
//	}
//}
//
//void AppDataValue2::Set_CalendarEntry(CalendarEntry & input_value)
//{
//	switch (input_value.Get_Type())
//	{
//		case CALENDAR_ENTRY_DATE:
//			this->Set_Date(input_value.Get_Date());
//			break;
//
//		case CALENDAR_ENTRY_DATERANGE:
//			this->Set_DateRange(input_value.Get_DateRange());
//			break;
//
//		case CALENDAR_ENTRY_WEEKANDDAY:
//			this->Set_WeekAndDay(input_value.Get_WeekAndDay());
//			break;
//
//		default:
//			break;
//	}
//}
//
//void AppDataValue2::Set_Void(void * input_value)
//{
//	this->Clear_Values();
//	this->application_value.void_pointer = input_value;
//	this->application_tag = APPLICATION_TAG_VOID_POINTER;
//}
//
//void * AppDataValue2::Get_Void() const
//{
//	if (this->application_tag == APPLICATION_TAG_VOID_POINTER)
//	{
//		return this->application_value.void_pointer;
//	}
//	return nullptr;
//}
//
//bool AppDataValue2::Get_Void(void * output_value) const
//{
//	(void)output_value;
//	if (this->application_tag == APPLICATION_TAG_VOID_POINTER)
//	{
//		output_value = this->application_value.void_pointer;
//		return true;
//	}
//	output_value = nullptr;
//	return false;
//}


void AppDataValue2::new_octet_string(OctetString * pointer, OctetString & input_value)
{
	pointer = new OctetString(input_value);
	(void)pointer;
}