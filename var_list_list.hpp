#ifndef VAR_LIST_LIST_H_
#define VAR_LIST_LIST_H_

#include <any>
#include <utility>
#include <vector>

#include "tiny_var_list.hpp"
#include "type_map.hpp"


struct var_list_list {
    /** Pair of MY_TYPE which allows to map static C++ types to runtime MY_TYPE
     * values. */
    using pair_enum_type = std::pair<MY_TYPE, MY_TYPE>;
    /** List of var_list. We use `std::any` to store pointers to var_list<K,V> objects.
     *
     * @note: We could do without the MY_TYPE enum trick and instead bruteforce
     * through the list with by `any_cast`ing every element, but this raises
     * exceptions which need to be caught when a cast fails. To get around this
     * issue, we add enum type pair (translated at compile-time to runtime
     * values) so that we can recognize at runtime what we stored.
     */
    std::vector<std::pair<pair_enum_type, std::any>> my_list;
    //std::vector<std::any> my_list;

    var_list_list() = default;

    /**
     * Appends a var_list<K,V> to my_list
     *
     * @tparam K  The key type
     * @tparam V  The value type
     *
     * @note: We could also use std::move and grab explicit ownership instead of
     * using pointers here? This would mean only accessing the sub-lists through
     * this object (shouldn't be a problem, only requires more access methods).
     */
    template<typename K, typename V>
    void append(var_list<K,V> *list)
    {
        pair_enum_type types{to_my_type<K>(), to_my_type<V>()};
        my_list.push_back({types,list});
    }

    /**
     * Searches for a value with key "key".
     *
     * @param key  the key of the value we are looking for
     *
     * @tparam K  the key type
     * @tparam V  the value type
     *
     * @return a pointer to the value if found, or nullptr
     */
    template <typename K, typename V>
    const V* search(const K &key) const noexcept
    {
        constexpr pair_enum_type types{to_my_type<K>(), to_my_type<V>()};
        for (auto &elem : my_list) {
            // First, check if we can find a list with the requested types
            if (std::get<0>(elem) == types)
            {
                // Now that we know we have a correctly typed `any` list, we can
                // cast it and search it with the key
                auto *casted_list = std::any_cast<var_list<K, V>*>(std::get<1>(elem));
                auto found = casted_list->search(key);
                if (found != nullptr)
                    return found;
            }
        }
        return nullptr;
    }
};


#endif // VAR_LIST_LIST_H_
