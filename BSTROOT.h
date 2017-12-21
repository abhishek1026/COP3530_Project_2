//
// Created by Abhishek on 12/2/2017.
//

#ifndef BSTROOT_H
#define BSTROOT_H

#include <stdexcept>
#include <iostream>
#include <cstdlib>

using namespace std;

namespace cop3530{
    template<class K, class V, bool (*comparison)(const K&, const K&),bool (*equality)(const K&, const K&)>
    class BSTROOT{

    private:

        struct Node{
            K key;
            V value;
            Node* left = nullptr;
            Node* right = nullptr;

            Node(K key, V value){
                this->key = key;
                this->value = value;
            }
        };

        typedef struct Node * NodePtr;


        NodePtr root = nullptr;

        void destroy(NodePtr curr){
            if(curr->left)
                destroy(curr->left);
            if(curr->right)
                destroy(curr->right);
            curr->left = curr->right = nullptr;
            delete curr;
        }

        void do_print_tree(NodePtr curr)const{

            if(curr->left){
                do_print_tree(curr->left);
            }

            cout << "Key: " << curr->key << " ::: " << "Value: " << curr->value << endl;

            if(curr->right){
                do_print_tree(curr->right);
            }

        }


        int do_num_nodes(NodePtr curr)const{

            if(curr == nullptr)
                return 0;

            int left_side = do_num_nodes(curr->left);
            int right_side = do_num_nodes(curr->right);

            return (1 + left_side + right_side);
        }

        int do_height(NodePtr curr)const{

            if(curr->left == nullptr && curr->right == nullptr){
                return 1;
            }

            int left_h = (curr->left) ? do_height(curr->left) : 0;
            int right_h = (curr->right) ? do_height(curr->right) : 0;

            return 1 + ((left_h > right_h) ? left_h : right_h);
        }

        NodePtr rotate_right(NodePtr root){

            NodePtr new_root = root->left;
            root->left = new_root->right;
            new_root->right = root;

            return new_root;
        }

        NodePtr rotate_left(NodePtr root){

            NodePtr new_root = root->right;
            root->right = new_root->left;
            new_root->left = root;

            return new_root;
        }

        NodePtr do_insert(NodePtr root, const K& key, const V& value){
            if(root == nullptr){
                return new Node(key,value);
            }
            if(equality(key,root->key)){
                root->value = value;
                return root;
            }
            if(comparison(root->key,key)){
                root->right = do_insert(root->right,key,value);
                root = rotate_left(root);
            }
            else{
                root->left = do_insert(root->left,key,value);
                root = rotate_right(root);

            }

            return root;

        }

        NodePtr do_remove_root(NodePtr root, const K& key){

            if(root->left == nullptr && root->right == nullptr){
                delete root;
                return nullptr;
            }

            if(root->right && root->left){
                NodePtr successor = root;
                bool keks = (successor->right->left != nullptr);
                if(keks)
                    successor = successor->right;
                while(keks && successor->left->left){
                    successor = successor->left;
                }
                NodePtr grab = (keks) ? successor->left : successor->right;
                root->value = grab->value;
                root->key = grab->key;
                if(!keks){
                    delete successor->right;
                    successor->right = nullptr;
                    return root;
                }
                if(successor->left->right == nullptr){
                    delete successor->left;
                    successor->left = nullptr;
                    return root;
                }
                else{
                    NodePtr delete_this = successor->left;
                    successor->left = delete_this->right;
                    delete delete_this;
                    return root;
                }
            }
            else{
                NodePtr promote_to_root = (root->left == nullptr) ? root->right : root->left;
                root->left = root->right = nullptr;
                delete root;
                return promote_to_root;
            }

        }

        NodePtr do_remove(NodePtr root, const K& key) {

            if (root == nullptr) {
                throw runtime_error("Error! User tried to remove key that does not exist in BSTROOT TreeMap!!!");
            }


            if (equality(root->key,key)) {
                return do_remove_root(root,key);
            }

            if(comparison(root->key,key)){
                root->right = do_remove(root->right, key);
            }

            else{
                root->left = do_remove(root->left, key);
            }

            return root;


        }

        V& do_lookup(NodePtr root, const K& key)const{
            if(root == nullptr){
                throw runtime_error("Error! User tried to search for key that does not exist in BSTROOT TreeMap!!!");
            }
            if(equality(root->key,key)){
                return root->value;
            }
            if(comparison(key,root->key)){
                return do_lookup(root->left,key);
            }
            else{
                return do_lookup(root->right,key);
            }
        }

        bool do_contains(NodePtr root, const K& key)const{
            if(root == nullptr){
                return false;
            }
            if(equality(key,root->key)){
                return true;
            }
            if(comparison(key,root->key)){
                return do_contains(root->left,key);
            }
            else{
                return do_contains(root->right,key);
            }
        }

        NodePtr do_copy(NodePtr src, NodePtr curr){

            if(src == nullptr){
                return nullptr;
            }

            curr = new Node(src->key, src->value);

            curr->left = do_copy(src->left, curr->left);
            curr->right = do_copy(src->right, curr->right);

            return  curr;
        }

    public:
        BSTROOT(){
            cout << "Creating BSTROOT-Based TreeMap!!!" << endl;
        }

        ~BSTROOT() {
            cout << "Destroying BSTROOT-Based TreeMap!!!" << endl;

            if (root) {
                destroy(root);
                root = nullptr;
            }

        }

        BSTROOT(const BSTROOT& src){

            cout << "Creating BSTROOT-Based TreeMap(COPY CTR)!!!" << endl;

            root = do_copy(src.root,root);

        }

        BSTROOT& operator=(const BSTROOT& src){

            cout << "Inside copy-assignment operator overloaded function for BSTROOT-Based TreeMap!!!" << endl;

            if(&src == this){
                return *this;
            }

            clear();

            root = do_copy(src.root,root);

            return *this;

        }

        BSTROOT& operator=(BSTROOT&& src) {

            cout << "Inside move-assignment operator overloaded function for BSTROOT-Based TreeMap!!!" << endl;

            if (&src == this)
                return *this;

            clear();

            root = src.root;

            src.root = nullptr;

            return *this;

        }

        BSTROOT(BSTROOT&& src) {

            cout << "Creating BSTROOT-Based TreeMap(MOVE CTR)!!!" << endl;

            root = src.root;

            src.root = nullptr;

        }

        void insert(const K& key, const V& value){
            root = do_insert(root, key, value);
        }

        V& lookup(const K& key)const{
            return do_lookup(root,key);
        }

        void remove(const K& key){
            root = do_remove(root, key);
        }

        bool contains(const K& key)const{
            return do_contains(root,key);
        }

        bool is_empty()const{
            return (size() == 0);
        }

        bool is_full()const{
            return false;
        }

        size_t size()const{
            return (size_t)do_num_nodes(root);
        }

        void clear(){
            if(root){
                destroy(root);
                root = nullptr;
            }
        }

        size_t height()const{
            if(!root)
                return 0;
            return (size_t)do_height(root);
        }

        int balance()const{
            if(!root)
                return 0;

            int balance = ((root->left) ? do_height(root->left) : 0) - ((root->right) ? do_height(root->right) : 0);

            return balance;

        }

        void print_tree()const{
            if(root){
                do_print_tree(root);
                return;
            }
            cout << "empty tree!" << endl;
            return;
        }



    };


}
#endif
