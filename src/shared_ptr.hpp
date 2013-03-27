/**
 * @file  shared_ptr.hpp
 * @brief shared_ptr is a minimal implementation of smart pointer, a subset of the C++11 std::shared_ptr or boost::shared_ptr.
 *
 *  This file includes "boost/shared_ptr.hpp" if LOGGER_USE_BOOST_SHARED_PTR is defined,
 * or <memory> (or <tr1/memory>) when C++11 (or experimental C++0x) is available,
 * and imports the symbol "shared_ptr" inside the current namespace (ie. Log::shared_ptr).
 *  If no std::shared_ptr is available, it defines a minimal shared_ptr implementation.
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#pragma once


namespace Log
{

//
// Try to detect the better shared_ptr to use, and then imports the symbol in the current namespace
// => if you include this "shared_ptr.hpp" file inside your own namespace you will
//    get a kind of universal easy to use "shared_ptr" type
//
#ifdef LOGGER_USE_BOOST_SHARED_PTR
    // Use Boost only if explicitly told
    #include <boost/shared_ptr.hpp>
    using boost::shared_ptr;
// Detect whether the compiler supports C++11 shared_ptr or its TR1 pre-version.
#elif (defined(__GNUC__) && (__GNUC__ > 4 || \
      (__GNUC__ == 4 && __GNUC_MINOR__ > 2)) && \
      defined(__GXX_EXPERIMENTAL_CXX0X__))
    // GCC 4.3 and following have std::shared_ptr support when called with -std=c++0x (or -std=c++11 starting with GCC 4.7)
    #include <memory>
    using std::shared_ptr
#elif (defined(__GNUC__) && (__GNUC__ == 4) && \
      defined(__GXX_EXPERIMENTAL_CXX0X__))
    // GCC 4.0/4.1/4.2 have std::shared_ptr support when when called with -std=c++0x
    #include <tr1/memory>
    using std::tr1:shared_ptr;
#elif defined(__clang__)
    // Clang 2.9 and above ? What is the most appropriate feature to check for shared_ptr support in Clang ?
    __has_feature(cxx_nullptr)
    #include <memory>
    using std::shared_ptr;
#elif defined(_MSC_VER) && (_MSC_VER >= 1600)
    // Visual Studio 2010 compile by default in C++11 mode
    #include <memory>
    using std::shared_ptr;
#elif defined(_MSC_VER) && (_MSC_VER >= 1500)
    // Visual Studio 2008 : beware, TR1 is provided with the Service Pack 1 only !
    #include <memory>
    using std::tr1:shared_ptr;
#else


/**
 * @brief minimal implementation of smart pointer, a subset of the C++11 std::shared_ptr or boost::shared_ptr.
 *
 * shared_ptr is a smart pointer retaining ownership of an object through a provided pointer,
 * and sharing this ownership with a reference counter.
 * It destroys the object when the last shared pointer pointing to it is destroyed or reset.
 */
template<class T>
class shared_ptr
{
public:
    /// @brief Default constructor
    shared_ptr(void) throw() : // nothrow
        px(NULL),
        pn(NULL)
    {
    }
    /// @brief Constructor with the provided pointer to manage
    explicit shared_ptr(T* p) : // throw std::bad_alloc
        px(p),
        pn(NULL)
    {
        acquire();
    }
    /// @brief Copy constructor (used by the copy-and-swap idiom)
    shared_ptr(const shared_ptr& ptr) : // throw std::bad_alloc
        px(ptr.px),
        pn(ptr.pn)
    {
        acquire();
    }
    /// @brief Assignment operator using the copy-and-swap idiom (copy constructor and swap method)
    shared_ptr& operator=(shared_ptr ptr) throw() // nothrow
    {
        swap(ptr);
        return *this;
    }
    /// @brief the destructor release its ownership
    inline ~shared_ptr(void) throw() // nothrow
    {
        release();
    }
    /// @brief this reset release its ownership
    inline void reset(void) throw() // nothrow
    {
        release();
    }
    /// @brief this reset release its ownership and re-acquire another one
    void reset(T* p) throw() // nothrow
    {
        release();
        px = p;
        acquire();
    }

    /// @brief Swap method for the copy-and-swap idiom (copy constructor and swap method)
    void swap(shared_ptr& lhs) throw() // nothrow
    {
        std::swap(px, lhs.px);
        std::swap(pn, lhs.pn);
    }

    // reference counter operations :
    inline operator bool() const throw() // nothrow
    {
        return (0 < use_count());
    }
    inline bool unique(void)  const throw() // nothrow
    {
        return (1 == use_count());
    }
    long use_count(void)  const throw() // nothrow
    {
        long count = 0;
        if (NULL != pn)
        {
            count = *pn;
        }
        return count;
    }

    // underlying pointer operations :
    inline T& operator*()  const throw() // nothrow
    {
        return *px;
    }
    inline T* operator->() const throw() // nothrow
    {
        return px;
    }
    inline T* get(void)  const throw() // nothrow
    {
        return px;
    }

    // comparaison operators
    inline bool operator== (const shared_ptr& ptr) const
    {
        return (px == ptr.px);
    }
    inline bool operator== (const T* p) const
    {
        return (px == p);
    }
    inline bool operator!= (const shared_ptr& ptr) const
    {
        return (px != ptr.px);
    }
    inline bool operator!= (const T* p) const
    {
        return (px != p);
    }
    inline bool operator<= (const shared_ptr& ptr) const
    {
        return (px <= ptr.px);
    }
    inline bool operator<= (const T* p) const
    {
        return (px <= p);
    }
    inline bool operator< (const shared_ptr& ptr) const
    {
        return (px < ptr.px);
    }
    inline bool operator< (const T* p) const
    {
        return (px < p);
    }
    inline bool operator>= (const shared_ptr& ptr) const
    {
        return (px >= ptr.px);
    }
    inline bool operator>= (const T* p) const
    {
        return (px >= p);
    }
    inline bool operator> (const shared_ptr& ptr) const
    {
        return (px > ptr.px);
    }
    inline bool operator> (const T* p) const
    {
        return (px > p);
    }

private:
    /// @brief acquire/share the ownership of the px pointer, initializing the reference counter
    void acquire(void)
    {
        if (NULL != px)
        {
            if (NULL == pn)
            {
                try
                {
                    pn = new long(1);
                }
                catch (std::bad_alloc&)
                {
                    delete px;
                    throw;
                }
            }
            else
            {
                ++(*pn);
            }
        }
    }

    /// @brief release the ownership of the px pointer, destroying the object when appropriate
    void release(void) throw() // nothrow
    {
        if (NULL != pn)
        {
            --(*pn);
            if (0 == *pn)
            {
                delete px;
                px = NULL;
                delete pn;
                pn = NULL;
            }
        }
    }

private:
    T*      px; //!< Native pointer
    long*   pn; //!< Reference counter
};


#endif // LOGGER_USE_BOOST_SHARED_PTR

} // namespace Log
