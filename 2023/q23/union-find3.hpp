#ifndef UNION_FIND_HPP
#define UNION_FIND_HPP 1
#include <algorithm>
namespace union_find {
    template <typename V, typename I>
    static I find_root(V &v, I i) {
        auto j = i;
        while(v[j].parent != j)
            j = v[j].parent;
        for (;;) {
            auto next = v[i].parent;
            if (next == j)
                return j;
            v[i].parent = j;
            i = next;
        }
    }
    template <typename IndexType = unsigned, typename RankType = unsigned>
	struct Vertex {
	    typedef IndexType index_type;
	    typedef RankType rank_type;
	    IndexType parent;
	    RankType rank;
	    Vertex(IndexType parent = 0):parent{parent}, rank{0} {}
	};
    template <typename V, typename I>
    static I union_by_rank(V &v, I i, I j) {
        i = find_root(v, i);
        j = find_root(v, j);
        if (i == j)
            return i;
        if (v[j].rank > v[i].rank)
            std::swap(i, j);
        else if (v[i].rank == v[j].rank)
            ++v[i].rank;
	v[j].parent = i;
        return i;
    }
    template <typename IndexType = unsigned, typename SizeType = unsigned>
	struct SizedVertex {
	    typedef IndexType index_type;
	    typedef SizeType size_type;
	    IndexType parent;
	    SizeType size;
	    SizedVertex(IndexType parent = 0, SizeType size = 1):parent{parent}, size{size} {}
	};
    template <typename V, typename I>
    static I union_by_size(V &v, I i, I j) {
        i = find_root(v, i);
        j = find_root(v, j);
        if (i == j)
            return i;
        if (v[j].size > v[i].size)
            std::swap(i, j);
	v[j].parent = i;
	v[i].size += v[j].size;
        return i;
    }
};
// using namespace union_find;
#endif

