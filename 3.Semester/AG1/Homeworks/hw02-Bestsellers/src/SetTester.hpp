// #PRIOR_NO
// #EX_BEGIN
//
// Created by bardanik on 05/11/22.
//

#ifndef HW02_BESTSELLERS_SETTESTER_HPP
#define HW02_BESTSELLERS_SETTESTER_HPP

#include <iostream>
#include "Bestsellers.hpp"
#include "Set.hpp"

using namespace std;

struct SetTester {

    static void runAll(){
        BVS_ShouldInsertAndContainKeysTest();
        BVS_ShouldInsertAndFindWithSameKeysTest();
        BVS_ShouldNotContainInEmptyTree();
        BVS_ShouldFindMinAndMaxOfTreeNodeTest();
        BVS_ShouldHaveRightStructureForBSTTest();
        BVS_CheckIfParentsAreValidTest();
        BVS_PredShouldPrintValuesInDescendingOrderTest();
        BVS_SuccShouldPrintValuesInAscendingOrderTest();
        BVS_DeleteTest();
        BVS_PairKeyTypeTest();
        AVL_ShouldHaveRightDepthsAfterInsertTest();
        AVL_ShouldHaveValidDepthsAfterDeleteTest();
        AVL_SingleRotationTest();
        BVS_ShouldKeepValidSizeInEachNodeAfterInsertTest();
        BVS_ShouldKeepValidSizeInEachNodeAfterDeleteTest();
        BVS_ShouldReturnValidNodeWithAtMethodTest1();
        BVS_ShouldReturnValidIndexWithIndexOfMethodTest();
        BVS_ShouldReturnValidNodeWithAteMethodTest2();
    }

    static void layout() {
        cout << '\n' << __func__ << " -> START" << endl;

        cout << __func__ << " ->    OK" << '\n' << endl;
    }

    static void BVS_ShouldInsertAndContainKeysTest() {
        cout << '\n' << __func__ << " -> START" << endl;

        Set<int> s;
        assert(s.isEmpty());
        s.InsertKey(5);
        s.InsertKey(6);
        s.InsertKey(6);
        s.InsertKey(1);
        s.InsertKey(7);
        s.InsertKey(3);

        assert(s.Contains(5));
        assert(s.Contains(6));
        assert(s.Contains(7));
        assert(s.Contains(1));
        assert(s.Contains(3));

        assert(s.size() == 5);
        assert(!s.isEmpty());


        cout << __func__ << " ->    OK" << '\n' << endl;
    }

    static void BVS_ShouldInsertAndFindWithSameKeysTest() {
        cout << '\n' << __func__ << " -> START" << endl;
        Set<int> s;

        s.InsertKey(5);
        s.InsertKey(6);
        s.InsertKey(6);
        s.InsertKey(1);
        s.InsertKey(7);
        s.InsertKey(3);

        assert(s.Find(5)->key_ == 5);
        assert(s.Find(6)->key_ == 6);
        assert(s.Find(7)->key_ == 7);
        assert(s.Find(1)->key_ == 1);
        assert(s.Find(3)->key_ == 3);
        assert(s.Find(10) == nullptr);

        cout << __func__ << " ->    OK" << '\n' << endl;
    }

    static void BVS_ShouldNotContainInEmptyTree() {
        cout << '\n' << __func__ << " -> START" << endl;

        Set<int> s;
        assert(!s.Contains(1));
        assert(!s.Contains(4));
        assert(!s.Contains(2));

        assert(s.Find(342) == nullptr);
        assert(s.Find(-342) == nullptr);

        cout << __func__ << " ->    OK" << '\n' << endl;
    }

