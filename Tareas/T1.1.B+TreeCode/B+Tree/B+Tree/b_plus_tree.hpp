//
//  b_plus_tree.hpp
//  B+Tree
//
//  Created by Henry on 20/02/18.
//  Copyright © 2018 A01019108. All rights reserved.
//  Based on: https://codereview.stackexchange.com/questions/134487/in-memory-b-tree-in-c

#ifndef b_plus_tree_hpp
#define b_plus_tree_hpp

#include <iostream>

#include <vector>
#include <algorithm>

#include "Node.h"
#include "INode.h"
#include "LNode.h"

namespace mds {
    template <typename T, typename D, typename Func = std::less<T>>
    class b_plus_tree {
        
        Func     cmp;
        unsigned leaf_degree;
        unsigned in_degree;
        node<T,D,Func>     *root;
        
    public:
        b_plus_tree(unsigned l_degree, unsigned i_degree, Func pcmp,
                    std::initializer_list<std::pair<T, D>> list)
        : cmp(pcmp),
        root(new lnode<T,D,Func>(leaf_degree, cmp)),
        in_degree(i_degree),
        leaf_degree(l_degree)
        {
            for (auto e : list) {
                insert(e.first, e.second);
            }
        }
        
        b_plus_tree(unsigned l_degree, unsigned i_degree,
                    std::initializer_list<std::pair<T, D>> list)
        : b_plus_tree(l_degree, i_degree, Func(), list)
        { }
        
        b_plus_tree(unsigned l_degree, unsigned i_degree, Func f)
        : b_plus_tree(l_degree, i_degree, f, {})
        { }
        
        b_plus_tree(unsigned l_degree, unsigned i_degree)
        : b_plus_tree(l_degree, i_degree, Func())
        { }
        
        b_plus_tree(unsigned degree, std::initializer_list<std::pair<T, D>> list)
        : b_plus_tree(degree, (3 * degree) / 2, list)
        { }
        
        b_plus_tree(unsigned degree, Func f)
        : b_plus_tree(degree, (3 * degree) / 2, Func())
        { }
        
        b_plus_tree(unsigned degree)
        : b_plus_tree(degree, Func())
        { }
        
        ~b_plus_tree() {
            root->destroy();
        }
        
        void remove(const T& key) {
            root->remove(key);
            if (root->size() == 0
                && !root->leaf()) {
                auto tmp = root;
                root = root->child(0);
                delete tmp;
            }
        }
        
        template<typename TT, typename DD>
        bool insert(TT&& key, DD&& data) {
            if (root->full()) {
                auto new_root = new inode<T,D,Func>(in_degree, cmp);
                new_root->childs().push_back(root);
                root = new_root;
                new_root->split_child(0);
            }
            return root->insert(
                                std::forward<TT>(key),
                                std::forward<DD>(data));
        }
        
        template<typename F>
        void walk(F func) const {
            std::cout << "Walk\n";
            auto n = root;
            for(auto const& value: n->keys) {
                std::cout << "root: " << value << std::endl;
            }
            for(auto const& value: ((inode<T,D,Func>*)n)->children) {
                std::cout << "children: " << value << std::endl;
                for(auto const& value: value->keys) {
                    std::cout << "keys: " << value << std::endl;
                }
            }
            while (!n->leaf()) {
                n = n->child(0);
                std::cout << "isLeaf: " << n->leaf()  << std::endl;
                for(auto const& value: n->keys) {
                    std::cout << "child: " << value << std::endl;
                }
            }
            while (n != nullptr) {
                for (auto i = 0u; i < n->size(); ++i) {
                    func(n->keys[i], (n->data())[i]);
                }
                n = n->bro;
            }
        }
        
        bool contains(const T& key) {
            return root->contains(key);
        }
        
    };
}

#endif /* b_plus_tree_hpp */
