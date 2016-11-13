#include "linearSolver.hh"

#include <Spacy/operator.hh>
#include <Spacy/vectorSpace.hh>
#include <Spacy/zeroVectorCreator.hh>

#include <utility>

namespace Spacy
{
  namespace CG
  {
    LinearSolver::LinearSolver(Operator A_, CallableOperator P_, const std::string& type )
      : OperatorBase(A_.range(),A_.domain()),
        cg(std::move(A_),std::move(P_),type)
    {
      using namespace Mixin;
      castAndAttach<Eps>(*this,cg);
      castAndAttach<AbsoluteAccuracy>(*this,cg);
      castAndAttach<RelativeAccuracy>(*this,cg);
      castAndAttach<Verbosity>(*this,cg);
      castAndAttach<IterativeRefinements>(*this,cg);
      castAndAttach<MaxSteps>(*this,cg);
    }

    LinearSolver::LinearSolver(const LinearSolver& other) :
      OperatorBase(other),
      Mixin::AbsoluteAccuracy(other.getAbsoluteAccuracy()),
      Mixin::RelativeAccuracy(other.getRelativeAccuracy()),
      Mixin::Eps(other.eps()),
      Mixin::Verbosity(other.getVerbosityLevel()),
      cg(other.cg)
    {
      using namespace Mixin;
      castAndAttach<Eps>(*this,cg);
      castAndAttach<AbsoluteAccuracy>(*this,cg);
      castAndAttach<RelativeAccuracy>(*this,cg);
      castAndAttach<Verbosity>(*this,cg);
      castAndAttach<IterativeRefinements>(*this,cg);
      castAndAttach<MaxSteps>(*this,cg);
    }

    Vector LinearSolver::operator()(const Vector& y) const
    {
      return cg.solve(zero(range()), y);
    }

    Solver& LinearSolver::impl()
    {
      return cg;
    }

    bool LinearSolver::isPositiveDefinite() const
    {
      return !cg.indefiniteOperator();
    }

    const CallableOperator& LinearSolver::P() const
    {
      return cg.P();
    }

    const CallableOperator& LinearSolver::A() const
    {
      return cg.A();
    }
  }


  CG::LinearSolver makeCGSolver(Operator A, CallableOperator P, Real relativeAccuracy, Real eps, bool verbose)
  {
    auto solver = CG::LinearSolver(std::move(A), std::move(P), "CG" );
    solver.setRelativeAccuracy(relativeAccuracy);
    solver.setEps(eps);
    solver.setVerbosity(verbose);
    return std::move(solver);
  }

  CG::LinearSolver makeRCGSolver(Operator A, CallableOperator P, Real relativeAccuracy, Real eps, bool verbose)
  {
    auto solver = CG::LinearSolver(std::move(A), std::move(P), "RCG");
    solver.setRelativeAccuracy(relativeAccuracy);
    solver.setEps(eps);
    solver.setVerbosity(verbose);
    return std::move(solver);
  }

  CG::LinearSolver makeTCGSolver(Operator A, CallableOperator P, Real relativeAccuracy, Real eps, bool verbose)
  {
    auto solver = CG::LinearSolver(std::move(A), std::move(P), "TCG");
    solver.setRelativeAccuracy(relativeAccuracy);
    solver.setEps(eps);
    solver.setVerbosity(verbose);
    return std::move(solver);
  }

  CG::LinearSolver makeTRCGSolver(Operator A, CallableOperator P, Real relativeAccuracy, Real eps, bool verbose)
  {
    auto solver = CG::LinearSolver(std::move(A), std::move(P), "TRCG");
    solver.setRelativeAccuracy(relativeAccuracy);
    solver.setEps(eps);
    solver.setVerbosity(verbose);
    return std::move(solver);
  }

}
