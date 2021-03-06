#ifndef CRYPTOKISESSIONINFO_H
#define CRYPTOKISESSIONINFO_H

#include <string>

#include "pkcs11.h"

/*!
 *@brief <b>PKCS#11 Session Info</b><br>
 * 
 * This class is a CK_SESSION_INFO wrapper, it
 * holds the original struct protected and
 * provides public functions to return its values.
 *
 * @see CryptokiSession
 * @see CK_SESSION_INFO
 *
 * @author Lucas Pandolfo Perin
 */
class CryptokiSessionInfo
{
	friend class CryptokiSession;
protected:
	CK_SESSION_INFO _info;
public:

	virtual ~CryptokiSessionInfo(){};

	enum CryptokiSessionFlags
	{
		EMPTY = 0,
		RW_SESSION = 2,
		SERIAL_SESSION =4,
		UNKNOWN = 32
	};

	unsigned long slotId();
	unsigned long state();
	CryptokiSessionInfo::CryptokiSessionFlags flags();
	unsigned long deviceError();//TODO(perin) enumerate erros later in device object
	CK_SESSION_INFO getSessionInfo();
};
#endif /*CRYPTOKISESSIONINFO_H*/
