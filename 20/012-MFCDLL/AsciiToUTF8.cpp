//AnsiToUtf8.cpp
#include "stdafx.h"
#include "AsciiToUTF8.h"
#include <Windows.h>

/*
//�ֽڼ� ת16����
DWORD BytesToHexStr(IN BYTE*nbData, DWORD nbDataSize,OUT char*szpHexBuf);
//ANSI ת UTF8
DWORD AnsiToUtf8(LPCSTR Ansi,OUT LPSTR szpUtf8Buf);
//unicode ת ascii
char* UniCodeToAscii(IN WCHAR*szpUnicodeStr,OUT char*szpAsciiStr);
//Uft-8 ת ascii
char* utf8ToAscii(IN char*szpUtf8,OUT char*szpAscii);

*/

DWORD AnsiToUtf8(LPCSTR Ansi,OUT LPSTR szpUtf8Buf)
{
	int WLength = MultiByteToWideChar(CP_ACP, 0, Ansi, -1, NULL, 0);
	LPWSTR pszW = (LPWSTR) _alloca((WLength+1) * sizeof(WCHAR));
	//Ansi�ַ���תUnicode�ַ���
	MultiByteToWideChar(CP_ACP, 0, Ansi, -1, pszW, WLength);

	//����UTF8ת������Ҫ�ռ��С
	int ALength = WideCharToMultiByte(CP_UTF8, 0, pszW, -1, NULL, 0, NULL, NULL);
	//LPSTR pszA = (LPSTR)_alloca( ALength + 1);
	WideCharToMultiByte(CP_UTF8, 0, pszW, -1, szpUtf8Buf, ALength, NULL, NULL);  
	szpUtf8Buf[ALength]=0;
	szpUtf8Buf[ALength+1]=0;
	//pszA[ALength] = 0;

	return ALength;//����UTF8�ַ�������
}

char* UniCodeToAscii(IN WCHAR*szpUnicodeStr,OUT char*szpAsciiStr)
{
	//Ԥ��-�������ж��ֽڵĳ���
	//CP_OEMCP
	int ansiiLen =WideCharToMultiByte(CP_ACP,0,szpUnicodeStr,-1,nullptr,0,nullptr,nullptr);
	//��ָ�򻺳�����ָ����������ڴ�
	//��szpUnicodeStr���ŵ�Unicode�����ִ� ת��ASCII��ŵ� szpAsciiStr������
	//CP_OEMCP
	WideCharToMultiByte(CP_ACP,0,szpUnicodeStr,-1,szpAsciiStr,ansiiLen,nullptr,nullptr);
	return szpAsciiStr;
}


WCHAR* utf8ToUnicode(IN char*szpUtf8,OUT WCHAR*szpUniCode)
{
	//Ԥ��_�������п��ֽڵĳ���
	//CP_UTF8 963ҳ��
	int unicodeLen = MultiByteToWideChar(CP_UTF8,0,szpUtf8,-1,nullptr,0);

	//��ָ�򻺳�����ָ����������ڴ�
	WCHAR *pUnicode = (wchar_t*)malloc(sizeof(wchar_t)*unicodeLen);
	//��ʼ�򻺳���ת���ֽ�
	//CP_UTF8 963ҳ�� Ҳ����
	MultiByteToWideChar(CP_UTF8,0,szpUtf8,-1,pUnicode,unicodeLen);
	wcscpy_s(szpUniCode,unicodeLen,pUnicode);
	free(pUnicode);
	return szpUniCode;
}

//ע��˺���û��⻺������С
char* utf8ToAscii(IN char*szpUtf8,OUT char*szpAscii)
{
	int iSizeUtf8 = MultiByteToWideChar(CP_UTF8,0,szpUtf8,-1,nullptr,0);
	WCHAR*putf8Buf =(WCHAR*)malloc(sizeof(WCHAR)*iSizeUtf8);
	utf8ToUnicode(szpUtf8,putf8Buf);
	UniCodeToAscii(putf8Buf,szpAscii);
	return szpAscii;
}
BOOL CharToHex(OUT char*szpBufHex,BYTE c)
{
	BYTE bLow =0;
	BYTE bHigh = 0;
	bLow = c%16;//ȡ��λ0..15
	bHigh = c/16;//ȡ��λ0..15
	if (bHigh>9)
	{
		szpBufHex[0]='A'+bHigh-10;//'B'
	}
	else//0..9
	{
		szpBufHex[0]='0'+bHigh;//'0'+2='2'
	}
	if (bLow>9)//a,b,c,e,f
	{
		szpBufHex[1]='A'+bLow-10;//'B'

	} 
	else//0..9
	{
		szpBufHex[1]='0'+bLow;//'0'+2='2'
	}
	szpBufHex[2]=0;//0
	return TRUE;
}

DWORD BytesToHexStr(IN BYTE*nbData, DWORD nbDataSize,OUT char*szpHexBuf)
{
	//1 //01
	for (DWORD i=0;i< nbDataSize;i++)
	{
		//����ٶ�
		CharToHex(&szpHexBuf[i*2],nbData[i]);
	}
	return TRUE;
}