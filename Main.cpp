#if !defined(WIN32) && !defined(_WIN32) && !defined(__WIN32__) && defined(__linux__)
#define LINUX
#endif // !defined(WIN32) && !defined(_WIN32) && !defined(__WIN32__)

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include "SDK/amx/amx.h"
#include "SDK/plugincommon.h"

typedef void(*logprintf_t)(char* format, ...);


logprintf_t logprintf;
extern void *pAMXFunctions;


cell AMX_NATIVE_CALL HelloWorld(AMX* amx, cell* params)
{
	logprintf("");
	return 1;
}

//Converts UNIX timestamp to date.
//PAWN native: native GetUnixDate(unixtime, &year=0, &month=0, &day=0, &hour=0, &minute=0, &second=0);
cell AMX_NATIVE_CALL GetUnixDate(AMX* amx, cell* params)
{
	cell* addr[6] = { NULL, NULL, NULL, NULL, NULL, NULL };

	// Convert UNXI timestamp to tm structure.
	time_t unix_time = params[1];
	struct tm* time = localtime(&unix_time);

	if (time == nullptr)
	{
		logprintf("ERROR: time is null");
		perror("native GetUnixDate()");
		return 1;
	}

	//Get the addresses of variables
	amx_GetAddr(amx, params[2], &addr[0]);
	amx_GetAddr(amx, params[3], &addr[1]);
	amx_GetAddr(amx, params[4], &addr[2]);
	amx_GetAddr(amx, params[5], &addr[3]);
	amx_GetAddr(amx, params[6], &addr[4]);
	amx_GetAddr(amx, params[7], &addr[5]);
	
	// Set the time
	if(*addr[0] != nullptr){
		*addr[0] = time->tm_year + 1900;	// Year
	}
	if(*addr[1] != nullptr){
		*addr[1] = time->tm_mon + 1;		// Month
	}
	if(*addr[2] != nullptr){
		*addr[2] = time->tm_mday;			// Day
	}
	if(*addr[3] != nullptr){
		*addr[3] = time->tm_hour;			// Hours
	}
	if(*addr[4] != nullptr){
		*addr[4] = time->tm_min;			// Minutes
	}
	if(*addr[5] != nullptr){
		*addr[5] = time->tm_sec;			// Seconds
	}
	
	return 1;
}

//Converts UNIX timestamp to foramtted string.
//PAWN native: native FormatUnixDate(output[], len, const format[], unixtime);
cell AMX_NATIVE_CALL FormatUnixDate(AMX* amx, cell* params)
{
	cell* addr[2] = {
		NULL,	// 0 - output
		NULL	// 1 - format
	};
	char *buf = new char[params[2]];
	int len = NULL;

	//Get the addresses
	amx_GetAddr(amx, params[1], &addr[0]);
	amx_GetAddr(amx, params[3], &addr[1]);
	amx_StrLen(addr[1], &len);
	len++;

	// Convert UNXI timestamp to tm structure.
	time_t unix_time = params[4];
	struct tm* time = localtime(&unix_time);

	/*if (localtime_s(&time, &unix_time) == NULL)
	{
		logprintf("ERROR: time is null");
		perror("native FormatUnixDate()");
		return 1;
	}*/

	// Get format string
	char* format = new char[len];
	amx_GetString(format, addr[1], 0, len);

	// Convert struct tm to string
	strftime(buf, params[2], format, time);

	// Set the string
	amx_SetString(addr[0], buf, 0, 0, params[2]);

	delete[] buf;
	delete[] format;

	return 1;
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];

	logprintf(" * SAMP Additionals plug-in -- by tmp64.");
	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	logprintf(" * SAMP Additionals plug-in was unloaded.");
}

AMX_NATIVE_INFO PluginNatives[] =
{
	{ "GetUnixDate", GetUnixDate },
	{ "FormatUnixDate", FormatUnixDate },
	{ 0, 0 }
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
	return amx_Register(amx, PluginNatives, -1);
}


PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
	return AMX_ERR_NONE;
}

//This function demonstrates: how to get a string (and its length) from PAWN.
//PAWN native: native PrintPawnString(const str[]);
/*cell AMX_NATIVE_CALL PrintPawnString(AMX* amx, cell* params)
{
	int
		len = NULL,
		ret = NULL;

	cell *addr = NULL;

	//Get the address of our string param (str) and then get its length
	amx_GetAddr(amx, params[1], &addr);
	amx_StrLen(addr, &len);

	//if the length of input isnt 0
	if (len)
	{
		//We increase len because we want to make room for the terminating null char when we allocate memory.
		//Also because GetString's size parameter counts the null chracter, we have to specify the length
		//of the string + 1; otherwise our string will be truncated to make room for the null char (we'd lose 1 character).
		len++;

		//Allocate memory to hold our string we're passing (str) and then "get" the string using our allocated memory to store it.
		char* text = new char[len];
		amx_GetString(text, addr, 0, len);

		//Use logprintf to print out string (text). We dont use std::cout because it doesnt write to the server log (only the console).
		logprintf(text);

		//Deallocate our memory...
		delete[] text;
	}
	return 1;
}*/
