#include <gtest/gtest.h>
#include "mock/PKCS11CallbackMocker.h"
#include "P11.h"
#include "P11Exception.h"

TEST(P11_Test, Finalize_OK)
{
	{P11 p11module("tests/pkcs11mocked.so");}
	EXPECT_TRUE(true);
}

TEST(P11_Test, Initialize_OK)
{
	P11 p11module("tests/pkcs11mocked.so");
	
	CK_LAMBDA_FUNCTION_LIST* pkcs11 = getMockerReference("tests/pkcs11mocked.so");
	
	bool called = false;
	pkcs11->C_Initialize = [&](void* ptr) -> CK_RV {
		called = true;
		return CKR_OK;
	};	

	EXPECT_NO_THROW(p11module.initialize());
	EXPECT_TRUE(called);
}

TEST(P11_Test, Initialize_Failed_causes_exception)
{
	P11 p11module("tests/pkcs11mocked.so");
	
	CK_LAMBDA_FUNCTION_LIST* pkcs11 = getMockerReference("tests/pkcs11mocked.so");
	
	pkcs11->C_Initialize = [&](void* ptr) {
		return CKR_GENERAL_ERROR;
	};	

	try {
		p11module.initialize();
		EXPECT_TRUE(false);
	} catch (P11Exception& e) {
		EXPECT_EQ(e.getErrorCode(), CKR_GENERAL_ERROR);
	}
}

TEST(P11_Test, GetInfo_OK)
{

	P11 p11module("tests/pkcs11mocked.so");
	
	CryptokiInfo info;
	info = p11module.getInfo();

	EXPECT_EQ(info.cryptokiVersion(), "6.66");
	EXPECT_EQ(info.cryptokiMajorVersion(), 6);
	EXPECT_EQ(info.cryptokiMinorVersion(), 66);
	EXPECT_EQ(info.flags(), CryptokiInfo::EMPTY);
}

TEST(P11_Test, GetInfo_Failed_causes_exception)
{

	P11 p11module("tests/pkcs11mocked.so");
	
	CK_LAMBDA_FUNCTION_LIST* pkcs11 = getMockerReference("tests/pkcs11mocked.so");
	
	pkcs11->C_GetInfo = [&](void* ptr) {
		return CKR_GENERAL_ERROR;
	};	

	try {
		p11module.getInfo();
		EXPECT_TRUE(false);
	} catch (P11Exception& e) {
		EXPECT_EQ(e.getErrorCode(), CKR_GENERAL_ERROR);
	}
}
