#include "example_common.h"
#include "iroha/iroha.h"

// This implements XORSHIFT32 random generator.
//
// $ ./xorshift -v -o /tmp/a.v

// y = NON_ZERO_SEED
//
// Repeat:
//   y = y ^ (y << 13)
//   y = y ^ (y >> 17)
//   y = y ^ (y << 15)
//   return y

using namespace iroha;

void build_stage(DesignTool *tool,
		 int amount, bool to_left,
		 IRegister *reg, IRegister *tmp_reg,
		 IState *st0, IState *st1,
		 IResource *shifter, IResource *xor_res) {
  // st 0: tmp <= shift(reg)
  IInsn *shift_insn = tool->CreateShiftInsn(reg, to_left, amount);
  shift_insn->outputs_.push_back(tmp_reg);
  st0->insns_.push_back(shift_insn);
  // st 1: reg <= reg ^ tmp
  IInsn *xor_insn = new IInsn(xor_res);
  xor_insn->inputs_.push_back(reg);
  xor_insn->inputs_.push_back(tmp_reg);
  xor_insn->outputs_.push_back(reg);
  st1->insns_.push_back(xor_insn);
  // set next
  tool->AddNextState(st0, st1);
}

IDesign *build_design() {
  IDesign *design = new IDesign;
  DesignTool *tool = Iroha::CreateDesignTool(design);

  IModule *module = new IModule(design, "XORSHIFT");
  design->modules_.push_back(module);
  ITable *table = new ITable(module);
  module->tables_.push_back(table);

  // Output pin
  IResource *ext_output = tool->GetResource(table, resource::kExtOutput);
  ResourceParams *params_output = ext_output->GetParams();
  params_output->SetExtOutputPort("data_out", 32);

  // Registers
  IRegister *y = tool->AllocRegister(table, "y", 32);
  tool->SetRegisterInitialValue(1, y);
  IRegister *tmp_reg = tool->AllocRegister(table, "tmp_reg", 32);

  // Shifter
  IResource *shifter = tool->CreateShifterResource(table);

  // Xor
  IResource *xor_res = tool->GetBinOpResource(table, resource::kBitXor, 32);

  // FSM
  IState *st0 = new IState(table);
  // Stage 1.
  table->states_.push_back(st0);
  IState *st1_0 = new IState(table);
  IState *st1_1 = new IState(table);
  table->states_.push_back(st1_0);
  table->states_.push_back(st1_1);
  build_stage(tool, 13, true, y, tmp_reg, st1_0, st1_1, shifter, xor_res);
  // Stage 2.
  IState *st2_0 = new IState(table);
  IState *st2_1 = new IState(table);
  table->states_.push_back(st2_0);
  table->states_.push_back(st2_1);
  build_stage(tool, 17, false, y, tmp_reg, st2_0, st2_1, shifter, xor_res);
  // Stage 3.
  IState *st3_0 = new IState(table);
  IState *st3_1 = new IState(table);
  table->states_.push_back(st3_0);
  table->states_.push_back(st3_1);
  build_stage(tool, 15, true, y, tmp_reg, st3_0, st3_1, shifter, xor_res);
  // Create loop.
  tool->AddNextState(st0, st1_0);
  tool->AddNextState(st1_1, st2_0);
  tool->AddNextState(st2_1, st3_0);
  tool->AddNextState(st3_1, st0);
  // Output
  IInsn *output_insn = new IInsn(ext_output);
  output_insn->inputs_.push_back(y);
  st0->insns_.push_back(output_insn);

  table->SetInitialState(st0);
  tool->Validate(NULL);

  delete tool;

  return design;
}
