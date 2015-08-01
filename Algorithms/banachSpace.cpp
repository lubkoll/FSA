#include "banachSpace.hh"

#include "Interface/abstractBanachSpace.hh"
#include "functionSpaceElement.hh"

#include <utility>

namespace Algorithm
{
  BanachSpace::BanachSpace(std::shared_ptr<Interface::AbstractBanachSpace> implementation)
    : Mixin::SharedImpl<Interface::AbstractBanachSpace>(implementation)
  {}

  void BanachSpace::setNorm(const Norm& norm)
  {
    impl().setNorm(norm.sharedImpl());
  }

  Norm BanachSpace::norm() const
  {
    return Norm( impl().sharedNorm() );
  }

  FunctionSpaceElement BanachSpace::element() const
  {
    return FunctionSpaceElement(impl().element());
  }

  unsigned BanachSpace::index() const
  {
    return impl().index();
  }

  void connectPrimalDual(BanachSpace& primalSpace, BanachSpace& dualSpace)
  {
    Interface::makePrimalDual( primalSpace.impl() , dualSpace.impl() );
  }

}