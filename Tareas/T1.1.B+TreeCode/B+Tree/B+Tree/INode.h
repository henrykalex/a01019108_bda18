//
//  InNode.h
//  B+Tree
//
//  Created by Henry on 20/02/18.
//  Copyright © 2018 A01019108. All rights reserved.
//

#ifndef INode_h
#define INode_h

#include "Node.h"
template <typename T, typename D, typename Func = std::less<T>>
struct inode : public node<T,D,Func> {
    
    std::vector<node<T,D,Func>*> children;
    
    inode(unsigned pmin_degree, const Func &pcmp)
    : node<T,D,Func>(pmin_degree, pcmp)
    { }
    
    node<T,D,Func>* split() override {
        auto new_node    = node<T,D,Func>::split();
        auto child_begin = children.begin() + node<T,D,Func>::min_degree;
        
        new_node->childs().assign(
                                  std::make_move_iterator(child_begin),
                                  std::make_move_iterator(childs().end()));
        children.erase(child_begin, children.end());
        return new_node;
    }
    
    node<T,D,Func>* create_node(unsigned min_degree) const override {
        return new inode(min_degree, node<T,D,Func>::cmp);
    }
    
    bool leaf() const override {
        return false;
    }
    
    std::vector<node<T,D,Func>*>& childs() override {
        return children;
    }
    
    node<T,D,Func>* child(unsigned i) const override {
        return children[i];
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
        auto index = node<T,D,Func>::find_bound_index(key);
        if (children[index]->full()) {
            node<T,D,Func>::split_child(index);
            index += node<T,D,Func>::cmp(node<T,D,Func>::keys[index], key);
        }
        return children[index]->insert(
                                       std::forward<TT>(key),
                                       std::forward<DD>(data));
    }
    
    bool contains(const T& key) const override {
        auto i = node<T,D,Func>::find_bound_index(key);
        return children[i]->contains(key);
    }
    
    void take_from_rigth_template(node<T,D,Func>* p, unsigned index) override {
        auto right = p->child(index + 1);
        
        node<T,D,Func>::keys.push_back(std::move(p->keys[index]));
        p->keys[index] = std::move(right->keys[0]);
        right->keys.erase(right->keys.begin());
        
        children.push_back(right->child(0));
        right->childs().erase(right->childs().begin());
    }
    
    void take_from_left_template(node<T,D,Func>* p, unsigned index) override {
        auto left = p->child(index - 1);
        
        node<T,D,Func>::keys.insert(node<T,D,Func>::keys.begin(), std::move(p->keys[index - 1]));
        p->keys[index - 1] = std::move(left->keys.back());
        children.insert(children.begin(), left->childs().back());
        
        left->keys.pop_back();
        left->childs().pop_back();
    }
    
    void merge_template(node<T,D,Func> *p, unsigned index) override {
        auto rigth = p->child(index + 1);
        
        node<T,D,Func>::keys.push_back(std::move(p->keys[index]));
        p->keys.erase(p->keys.begin() + index);
        p->childs().erase(p->childs().begin() + index + 1);
        
        children.insert(children.end(),
                        std::make_move_iterator(rigth->childs().begin()),
                        std::make_move_iterator(rigth->childs().end()));
        
        node<T,D,Func>::keys.insert(node<T,D,Func>::keys.end(),
                          std::make_move_iterator(rigth->keys.begin()),
                          std::make_move_iterator(rigth->keys.end()));
        
        delete rigth;
    }
    
    unsigned fill(unsigned index) {
        auto deg = child(index)->min_degree;
        if (index != node<T,D,Func>::size()
            && deg <= children[index + 1]->size()) {
            take_from_rigth(index);
        }
        else if (index != 0
                 && deg <= children[index - 1]->size()) {
            take_from_left(index);
        }
        else {
            if (index == node<T,D,Func>::size()) {
                --index;
            }
            merge(index);
        }
        return index;
    }
    void take_from_rigth(unsigned index) override {
        children[index]->take_from_rigth_template(this, index);
    }
    
    void take_from_left(unsigned index) override {
        children[index]->take_from_left_template(this, index);
    }
    
    void merge(unsigned index) override {
        children[index]->merge_template(this, index);
    }
    
    void remove(const T& key) override {
        auto i   = node<T,D,Func>::find_bound_index(key);
        auto deg = child(i)->min_degree;
        if (child(i)->size() < deg) {
            i = fill(i);
        }
        child(i)->remove(key);
    }
    
    void destroy() override {
        for (auto c : children) {
            c->destroy();
        }
        delete this;
    }
    
};
#endif /* INode_h */
