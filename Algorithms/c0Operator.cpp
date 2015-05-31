#include "c0Operator.hh"

#include "Interface/abstractC0Operator.hh"
#include "functionSpaceElement.hh"

namespace Algorithm
{
  C0Operator::C0Operator(std::shared_ptr<AbstractC0Operator> impl)
    : impl_(impl)
  {}

//  void Operator::setArgument(const FunctionSpaceElement &x)
//  {
//    impl_->setArgument(x.impl());
//  }

//  FunctionSpaceElement Operator::operator()() const
//  {
//    return (*impl_)();
//  }

  FunctionSpaceElement C0Operator::operator()(const FunctionSpaceElement& x) const
  {
//    setArgument(x);
    return (*impl_)(x.impl());
  }

  AbstractC0Operator& C0Operator::impl()
  {
    return *impl_;
  }

  const AbstractC0Operator& C0Operator::impl() const
  {
    return *impl_;
  }
}
