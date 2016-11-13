#include "terminationCriteria.hh"

#include <Spacy/Algorithm/dampingFactor.hh>
#include <Spacy/vector.hh>
#include <Spacy/c1Operator.hh>

#include <cmath>
#include <iostream>

namespace Spacy
{
  namespace Newton
  {
    namespace Termination
    {
      AffineCovariant::AffineCovariant(const C1Operator&, double relativeAccuracy, bool verbose)
        : Mixin::RelativeAccuracy(relativeAccuracy),
          Mixin::Verbosity(verbose)
      {}

      bool AffineCovariant::operator()(DampingFactor nu, const Vector& x, const Vector& dx) const
      {
        if(beforeFirstIteration_)
        {
          beforeFirstIteration_ = false;
          return false;
        }
        if(abs(get(nu-1)) > eps()) return false;

        auto norm_x = norm(x), norm_dx = norm(dx);
        if( norm_x == 0 && norm_dx == 0 ) return true;

        if( norm_dx < getRelativeAccuracy() * norm_x )
        {
          if( verbose() ) std::cout << "Terminating (rel. acc.: " << norm_dx/norm_x << ")\n";
          return true;
        }

        return false;
      }


      AffineContravariant::AffineContravariant(const C1Operator& F, double relativeAccuracy, bool verbose)
        : Mixin::RelativeAccuracy(relativeAccuracy),
          Mixin::Verbosity(verbose), F_(F)
      {}

      bool AffineContravariant::operator()(DampingFactor nu, const Vector& x, const Vector&) const
      {
        if( initialResidual < 0 )
        {
          initialResidual = norm( F_(x) );
          if( verbose() ) std::cout << "Initial residual: " << initialResidual << std::endl;
          if( initialResidual == 0 )
            return true;
          return false;
        }

        if(abs(get(nu-1)) > eps()) return false;

        if( verbose() ) std::cout << "Residual: " << norm(F_(x)) << ", relative accuracy: " << getRelativeAccuracy() << ", initialResidual: " << initialResidual << std::endl;

        if( norm( F_(x) ) < getRelativeAccuracy() * initialResidual )
        {
          if( verbose() ) std::cout << "Terminating (rel. acc.: " << norm(F_(x))/initialResidual << ")\n";
          return true;
        }

        return false;
      }
    }
  }
}

