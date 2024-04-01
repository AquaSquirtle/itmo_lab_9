#pragma once
#include "iostream"

template<typename Predicate>
struct FilterType {
    Predicate func_;
    FilterType(Predicate func)
            : func_(func)
    {}
};

template<typename Container, typename Predicate>
class FilterView {
public:
    FilterView(const Container& container, Predicate pred)
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
        iterator(iter begin, iter end, Predicate pred)
        : iter_(begin)
        , end_(end)
        , pred_(pred)
        {
            find_next();
        };

        iterator& operator=(const iterator&) = default;

        iterator(const iterator&) = default;

        iterator& operator++() {
            ++iter_;
            find_next();
            return *this;
        }
        iterator operator++(int) {
            auto temp = *this;
            ++(*this);
            return temp;
        }
        iterator& operator--() {
            --iter_;
            find_prev();
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
        void find_next() {
            while (iter_ != end_ && !pred_(*iter_)) {
                ++iter_;
            }
        }
        void find_prev() {
            while (!pred_(*iter_)) {
                --iter_;
            }
        }
        iter iter_;
        iter end_;
        Predicate pred_;
    };

public:
    using const_iterator = iterator;
    iterator begin() const {
        return iterator(container_.begin(), container_.end(), pred_);
    }
    iterator end() const {
        return iterator(container_.end(), container_.end(), pred_);
    }
private:
    const Container& container_;
    Predicate pred_;
};


template<typename Container, typename Predicate>
FilterView<Container, Predicate> operator | (const Container& container, const FilterType<Predicate>& range_type)
requires (HasForwardIter<Container>)
{
    return FilterView<Container, Predicate>(container, range_type.func_);
}

template<typename Predicate>
FilterType<Predicate> filter(Predicate func) {
    return FilterType<Predicate>(func);
}
