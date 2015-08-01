#include "c1Operator.hh"

#include "functionSpaceElement.hh"
#include "Interface/Operator/linearizedOperator.hh"

namespace Algorithm
{
  C1Operator::C1Operator(std::unique_ptr<Interface::AbstractC1Operator>&& impl)
    : Operator(std::unique_ptr<Interface::AbstractOperator>(impl.release()))
  {}

  FunctionSpaceElement C1Operator::d1(const FunctionSpaceElement& x, const FunctionSpaceElement& dx) const
  {
    return impl().d1( x.impl() , dx.impl() );
  }

  LinearOperator C1Operator::getLinearization(const FunctionSpaceElement& x) const
  {
    return LinearOperator( dynamic_cast<const Interface::AbstractC1Operator&>( impl() ).linearization(x.impl()) );
  }

  Interface::AbstractC1Operator& C1Operator::impl()
  {
    return dynamic_cast<Interface::AbstractC1Operator&>(Operator::impl());
  }

  const Interface::AbstractC1Operator& C1Operator::impl() const
  {
    return dynamic_cast<const Interface::AbstractC1Operator&>(Operator::impl());
  }
}