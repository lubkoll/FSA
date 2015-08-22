#ifndef ALGORITHM_INTERFACE_HESSIAN_HH
#define ALGORITHM_INTERFACE_HESSIAN_HH

#include <memory>

#include "vector.hh"
#include "abstractFunctional.hh"
#include "Interface/Operator/abstractLinearOperator.hh"
#include "Util/Mixins/impl.hh"

namespace Algorithm
{
  namespace Interface
  {
    class Hessian : public AbstractLinearOperator, public Mixin::UniqueImpl<AbstractFunctional>
    {
    public:
      Hessian(Hessian&&);
      Hessian(std::unique_ptr<AbstractFunctional>&& A, const Vector& x);

      Vector operator ()(const Vector& dx) const final override;

      std::unique_ptr<AbstractLinearSolver> solver() const final override;

    private:
      Hessian* cloneImpl() const;

      Vector x_;
    };
  }
}

#endif // ALGORITHM_INTERFACE_HESSIAN_HH