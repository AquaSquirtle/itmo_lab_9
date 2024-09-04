#pragma once
#include "iostream"
#include "lib/adaptor_consepts/consepts.hpp"




struct DropType {
    size_t n_;
    DropType(size_t n)
            : n_(n)
    {}
};

template<typename Container>
class DropView {
public:
    DropView(const Container& container, size_t n)
            : container_(container)
            , n_(n)
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
            return *iter_;
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
        auto temp = container_.begin();
        for (int i = 0; i < n_; ++i) {
            ++temp;
            if (temp == container_.end()) {
                break;
            }
        }
        return iterator(temp);
    }

    iterator end() const {
        return iterator(container_.end());
    }

private:
    const Container& container_;
    size_t n_;
};


template<typename Container>
DropView<Container> operator | (const Container& container, const DropType& range_type)
requires (HasForwardIter<Container>)
{
    return DropView<Container>(container, range_type.n_);
}

DropType drop(size_t n) {
    return {n};
}
