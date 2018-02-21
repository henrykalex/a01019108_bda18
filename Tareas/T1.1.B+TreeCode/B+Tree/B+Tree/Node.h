//
//  Node.h
//  B+Tree
//
//  Created by Henry on 20/02/18.
//  Copyright © 2018 A01019108. All rights reserved.
//

#ifndef Node_h
#define Node_h
template <typename T, typename D, typename Func = std::less<T>>
struct node {
    unsigned min_degree;
    std::vector<T> keys;
    node           *bro;
    const Func     &cmp;
    
    node(unsigned pmin_degree, const Func &pcmp)
    : min_degree(pmin_degree),
    bro(nullptr),
    cmp(pcmp)
    { }
    
    virtual node* split() {
        auto new_node  = create_node(min_degree);
        auto key_begin = keys.begin() + min_degree;
        
        new_node->keys.assign(
                              std::make_move_iterator(key_begin),
                              std::make_move_iterator(keys.end()));
        keys.erase(key_begin, keys.end());
        return new_node;
    }
    
    bool index_contains(unsigned index, const T &key) const {
        return index < keys.size()
        && !cmp(keys[index], key)
        && !cmp(key, keys[index]);
    }
    
    bool full() const {
        return keys.size() == (2 * min_degree - 1);
    }
    
    unsigned find_bound_index(const T &key) const {
        auto bound = std::lower_bound(keys.begin(), keys.end(), key, cmp);
        return std::distance(keys.begin(), bound);
    }
    
    void split_child(unsigned i) {
        auto left     = child(i);
        auto new_node = left->split();
        
        keys.insert(keys.begin() + i, left->keys.back());
        childs().insert(childs().begin() + i + 1, new_node);
        if (!left->leaf()) {
            left->keys.pop_back();
        }
    }
    
    unsigned size() {
        return keys.size();
    }
    
    virtual void take_from_rigth(unsigned index) {
        throw std::runtime_error("take_from_rigth(unsigned) is unsupported");
    }
    virtual void take_from_left(unsigned index) {
        throw std::runtime_error("take_from_left(unsigned) is unsupported");
    }
    virtual void merge(unsigned index) {
        throw std::runtime_error("merge(unsigned) is unsupported");
    }
    virtual unsigned fill(unsigned index) {
        throw std::runtime_error("child(unsigned) is unsupported");
    }
    virtual std::vector<node*>& childs() {
        throw std::runtime_error("childs() is unsupported");
    }
    virtual std::vector<D>& data() {
        throw std::runtime_error("data() is unsupported");
    }
    virtual node* child(unsigned i) const {
        throw std::runtime_error("child(unsigned) is unsupported");
    }
    virtual bool insert_index(const T& key, const D& data) {
        throw std::runtime_error("insert_index(const T&, const D&) is unsupported");
    }
    
    
    virtual void merge_template(node *p, unsigned index) = 0;
    virtual void take_from_rigth_template(node* parent, unsigned index) = 0;
    virtual void take_from_left_template(node* parent, unsigned index) = 0;
    virtual node* create_node(unsigned min_degree) const = 0;
    virtual bool leaf() const = 0;
    virtual void remove(const T& key) = 0;
    virtual bool insert(const T& key, const D& data) = 0;
    virtual bool insert(T&& key, const D& data) = 0;
    virtual bool insert(const T& key, D&& data) = 0;
    virtual bool insert(T&& key, D&& data) = 0;
    virtual bool contains(const T& key) const = 0;
    virtual void destroy() = 0;
    
};

#endif /* Node_h */
