// Copyright 2016, VIXL authors
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//   * Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//   * Neither the name of ARM Limited nor the names of its contributors may be
//     used to endorse or promote products derived from this software without
//     specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// -----------------------------------------------------------------------------
// This file is auto generated from the
// test/a32/config/template-simulator-a32.cc.in template file using
// tools/generate_tests.py.
//
// PLEASE DO NOT EDIT.
// -----------------------------------------------------------------------------

#include "test-runner.h"

#include "test-utils.h"
#include "test-utils-a32.h"

#include "a32/assembler-a32.h"
#include "a32/macro-assembler-a32.h"
#include "a32/disasm-a32.h"

#define __ masm.
#define BUF_SIZE (4096)

#ifdef VIXL_INCLUDE_SIMULATOR
// Run tests with the simulator.

#define SETUP() MacroAssembler masm(BUF_SIZE)

#define START() masm.GetBuffer().Reset()

#define END() \
  __ Hlt(0);  \
  __ FinalizeCode();

// TODO: Run the tests in the simulator.
#define RUN()

#define TEARDOWN()

#else  // ifdef VIXL_INCLUDE_SIMULATOR.

#define SETUP() MacroAssembler masm(BUF_SIZE);

#define START()             \
  masm.GetBuffer().Reset(); \
  __ Push(r4);              \
  __ Push(r5);              \
  __ Push(r6);              \
  __ Push(r7);              \
  __ Push(r8);              \
  __ Push(r9);              \
  __ Push(r10);             \
  __ Push(r11);             \
  __ Push(r12);             \
  __ Push(lr)

#define END()  \
  __ Pop(lr);  \
  __ Pop(r12); \
  __ Pop(r11); \
  __ Pop(r10); \
  __ Pop(r9);  \
  __ Pop(r8);  \
  __ Pop(r7);  \
  __ Pop(r6);  \
  __ Pop(r5);  \
  __ Pop(r4);  \
  __ Bx(lr);   \
  __ FinalizeCode();

// Copy the generated code into a memory area garanteed to be executable before
// executing it.
#define RUN()                                                  \
  {                                                            \
    ExecutableMemory code(masm.GetBuffer().GetCursorOffset()); \
    code.Write(masm.GetBuffer().GetOffsetAddress<byte*>(0),    \
               masm.GetBuffer().GetCursorOffset());            \
    int pcs_offset = masm.IsT32() ? 1 : 0;                     \
    code.Execute(pcs_offset);                                  \
  }

#define TEARDOWN()

#endif  // ifdef VIXL_INCLUDE_SIMULATOR

