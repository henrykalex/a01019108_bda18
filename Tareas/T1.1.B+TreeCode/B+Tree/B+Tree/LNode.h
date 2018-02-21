//
//  LNode.h
//  B+Tree
//
//  Created by Henry on 21/02/18.
//  Copyright © 2018 A01019108. All rights reserved.
//

#ifndef LNode_h
#define LNode_h

#include "Node.h"

template <typename T, typename D, typename Func = std::less<T>>
struct lnode : public node<T,D,Func> {
    
    std::vector<D> datas;
    
    lnode(unsigned pmin_degree, const Func &pcmp)
    : node<T,D,Func>(pmin_degree, pcmp)
    { }
    
    node<T,D,Func>* split() override {
        auto new_node   = node<T,D,Func>::split();
        auto data_begin = data().begin() + node<T,D,Func>::min_degree;
        new_node->data().assign(
                                std::make_move_iterator(data_begin),
                                std::make_move_iterator(data().end()));
        data().erase(data_begin, datas.end());
        
        new_node->bro = node<T,D,Func>::bro;
        node<T,D,Func>::bro           = new_node;
        return new_node;
    }
    
    node<T,D,Func>* create_node(unsigned min_degree) const override {
        return new lnode(min_degree, node<T,D,Func>::cmp);
    }
    
    bool insert(const T& key, const D& data) override {
        return generic_insert(key, data);
    }
    
    bool insert(T&& key, const D& data) override {
        return generic_insert(std::move(key), data);
    }
    
    bool insert(const T& key, D&& data) override {
        return generic_insert(key, std::move(data));
    }
    
    bool insert(T&& key, D&& data) override {
        return generic_insert(std::move(key), std::move(data));
    }
    
    template<typename TT, typename DD>
    bool generic_insert(TT&& key, DD&& data) {
        auto bound     = node<T,D,Func>::find_bound_index(key);
        bool not_equal = !node<T,D,Func>::index_contains(bound, key);
        
        if (not_equal) {
            node<T,D,Func>::keys.insert(node<T,D,Func>::keys.begin() + bound,
                              std::forward<TT>(key));
            datas.insert(datas.begin() + bound,
                         std::forward<DD>(data));
        }
        return not_equal;
    }
    
    bool leaf() const override {
        return true;
    }
    std::vector<D>& data() override {
        return datas;
    }
    
    bool contains(const T& key) const override {
        auto i = node<T,D,Func>::find_bound_index(key);
        return node<T,D,Func>::index_contains(i, key);
    }
    
    void take_from_rigth_template(node<T,D,Func>* p, unsigned index) {
        auto right = p->child(index + 1);
        
        node<T,D,Func>::keys.push_back(std::move(right->keys[0]));
        data().push_back(std::move((right->data())[0]));
        right->keys.erase(right->keys.begin());
        right->data().erase(right->data().begin());
        
        p->keys[index] = node<T,D,Func>::keys.back();
    }
    
    void take_from_left_template(node<T,D,Func>* p, unsigned index) override {
        auto left = p->child(index - 1);
        
        node<T,D,Func>::keys.insert(node<T,D,Func>::keys.begin(), std::move(left->keys.back()));
        datas.insert(datas.begin(), std::move(left->data().back()));
        left->keys.pop_back();
        left->data().pop_back();
        
        p->keys[index - 1] = left->keys.back();
    }
    
    void merge_template(node<T,D,Func> *p, unsigned index) override {
        auto rigth = p->child(index + 1);
        p->keys.erase(p->keys.begin() + index);
        p->childs().erase(p->childs().begin() + index + 1);
        
        node<T,D,Func>::keys.insert(node<T,D,Func>::keys.end(),
                          std::make_move_iterator(rigth->keys.begin()),
                          std::make_move_iterator(rigth->keys.end()));
        
        datas.insert(datas.end(),
                     std::make_move_iterator(rigth->data().begin()),
                     std::make_move_iterator(rigth->data().end()));
        
        node<T,D,Func>::bro = rigth->bro;
        delete rigth;
    }
    
    
    void remove(const T& key) override {
        auto i = node<T,D,Func>::find_bound_index(key);
        if (node<T,D,Func>::index_contains(i, key)) {
            datas.erase(datas.begin() + i);
            node<T,D,Func>::keys.erase(node<T,D,Func>::keys.begin() + i);
        }
    }
    
    void destroy() override {
        delete this;
    }
};

#endif /* LNode_h */
