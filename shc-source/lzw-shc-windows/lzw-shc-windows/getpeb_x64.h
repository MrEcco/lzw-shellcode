#ifndef _GETPEB_X64_H_
#define _GETPEB_X64_H_

#include <winnt.h>
#include <winternl.h>

#ifdef __cplusplus
extern "C" {
#endif
	__forceinline PEB *getPEB();
	void getEIP();
#ifdef __cplusplus
}
#endif
#endif /* _GETPEB_X64_H_ */