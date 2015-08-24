#include "luSolver.hh"

#include "util.hh"
#include "vectorSpace.hh"
#include "../../vectorSpace.hh"

namespace Algorithm
{
  namespace
  {
    dolfin::Parameters default_parameters()
    {
      dolfin::Parameters p("linear_variational_solver");

      p.add("linear_solver", "default");

      p.add("print_rhs", false);
      p.add("print_matrix", false);

      p.add(dolfin::LUSolver::default_parameters());

      return p;
    }
  }

  namespace Fenics
  {
    LUSolver::LUSolver(std::shared_ptr<dolfin::GenericMatrix> A, const dolfin::FunctionSpace& space,
                       ::Algorithm::VectorSpace* domain , ::Algorithm::VectorSpace* range,
                       bool symmetric, const std::string& solverName)
      : OperatorBase(domain,range),
        solver_(solverName),
        space_(space)
    {
      auto parameters = default_parameters();
      solver_.parameters.update(parameters("lu_solver"));
      solver_.parameters["symmetric"] = symmetric;
      solver_.set_operator(A);
    }

    ::Algorithm::Vector LUSolver::operator()(const ::Algorithm::Vector& x) const
    {
      // Solve linear system
      dolfin::Function x_(space_);
      copy(x,x_);
      auto y_ = x_.vector()->copy();
      solver_.solve( *y_, *x_.vector() );
      auto y = range().element();

      copy(*y_, y);
      return y;
    }


    TransposedLUSolver::TransposedLUSolver(std::shared_ptr<dolfin::GenericMatrix> A, const dolfin::FunctionSpace& space,
                       ::Algorithm::VectorSpace* domain , ::Algorithm::VectorSpace* range,
                       bool symmetric, const std::string& solverName)
      : OperatorBase(domain,range),
        solver_(solverName),
        space_(space)
    {
      auto parameters = default_parameters();
      solver_.parameters.update(parameters("lu_solver"));
      solver_.parameters["symmetric"] = symmetric;
      solver_.set_operator(A);
    }

    ::Algorithm::Vector TransposedLUSolver::operator()(const ::Algorithm::Vector& x) const
    {
      // Solve linear system
      dolfin::Function x_(space_);
      copy(x,x_);
      auto y_ = x_.vector()->copy();
      solver_.solve_transpose( *y_, *x_.vector() );
      auto y = range().element();

      copy(*y_, y);
      return y;
    }
  }
}
