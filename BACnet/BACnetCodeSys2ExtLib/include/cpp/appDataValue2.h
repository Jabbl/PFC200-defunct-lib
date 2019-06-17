/********************************************************************
* Copyright (C) 2019 PowerTech Engineering AS <post@pt-eng.no>
*
* This code may not be distributed, used or sold without explicit
* written permission from PowerTech Engineering AS.
*********************************************************************/

#pragma once

#include <stdint.h>
#include "apduSettings.h"
#include "OctetString.h"

struct octstring
{
	size_t size;
	uint8_t choice;
	uint32_t value;
};

//class ValueList;

class AppDataValue2
{
public:
	// Initialize without values
	AppDataValue2(void)
	{
		this->Set_Null();
	};

	// Initialize as a boolean value and
	AppDataValue2(bool initial_value) :
		application_value()
	{
		this->Set_Boolean(initial_value);
	};

	// Initialize as an unsigned value
	AppDataValue2(uint32_t initial_value) :
		application_value()
	{
		this->Set_Unsigned(initial_value);
	};

	// Initialize as a signed value
	AppDataValue2(int32_t initial_value) :
		application_value()
	{
		this->Set_Signed(initial_value);
	};

	// Initialize as a real value
	AppDataValue2(float initial_value) :
		application_value()
	{
		this->Set_Real(initial_value);
	};

	// Initialize as an initial double value
	AppDataValue2(double initial_value) :
		application_value()
	{
		this->Set_Double(initial_value);
	};

	// Initialize as an octet string
	AppDataValue2(OctetString& initial_value) :
		application_value()
	{
		this->Set_Octet_String(initial_value);
	};

	//// Initialize as a character string
	//AppDataValue2(CharacterString& initial_value) :
	//	application_value()
	//{
	//	this->Set_Character_String(initial_value);
	//};

	//// Initialize as a bit string
	//AppDataValue2(BitString& initial_value) :
	//	application_value()
	//{
	//	this->Set_Bit_String(initial_value);
	//};

	//// Initialize as a date value
	//AppDataValue2(Date& initial_value) :
	//	application_value()
	//{
	//	this->Set_Date(initial_value);
	//};

	//// Initialize as a date value
	//AppDataValue2(uint16_t year, uint8_t month, uint8_t day, uint8_t weekday) :
	//	application_value()
	//{
	//	this->Set_Date(year, month, day, weekday);
	//};

	//// Initialize as a time value
	//AppDataValue2(Time& initial_value) :
	//	application_value()
	//{
	//	this->Set_Time(initial_value);
	//};

	//// Initialize as a time value
	//AppDataValue2(uint8_t hour, uint8_t minute, uint8_t second, uint8_t hundredth) :
	//	application_value()
	//{
	//	this->Set_Time(hour, minute, second, hundredth);
	//};

	//// Initialize as an object identifier
	//AppDataValue2(ObjectIdentifier& initial_value) :
	//	application_value()
	//{
	//	this->Set_Object_ID(initial_value);
	//};

	//// Initialize as an object identifier
	//AppDataValue2(uint16_t object_type, uint32_t object_instance) :
	//	application_value()
	//{
	//	this->Set_Object_ID(object_type, object_instance);
	//};

	//// Initialize as a datetime value
	//AppDataValue2(DateTime& initial_value) :
	//	application_value()
	//{
	//	this->Set_DateTime(initial_value);
	//};

	//// Initialize as a datetime value
	//AppDataValue2(uint16_t year, uint8_t month, uint8_t day, uint8_t weekday, uint8_t hour, uint8_t minute, uint8_t second, uint8_t hundredth) :
	//	application_value()
	//{
	//	this->Set_DateTime(year, month, day, weekday, hour, minute, second, hundredth);
	//};

	//// Initialize with existing AppDataValue2
	//AppDataValue2(const AppDataValue2& copy) :
	//	application_value()
	//{
	//	*this = copy;
	//};

	~AppDataValue2()
	{
		//this->Clear_Values();
	};

	//// Assignment
	//AppDataValue2& operator =(const AppDataValue2& copy);

	//// Handle comparison
	//bool operator ==(const AppDataValue2& rhs) const;

	// Get tag of current value in storage
	inline ApplicationTag Get_Tag() const { return this->application_tag; }

	/** Clear all stored items
	*/
	void Clear_Values();


	/** Assume value is bool and return it
	@return - Value from data if application tag is Boolean, false if not
	*/
	bool Get_Bool() const;

