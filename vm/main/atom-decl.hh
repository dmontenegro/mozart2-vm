// Copyright © 2012, Université catholique de Louvain
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// *  Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
// *  Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#ifndef __ATOM_DECL_H
#define __ATOM_DECL_H

#include "store.hh"
#include "atomtable.hh"

class Atom;

template <>
class Storage<Atom> {
public:
  typedef AtomImpl* Type;
};

template <>
class Implementation<Atom> {
public:
  typedef SelfType<Atom>::Self Self;

  Implementation<Atom>(const AtomImpl* value) : _value(value) {}

  inline
  BuiltinResult equals(Self self, VM vm, UnstableNode* right, UnstableNode* result);

  const AtomImpl* value() const { return _value; }

private:
  const AtomImpl* _value;
};

class Atom: public Type {
public:
  Atom() : Type("Atom", true) {}

  typedef Node* Self;

  static const Atom* const type;

  static AtomImpl* build(VM vm, std::size_t size, char16_t* data) {
    assert(size == (size << 5) >> 5);
    return vm->atomTable.get(vm, size, data);
  }
private:
  static const Atom rawType;
};
/*
template<>
class Accessor<Atom, AtomImpl*> {
public:
  template<class... Args>
  static void init(const Type*& type, MemWord& value, VM vm, Args... args) {
    type = Atom::type;
    value.init(vm, Atom::build(vm, args...));
  }
  static Implementation<Atom> get(MemWord value) {
    return Implementation<Atom>(value.get<AtomImpl*>());
  }
};
*/
#endif // __ATOM_DECL_H