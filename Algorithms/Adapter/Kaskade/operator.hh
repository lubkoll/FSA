#ifndef ALGORITHM_OPERATORS_KASKADE_OPERATOR_HH
#define ALGORITHM_OPERATORS_KASKADE_OPERATOR_HH

#include <memory>
#include <utility>

#include "fem/assemble.hh"
#include "fem/istlinterface.hh"

#include "../../vectorSpace.hh"
#include "vectorSpace.hh"
#include "../../operator.hh"
#include "Interface/Operator/linearizedOperator.hh"
#include "Interface/Operator/abstractOperator.hh"
#include "Util/Mixins/disableAssembly.hh"
#include "Util/castTo.hh"
#include "Util/create.hh"

#include "directSolver.hh"
#include "vector.hh" // copy

namespace Algorithm
{
  namespace Kaskade
  {
    template <class OperatorImpl>
    class Operator :
        public Interface::AbstractOperator , public Mixin::DisableAssembly
    {
      using AnsatzVariableSetDescription = typename OperatorImpl::AnsatzVars;
      using TestVariableSetDescription = typename OperatorImpl::TestVars;
      using VectorImpl = typename AnsatzVariableSetDescription::template CoefficientVectorRepresentation<>::type;
      using Spaces = typename AnsatzVariableSetDescription::Spaces;
      using Variables = typename AnsatzVariableSetDescription::Variables;
      using Assembler = ::Kaskade::VariationalFunctionalAssembler< ::Kaskade::LinearizationAt<OperatorImpl> >;
      using Domain = typename Assembler::AnsatzVariableSetDescription::template CoefficientVectorRepresentation<>::type;
      using Range = typename Assembler::TestVariableSetDescription::template CoefficientVectorRepresentation<>::type;
      using Matrix = ::Kaskade::MatrixAsTriplet<double>;
      using KaskadeOperator = ::Kaskade::MatrixRepresentedOperator<Matrix,Domain,Range>;

    public:
      Operator(const OperatorImpl& f,
               ::Algorithm::VectorSpace* domain_, ::Algorithm::VectorSpace* range_,
               int rbegin = 0, int rend = OperatorImpl::AnsatzVars::noOfVariables,
               int cbegin = 0, int cend = OperatorImpl::TestVars::noOfVariables)
        : AbstractOperator(domain_,range_),
          f_(f),
          spaces_( extractSpaces<AnsatzVariableSetDescription>(domain()) ),
          assembler_(spaces_),
          rbegin_(rbegin), rend_(rend), cbegin_(cbegin), cend_(cend)
      {}

      Operator(const OperatorImpl& f, ::Algorithm::VectorSpace& domain, ::Algorithm::VectorSpace& range,
               int rbegin = 0, int rend = OperatorImpl::AnsatzVars::noOfVariables,
               int cbegin = 0, int cend = OperatorImpl::TestVars::noOfVariables)
        : Operator(f,&domain,&range,rbegin,rend,cbegin,cend)
      {}

      Operator(const Operator& g)
        : AbstractOperator(g.domain_ptr(),g.range_ptr()),
          DisableAssembly(g.assemblyIsDisabled()),
          f_(g.f_), spaces_(g.spaces_),
          assembler_(spaces_),
          rbegin_(g.rbegin_), rend_(g.rend_), cbegin_(g.cbegin_), cend_(g.cend_)
      {
        if( g.A_ != nullptr ) A_ = std::make_unique<KaskadeOperator>(*g.A_);
      }


      Operator(const Operator& g, bool disableAssembly)
        : AbstractOperator(g.domain_ptr(),g.range_ptr()),
          DisableAssembly(disableAssembly),
          f_(g.f_), spaces_(g.spaces_),
          assembler_(spaces_),
          A_( std::make_unique<KaskadeOperator>(*g.A_) )
      {}

      ::Algorithm::Vector operator()(const ::Algorithm::Vector& x) const final override
      {
        primalDualIgnoreReset(std::bind(&Operator::assembleOperator,std::ref(*this), std::placeholders::_1),x);

        VectorImpl v( assembler_.rhs() );

        auto y = range().element();
        copyFromCoefficientVector<TestVariableSetDescription>(v,y);
        return y;
      }

      ::Algorithm::Vector d1(const ::Algorithm::Vector& x, const ::Algorithm::Vector& dx) const final override
      {
        primalDualIgnoreReset(std::bind(&Operator::assembleGradient,std::ref(*this), std::placeholders::_1),x);

        VectorImpl dx_( AnsatzVariableSetDescription::template CoefficientVectorRepresentation<>::init(spaces_) );
        copyToCoefficientVector<AnsatzVariableSetDescription>(dx,dx_);
        VectorImpl y_( TestVariableSetDescription::template CoefficientVectorRepresentation<>::init(spaces_) );

        A_->apply( dx_ , y_ );

        auto y = range().element();
        copyFromCoefficientVector<TestVariableSetDescription>(y_,y);

        return y;
      }

    protected:
      void assembleOperator(const ::Algorithm::Vector& x) const
      {
        if( assemblyIsDisabled() ) return;
        if( ( (assembler_.valid() & Assembler::RHS) != 0 ) && (old_X_A_==x) ) return;

        AnsatzVariableSetDescription variableSet(spaces_);
        typename AnsatzVariableSetDescription::VariableSet u(variableSet);

        copy(x,u);

        assembler_.assemble(::Kaskade::linearization(f_,u) , Assembler::RHS , nAssemblyThreads );

        old_X_A_ = x;
      }

      void assembleGradient(const ::Algorithm::Vector& x) const
      {
        if( assemblyIsDisabled() ) return;
        if( ( (assembler_.valid() & Assembler::MATRIX) != 0 ) && (old_X_dA_==x) ) return;

        AnsatzVariableSetDescription variableSet(spaces_);
        typename AnsatzVariableSetDescription::VariableSet u(variableSet);

        copy(x,u);

        assembler_.assemble(::Kaskade::linearization(f_,u) , Assembler::MATRIX , nAssemblyThreads );
        A_ = std::make_unique< KaskadeOperator >( assembler_.template get<Matrix>(onlyLowerTriangle_,rbegin_,rend_,cbegin_,cend_) );
        old_X_dA_ = x;
      }

      Operator* cloneImpl() const final override
      {
        return new Operator(*this);
      }

      std::unique_ptr<Interface::LinearizedOperator> makeLinearization(const ::Algorithm::Vector& x) const
      {
//        primalDualIgnoreReset(std::bind(&Operator::assembleOperator,std::ref(*this), std::placeholders::_1),x);
        primalDualIgnoreReset(std::bind(&Operator::assembleGradient,std::ref(*this), std::placeholders::_1),x);
        return std::make_unique<Interface::LinearizedOperator>(std::make_unique< Operator<OperatorImpl> >(*this,true),x);
      }

      std::unique_ptr<Interface::AbstractLinearSolver> makeSolver() const
      {
        assert (A_ != nullptr);
        return std::make_unique< DirectSolver<AnsatzVariableSetDescription,TestVariableSetDescription> >( *A_ , spaces_, range_ptr() , domain_ptr() );
      }

      OperatorImpl f_;
      Spaces spaces_;
      mutable Assembler assembler_;
      mutable std::unique_ptr< KaskadeOperator > A_ = nullptr;
      mutable ::Algorithm::Vector old_X_A_, old_X_dA_;
      unsigned nAssemblyThreads = 1;
      bool onlyLowerTriangle_ = false;
      int rbegin_=0, rend_=OperatorImpl::AnsatzVars::noOfVariables;
      int cbegin_=0, cend_=OperatorImpl::TestVars::noOfVariables;
    };

    template <class OperatorImpl>
    auto makeOperator(const OperatorImpl& f,
                      ::Algorithm::VectorSpace* domain,
                      ::Algorithm::VectorSpace* range,
                      int rbegin = 0, int rend = OperatorImpl::AnsatzVars::noOfVariables,
                      int cbegin = 0, int cend = OperatorImpl::TestVars::noOfVariables)
    {
      return createFromUniqueImpl< ::Algorithm::Operator , Operator<OperatorImpl> >( f, domain , range , rbegin , rend , cbegin , cend);
    }

    template <class OperatorImpl>
    auto makeOperator(const OperatorImpl& f,
                      ::Algorithm::VectorSpace& domain,
                      ::Algorithm::VectorSpace& range,
                      int rbegin = 0, int rend = OperatorImpl::AnsatzVars::noOfVariables,
                      int cbegin = 0, int cend = OperatorImpl::TestVars::noOfVariables)
    {
      return createFromUniqueImpl< ::Algorithm::Operator , Operator<OperatorImpl> >( f, domain , range , rbegin , rend , cbegin , cend);
    }
  }
}

#endif // ALGORITHM_OPERATORS_KASKADE_OPERATOR_HH