	/** Verify that value is boolean before returning it
	@param output_value - Value from data if application tag is correct
	@return - Wether the application tag matches the requested value
	*/
	bool Get_Bool(bool& output_value) const;

	/** Assume value is unsigned and return it
	@return - Value from data if application tag is Unsigned_Int, 0 if not
	*/
	uint32_t Get_Unsigned() const;

	/** Verify that value is an unsigned integer before returning it
	@param output_value - Value from data if application tag is correct
	@return - Wether the application tag matches the requested value
	*/
	bool Get_Unsigned(uint32_t& output_value) const;

	/** Assume value is signed and return it
	@return - Value from data if application tag is Signed_Int, 0 if not
	*/
	int32_t Get_Signed() const;

	/** Verify that value is a signed integer before returning it
	@param output_value - Value from data if application tag is correct
	@return - Wether the application tag matches the requested value
	*/
	bool Get_Signed(int32_t& output_value) const;

	/** Assume value is real and return it
	@return - Value from data if application tag is Real, 0 if not
	*/
	float Get_Real() const;

	/** Verify that value is real before returning it
	@param output_value - Value from data if application tag is correct
	@return - Wether the application tag matches the requested value
	*/
	bool Get_Real(float& output_value) const;

	/** Assume value is double and return it
	@return - Value from data if application tag is Double, empty if not
	*/
	double Get_Double() const;

	/** Verify that value is double before returning it
	@param output_value - Value from data if application tag is correct
	@return - Wether the application tag matches the requested value
	*/
	bool Get_Double(double& output_value) const;

	/** Assume value is octetstring and return it
	@return - Value from data if application tag is Octetstring, empty if not
	*/
	OctetString Get_OctetString() const;

	/** Verify that value is octet string before returning it
	@param output_value - Value from data if application tag is correct
	@return - Wether the application tag matches the requested value
	*/
	bool Get_OctetString(OctetString& output_value) const;

	///** Assume value is characterstring and return it
	//@return - Value from data if application tag is Characterstring, empty if not
	//*/
	//CharacterString Get_CharacterString() const;

	///** Verify that value is character string before returning it
	//@param output_value - Value from data if application tag is correct
	//@return - Wether the application tag matches the requested value
	//*/
	//bool Get_CharacterString(CharacterString& output_value) const;

	///** Assume value is bitstring and return it
	//@return - Value from data if application tag is Bitstring, 0 if not
	//*/
	//BitString Get_BitString() const;

	///** Verify that value is bit string before returning it
	//@param output_value - Value from data if application tag is correct
	//@return - Wether the application tag matches the requested value
	//*/
	//bool Get_BitString(BitString& output_value) const;

	/** Assume value is enumerated and return it
	@return - Value from data if application tag is Enumerated, 0 if not
	*/
	uint32_t Get_Enumerated() const;

	/** Verify that value is enumerated before returning it
	@param output_value - Value from data if application tag is correct
	@return - Wether the application tag matches the requested value
	*/
	bool Get_Enumerated(uint32_t& output_value) const;

	///** Assume value is Date and return it
	//@return - Value from data if application tag is Date or DateTime, wildcard if not
	//*/
	//Date Get_Date() const;

	///** Verify that value is Date or DateTime before returning it
	//@param output_value - Value from data if application tag is correct
	//@return - Wether the application tag matches the requested value
	//*/
	//bool Get_Date(Date& output_value) const;

	///** Assume value is Time and return it
	//@return - Value from data if application tag is Time or DateTime, wildcard if not
	//*/
	//Time Get_Time() const;

	///** Verify that value is Time before returning it
	//@param output_value - Value from data if application tag is correct
	//@return - Wether the application tag matches the requested value
	//*/
	//bool Get_Time(Time& output_value) const;

	///** Assume value is Object Identifier and return it
	//@return - Value from data if application tag is Object Identifier, wildcard if not
	//*/
	//ObjectIdentifier Get_Object_ID() const;

	///** Verify that value is Object Identifier before returning it
	//@param output_value - Value from data if application tag is correct
	//@return - Wether the application tag matches the requested value
	//*/
	//bool Get_Object_ID(ObjectIdentifier& output_value) const;

	///** Assume value is DateTime and return it
	//@return - Value from data if application tag is DateTime, wildcard if not
	//*/
	//DateTime Get_DateTime() const;

	///** Verify that value is DateTime before returning it
	//@param output_value - Value from data if application tag is correct
	//@return - Wether the application tag matches the requested value
	//*/
	//bool Get_DateTime(DateTime& output_value) const;