    static void BVS_ShouldFindMinAndMaxOfTreeNodeTest() {
        cout << '\n' << __func__ << " -> START" << endl;
        Set<int> s;
        s.InsertKey(5);
        s.InsertKey(7);
        s.InsertKey(3);
        s.InsertKey(6);
        s.InsertKey(10);
        s.InsertKey(-10);
        s.InsertKey(24);
        s.InsertKey(8);

        assert(s.Min(s.Find(5)) != nullptr);
        assert(s.Min(s.Find(5))->key_ == -10);
        assert(s.Min(s.Find(3)) != nullptr);
        assert(s.Min(s.Find(3))->key_ == -10);
        assert(s.Min(s.Find(-10)) != nullptr);
        assert(s.Min(s.Find(-10))->key_ == -10);
        assert(s.Min(s.Find(6)) != nullptr);
        assert(s.Min(s.Find(6))->key_ == 6);
        assert(s.Min(s.Find(7)) != nullptr);
        assert(s.Min(s.Find(7))->key_ == 6);
        assert(s.Min(s.Find(10)) != nullptr);
        assert(s.Min(s.Find(10))->key_ == 8);
        assert(s.Min(s.Find(24)) != nullptr);
        assert(s.Min(s.Find(24))->key_ == 24);

        assert(s.Max(s.Find(5)) != nullptr);
        assert(s.Max(s.Find(5))->key_ == 24);
        assert(s.Max(s.Find(3)) != nullptr);
        assert(s.Max(s.Find(3))->key_ == 3);
        assert(s.Max(s.Find(-10)) != nullptr);
        assert(s.Max(s.Find(-10))->key_ == -10);
        assert(s.Max(s.Find(6)) != nullptr);
        assert(s.Max(s.Find(6))->key_ == 6);
        assert(s.Max(s.Find(7)) != nullptr);
        assert(s.Max(s.Find(7))->key_ == 24);
        assert(s.Max(s.Find(10)) != nullptr);
        assert(s.Max(s.Find(10))->key_ == 24);
        assert(s.Max(s.Find(24)) != nullptr);
        assert(s.Max(s.Find(24))->key_ == 24);


        cout << __func__ << " ->    OK" << '\n' << endl;
    }

    static void BVS_ShouldHaveRightStructureForBSTTest() {
        cout << '\n' << __func__ << " -> START" << endl;
        Set<int> s;
        s.InsertKey(5);
        s.InsertKey(7);
        s.InsertKey(3);
        s.InsertKey(6);
        s.InsertKey(10);
        s.InsertKey(-10);
        s.InsertKey(24);
        s.InsertKey(8);

        assert(s.root_->key_ == 5);
        assert(s.root_->left_->key_ == 3);
        assert(s.root_->left_->left_->key_ == -10);
        assert(s.root_->right_->key_ == 7);
        assert(s.root_->right_->right_->key_ == 10);
        assert(s.root_->right_->right_->right_->key_ == 24);

        cout << __func__ << " ->    OK" << '\n' << endl;
    }

    static void BVS_CheckIfParentsAreValidTest() {
        cout << '\n' << __func__ << " -> START" << endl;

        Set<int> s;
        s.InsertKey(5);
        s.InsertKey(7);
        s.InsertKey(3);
        s.InsertKey(6);
        s.InsertKey(10);
        s.InsertKey(-10);
        s.InsertKey(24);
        s.InsertKey(8);

        auto max = s.Max();
        auto min = s.Min();

        assert(max->parent_->key_ == 10);
        assert(max->parent_->parent_->key_ == 7);
        assert(max->parent_->parent_->parent_->key_ == 5);
        assert(max->parent_->parent_->parent_->parent_ == nullptr);

        assert(min->parent_->key_ == 3);
        assert(min->parent_->parent_->key_ == 5);
        assert(min->parent_->parent_->parent_ == nullptr);

        cout << __func__ << " ->    OK" << '\n' << endl;
    }

