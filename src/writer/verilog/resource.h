// -*- C++ -*-
#ifndef _writer_verilog_resource_h_
#define _writer_verilog_resource_h_

#include "writer/verilog/common.h"

#include <map>

namespace iroha {
namespace writer {
namespace verilog {

class Resource {
public:
  Resource(const IResource &res, const Table &tab);

  static Resource *Create(const IResource &res, const Table &tab);

  virtual void BuildResource();
  virtual void BuildInsn(IInsn *insn, State *st);
  virtual string ReadySignal(IInsn *insn);

protected:
  void WriteInputSel(const string &name,
		     const map<IState *, IInsn *> &callers,
		     int nth,
		     ostream &os);
  void CollectResourceCallers(const string &opr,
			      map<IState *, IInsn *> *callers);
  void WriteWire(const string &name, const IValueType &type,
		 ostream &os);
  string JoinStates(const map<IState *, IInsn *> &sts);
  string JoinStatesWithSubState(const map<IState *, IInsn *> &sts, int sub);
  void WriteStateUnion(const map<IState *, IInsn *> &callers,
		       ostream &os);

  const IResource &res_;
  const Table &tab_;
  ModuleTemplate *tmpl_;
};

}  // namespace verilog
}  // namespace writer
}  // namespace iroha

#endif  // _writer_verilog_resource_h_