namespace vixl {
namespace aarch32 {

// List of instruction encodings:
#define FOREACH_INSTRUCTION(M) \
  M(Cmn)                       \
  M(Cmp)                       \
  M(Mov)                       \
  M(Movs)                      \
  M(Mvn)                       \
  M(Mvns)                      \
  M(Teq)                       \
  M(Tst)

// Values to be passed to the assembler to produce the instruction under test.
struct Operands {
  Condition cond;
  Register rd;
  uint32_t immediate;
};

// Input data to feed to the instruction.
struct Inputs {
  uint32_t apsr;
  uint32_t rd;
};

// This structure contains all input data needed to test one specific encoding.
// It used to generate a loop over an instruction.
struct TestLoopData {
  // The `operands` fields represents the values to pass to the assembler to
  // produce the instruction.
  Operands operands;
  // Description of the operands, used for error reporting.
  const char* operands_description;
  // Unique identifier, used for generating traces.
  const char* identifier;
  // Array of values to be fed to the instruction.
  size_t input_size;
  const Inputs* inputs;
};

static const Inputs kCondition[] = {{NFlag, 0xabababab},
                                    {ZFlag, 0xabababab},
                                    {CFlag, 0xabababab},
                                    {VFlag, 0xabababab},
                                    {NZFlag, 0xabababab},
                                    {NCFlag, 0xabababab},
                                    {NVFlag, 0xabababab},
                                    {ZCFlag, 0xabababab},
                                    {ZVFlag, 0xabababab},
                                    {CVFlag, 0xabababab},
                                    {NZCFlag, 0xabababab},
                                    {NZVFlag, 0xabababab},
                                    {NCVFlag, 0xabababab},
                                    {ZCVFlag, 0xabababab},
                                    {NZCVFlag, 0xabababab}};

static const Inputs kModifiedImmediate[] = {{NoFlag, 0x00000000},
                                            {NoFlag, 0x00000001},
                                            {NoFlag, 0x00000002},
                                            {NoFlag, 0x00000020},
                                            {NoFlag, 0x0000007d},
                                            {NoFlag, 0x0000007e},
                                            {NoFlag, 0x0000007f},
                                            {NoFlag, 0x00007ffd},
                                            {NoFlag, 0x00007ffe},
                                            {NoFlag, 0x00007fff},
                                            {NoFlag, 0x33333333},
                                            {NoFlag, 0x55555555},
                                            {NoFlag, 0x7ffffffd},
                                            {NoFlag, 0x7ffffffe},
                                            {NoFlag, 0x7fffffff},
                                            {NoFlag, 0x80000000},
                                            {NoFlag, 0x80000001},
                                            {NoFlag, 0xaaaaaaaa},
                                            {NoFlag, 0xcccccccc},
                                            {NoFlag, 0xffff8000},
                                            {NoFlag, 0xffff8001},
                                            {NoFlag, 0xffff8002},
                                            {NoFlag, 0xffff8003},
                                            {NoFlag, 0xffffff80},
                                            {NoFlag, 0xffffff81},
                                            {NoFlag, 0xffffff82},
                                            {NoFlag, 0xffffff83},
                                            {NoFlag, 0xffffffe0},
                                            {NoFlag, 0xfffffffd},
                                            {NoFlag, 0xfffffffe},
                                            {NoFlag, 0xffffffff}};

// A loop will be generated for each element of this array.
static const TestLoopData kTests[] = {{{eq, r0, 0xabababab},
                                       "eq r0 0xabababab",
                                       "Condition_eq_r0_0xabababab",
                                       ARRAY_SIZE(kCondition),
                                       kCondition},
                                      {{ne, r0, 0xabababab},
                                       "ne r0 0xabababab",
                                       "Condition_ne_r0_0xabababab",
                                       ARRAY_SIZE(kCondition),
                                       kCondition},
                                      {{cs, r0, 0xabababab},
                                       "cs r0 0xabababab",
                                       "Condition_cs_r0_0xabababab",
                                       ARRAY_SIZE(kCondition),
                                       kCondition},
                                      {{cc, r0, 0xabababab},
                                       "cc r0 0xabababab",
                                       "Condition_cc_r0_0xabababab",
                                       ARRAY_SIZE(kCondition),
                                       kCondition},
                                      {{mi, r0, 0xabababab},
                                       "mi r0 0xabababab",
                                       "Condition_mi_r0_0xabababab",
                                       ARRAY_SIZE(kCondition),
                                       kCondition},
                                      {{pl, r0, 0xabababab},
                                       "pl r0 0xabababab",
                                       "Condition_pl_r0_0xabababab",
                                       ARRAY_SIZE(kCondition),
                                       kCondition},
                                      {{vs, r0, 0xabababab},
                                       "vs r0 0xabababab",
                                       "Condition_vs_r0_0xabababab",
                                       ARRAY_SIZE(kCondition),
                                       kCondition},
                                      {{vc, r0, 0xabababab},
                                       "vc r0 0xabababab",
                                       "Condition_vc_r0_0xabababab",
                                       ARRAY_SIZE(kCondition),
                                       kCondition},
                                      {{hi, r0, 0xabababab},
                                       "hi r0 0xabababab",
                                       "Condition_hi_r0_0xabababab",
                                       ARRAY_SIZE(kCondition),
                                       kCondition},
                                      {{ls, r0, 0xabababab},
                                       "ls r0 0xabababab",
                                       "Condition_ls_r0_0xabababab",
                                       ARRAY_SIZE(kCondition),
                                       kCondition},
                                      {{ge, r0, 0xabababab},
                                       "ge r0 0xabababab",
                                       "Condition_ge_r0_0xabababab",
                                       ARRAY_SIZE(kCondition),
                                       kCondition},
                                      {{lt, r0, 0xabababab},
                                       "lt r0 0xabababab",
                                       "Condition_lt_r0_0xabababab",
                                       ARRAY_SIZE(kCondition),
                                       kCondition},
                                      {{gt, r0, 0xabababab},
                                       "gt r0 0xabababab",
                                       "Condition_gt_r0_0xabababab",
                                       ARRAY_SIZE(kCondition),
                                       kCondition},
                                      {{le, r0, 0xabababab},
                                       "le r0 0xabababab",
                                       "Condition_le_r0_0xabababab",
                                       ARRAY_SIZE(kCondition),
                                       kCondition},
                                      {{al, r0, 0xabababab},
                                       "al r0 0xabababab",
                                       "Condition_al_r0_0xabababab",
                                       ARRAY_SIZE(kCondition),
                                       kCondition},
                                      {{al, r0, 0x000001fe},
                                       "al r0 0x000001fe",
                                       "ModifiedImmediate_al_r0_0x000001fe",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x000003fc},
                                       "al r0 0x000003fc",
                                       "ModifiedImmediate_al_r0_0x000003fc",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x000007f8},
                                       "al r0 0x000007f8",
                                       "ModifiedImmediate_al_r0_0x000007f8",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x00000ff0},
                                       "al r0 0x00000ff0",
                                       "ModifiedImmediate_al_r0_0x00000ff0",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x00001fe0},
                                       "al r0 0x00001fe0",
                                       "ModifiedImmediate_al_r0_0x00001fe0",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x00003fc0},
                                       "al r0 0x00003fc0",
                                       "ModifiedImmediate_al_r0_0x00003fc0",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x00007f80},
                                       "al r0 0x00007f80",
                                       "ModifiedImmediate_al_r0_0x00007f80",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x0000ff00},
                                       "al r0 0x0000ff00",
                                       "ModifiedImmediate_al_r0_0x0000ff00",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x0001fe00},
                                       "al r0 0x0001fe00",
                                       "ModifiedImmediate_al_r0_0x0001fe00",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x0003fc00},
                                       "al r0 0x0003fc00",
                                       "ModifiedImmediate_al_r0_0x0003fc00",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x0007f800},
                                       "al r0 0x0007f800",
                                       "ModifiedImmediate_al_r0_0x0007f800",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x000ff000},
                                       "al r0 0x000ff000",
                                       "ModifiedImmediate_al_r0_0x000ff000",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x001fe000},
                                       "al r0 0x001fe000",
                                       "ModifiedImmediate_al_r0_0x001fe000",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x003fc000},
                                       "al r0 0x003fc000",
                                       "ModifiedImmediate_al_r0_0x003fc000",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x007f8000},
                                       "al r0 0x007f8000",
                                       "ModifiedImmediate_al_r0_0x007f8000",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x00ff0000},
                                       "al r0 0x00ff0000",
                                       "ModifiedImmediate_al_r0_0x00ff0000",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x01fe0000},
                                       "al r0 0x01fe0000",
                                       "ModifiedImmediate_al_r0_0x01fe0000",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x03fc0000},
                                       "al r0 0x03fc0000",
                                       "ModifiedImmediate_al_r0_0x03fc0000",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x07f80000},
                                       "al r0 0x07f80000",
                                       "ModifiedImmediate_al_r0_0x07f80000",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x0ff00000},
                                       "al r0 0x0ff00000",
                                       "ModifiedImmediate_al_r0_0x0ff00000",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x1fe00000},
                                       "al r0 0x1fe00000",
                                       "ModifiedImmediate_al_r0_0x1fe00000",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x3fc00000},
                                       "al r0 0x3fc00000",
                                       "ModifiedImmediate_al_r0_0x3fc00000",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x7f800000},
                                       "al r0 0x7f800000",
                                       "ModifiedImmediate_al_r0_0x7f800000",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0xff000000},
                                       "al r0 0xff000000",
                                       "ModifiedImmediate_al_r0_0xff000000",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x000000ff},
                                       "al r0 0x000000ff",
                                       "ModifiedImmediate_al_r0_0x000000ff",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x00ff00ff},
                                       "al r0 0x00ff00ff",
                                       "ModifiedImmediate_al_r0_0x00ff00ff",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0xff00ff00},
                                       "al r0 0xff00ff00",
                                       "ModifiedImmediate_al_r0_0xff00ff00",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0xffffffff},
                                       "al r0 0xffffffff",
                                       "ModifiedImmediate_al_r0_0xffffffff",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x00000156},
                                       "al r0 0x00000156",
                                       "ModifiedImmediate_al_r0_0x00000156",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x000002ac},
                                       "al r0 0x000002ac",
                                       "ModifiedImmediate_al_r0_0x000002ac",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x00000558},
                                       "al r0 0x00000558",
                                       "ModifiedImmediate_al_r0_0x00000558",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x00000ab0},
                                       "al r0 0x00000ab0",
                                       "ModifiedImmediate_al_r0_0x00000ab0",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x00001560},
                                       "al r0 0x00001560",
                                       "ModifiedImmediate_al_r0_0x00001560",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x00002ac0},
                                       "al r0 0x00002ac0",
                                       "ModifiedImmediate_al_r0_0x00002ac0",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x00005580},
                                       "al r0 0x00005580",
                                       "ModifiedImmediate_al_r0_0x00005580",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x0000ab00},
                                       "al r0 0x0000ab00",
                                       "ModifiedImmediate_al_r0_0x0000ab00",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x00015600},
                                       "al r0 0x00015600",
                                       "ModifiedImmediate_al_r0_0x00015600",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x0002ac00},
                                       "al r0 0x0002ac00",
                                       "ModifiedImmediate_al_r0_0x0002ac00",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x00055800},
                                       "al r0 0x00055800",
                                       "ModifiedImmediate_al_r0_0x00055800",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x000ab000},
                                       "al r0 0x000ab000",
                                       "ModifiedImmediate_al_r0_0x000ab000",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x00156000},
                                       "al r0 0x00156000",
                                       "ModifiedImmediate_al_r0_0x00156000",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x002ac000},
                                       "al r0 0x002ac000",
                                       "ModifiedImmediate_al_r0_0x002ac000",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x00558000},
                                       "al r0 0x00558000",
                                       "ModifiedImmediate_al_r0_0x00558000",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x00ab0000},
                                       "al r0 0x00ab0000",
                                       "ModifiedImmediate_al_r0_0x00ab0000",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x01560000},
                                       "al r0 0x01560000",
                                       "ModifiedImmediate_al_r0_0x01560000",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x02ac0000},
                                       "al r0 0x02ac0000",
                                       "ModifiedImmediate_al_r0_0x02ac0000",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x05580000},
                                       "al r0 0x05580000",
                                       "ModifiedImmediate_al_r0_0x05580000",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x0ab00000},
                                       "al r0 0x0ab00000",
                                       "ModifiedImmediate_al_r0_0x0ab00000",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x15600000},
                                       "al r0 0x15600000",
                                       "ModifiedImmediate_al_r0_0x15600000",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x2ac00000},
                                       "al r0 0x2ac00000",
                                       "ModifiedImmediate_al_r0_0x2ac00000",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x55800000},
                                       "al r0 0x55800000",
                                       "ModifiedImmediate_al_r0_0x55800000",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0xab000000},
                                       "al r0 0xab000000",
                                       "ModifiedImmediate_al_r0_0xab000000",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x000000ab},
                                       "al r0 0x000000ab",
                                       "ModifiedImmediate_al_r0_0x000000ab",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0x00ab00ab},
                                       "al r0 0x00ab00ab",
                                       "ModifiedImmediate_al_r0_0x00ab00ab",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0xab00ab00},
                                       "al r0 0xab00ab00",
                                       "ModifiedImmediate_al_r0_0xab00ab00",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate},
                                      {{al, r0, 0xabababab},
                                       "al r0 0xabababab",
                                       "ModifiedImmediate_al_r0_0xabababab",
                                       ARRAY_SIZE(kModifiedImmediate),
                                       kModifiedImmediate}};