    static void BVS_PredShouldPrintValuesInDescendingOrderTest() {
        cout << '\n' << __func__ << " -> START" << endl;

        Set<int> s;
        s.InsertKey(5);
        s.InsertKey(7);
        s.InsertKey(3);
        s.InsertKey(6);
        s.InsertKey(10);
        s.InsertKey(-10);
        s.InsertKey(24);
        s.InsertKey(8);

        vector<int> expected = {24, 10, 8, 7, 6, 5, 3, -10};
        vector<int> result = {};

        for (auto current = s.Max(); current != nullptr; current = s.Predecessor(current)) {
            cout << current->key_ << " ";
            result.push_back(current->key_);
        }
        cout << endl;

        assert(expected == result);


        expected = {8, 7, 6, 5, 3, -10};
        result = {};

        for (auto current = s.Find(8); current != nullptr; current = s.Predecessor(current)) {
            cout << current->key_ << " ";
            result.push_back(current->key_);
        }
        cout << endl;

        assert(expected == result);


        expected = {-10};
        result = {};

        for (auto current = s.Find(-10); current != nullptr; current = s.Predecessor(current)) {
            cout << current->key_ << " ";
            result.push_back(current->key_);
        }
        cout << endl;

        assert(expected == result);

        expected = {10, 8, 7, 6, 5, 3, -10};
        result = {};

        for (auto current = s.Find(10); current != nullptr; current = s.Predecessor(current)) {
            cout << current->key_ << " ";
            result.push_back(current->key_);
        }
        cout << endl;

        assert(expected == result);

        cout << __func__ << " ->    OK" << '\n' << endl;
    }

    static void BVS_SuccShouldPrintValuesInAscendingOrderTest() {
        cout << '\n' << __func__ << " -> START" << endl;

        Set<int> s;
        s.InsertKey(5);
        s.InsertKey(7);
        s.InsertKey(3);
        s.InsertKey(6);
        s.InsertKey(10);
        s.InsertKey(-10);
        s.InsertKey(24);
        s.InsertKey(8);

        vector<int> expected = {-10, 3, 5, 6, 7, 8, 10, 24};
        vector<int> result = {};

        for (auto current = s.Min(); current != nullptr; current = s.Successor(current)) {
            cout << current->key_ << " ";
            result.push_back(current->key_);
        }
        cout << endl;

        assert(expected == result);


        expected = {8, 10, 24};
        result = {};

        for (auto current = s.Find(8); current != nullptr; current = s.Successor(current)) {
            cout << current->key_ << " ";
            result.push_back(current->key_);
        }
        cout << endl;

        assert(expected == result);


        expected = {24};
        result = {};

        for (auto current = s.Find(24); current != nullptr; current = s.Successor(current)) {
            cout << current->key_ << " ";
            result.push_back(current->key_);
        }
        cout << endl;

        assert(expected == result);

        expected = {3, 5, 6, 7, 8, 10, 24};
        result = {};

        for (auto current = s.Find(3); current != nullptr; current = s.Successor(current)) {
            cout << current->key_ << " ";
            result.push_back(current->key_);
        }
        cout << endl;

        assert(expected == result);

        cout << __func__ << " ->    OK" << '\n' << endl;
    }

    static void BVS_DeleteTest() {
        cout << '\n' << __func__ << " -> START" << endl;

        Set<int> s;
        s.InsertKey(25);
        s.InsertKey(15);
        s.InsertKey(35);
        s.InsertKey(5);
        s.InsertKey(20);
        s.InsertKey(30);
        s.InsertKey(40);
        assert(s.size() == 7);
        s.DeleteKey(5);
        assert(s.size() == 6);
        assert(s.Find(15)->left_ == nullptr);
        assert(s.Min()->key_ == 15);
        s.DeleteKey(15);
        assert(s.size() == 5);
        assert(s.root_->left_->key_ == 20);
        assert(s.root_->left_->right_ == nullptr);
        assert(s.root_->left_->left_ == nullptr);
        assert(s.root_->left_->parent_ == s.root_);
        assert(s.root_->left_->parent_->key_ == 25);

        s.DeleteKey(25);
        assert(s.size() == 4);
        assert(s.root_->key_ == 30);
        assert(s.root_->left_->key_ == 20);
        assert(s.root_->left_->right_ == nullptr);
        assert(s.root_->left_->left_ == nullptr);

        s.DeleteKey(30);
        s.DeleteKey(35);
        s.DeleteKey(40);
        s.DeleteKey(20);
        assert(s.size() == 0);
        assert(s.root_ == nullptr);

        cout << __func__ << " ->    OK" << '\n' << endl;
    }

