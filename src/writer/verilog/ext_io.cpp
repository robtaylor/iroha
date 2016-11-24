#include "writer/verilog/ext_io.h"

#include "iroha/i_design.h"
#include "iroha/resource_class.h"
#include "iroha/resource_params.h"
#include "writer/module_template.h"
#include "writer/names.h"
#include "writer/verilog/module.h"
#include "writer/verilog/ports.h"
#include "writer/verilog/state.h"
#include "writer/verilog/insn_writer.h"
#include "writer/verilog/table.h"

namespace iroha {
namespace writer {
namespace verilog {

ExtIO::ExtIO(const IResource &res, const Table &table)
  : Resource(res, table), has_default_output_value_(false),
    default_output_value_(0) {
  auto *klass = res.GetClass();
  if (resource::IsExtOutput(*klass)) {
    auto *params = res.GetParams();
    has_default_output_value_ =
      params->GetDefaultValue(&default_output_value_);
  }
}

void ExtIO::BuildResource() {
  auto *klass = res_.GetClass();
  auto *params = res_.GetParams();
  if (resource::IsExtInput(*klass)) {
    auto *ports = tab_.GetPorts();
    string input_port;
    int width;
    params->GetExtInputPort(&input_port, &width);
    ports->AddPort(input_port, Port::INPUT, width);
    BuildPathRec(tab_.GetModule(), input_port, width, false);
  }
  if (resource::IsExtOutput(*klass)) {
    auto *ports = tab_.GetPorts();
    string output_port;
    int width;
    params->GetExtOutputPort(&output_port, &width);
    ports->AddPort(output_port, Port::OUTPUT, width);
    if (has_default_output_value_) {
      ostream &os = tab_.StateOutputSectionStream();
      os << "      " << output_port << " <= "
	 << SelectValueByState(Util::Itoa(default_output_value_)) << ";\n";
    }
    BuildPathRec(tab_.GetModule(), output_port, width, true);
  }
}

void ExtIO::BuildInsn(IInsn *insn, State *st) {
  auto *klass = res_.GetClass();
  if (resource::IsExtInput(*klass)) {
    BuildExtInputInsn(insn);
  }
  if (resource::IsExtOutput(*klass) &&
      !has_default_output_value_) {
    auto *params = res_.GetParams();
    string output_port;
    int width;
    params->GetExtOutputPort(&output_port, &width);
    ostream &os = st->StateBodySectionStream();
    os << "          " << output_port << " <= "
       << InsnWriter::RegisterValue(*insn->inputs_[0], tab_.GetNames());
    os << ";\n";
  }
}

void ExtIO::BuildPathRec(Module *child_mod, const string &port, int width,
			 bool is_output) {
  if (child_mod == nullptr) {
    return;
  }
  Module *mod = child_mod->GetParentModule();
  if (mod == nullptr) {
    return;
  }
  ostream &os = mod->ChildModuleInstSectionStream(child_mod);
  os << ", ." << port << "(" << port << ")";
  auto *ports = mod->GetPorts();
  Port::PortType type;
  if (is_output) {
    type = Port::OUTPUT_WIRE;
  } else {
    type = Port::INPUT;
  }
  ports->AddPort(port, type, width);
  BuildPathRec(mod, port, width, is_output);
}

void ExtIO::BuildExtInputInsn(IInsn *insn) {
  auto *params = res_.GetParams();
  string input_port;
  int width;
  params->GetExtInputPort(&input_port, &width);
  ostream &ws = tmpl_->GetStream(kInsnWireValueSection);
  ws << "  assign " << InsnWriter::InsnOutputWireName(*insn, 0)
     << " = "
     << input_port << ";\n";
}

void ExtIO::CollectNames(Names *names) {
  auto *klass = res_.GetClass();
  auto *params = res_.GetParams();
  string port;
  int width;
  if (resource::IsExtInput(*klass)) {
    params->GetExtInputPort(&port, &width);
  } else if (resource::IsExtOutput(*klass)) {
    params->GetExtOutputPort(&port, &width);
  }
  names->ReserveGlobalName(port);
}

}  // namespace verilog
}  // namespace writer
}  // namespace iroha
