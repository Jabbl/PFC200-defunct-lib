#pragma once


#define BACNET_VENDOR_ID 1124
#define BACNET_VENDOR_NAME "PowerTech Engineering AS"

// Settings may be used during debugging or testing to enable/disable license checks.
#ifdef WIN32
//#define LICENSING_DISABLE
#define LICENSE_ALLOW_INVALID_HARDWARE_ID
#else
//#define LICENSING_DISABLE
//#define LICENSE_ALLOW_INVALID_HARDWARE_ID
#endif


// Limit the max number of COV subscriptions to a reasonable count because we don't want
// a malicious top-system DDOS-ing us with millions of subscriptions until we're out of memory.
#define MAX_COV_SUBSCRIPTIONS 10000

// Limit how many COV- subscriptions we process each second to a maximum of 1/40th of the max.
// This will let us handle every COV subscription within max 3 seconds (mark, clear and send)
#define MAX_COV_PROCESS_PER_CYCLE MAX_COV_SUBSCRIPTIONS/40

// Limit how many COV notification updates we can send each scan to avoid spamming the network
#define MAX_COV_SUBSCRIPTIONS_PACKETS_PER_CYCLE 10


// Let the backgroundworker spawn its own thread
#define BACKGROUNDWORKER_MODE_ASYNC 1


#define BACNET_NATIVE_OBJECTS_ENABLED (0)



#define INTRINSIC_REPORTING

#define BACAPP_ALL
#define BACFILE
#define BACNET_PROPERTY_LISTS 1

#define BACDL_BIP 1

#define PRINT_ENABLED 1

#define BBMD_ENABLED 1

#define MAX_OBJECT_NAME_SIZE 128			// Minimum 64 characters, ref.: ASHRAE Table K-4. Minimum Character-String Lengths
#define MAX_OBJECT_PARTNAME_SIZE 48
#define MAX_OBJECT_DESC_SIZE 256			// Minimum 255 characters, ref.: ASHRAE Table K-4. Minimum Character-String Lengths
#define MAX_DEVICE_TYPE_STRINGSIZE 65		// Minimum 64 characters, ref.: ASHRAE Table K-4. Minimum Character-String Lengths
#define MAX_STATETEXT_NAME_SIZE 33			// Minimum 32 characters, ref.: ASHRAE Table K-4. Minimum Character-String Lengths
#define MAX_CHARACTERSTRING_OBJECT_SIZE 256	// Character string size


// libxml2 features
#define LIBXML_READER_ENABLED
#define LIBXML_WRITER_ENABLED
#define LIBXML_TREE_ENABLED
#define LIBXML_OUTPUT_ENABLED
