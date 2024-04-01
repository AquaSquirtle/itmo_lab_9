#pragma once
#include "iostream"
#include "lib/adaptor_consepts/consepts.hpp"

template<typename Predicate>
struct TransformType {
    Predicate func_;
    TransformType(Predicate func)
    : func_(func)
    {}
};

template<typename Container, typename Predicate>
class TransformView {
public:
    TransformView(const Container& container, Predicate pred)
    : container_(container)
    , pred_(pred)
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
        iterator(iter begin, Predicate pred)
        : iter_(begin)
        , pred_(pred)
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
            return pred_(*iter_);
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
        Predicate pred_;
    };

    using const_iterator = iterator;
    iterator begin() const {
        return iterator(container_.begin(), pred_);
    }

    iterator end() const {
        return iterator(container_.end(), pred_);
    }

private:
    const Container& container_;
    Predicate pred_;
};



template<typename Container,typename Predicate>
TransformView<Container, Predicate>
operator | (const Container& container, const TransformType<Predicate>& range_type)
requires (HasForwardIter<Container>)
{
    return TransformView<Container, Predicate>(container, range_type.func_);
}

template<typename Predicate>
TransformType<Predicate> transform(Predicate func) {
    return TransformType<Predicate>(func);
}
