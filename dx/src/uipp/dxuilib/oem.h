#ifndef __OEM_H_
#define __OEM_H_

#include <dxconfig.h>



char *ScrambleAndEncrypt(const char *src, const char *hash, char *cryptbuf);
char *ScrambleString(const char *str, const char *hash);


#endif /* __OEM_H_ */
