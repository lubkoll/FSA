#include "abstractC2Functional.hh"

#include "Interface/abstractBanachSpace.hh"

#include <utility>

namespace Algorithm
{
  AbstractC2Functional::AbstractC2Functional(const AbstractBanachSpace &domain)
    : AbstractC1Functional(domain)
  {}

  double AbstractC2Functional::d1(const AbstractFunctionSpaceElement &dx) const
  {
    return (*(derivative_->d0())) * dx;
  }

  std::shared_ptr<AbstractC1Operator> AbstractC2Functional::getDerivative() const
  {
    return derivative_;
  }

  void AbstractC2Functional::setDerivative(std::shared_ptr<AbstractC1Operator> derivative)
  {
    derivative_ = derivative;
  }
}