    static void BVS_PairKeyTypeTest() {
        cout << '\n' << __func__ << " -> START" << endl;

        Set<pair<int, string >> s1;
        s1.InsertKey({5, "a"});
        s1.InsertKey({5, "b"});

        for (auto beg = s1.Min(); beg != nullptr; beg = s1.Successor(beg)) {
            cout << "{ " << beg->key_.first << ", " << beg->key_.second << " }, ";
        }
        cout << endl;

        cout << __func__ << " ->    OK" << '\n' << endl;
    }

    static void AVL_ShouldHaveRightDepthsAfterInsertTest() {
        cout << '\n' << __func__ << " -> START" << endl;

        Set<int> s;
        s.InsertKey(25);
        assert(s.root_->height_ == 0);
        s.InsertKey(15);
        assert(s.root_->height_ == 1);
        assert(s.root_->left_->height_ == 0);
        s.InsertKey(35);
        assert(s.root_->height_ == 1);
        assert(s.root_->left_->height_ == 0);
        assert(s.root_->right_->height_ == 0);
        s.InsertKey(5);
        assert(s.root_->height_ == 2);
        assert(s.root_->left_->height_ == 1);
        assert(s.root_->left_->left_->height_ == 0);
        assert(s.root_->right_->height_ == 0);
        s.InsertKey(20);
        assert(s.root_->height_ == 2);
        assert(s.root_->left_->height_ == 1);
        assert(s.root_->left_->left_->height_ == 0);
        assert(s.root_->left_->right_->height_ == 0);
        assert(s.root_->right_->height_ == 0);
        s.InsertKey(30);
        assert(s.root_->height_ == 2);
        assert(s.root_->left_->height_ == 1);
        assert(s.root_->left_->left_->height_ == 0);
        assert(s.root_->left_->right_->height_ == 0);
        assert(s.root_->right_->height_ == 1);
        assert(s.root_->right_->left_->height_ == 0);
        s.InsertKey(40);
        assert(s.root_->height_ == 2);
        assert(s.root_->left_->height_ == 1);
        assert(s.root_->left_->left_->height_ == 0);
        assert(s.root_->left_->right_->height_ == 0);
        assert(s.root_->right_->height_ == 1);
        assert(s.root_->right_->left_->height_ == 0);
        assert(s.root_->right_->right_->height_ == 0);

        cout << __func__ << " ->    OK" << '\n' << endl;

    }

    static void AVL_ShouldHaveValidDepthsAfterDeleteTest() {
        cout << '\n' << __func__ << " -> START" << endl;
        Set<int> s;
        s.InsertKey(25);
        s.InsertKey(15);
        s.InsertKey(35);
        s.InsertKey(5);
        s.InsertKey(20);
        s.InsertKey(30);
        s.InsertKey(40);

        s.DeleteKey(20);
        assert(s.root_->height_ == 2);
        assert(s.root_->left_->height_ == 1);
        assert(s.root_->left_->left_->height_ == 0);
        assert(s.root_->right_->height_ == 1);
        assert(s.root_->right_->left_->height_ == 0);
        assert(s.root_->right_->right_->height_ == 0);
        s.DeleteKey(5);
        assert(s.root_->height_ == 2);
        assert(s.root_->left_->height_ == 0);
        assert(s.root_->right_->height_ == 1);
        assert(s.root_->right_->left_->height_ == 0);
        assert(s.root_->right_->right_->height_ == 0);
        s.DeleteKey(25);
        assert(s.root_->height_ == 2);
        assert(s.root_->left_->height_ == 0);
        assert(s.root_->right_->height_ == 1);
        assert(s.root_->right_->right_->height_ == 0);
        s.DeleteKey(30);
        assert(s.root_->height_ == 1);
        assert(s.root_->left_->height_ == 0);
        assert(s.root_->right_->height_ == 0);
        s.DeleteKey(35);
        assert(s.root_->height_ == 1);
        assert(s.root_->left_->height_ == 0);
        s.DeleteKey(40);
        assert(s.root_->height_ == 0);
        s.DeleteKey(15);
        assert(s.size() == 0);
        assert(s.root_ == nullptr);

        cout << __func__ << " ->    OK" << '\n' << endl;
    }

