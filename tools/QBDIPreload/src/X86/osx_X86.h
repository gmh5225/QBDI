/*
 * This file is part of QBDI.
 *
 * Copyright 2017 - 2021 Quarkslab
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef QBDIPRELOAD_X86_H
#define QBDIPRELOAD_X86_H

#include <QBDI.h>

#include <mach/thread_status.h>

static const uint8_t BRK_INS = 0xCC;

#define MACH_HEADER mach_header
#define MACH_MAGIC MH_MAGIC
#define MACH_SEG segment_command
#define MACH_SEG_CMD LC_SEGMENT
#define THREAD_STATE x86_thread_state32_t
#define THREAD_STATE_COUNT x86_THREAD_STATE32_COUNT
#define THREAD_STATE_FP x86_float_state32_t
#define THREAD_STATE_FP_COUNT x86_FLOAT_STATE32_COUNT
#define THREAD_STATE_FP_ID x86_FLOAT_STATE32
#define THREAD_STATE_ID x86_THREAD_STATE32

void qbdipreload_threadCtxToGPRState(const void *gprCtx, GPRState *gprState);
void qbdipreload_floatCtxToFPRState(const void *fprCtx, FPRState *fprState);

static inline rword getPC(THREAD_STATE *state) { return state->__rip; }

static inline void setPC(THREAD_STATE *state, rword address) {
  state->__eip = address;
}

static inline void prepareStack(void *newStack, size_t sizeStack,
                                THREAD_STATE *state) {
  state->__ebp = (rword)newStack + sizeStack - 8;
  state->__esp = state->__ebp;
}

static inline void fixSignalPC(THREAD_STATE *state) { state->__eip -= 1; }

#endif // QBDIPRELOAD_X86_H
