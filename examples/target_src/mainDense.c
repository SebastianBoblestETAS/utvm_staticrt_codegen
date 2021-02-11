#include <stdint.h>
#include <stdio.h>

#include "tvm/runtime/c_runtime_api.h"

#ifdef _DEBUG
#include <stdio.h>
#define DBGPRINTF(format, ...) printf(format, ##__VA_ARGS__)
#else
#define DBGPRINTF(format, ...)
#endif

#include <tvm/runtime/crt/packed_func.h>
TVMModuleHandle TVMArgs_AsModuleHandle(const TVMArgs* args, size_t index);

void TVMWrap_Init();
void* TVMWrap_GetInputPtr(int index);
void TVMWrap_Run();
void* TVMWrap_GetOutputPtr(int index);

void TVMPlatformAbort(tvm_crt_error_t e) { exit(1); }

int main() {
  TVMWrap_Init();

  float* input = (float*)TVMWrap_GetInputPtr(0);
  input[0] = 0.4f;
  input[1] = 0.5f;

  TVMWrap_Run();

  const int numOutputs = 2;

  float* result = (float*)TVMWrap_GetOutputPtr(0);

  for (int i = 0; i < numOutputs; ++i) {
    printf("out[%d]=%f\n", i, result[i]);
  }

}
