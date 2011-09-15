/* mw_array_container.h
 * Bring in some STL container functionality for mwArray.
 * Derived from: http://jeffmatherphotography.com/dispatches/2008/08/using-c-iterators-on-matlab-mxarrays/
 * With much guidance from: http://accu.org/index.php/journals/389
 * Ver 0.2
 * Peter H. Li 2011 FreeBSD License
 */

#ifndef SKIP_PTR
#define SKIP_PTR

#include <iterator>


// Still need friend stuff for const?
// See exercise #11: http://accu.org/index.php/journals/389
template <class T, typename elem_type = T> 
class skip_ptr
{
public:
  typedef skip_ptr<T> self_type;
  
  // STL requirements
  typedef std::random_access_iterator_tag iterator_category;
  typedef T         value_type;
  typedef T*        pointer;
  typedef const T*  const_pointer;
  typedef T&        reference;
  typedef const T&  const_reference;
  typedef mwIndex   size_type;
  typedef ptrdiff_t difference_type;
  
  explicit skip_ptr(T *p, difference_type step = -1) : _p(p), _step(step) {}
  
  
  // Core functionality
  T &operator*()  { return *_p; }
  T *operator->() { return &(operator*()); }

  bool operator==(const self_type &other) const 
    { return _p == other._p && _step == other._step; }  
  bool operator<(const self_type &other) const { return _p < other._p; }
  
  self_type operator+(difference_type n) const {
    return skip_ptr(_p + n*_step, _step);
  };
  
  self_type &operator+=(difference_type n) {
    _p += n*_step;
    return *this;
  }
  
  difference_type operator-(self_type &other) const {
    return (_p - other._p) / _step;
  }

  
  // Implemented based on core functionality
  bool operator!=(const self_type &other) const { return !(*this == other); }
  bool operator<=(const self_type &other) const 
    { return *this < other || *this == other;  }
  bool operator>(const self_type &other) const { return !(*this <= other); }
  bool operator>=(const self_type &other) const 
    { return *this > other || *this = other; }

  self_type operator-(difference_type n) { return *this + (-n); }
  self_type &operator-=(difference_type n) { return *this += (-n); }
  self_type &operator++() { return *this +=  1; }
  self_type &operator--() { return *this += -1; }
  
  self_type operator++(int) {
    self_type tmp(*this);
    ++(*this);
    return tmp;
  }
  
  self_type operator--(int) {
    self_type tmp(*this);
    --(*this);
    return tmp;
  }
  
private:
  T *_p;
  difference_type _step;
};


#endif
