/* AUTOGENERATED FILE. DO NOT EDIT. */
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "unity.h"
#include "cmock.h"
#include "Mock_rtime.h"

static const char* CMockString_rtime_get = "rtime_get";

typedef struct _CMOCK_rtime_get_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  Time* ReturnVal;
  int CallOrder;

} CMOCK_rtime_get_CALL_INSTANCE;

static struct Mock_rtimeInstance
{
  int rtime_get_IgnoreBool;
  Time* rtime_get_FinalReturn;
  CMOCK_rtime_get_CALLBACK rtime_get_CallbackFunctionPointer;
  int rtime_get_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE rtime_get_CallInstance;
} Mock;

extern jmp_buf AbortFrame;
extern int GlobalExpectCount;
extern int GlobalVerifyOrder;

void Mock_rtime_Verify(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  if (Mock.rtime_get_IgnoreBool)
    Mock.rtime_get_CallInstance = CMOCK_GUTS_NONE;
  UNITY_SET_DETAIL(CMockString_rtime_get);
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.rtime_get_CallInstance, cmock_line, CMockStringCalledLess);
  if (Mock.rtime_get_CallbackFunctionPointer != NULL)
    Mock.rtime_get_CallInstance = CMOCK_GUTS_NONE;
}

void Mock_rtime_Init(void)
{
  Mock_rtime_Destroy();
}

void Mock_rtime_Destroy(void)
{
  CMock_Guts_MemFreeAll();
  memset(&Mock, 0, sizeof(Mock));
  Mock.rtime_get_CallbackFunctionPointer = NULL;
  Mock.rtime_get_CallbackCalls = 0;
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
}

Time* rtime_get(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_rtime_get_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_rtime_get);
  cmock_call_instance = (CMOCK_rtime_get_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.rtime_get_CallInstance);
  Mock.rtime_get_CallInstance = CMock_Guts_MemNext(Mock.rtime_get_CallInstance);
  if (Mock.rtime_get_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    if (cmock_call_instance == NULL)
      return Mock.rtime_get_FinalReturn;
    Mock.rtime_get_FinalReturn = cmock_call_instance->ReturnVal;
    return cmock_call_instance->ReturnVal;
  }
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  if (cmock_call_instance->CallOrder > ++GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledEarly);
  if (cmock_call_instance->CallOrder < GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLate);
  if (Mock.rtime_get_CallbackFunctionPointer != NULL)
  {
    cmock_call_instance->ReturnVal = Mock.rtime_get_CallbackFunctionPointer(Mock.rtime_get_CallbackCalls++);
  }
  UNITY_CLR_DETAILS();
  return cmock_call_instance->ReturnVal;
}

void rtime_get_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, Time* cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_rtime_get_CALL_INSTANCE));
  CMOCK_rtime_get_CALL_INSTANCE* cmock_call_instance = (CMOCK_rtime_get_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.rtime_get_CallInstance = CMock_Guts_MemChain(Mock.rtime_get_CallInstance, cmock_guts_index);
  Mock.rtime_get_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->ReturnVal = cmock_to_return;
  Mock.rtime_get_IgnoreBool = (int)1;
}

void rtime_get_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, Time* cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_rtime_get_CALL_INSTANCE));
  CMOCK_rtime_get_CALL_INSTANCE* cmock_call_instance = (CMOCK_rtime_get_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.rtime_get_CallInstance = CMock_Guts_MemChain(Mock.rtime_get_CallInstance, cmock_guts_index);
  Mock.rtime_get_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->ReturnVal = cmock_to_return;
  UNITY_CLR_DETAILS();
}

void rtime_get_StubWithCallback(CMOCK_rtime_get_CALLBACK Callback)
{
  Mock.rtime_get_IgnoreBool = (int)0;
  Mock.rtime_get_CallbackFunctionPointer = Callback;
}

