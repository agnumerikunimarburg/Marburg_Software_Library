// implementation of MathTL::Vector inline functions

#include <io/vector_io.h>
#include <cassert>
#include <algorithm>

namespace MathTL
{
  template <class C>
  inline
  Vector<C>::Vector()
    : values_(0), size_(0)
  {
  }
  
  template <class C>
  inline
  Vector<C>::Vector(const size_type s, const bool initialize)
    : values_(0), size_(s)
  {
    if (s > 0)
      {
	values_ = new C[s]; // calls C()
	
	if (initialize)
	  *this = 0;
      }
  }

  template <class C>
  inline
  Vector<C>::Vector(const Vector<C>& v)
    : values_(0), size_(v.size())
  {
    if (size_ > 0)
      {
	values_ = new C[size_];
	std::copy(v.begin(), v.end(), begin());
      }
  }
 
  template <class C>
  inline
  Vector<C>::~Vector()
  {
    if (values_ != 0)
      delete [] values_;
  }
  
  template <class C>
  inline
  const typename Vector<C>::size_type
  Vector<C>::size() const
  {
    return size_;
  }

  template <class C>
  void Vector<C>::resize(const size_type s, const bool initialize)
  {
    if (s == 0)
      {
	if (values_ != 0) delete [] values_;
	values_ = 0;
	size_ = 0;
      }
    else
      {
	if (size_ != s)
	  {
	    if (values_ != 0) delete [] values_;
	    values_ = new C[s];
	    size_ = s;
	  }

	if (initialize)
	  *this = 0;
      }
  }

  template <class C>
  inline
  const C Vector<C>::operator [] (const size_type i) const
  {
    assert(i < size_);
    return values_[i];
  }

  template <class C>
  inline
  const C Vector<C>::operator () (const size_type i) const
  {
    assert(i < size_);
    return values_[i];
  }

  template <class C>
  inline
  C& Vector<C>::operator [] (const size_type i)
  {
    assert(i < size_);
    return values_[i];
  }

  template <class C>
  inline
  C& Vector<C>::operator () (const size_type i)
  {
    assert(i < size_);
    return values_[i];
  }

  template <class C>
  inline
  typename Vector<C>::const_iterator
  Vector<C>::begin() const
  {
    return &values_[0];
  }

  template <class C>
  inline
  typename Vector<C>::iterator
  Vector<C>::begin()
  {
    return &values_[0];
  }

  template <class C>
  inline
  typename Vector<C>::const_iterator
  Vector<C>::end() const
  {
    return &values_[size_];
  }

  template <class C>
  inline
  typename Vector<C>::iterator
  Vector<C>::end()
  {
    return &values_[size_];
  }

  template <class C>
  inline
  Vector<C>& Vector<C>::operator = (const C c)
  {
    assert(size() > 0);
    std::fill(begin(), end(), c);
    return *this;
  }

  template <class C>
  bool Vector<C>::operator == (const Vector<C>& v)
  {
    if (size_ != v.size()) return false;

    for (unsigned int i(0); i < size_; i++)
      if (v[i] != values_[i]) return false;

    return true;
  }

  template <class C>
  inline
  bool Vector<C>::operator != (const Vector<C>& v)
  {
    return !((*this) == v);
  }

  template <class C>
  void Vector<C>::add(const Vector<C>& v)
  {
    assert(size_ > 0);
    assert(size_ == v.size());

    iterator it(begin()), itend(end());
    const_iterator itv(v.begin());
    while(it != itend)
      *it++ += *itv++;
  }
   
  template <class C>
  void Vector<C>::sadd(const C s, const Vector<C>& v)
  {
    assert(size_ > 0);
    assert(size_ == v.size());

    iterator it(begin()), itend(end());
    const_iterator itv(v.begin());
    while(it != itend)
      {
	*it = s*(*it) + *itv++;
	++it;
      }
  }
  
  template <class C>
  void Vector<C>::scale(const C s)
  {
    assert(size_ > 0);
    
    iterator it(begin()), itend(end());
    while(it != itend)
      *it++ *= s;
  }

  template <class C>
  Vector<C>& Vector<C>::operator += (const Vector<C>& v)
  {
    add(v); // handles the assertions
    return *this;
  }

  template <class C>
  Vector<C>& Vector<C>::operator -= (const Vector<C>& v)
  {
    assert(size_ > 0);
    assert(size_ == v.size());
    
    iterator it(begin()), itend(end());
    const_iterator itv(v.begin());
    while(it != itend)
      *it++ -= *itv++;
  }
   
  template <class C>
  Vector<C>& Vector<C>::operator *= (const C s)
  {
    scale(s); // handles the assertions
    return *this;
  }

  template <class C>
  Vector<C>& Vector<C>::operator /= (const C s)
  {
    // we don't catch the division by zero exception here!
    return (*this *= 1.0/s);
  }

  template <class C>
  inline
  std::ostream& operator << (std::ostream& os, const Vector<C>& v)
  {
    print_vector(v, os);
  }
}
