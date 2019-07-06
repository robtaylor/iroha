// -*- C++ -*-
#ifndef _writer_dot_writer_h_
#define _writer_dot_writer_h_

#include "iroha/common.h"

namespace iroha {

class Dot;

namespace writer {

class DotWriter {
public:
  DotWriter(const IDesign *design, ostream &os);
  ~DotWriter();

  void Write();

private:
  void WriteModule(const IModule &mod);
  string TableName(const ITable &tab);

  const IDesign *design_;
  ostream &os_;
  std::unique_ptr<Dot> dot_;
};

}  // namespace writer
}  // namespace iroha

#endif
