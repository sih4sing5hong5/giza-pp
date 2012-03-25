/*
  Copyright (C) 1997,1998,1999,2000,2001  Franz Josef Och (RWTH Aachen - Lehrstuhl fuer Informatik VI)

  This file is part of GIZA++ ( extension of GIZA ).

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
  USA.
*/

#ifndef GIZAPP_POINTER_H_
#define GIZAPP_POINTER_H_

#include <cassert>
#include <ostream>

// TODO: make sure this class is allowed to copying.
template<class T>
class SmartPointer {
 public:
  explicit SmartPointer(T* ptr=0) : ptr_(ptr) {}
  virtual ~SmartPointer() {}

  T& operator*() const { return *ptr_; }
  T* operator->() const { return ptr_; }
  T* ptr() const { return ptr_; }
  operator bool() const { return ptr_ != 0; }

 protected:
  T* ptr_;
};

template<class T> inline ostream &operator<<(ostream& out,
                                             const SmartPointer<T>& ptr) {
  if (ptr.ptr()) {
    return out << *ptr;
  } else {
    return out <<"nullpointer";
  }
}

// TODO: make sure this class is allowed to copying.
template<class T>
class SmartPointerConst
{
 public:
  explicit SmartPointerConst(const T* ptr = 0) : ptr_(ptr) {}
  virtual ~SmartPointerConst() {}

  const T& operator*() const { return *ptr_; }
  const T* operator->() const { return ptr_; }
  const T*ptr() const { return ptr_; }

  operator bool() const { return ptr_ != 0; }

 protected:
  const T* ptr_;
};

template<class T> inline ostream &operator<<(ostream& out,
                                             const SmartPointerConst<T>& ptr) {
  if (ptr.ptr()) {
    return out << *ptr;
  } else {
    return out <<"nullpointer";
  }
}

template <class T>
class UP : public SmartPointer<T> {
 public:
  explicit UP(T* ptr=0) : SmartPointer<T>(ptr) {}
  ~UP() {}
};

template<class T> inline bool operator==(const UP<T>& s1, const UP<T>& s2) {
  return s1.ptr()==s2.ptr();
}

template<class T>  inline bool operator<(const UP<T>& s1, const UP<T>& s2) {
  return s1.ptr() < s2.ptr();
}

template<class T> inline int Hash(const UP<T> &wp) {
  return (wp.ptr()) ? Hash(*wp) : 0;
}

template <class T>
class UPConst : public SmartPointerConst<T> {
 public:
  explicit UPConst(const T* ptr=0) : SmartPointerConst<T>(ptr) {}
  ~UPConst() {}
};

template<class T> inline bool operator==(const UPConst<T>& s1, const UPConst<T>& s2) {
  return s1.ptr()==s2.ptr();
}

template<class T> inline bool operator<(const UPConst<T>& s1, const UPConst<T>& s2) {
  return s1.ptr()<s2.ptr();
}

template<class T> inline int Hash(const UPConst<T> &wp) {
  return (wp.ptr()) ? Hash(*wp) : 0;
}

template <class T>
class MP : public SmartPointer<T> {
 public:
  MP(T* ptr = 0) : SmartPointer<T>(ptr) {}
  ~MP() {}
};

template <class T> inline bool operator==(const MP<T>& s1, const MP<T>& s2) {
  assert(s1); assert(s2); return *s1 == *s2;
}

template <class T> inline bool operator<(const MP<T>& s1, const MP<T>& s2) {
  assert(s1); assert(s2); return *s1 < *s2;
}

template <class T> inline int Hash(const MP<T> &wp) {
  return (wp.ptr()) ? Hash(*wp) : 0;
}

template <class T>
class MPConst : public SmartPointerConst<T> {
 public:
  explicit MPConst(const T* ptr = 0) : SmartPointerConst<T>(ptr) {}
  ~MPConst() {}
};

template <class T> inline bool operator==(const MPConst<T>&s1,const MPConst<T>&s2) {
  assert(s1); assert(s2); return *s1 == *s2;
}

template <class T> inline bool operator<(const MPConst<T>&s1,const MPConst<T>&s2){
  assert(s1); assert(s2); return *s1 < *s2;
}

template <class T> inline int Hash(const MPConst<T> &wp) {
  return (wp.ptr()) ? Hash(*wp) : 0;
}

template <class T>
class DELP : public SmartPointer<T> {
 public:
  explicit DELP(T* ptr = 0) : SmartPointer<T>(ptr) {}

  ~DELP() {
    delete this->ptr_;
    this->ptr_ = 0;
  }

  const DELP<T>&operator=(DELP<T>& x) {
    delete this->ptr_;
    this->ptr_ = x.ptr_;
    x.ptr_ = 0;
    return *this;
  }

  void set(T* p) {
    delete this->ptr_;
    this->ptr_ = p;
  }

  friend bool operator==(const DELP<T>&s1,const DELP<T>&s2) {
    return *(s1.ptr_)== *(s2.ptr_);
  }

  friend bool operator<(const DELP<T>&s1,const DELP<T>&s2) {
    return *(s1.ptr_) < *(s2.ptr_);
  }

  friend inline int Hash(const DELP<T> &wp) {
    return (wp.ptr_) ? Hash(*wp.ptr_) : 0;
  }

 private:
  DELP(const DELP<T>&x);
};
#endif  // GIZAPP_POINTER_H_
