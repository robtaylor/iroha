#include "opt/pipeline/reg_info.h"

#include "iroha/i_design.h"
#include "iroha/stl_util.h"
#include "opt/loop/loop_block.h"
#include "opt/optimizer_log.h"

namespace iroha {
namespace opt {
namespace pipeline {

RegInfo::RegInfo(loop::LoopBlock *lb) : lb_(lb) {}

RegInfo::~RegInfo() { STLDeleteSecondElements(&wr_deps_); }

bool RegInfo::BuildWRDep(OptimizerLog *opt_log) {
  map<IRegister *, int> write_pos;
  map<IRegister *, int> last_read_pos;
  int sindex = 0;
  for (IState *st : lb_->GetStates()) {
    for (IInsn *insn : st->insns_) {
      // Reads.
      for (IRegister *reg : insn->inputs_) {
        last_read_pos[reg] = sindex;
      }
      // Writes.
      for (IRegister *reg : insn->outputs_) {
        if (write_pos.find(reg) != write_pos.end()) {
          // write conflicts.
          ostream &os = opt_log->GetDumpStream();
          os << "Give up due to multiple writes<br/>\n";
          return false;
        }
        if (!reg->IsNormal()) {
          continue;
        }
        write_pos[reg] = sindex;
      }
    }
    ++sindex;
  }
  ostream &os = opt_log->GetDumpStream();
  for (auto it : last_read_pos) {
    IRegister *reg = it.first;
    auto jt = write_pos.find(reg);
    if (jt == write_pos.end()) {
      // no write in this loop.
      continue;
    }
    int windex = jt->second;
    int rindex = it.second;
    if (windex < rindex) {
      // Write -> Read.
      WRDep *dep = new WRDep();
      dep->wst_index_ = windex;
      dep->rst_index_ = rindex;
      wr_deps_[reg] = dep;
    }
  }
  if (wr_deps_.size() > 0) {
    os << "In pipleine register W-R dependencies.<br/>\n";
    for (auto p : wr_deps_) {
      WRDep *d = p.second;
      IRegister *reg = p.first;
      auto &sts = lb_->GetStates();
      os << "r_" << reg->GetId() << " " << reg->GetName()
         << " w:" << sts[d->wst_index_]->GetId()
         << " r:" << sts[d->rst_index_]->GetId() << "<br/>\n";
    }
  }
  return true;
}

}  // namespace pipeline
}  // namespace opt
}  // namespace iroha