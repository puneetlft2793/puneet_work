#ifndef LINUXDEFINES_H
#define LINUXDEFINES_H

#define INVALID_SOCKET	(SOCKET) (~0)
#define SOCKET_ERROR	(-1)
#define WORD		unsigned short
#define BYTE		unsigned char
#define DWORD 		unsigned long
#define SOCKET		unsigned int 
#define errno_t		int
#define DWORD_PTR	unsigned long
#define MAKEWORD(a, b)	((WORD)(((BYTE)(((DWORD_PTR)(a)) & 0xff)) | ((WORD)((BYTE)(((DWORD_PTR)(b)) & 0xff))) << 8 ))

#endif 