    static void AVL_SingleRotationTest() {
        cout << '\n' << __func__ << " -> START" << endl;

        Set<int> s1;
        s1.InsertKey(10);
        s1.InsertKey(15);
        s1.InsertKey(20);
        assert(s1.root_->key_ == 15);
        cout << __func__ << " ->    OK" << '\n' << endl;
    }

    static void BVS_ShouldKeepValidSizeInEachNodeAfterInsertTest() {
        cout << '\n' << __func__ << " -> START" << endl;
        Set<int> s;
        s.InsertKey(25);
        assert(s.root_->size_ == 1);
        s.InsertKey(15);
        assert(s.root_->size_ == 2);
        assert(s.root_->left_->size_ == 1);
        s.InsertKey(35);
        assert(s.root_->size_ == 3);
        assert(s.root_->left_->size_ == 1);
        assert(s.root_->right_->size_ == 1);
        s.InsertKey(5);
        assert(s.root_->size_ == 4);
        assert(s.root_->left_->size_ == 2);
        assert(s.root_->left_->left_->size_ == 1);
        assert(s.root_->right_->size_ == 1);
        s.InsertKey(20);
        assert(s.root_->size_ == 5);
        assert(s.root_->left_->size_ == 3);
        assert(s.root_->left_->left_->size_ == 1);
        assert(s.root_->left_->right_->size_ == 1);
        assert(s.root_->right_->size_ == 1);
        s.InsertKey(30);
        assert(s.root_->size_ == 6);
        assert(s.root_->left_->size_ == 3);
        assert(s.root_->left_->left_->size_ == 1);
        assert(s.root_->left_->right_->size_ == 1);
        assert(s.root_->right_->size_ == 2);
        assert(s.root_->right_->left_->size_ == 1);
        s.InsertKey(40);
        assert(s.root_->size_ == 7);
        assert(s.root_->left_->size_ == 3);
        assert(s.root_->left_->left_->size_ == 1);
        assert(s.root_->left_->right_->size_ == 1);
        assert(s.root_->right_->size_ == 3);
        assert(s.root_->right_->left_->size_ == 1);
        assert(s.root_->right_->right_->size_ == 1);

        cout << __func__ << " ->    OK" << '\n' << endl;
    }

    static void BVS_ShouldKeepValidSizeInEachNodeAfterDeleteTest() {
        cout << '\n' << __func__ << " -> START" << endl;

        Set<int> s;
        s.InsertKey(25);
        s.InsertKey(15);
        s.InsertKey(35);
        s.InsertKey(5);
        s.InsertKey(20);
        s.InsertKey(30);
        s.InsertKey(40);
        assert(s.size() == 7);
        assert(s.root_->size_ == 7);
        assert(s.root_->left_->size_ == 3);
        assert(s.root_->left_->left_->size_ == 1);
        assert(s.root_->left_->right_->size_ == 1);
        assert(s.root_->right_->size_ == 3);
        assert(s.root_->right_->left_->size_ == 1);
        assert(s.root_->right_->right_->size_ == 1);
        s.DeleteKey(5);
        assert(s.root_->size_ == 6);
        assert(s.root_->left_->size_ == 2);
        assert(s.root_->left_->right_->size_ == 1);
        assert(s.root_->right_->size_ == 3);
        assert(s.root_->right_->left_->size_ == 1);
        assert(s.root_->right_->right_->size_ == 1);
        s.DeleteKey(15);
        assert(s.root_->size_ == 5);
        assert(s.root_->left_->size_ == 1);
        assert(s.root_->right_->size_ == 3);
        assert(s.root_->right_->left_->size_ == 1);
        assert(s.root_->right_->right_->size_ == 1);
        s.DeleteKey(25);
        assert(s.root_->size_ == 4);
        assert(s.root_->left_->size_ == 1);
        assert(s.root_->right_->size_ == 2);
        assert(s.root_->right_->right_->size_ == 1);
        s.DeleteKey(30);
        assert(s.root_->size_ == 3);
        assert(s.root_->left_->size_ == 1);
        assert(s.root_->right_->size_ == 1);
        s.DeleteKey(35);
        assert(s.root_->size_ == 2);
        assert(s.root_->left_->size_ == 1);
        s.DeleteKey(40);
        assert(s.root_->size_ == 1);
        s.DeleteKey(20);
        assert(s.size() == 0);
        cout << __func__ << " ->    OK" << '\n' << endl;
    }

