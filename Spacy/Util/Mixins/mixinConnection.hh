#ifndef SPACY_MIXINS_EQUALITY_POINTER_COMPARISON_HH
#define SPACY_MIXINS_EQUALITY_POINTER_COMPARISON_HH

#include <vector>

namespace Spacy
{
  namespace Mixin
  {
    /// Connect objects of type Impl that provides a suitable method void update(Impl*) to another object of same type.
    template <class Impl>
    class MixinConnection
    {
    public:
      /// Attach observer.
      void attach(Impl& observer)
      {
        observers_.push_back(&observer);
      }

      /// Detach observer.
      void detach(Impl& observer)
      {
        auto iend = end(observers_);
        for(auto iter = begin(observers_); iter!= iend; ++iter)
          if( *iter == &observer )
          {
            observers_.erase(iter);
            return;
          }
      }

      /// Notify observers about changes.
      void notify()
      {
        for( Impl* observer : observers_ )
          observer->update(static_cast<Impl*>(this));
      }

    private:
      std::vector<Impl*> observers_ = {};
    };
  }

  template <class Base, class Source, class ToAttach>
  void castAndAttach(Source& source, ToAttach& toAttach)
  {
    static_cast<Base&>(source).attach(static_cast<Base&>(toAttach));
  }

  template <class Base, class Source, class ToAttach>
  void castAndDetach(Source& source, ToAttach& toAttach)
  {
    static_cast<Base&>(source).detach(static_cast<Base&>(toAttach));
  }
}

#endif // SPACY_MIXINS_EQUALITY_POINTER_COMPARISON_HH
