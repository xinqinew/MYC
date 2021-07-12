//AnsiToUtf8.h
#pragma once
//字节集 转16进制
DWORD BytesToHexStr(IN BYTE*nbData, DWORD nbDataSize,OUT char*szpHexBuf);
//ANSI 转 UTF8
DWORD AnsiToUtf8(LPCSTR Ansi,OUT LPSTR szpUtf8Buf);
//unicode 转 ascii
char* UniCodeToAscii(IN WCHAR*szpUnicodeStr,OUT char*szpAsciiStr);
//Uft-8 转 ascii
char* utf8ToAscii(IN char*szpUtf8,OUT char*szpAscii);