    static void BVS_ShouldReturnValidNodeWithAtMethodTest1() {
        cout << '\n' << __func__ << " -> START" << endl;

        Set<int> s;
        s.InsertKey(25);
        s.InsertKey(15);
        s.InsertKey(35);
        s.InsertKey(5);
        s.InsertKey(20);
        s.InsertKey(30);
        s.InsertKey(40);

        assert(s.at(0) != nullptr);
        assert(s.at(0)->key_ == 40);
        assert(s.at(1)->key_ == 35);
        assert(s.at(2)->key_ == 30);
        assert(s.at(3)->key_ == 25);
        assert(s.at(4)->key_ == 20);
        assert(s.at(5)->key_ == 15);
        assert(s.at(6)->key_ == 5);

        try{
            s.at(7);
            assert(false);
        } catch (out_of_range &e){}
        try{
            s.at(-1);
            assert(false);
        } catch (out_of_range &e){}

        Set<int> s2;

        try{
            s2.at(0);
            assert(false);
        } catch (out_of_range &e){}

        cout << __func__ << " ->    OK" << '\n' << endl;
    }

    static void BVS_ShouldReturnValidNodeWithAteMethodTest2(){
        cout << '\n' << __func__ << " -> START" << endl;

        Set<int> s1;
        s1.InsertKey(1);
        s1.InsertKey(0);
        s1.InsertKey(3);
        s1.InsertKey(2);

        assert(s1.at(0)->key_ == 3);
        assert(s1.at(1)->key_ == 2);
        assert(s1.at(2)->key_ == 1);
        assert(s1.at(3)->key_ == 0);


        cout << __func__ << " ->    OK" << '\n' << endl;
    }

    static void BVS_ShouldReturnValidIndexWithIndexOfMethodTest(){
        cout << '\n' << __func__ << " -> START" << endl;

        Set<int> s;
        s.InsertKey(25);
        s.InsertKey(15);
        s.InsertKey(35);
        s.InsertKey(5);
        s.InsertKey(20);
        s.InsertKey(30);
        s.InsertKey(40);

        assert(s.IndexOf(40) == 0);
        assert(s.IndexOf(35) == 1);
        assert(s.IndexOf(30) == 2);
        assert(s.IndexOf(25) == 3);
        assert(s.IndexOf(20) == 4);
        assert(s.IndexOf(15) == 5);
        assert(s.IndexOf(5) == 6);
        try{
            s.IndexOf(-1);
            assert(false);
        } catch (out_of_range &e){}
        try{
            s.IndexOf(7);
            assert(false);
        } catch (out_of_range &e){}

        Set<int> s2;

        try{
            s2.IndexOf(0);
            assert(false);
        } catch (out_of_range &e){}

        cout << __func__ << " ->    OK" << '\n' << endl;
    }

};

#endif //HW02_BESTSELLERS_SETTESTER_HPP

// #EX_END
