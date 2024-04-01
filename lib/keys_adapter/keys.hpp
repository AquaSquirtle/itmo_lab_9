#pragma once
#include "iostream"
#include "lib/adaptor_consepts/consepts.hpp"


struct KeysType {};
template<typename Container>
class KeysView {
public:
    KeysView(const Container& container)
    : container_(container)
    {}

    class iterator {
    public:
        using iter = Container::const_iterator;
        using value_type = Container::const_iterator::value_type;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::conditional_t<
                HasBidirectionalIter<Container>
                ,std::bidirectional_iterator_tag,
                std::forward_iterator_tag>;

        iterator(iter begin)
        : iter_(begin)
        {};

        iterator& operator=(const iterator&) = default;

        iterator(const iterator&) = default;

        iterator& operator++() {
            ++iter_;
            return *this;
        }
        iterator operator++(int) {
            auto temp = *this;
            ++(*this);
            return temp;
        }

        iterator& operator--() {
            --iter_;
            return *this;
        }

        iterator operator--(int) {
            auto temp = *this;
            --(*this);
            return temp;
        }

        auto operator*() {
            if constexpr (is_pair<decltype(*iter_)>) {
                return (*iter_).first;
            } else {
                return *iter_;
            }
        }
        iter operator->() {
            return iter_;
        }
        bool operator==(const iterator& other) const {
            return other.iter_ == this->iter_;
        }
        bool operator!=(const iterator& other) const {
            return other.iter_ != this->iter_;
        }
    private:
        iter iter_;
    };
    using const_iterator = iterator;
    iterator begin() const {
        return iterator(container_.begin());
    }

    iterator end() const {
        return iterator(container_.end());
    }

private:
    const Container& container_;
};


template<typename Container>
KeysView<Container> operator | (const Container& container, const KeysType& range_type)
requires (HasForwardIter<Container>)
{
    return KeysView<Container>(container);
}

KeysType keys() {
    return {};
}
