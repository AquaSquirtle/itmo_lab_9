#pragma once
#include "iostream"

template<typename Pair>
concept is_pair = requires (Pair pair) {
    pair.first;
    pair.second;
};

template<typename Container>
concept HasBidirectionalIter =
    std::is_same<typename Container::iterator::iterator_category, std::bidirectional_iterator_tag>() == true ||
    std::is_same<typename Container::iterator::iterator_category, std::random_access_iterator_tag>() == true ||
    std::is_same<typename Container::iterator::iterator_category, std::contiguous_iterator_tag>() == true;

template<typename Container>
concept HasForwardIter =
        HasBidirectionalIter<Container> ||
        std::is_same<typename Container::iterator::iterator_category, std::forward_iterator_tag>() == true;