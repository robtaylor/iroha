// -*- C++ -*-
#ifndef _writer_verilog_state_h_
#define _writer_verilog_state_h_

#include "writer/cxx/common.h"

namespace iroha {
namespace writer {
namespace cxx {

class State {
public:
  State(IState *st, Table *tab);

  void Build();
  string GetMethodName();
  IState *GetIState() const;

private:
  void WriteInsn(IInsn *insn, ostream &os);
  void WriteTransitionInsn(IInsn *insn, ostream &os);
  void OrderInsns(vector<IInsn *> *insns);

  IState *i_st_;
  Table *tab_;
};

}  // namespace cxx
}  // namespace writer
}  // namespace iroha

#endif  // _writer_verilog_state_h_