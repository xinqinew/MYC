//AnsiToUtf8.h
#pragma once
//�ֽڼ� ת16����
DWORD BytesToHexStr(IN BYTE*nbData, DWORD nbDataSize,OUT char*szpHexBuf);
//ANSI ת UTF8
DWORD AnsiToUtf8(LPCSTR Ansi,OUT LPSTR szpUtf8Buf);
//unicode ת ascii
char* UniCodeToAscii(IN WCHAR*szpUnicodeStr,OUT char*szpAsciiStr);
//Uft-8 ת ascii
char* utf8ToAscii(IN char*szpUtf8,OUT char*szpAscii);