#include "opt/pipeline/pipeliner.h"

#include "iroha/i_design.h"
#include "iroha/resource_class.h"
#include "opt/loop/loop_block.h"
#include "opt/optimizer_log.h"

namespace iroha {
namespace opt {
namespace pipeline {

Pipeliner::Pipeliner(ITable *tab, loop::LoopBlock *lb)
    : tab_(tab), lb_(lb), opt_log_(nullptr) {
  opt_log_ = tab->GetModule()->GetDesign()->GetOptimizerLog();
}

bool Pipeliner::Pipeline() {
  lb_->Annotate(opt_log_);
  ostream &os = opt_log_->GetDumpStream();
  int ns = lb_->GetStates().size();
  os << "Pipeliner " << lb_->GetStates().size() << " states, "
     << lb_->GetLoopCount() << " loop <br/>";
  // prepare states.
  int plen = ns + (ns - 1);
  for (int i = 0; i < plen; ++i) {
    IState *st = new IState(tab_);
    pipeline_st_.push_back(st);
    tab_->states_.push_back(st);
  }
  for (int i = 0; i < ns; ++i) {
    for (int j = 0; j <= i; ++j) {
      PlaceState(i, j);
    }
  }
  for (int i = 1; i < ns; ++i) {
    for (int j = i; j < ns; ++j) {
      PlaceState(i + ns - 1, j);
    }
  }
  return true;
}

void Pipeliner::PlaceState(int pidx, int lidx) {
  IState *pst = pipeline_st_[pidx];
  ostream &os = opt_log_->State(pst);
  os << "[" << lidx << "]";
  IState *lst = lb_->GetStates().at(lidx);
  for (IInsn *insn : lst->insns_) {
    IResource *res = insn->GetResource();
    if (resource::IsTransition(*(res->GetClass()))) {
      continue;
    }
    IInsn *new_insn = new IInsn(res);
    new_insn->inputs_ = insn->inputs_;
    new_insn->outputs_ = insn->outputs_;
    pst->insns_.push_back(new_insn);
  }
}

}  // namespace pipeline
}  // namespace opt
}  // namespace iroha