	///** Assume value is an array and return it
	//@return - Pointer to list if application tag is Array, wildcard if not
	//*/
	//ValueList* Get_Array() const;

	///** Verify that value is an Array before returning it
	//@param output_value - Value from data if application tag is correct
	//@return - Wether the application tag matches the requested value
	//*/
	//bool Get_Array(ValueList* output_value) const;

	///** Assume value is a list and return it
	//@return - Pointer to list if application tag is List, wildcard if not
	//*/
	//ValueList* Get_List() const;
	//
	///** Verify that value is a List before returning it
	//@param output_value - Value from data if application tag is correct
	//@return - Wether the application tag matches the requested value
	//*/
	//bool Get_List(ValueList* output_value) const;


	/** Set the value to NULL
	*/
	void Set_Null();

	/** Set the value to a bool
	@param input_value [in] - Value to set
	*/
	void Set_Boolean(bool input_value);

	/** Set the value to an usigned integer
	@param input_value [in] - Value to set
	*/
	void Set_Unsigned(uint32_t input_value);

	/** Set the value to a signed integer
	@param input_value [in] - Value to set
	*/
	void Set_Signed(int32_t input_value);

	/** Set the value to a float value
	@param input_value [in] - Value to set
	*/
	void Set_Real(float input_value);

	/** Set the value to a double-presicion float value
	@param input_value [in] - Value to set
	*/
	void Set_Double(double input_value);

	/** Set the value to an octet string
	@param input_value [in] - Value to set
	*/
	void Set_Octet_String(OctetString& input_value);

	///** Set the value to a character string
	//@param input_value [in] - Value to set
	//*/
	//void Set_Character_String(CharacterString& input_value);

	///** Set the value to a character string
	//@param input_value [in] - Value to set
	//*/
	//void Set_Character_String(const char* input_value);

	///** Set the value to a bit string
	//@param input_value [in] - Value to set
	//*/
	//void Set_Bit_String(BitString& input_value);

	/** Set the value to an enumeration
	@param input_value [in] - Value to set
	*/
	void Set_Enumerated(uint32_t input_value);

	///** Set the value to a date
	//@param input_value [in] - Value to set
	//*/
	//void Set_Date(const Date& input_value);

	///** Set the value to a date
	//@param year [in] - Year to set
	//@param month [in] - Month to set
	//@param day [in] - Day to set
	//@param weekday [in] - Weekday to set
	//*/
	//void Set_Date(uint16_t year, uint8_t month, uint8_t day, uint8_t weekday);

	///** Set the value to a time
	//@param input_value [in] - Value to set
	//*/
	//void Set_Time(Time& input_value);

	///** Set the value to a time
	//@param hour [in] - Hour to set
	//@param minute [in] - Minute to set
	//@param second [in] - Second to set
	//@param hundredth [in] - Hundredth to set
	//*/
	//void Set_Time(uint8_t hour, uint8_t minute, uint8_t second, uint8_t hundredth);

	///** Set the value to an object identifier
	//@param input_value [in] - Value to set
	//*/
	//void Set_Object_ID(ObjectIdentifier& input_value);

	///** Set the value to an object identifier
	//@param type [in] - Value type of referenced object
	//@param instance [in] - Instance number of referenced object
	//*/
	//void Set_Object_ID(uint16_t type, uint32_t instance);

	///** Set the value to a datetime value
	//@param input_value [in] - Value to set
	//*/
	//void Set_DateTime(DateTime& input_value);

	///** Set the value to a datetime value
	//@param year [in] - Year to set
	//@param month [in] - Month to set
	//@param day [in] - Day to set
	//@param weekday [in] - Weekday to set
	//@param hour [in] - Hour to set
	//@param minute [in] - Minute to set
	//@param second [in] - Second to set
	//@param hundredth [in] - Hundredth to set
	//*/
	//void Set_DateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t weekday, uint8_t hour, uint8_t minute, uint8_t second, uint8_t hundredth);

	///** Set the value to an empty list
	//*/
	//void Set_List();

	///** Set the value to a list
	//@param input_list [in] - List to copy values from
	//*/
	//void Set_List(const ValueList& input_list);

	///** Set the value to an empty array (handled as list)
	//*/
	//void Set_Array();

	///** Set the value to an array (handled as list)
	//@param input_array [in] - Array to copy values from
	//*/
	//void Set_Array(const ValueList& input_array);

	///** Write application data value to apdu
	//@param write_buffer [in] - Write buffer to use for writing
	//@return - False if write failed (for any reason)
	//*/
	//bool Apdu_Encode(ApduWriteBuffer& write_buffer) const;

