#ifndef MBGL_UTIL_STD
#define MBGL_UTIL_STD

#include <memory>
#include <type_traits>
#include <utility>

namespace mbgl {
namespace util {

template <typename Container, typename ForwardIterator, typename Predicate>
void erase_if(Container &container, ForwardIterator it, const ForwardIterator end, Predicate pred) {
    while (it != end) {
        if (pred(*it)) {
            container.erase(it++);
        } else {
            ++it;
        }
    }
}

template <typename Container, typename Predicate>
void erase_if(Container &container, Predicate pred) {
    erase_if(container, container.begin(), container.end(), pred);
}

// Use this for containers that only provide an erase_after function. Make sure to pass in a
// before_begin iterator (see below), otherwise, it's going to fail to erase the first element.
template <typename Container, typename ForwardIterator, typename Predicate>
void erase_after_if(Container &container, ForwardIterator it, const ForwardIterator end, Predicate pred) {
    for (ForwardIterator next; it != end && (next = std::next(it)) != end; ++it) {
        if (pred(*next)) {
            container.erase_after(it);
        }
    }
}

template <typename Container, typename Predicate>
void erase_after_if(Container &container, Predicate pred) {
    erase_after_if(container, container.before_begin(), container.end(), pred);
}

} // namespace util
} // namespace mbgl

#endif
