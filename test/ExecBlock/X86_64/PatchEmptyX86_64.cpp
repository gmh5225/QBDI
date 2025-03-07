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

#include "ExecBlock/PatchEmpty.h"

#include "X86InstrInfo.h"
#include "llvm/MC/MCInst.h"

QBDI::Patch generateEmptyPatch(QBDI::rword address,
                               const QBDI::LLVMCPUs &llvmcpu) {
  llvm::MCInst inst;

  inst.setOpcode(llvm::X86::NOOP);

  QBDI::Patch p{inst, address, 1, llvmcpu.getCPU(QBDI::CPUMode::DEFAULT)};
  p.finalizeInstsPatch();
  return p;
}