// We record all inputs to the instructions as outputs. This way, we also check
// that what shouldn't change didn't change.
struct TestResult {
  size_t output_size;
  const Inputs* outputs;
};

// These headers each contain an array of `TestResult` with the reference output
// values. The reference arrays are names `kReference{mnemonic}`.
#include "a32/traces/simulator-cond-rd-operand-const-t32-cmn.h"
#include "a32/traces/simulator-cond-rd-operand-const-t32-cmp.h"
#include "a32/traces/simulator-cond-rd-operand-const-t32-mov.h"
#include "a32/traces/simulator-cond-rd-operand-const-t32-movs.h"
#include "a32/traces/simulator-cond-rd-operand-const-t32-mvn.h"
#include "a32/traces/simulator-cond-rd-operand-const-t32-mvns.h"
#include "a32/traces/simulator-cond-rd-operand-const-t32-teq.h"
#include "a32/traces/simulator-cond-rd-operand-const-t32-tst.h"

// The maximum number of errors to report in detail for each test.
static const unsigned kErrorReportLimit = 8;

typedef void (MacroAssembler::*Fn)(Condition cond, Register rd,
                                   const Operand& op);

static void TestHelper(Fn instruction, const char* mnemonic,
                       const TestResult reference[]) {
  SETUP();
  masm.SetT32(true);
  START();

  // Data to compare to `reference`.
  TestResult* results[ARRAY_SIZE(kTests)];

  // Test cases for memory bound instructions may allocate a buffer and save its
  // address in this array.
  byte* scratch_memory_buffers[ARRAY_SIZE(kTests)];

  // Generate a loop for each element in `kTests`. Each loop tests one specific
  // instruction.
  for (unsigned i = 0; i < ARRAY_SIZE(kTests); i++) {
    // Allocate results on the heap for this test.
    results[i] = new TestResult;
    results[i]->outputs = new Inputs[kTests[i].input_size];
    results[i]->output_size = kTests[i].input_size;

    uintptr_t input_address = reinterpret_cast<uintptr_t>(kTests[i].inputs);
    uintptr_t result_address = reinterpret_cast<uintptr_t>(results[i]->outputs);

    scratch_memory_buffers[i] = NULL;

    Label loop;
    UseScratchRegisterScope scratch_registers(&masm);
    // Include all registers from r0 ro r12.
    scratch_registers.Include(RegisterList(0x1fff));

    // Values to pass to the macro-assembler.
    Condition cond = kTests[i].operands.cond;
    Register rd = kTests[i].operands.rd;
    uint32_t immediate = kTests[i].operands.immediate;
    Operand op(immediate);
    scratch_registers.Exclude(rd);

    // Allocate reserved registers for our own use.
    Register input_ptr = scratch_registers.Acquire();
    Register input_end = scratch_registers.Acquire();
    Register result_ptr = scratch_registers.Acquire();

    // Initialize `input_ptr` to the first element and `input_end` the address
    // after the array.
    __ Mov(input_ptr, input_address);
    __ Add(input_end, input_ptr,
           sizeof(kTests[i].inputs[0]) * kTests[i].input_size);
    __ Mov(result_ptr, result_address);
    __ Bind(&loop);

    {
      UseScratchRegisterScope temp_registers(&masm);
      Register nzcv_bits = temp_registers.Acquire();
      Register saved_q_bit = temp_registers.Acquire();
      // Save the `Q` bit flag.
      __ Mrs(saved_q_bit, APSR);
      __ And(saved_q_bit, saved_q_bit, QFlag);
      // Set the `NZCV` and `Q` flags together.
      __ Ldr(nzcv_bits, MemOperand(input_ptr, offsetof(Inputs, apsr)));
      __ Orr(nzcv_bits, nzcv_bits, saved_q_bit);
      __ Msr(APSR_nzcvq, nzcv_bits);
    }
    __ Ldr(rd, MemOperand(input_ptr, offsetof(Inputs, rd)));

    (masm.*instruction)(cond, rd, op);

    {
      UseScratchRegisterScope temp_registers(&masm);
      Register nzcv_bits = temp_registers.Acquire();
      __ Mrs(nzcv_bits, APSR);
      // Only record the NZCV bits.
      __ And(nzcv_bits, nzcv_bits, NZCVFlag);
      __ Str(nzcv_bits, MemOperand(result_ptr, offsetof(Inputs, apsr)));
    }
    __ Str(rd, MemOperand(result_ptr, offsetof(Inputs, rd)));

    // Advance the result pointer.
    __ Add(result_ptr, result_ptr, sizeof(kTests[i].inputs[0]));
    // Loop back until `input_ptr` is lower than `input_base`.
    __ Add(input_ptr, input_ptr, sizeof(kTests[i].inputs[0]));
    __ Cmp(input_ptr, input_end);
    __ B(ne, &loop);
  }

  END();

  RUN();

  if (Test::generate_test_trace()) {
    // Print the results.
    for (size_t i = 0; i < ARRAY_SIZE(kTests); i++) {
      printf("static const Inputs kOutputs_%s_%s[] = {\n", mnemonic,
             kTests[i].identifier);
      for (size_t j = 0; j < results[i]->output_size; j++) {
        printf("  { ");
        printf("0x%08" PRIx32, results[i]->outputs[j].apsr);
        printf(", ");
        printf("0x%08" PRIx32, results[i]->outputs[j].rd);
        printf(" },\n");
      }
      printf("};\n");
    }
    printf("static const TestResult kReference%s[] = {\n", mnemonic);
    for (size_t i = 0; i < ARRAY_SIZE(kTests); i++) {
      printf("  {\n");
      printf("    ARRAY_SIZE(kOutputs_%s_%s),\n", mnemonic,
             kTests[i].identifier);
      printf("    kOutputs_%s_%s,\n", mnemonic, kTests[i].identifier);
      printf("  },\n");
    }
    printf("};\n");
  } else {
    // Check the results.
    unsigned total_error_count = 0;
    for (size_t i = 0; i < ARRAY_SIZE(kTests); i++) {
      bool instruction_has_errors = false;
      for (size_t j = 0; j < kTests[i].input_size; j++) {
        uint32_t apsr = results[i]->outputs[j].apsr;
        uint32_t rd = results[i]->outputs[j].rd;
        uint32_t apsr_input = kTests[i].inputs[j].apsr;
        uint32_t rd_input = kTests[i].inputs[j].rd;
        uint32_t apsr_ref = reference[i].outputs[j].apsr;
        uint32_t rd_ref = reference[i].outputs[j].rd;

        if (((apsr != apsr_ref) || (rd != rd_ref)) &&
            (++total_error_count <= kErrorReportLimit)) {
          // Print the instruction once even if it triggered multiple failures.
          if (!instruction_has_errors) {
            printf("Error(s) when testing \"%s %s\":\n", mnemonic,
                   kTests[i].operands_description);
            instruction_has_errors = true;
          }
          // Print subsequent errors.
          printf("  Input:    ");
          printf("0x%08" PRIx32, apsr_input);
          printf(", ");
          printf("0x%08" PRIx32, rd_input);
          printf("\n");
          printf("  Expected: ");
          printf("0x%08" PRIx32, apsr_ref);
          printf(", ");
          printf("0x%08" PRIx32, rd_ref);
          printf("\n");
          printf("  Found:    ");
          printf("0x%08" PRIx32, apsr);
          printf(", ");
          printf("0x%08" PRIx32, rd);
          printf("\n\n");
        }
      }
    }

    if (total_error_count > kErrorReportLimit) {
      printf("%u other errors follow.\n",
             total_error_count - kErrorReportLimit);
    }
// TODO: Do this check for the simulator too when it is ready.
#ifndef VIXL_INCLUDE_SIMULATOR
    VIXL_CHECK(total_error_count == 0);
#endif
  }

  for (size_t i = 0; i < ARRAY_SIZE(kTests); i++) {
    delete[] results[i]->outputs;
    delete results[i];
    delete scratch_memory_buffers[i];
  }

  TEARDOWN();
}

// Instantiate tests for each instruction in the list.
#define TEST(mnemonic)                                                      \
  static void Test_##mnemonic() {                                           \
    TestHelper(&MacroAssembler::mnemonic, #mnemonic, kReference##mnemonic); \
  }                                                                         \
  static Test test_##mnemonic(                                              \
      "AARCH32_SIMULATOR_COND_RD_OPERAND_CONST_T32_" #mnemonic,             \
      &Test_##mnemonic);
FOREACH_INSTRUCTION(TEST)
#undef TEST

}  // aarch32
}  // vixl
