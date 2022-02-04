#ifndef TINY_VAR_LIST_H_
#define TINY_VAR_LIST_H_

#include <unordered_map>

/**
 * A very simple and minimal `std::unordered_map` wrapper with append and search
 * function.
 *
 * @tparam K  the key type for the list
 * @tparam V  the mapped type for the list
 */
template <typename K, typename V>
struct var_list {
    using key_type = const K;
    using value_type = V;
    using key_value_type = typename std::unordered_map<K,V>::value_type;
    std::unordered_map<K,V> my_list;

    var_list() = default;

    var_list(std::initializer_list<key_value_type> l) : my_list{l} {}

    /**
     * Appends a pair of type key_value_type to my_list
     *
     * @param new_var the pair to be appended
     *
     * @note: Again, we can use std::move to get ownership instead.
     * This might be the most sensible choice in this case?
     *
     * void append(key_value_type new_var)
     * { my_list.insert(new_var); }
     */
    void append(key_value_type &&new_var) {
         my_list.insert(std::move(new_var));
    }

    /**
     * @param key  The (supposed unique) key used to search the value
     *
     * @return The pointer to the value if found, nullptr otherwise
     */
    const V* search(key_type &key) const noexcept {
        auto found = my_list.find(key);
        if (found != my_list.end())
            return &found->second;
        return nullptr;
    }
};


#endif // TINY_VAR_LIST_H_
