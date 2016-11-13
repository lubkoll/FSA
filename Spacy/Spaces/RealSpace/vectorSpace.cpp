#include "vectorSpace.hh"

#include <Spacy/vector.hh>
#include <Spacy/zeroVectorCreator.hh>
#include <Spacy/Util/cast.hh>
#include "real.hh"

Spacy::VectorSpace Spacy::RealSpace::makeHilbertSpace(bool defaultIndex)
{
  return ::Spacy::makeHilbertSpace( [](const VectorSpace* space)
                                      {
                                        return Real{*space};
                                      } ,
                                    [](const ::Spacy::Vector& x, const ::Spacy::Vector& y)
                                      {
                                        return Real( get( cast_ref<Real>(x) * cast_ref<Real>(y) ) );
                                      } ,
                                    defaultIndex
                                   );
}

Spacy::VectorSpace Spacy::makeRealSpace(bool defaultIndex)
{
  return Spacy::RealSpace::makeHilbertSpace(defaultIndex);
}