	///** Write application data value to apdu with context tag
	//@param write_buffer [in] - Write buffer to use for writing
	//@param context_tag [in] - Context tag to encode with
	//@return - False if write failed (for any reason)
	//*/
	//bool Apdu_Encode(ApduWriteBuffer& write_buffer, uint8_t context_tag) const;

	///*** ANY OTHER DATATYPES BELOW THIS POINT ***/

	////**
	//// DATERANGE
	////**

	//// Assume that stored value is DateRange and fetch it
	//DateRange Get_DateRange();

	///** Check if value is DateRange and fetch it
	//@param output_value [out] - Gets filled with stored data if tag is correct
	//@return - True if tag is correct, false if not
	//*/
	//bool Get_DateRange(DateRange& output_value);

	//// Replace existing values with a DateRange
	//void Set_DateRange(const DateRange& input_value);

	//// Replace existing values with a DateRange
	//void Set_DateRange(const Date& from_date, const Date& to_date);

	////**
	//// WEEKANDDAY
	////**

	//// Assume that stored value is WeekAndDay and fetch it
	//WeekAndDay Get_WeekAndDay();

	///** Check if value is WeekAndDay and fetch it
	//@param output_value [out] - Gets filled with stored data if tag is correct
	//@return - True if tag is correct, false if not
	//*/
	//bool Get_WeekAndDay(WeekAndDay& output_value);

	//// Replace existing values with a WeekAndDay
	//void Set_WeekAndDay(const WeekAndDay& input_value);

	//// Replace existing values with a WeekAndDay
	//void Set_WeekAndDay(uint8_t month, uint8_t week_of_month, uint8_t day_of_week);

	////**
	//// CalendarEntry
	////**

	///** Check if value is Date, DateRange or WeekAndDay and output it as CalendarEntry
	//@param output_value [out] - Gets filled with stored data if tag is correct
	//@return - True if tag is correct, false if not
	//*/
	//bool Get_CalendarEntry(CalendarEntry& output_value);

	//// Replace existing values with the value from a calendar entry
	//void Set_CalendarEntry(CalendarEntry& input_value);

	////**
	//// TEMPORARY(?) Void pointer specifically for object list
	////**

	//void Set_Void(void* input_value);

	//// Fetch pointer to any value
	//void* Get_Void() const;

	//// Verify and fetch pointer to any value
	//bool Get_Void(void* output_value) const;

private:

	/*** VALUES ***/

	void new_octet_string(OctetString* pointer, OctetString& input_value);


	ApplicationTag application_tag;

	/** Do not put datatypes greater than 12 bytes directly in the union
	* To Access larger datatypes, use pointers and memory allocation
	* Because of this, the struct is currently just 16 bytes
	*/
	union app_data
	{
		app_data()
		{
			this->clear();
		}

		~app_data()
		{
		}

		void clear()
		{
			memset(this, 0, sizeof(*this));
		}


		bool Boolean;

		uint32_t Unsigned_Int;

		int32_t Signed_Int;

		float Real;

		double Double;

		// TODO: These values
		//struct
		//{
		//	union
		//	{
		//		uint8_t small[4];
		//		BitString* big;
		//	};
		//	size_t size;
		//	uint8_t choice;
		//} Bit_String;

		//CharacterString* Character_String;

		uint32_t Enumerated;

		//struct 
		//{
		//	uint16_t year;		// Years since 0
		//	uint8_t month;		// 1 = Jan, 13 = odd, 14 = even
		//	uint8_t day;		// 1..31,	32 = last in month
		//	uint8_t weekday;	// 1 = Mon
		//	uint8_t hour;		// 0..23
		//	uint8_t minute;		// 0..59
		//	uint8_t second;		// 0..59
		//	uint8_t hundredths;	// 0..99
		//}DateTime;
		//
		//struct
		//{
		//	uint16_t object_type;
		//	uint32_t object_instance;
		//}Object_Id;

		//ValueList* List;

		//void* void_pointer;

		//struct
		//{
		//	uint16_t from_year;
		//	uint8_t from_month;
		//	uint8_t from_day;
		//	uint8_t from_weekday;
		//	uint16_t to_year;
		//	uint8_t to_month;
		//	uint8_t to_day;
		//	uint8_t to_weekday;
		//}DateRange;

		//struct
		//{
		//	uint8_t month;
		//	uint8_t week_of_month;
		//	uint8_t day_of_week;
		//}WeekAndDay;

	}application_value;

	octstring Octet_String;
};
