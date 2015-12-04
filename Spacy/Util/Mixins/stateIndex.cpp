// Copyright (C) 2015 by Lars Lubkoll. All rights reserved.
// Released under the terms of the GNU General Public License version 3 or later.

#include "stateIndex.hh"

#include <cmath>

Spacy::Mixin::StateIndex::StateIndex(unsigned index) noexcept
  : index_(index)
{}

void Spacy::Mixin::StateIndex::setStateIndex(unsigned index)
{
  index_ = index;
  notify();
}

double Spacy::Mixin::StateIndex::stateIndex() const noexcept
{
  return index_;
}

void Spacy::Mixin::StateIndex::update(StateIndex* changedSubject)
{
  setStateIndex( changedSubject->stateIndex() );
}
