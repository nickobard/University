struct MapTester {

    static void runAll() {
        BVS_ShouldInsertAndContainKeysTest();
        BVS_ShouldInsertAndFindWithSameKeysTest();
        BVS_ShouldNotContainNodesInEmptyTreeTest();
        BVS_ShouldFindMinAndMaxOfTreeNodeTest();
        BVS_ShouldHaveRightStructureTest();
        BVS_CheckIfParentsAreValidTest();
        BVS_PredShouldPrintValuesInDescendingOrderTest();
        BVS_SuccShouldPrintValuesInAscendingOrderTest();
        BVS_DeleteTest();
        BVS_PairKeyTypeTest();
        BVS_ShouldKeepValidSizeInEachNodeAfterInsertTest();
        BVS_ShouldKeepValidSizeInEachNodeAfterDeleteTest();
        BVS_ShouldReturnValidNodeWithAtMethodTest1();
        BVS_ShouldReturnValidNodeWithAtMethodTest2();
        BVS_ShouldReturnValidIndexWithIndexOfMethodTest();
        AVL_ShouldHaveRightDepthsAfterInsertTest();
        AVL_ShouldHaveValidDepthsAfterDeleteTest();
        AVL_SingleRotationTest1();
        AVL_SingleRotationTest2();
        AVL_DoubleRotationsTest();

        BVS_ShouldHaveCorrectTotalAmountTest();
        BVS_ShouldFindCorrectRangeSubTreeTest();
        BVS_ShouldReturnCorrectRangeSumTest();
    }

    static void layout() {
        cout << '\n' << __func__ << " -> START" << endl;

        cout << __func__ << " ->    OK" << '\n' << endl;
    }

    static void BVS_ShouldInsertAndContainKeysTest() {
        cout << '\n' << __func__ << " -> START" << endl;

        Map<int, int> s;
        assert(s.isEmpty());
        s.InsertKey(5, 5);
        s.InsertKey(6, 6);
        s.InsertKey(6, 6);
        s.InsertKey(1, 1);
        s.InsertKey(7, 7);
        s.InsertKey(3, 3);

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
        Map<int, int> s;

        s.InsertKey(5, 5);
        s.InsertKey(6, 6);
        s.InsertKey(6, 6);
        s.InsertKey(1, 1);
        s.InsertKey(7, 7);
        s.InsertKey(3, 3);

        assert(s.Find(5)->key_ == 5);
        assert(s.Find(6)->key_ == 6);
        assert(s.Find(7)->key_ == 7);
        assert(s.Find(1)->key_ == 1);
        assert(s.Find(3)->key_ == 3);
        assert(s.Find(10) == nullptr);

        cout << __func__ << " ->    OK" << '\n' << endl;
    }

    static void BVS_ShouldNotContainNodesInEmptyTreeTest() {
        cout << '\n' << __func__ << " -> START" << endl;

        Map<int, int> s;
        assert(!s.Contains(1));
        assert(!s.Contains(4));
        assert(!s.Contains(2));

        assert(s.Find(342) == nullptr);
        assert(s.Find(-342) == nullptr);

        cout << __func__ << " ->    OK" << '\n' << endl;
    }

    static void BVS_ShouldFindMinAndMaxOfTreeNodeTest() {
        cout << '\n' << __func__ << " -> START" << endl;
        Map<int, int> s;
        s.InsertKey(5, 5);
        s.InsertKey(7, 7);
        s.InsertKey(3, 3);
        s.InsertKey(6, 6);
        s.InsertKey(10, 10);
        s.InsertKey(-10, -10);
        s.InsertKey(24, 24);
        s.InsertKey(8, 8);

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

    static void BVS_ShouldHaveRightStructureTest() {
        cout << '\n' << __func__ << " -> START" << endl;
        Map<int, int> s;
        s.InsertKey(5, 5);
        s.InsertKey(7, 7);
        s.InsertKey(3, 3);
        s.InsertKey(6, 6);
        s.InsertKey(10, 10);
        s.InsertKey(-10, -10);
        s.InsertKey(24, 24);
        s.InsertKey(8, 8);

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

        Map<int, int> s;
        s.InsertKey(5, 5);
        s.InsertKey(7, 7);
        s.InsertKey(3, 3);
        s.InsertKey(6, 6);
        s.InsertKey(10, 10);
        s.InsertKey(-10, -10);
        s.InsertKey(24, 24);
        s.InsertKey(8, 8);

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

        Map<int, int> s;
        s.InsertKey(5, 5);
        s.InsertKey(7, 7);
        s.InsertKey(3, 3);
        s.InsertKey(6, 6);
        s.InsertKey(10, 10);
        s.InsertKey(-10, -10);
        s.InsertKey(24, 24);
        s.InsertKey(8, 8);

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

        Map<int, int> s;
        s.InsertKey(5, 5);
        s.InsertKey(7, 7);
        s.InsertKey(3, 3);
        s.InsertKey(6, 6);
        s.InsertKey(10, 10);
        s.InsertKey(-10, -10);
        s.InsertKey(24, 24);
        s.InsertKey(8, 8);

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

        Map<int, int> s;
        s.InsertKey(25, 25);
        s.InsertKey(15, 15);
        s.InsertKey(35, 35);
        s.InsertKey(5, 5);
        s.InsertKey(20, 20);
        s.InsertKey(30, 30);
        s.InsertKey(40, 40);
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

        Map<pair<int, string>, int> s1;
        s1.InsertKey({5, "a"}, 5);
        s1.InsertKey({5, "b"}, 5);

        for (auto beg = s1.Min(); beg != nullptr; beg = s1.Successor(beg)) {
            cout << "{ " << beg->key_.first << ", " << beg->key_.second << " }, ";
        }
        cout << endl;

        cout << __func__ << " ->    OK" << '\n' << endl;
    }

    static void BVS_ShouldKeepValidSizeInEachNodeAfterInsertTest() {
        cout << '\n' << __func__ << " -> START" << endl;
        Map<int, int> s;
        s.InsertKey(25, 25);
        assert(s.root_->size_ == 1);
        s.InsertKey(15, 15);
        assert(s.root_->size_ == 2);
        assert(s.root_->left_->size_ == 1);
        s.InsertKey(35, 35);
        assert(s.root_->size_ == 3);
        assert(s.root_->left_->size_ == 1);
        assert(s.root_->right_->size_ == 1);
        s.InsertKey(5, 5);
        assert(s.root_->size_ == 4);
        assert(s.root_->left_->size_ == 2);
        assert(s.root_->left_->left_->size_ == 1);
        assert(s.root_->right_->size_ == 1);
        s.InsertKey(20, 20);
        assert(s.root_->size_ == 5);
        assert(s.root_->left_->size_ == 3);
        assert(s.root_->left_->left_->size_ == 1);
        assert(s.root_->left_->right_->size_ == 1);
        assert(s.root_->right_->size_ == 1);
        s.InsertKey(30, 30);
        assert(s.root_->size_ == 6);
        assert(s.root_->left_->size_ == 3);
        assert(s.root_->left_->left_->size_ == 1);
        assert(s.root_->left_->right_->size_ == 1);
        assert(s.root_->right_->size_ == 2);
        assert(s.root_->right_->left_->size_ == 1);
        s.InsertKey(40, 40);
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

        Map<int, int> s;
        s.InsertKey(25, 25);
        s.InsertKey(15, 15);
        s.InsertKey(35, 35);
        s.InsertKey(5, 5);
        s.InsertKey(20, 20);
        s.InsertKey(30, 30);
        s.InsertKey(40, 40);
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

        Map<int, int> s;
        s.InsertKey(25, 25);
        s.InsertKey(15, 15);
        s.InsertKey(35, 35);
        s.InsertKey(5, 5);
        s.InsertKey(20, 20);
        s.InsertKey(30, 30);
        s.InsertKey(40, 40);

        assert(s.at(0) != nullptr);
        assert(s.at(0)->key_ == 40);
        assert(s.at(1)->key_ == 35);
        assert(s.at(2)->key_ == 30);
        assert(s.at(3)->key_ == 25);
        assert(s.at(4)->key_ == 20);
        assert(s.at(5)->key_ == 15);
        assert(s.at(6)->key_ == 5);

        try {
            s.at(7);
            assert(false);
        } catch (out_of_range &e) {}
        try {
            s.at(-1);
            assert(false);
        } catch (out_of_range &e) {}

        Map<int, int> s2;

        try {
            s2.at(0);
            assert(false);
        } catch (out_of_range &e) {}

        cout << __func__ << " ->    OK" << '\n' << endl;
    }

    static void BVS_ShouldReturnValidNodeWithAtMethodTest2() {
        cout << '\n' << __func__ << " -> START" << endl;

        Map<int, int> s1;
        s1.InsertKey(1, 1);
        s1.InsertKey(0, 0);
        s1.InsertKey(3, 3);
        s1.InsertKey(2, 2);

        assert(s1.at(0)->key_ == 3);
        assert(s1.at(1)->key_ == 2);
        assert(s1.at(2)->key_ == 1);
        assert(s1.at(3)->key_ == 0);


        cout << __func__ << " ->    OK" << '\n' << endl;
    }

    static void BVS_ShouldReturnValidIndexWithIndexOfMethodTest() {
        cout << '\n' << __func__ << " -> START" << endl;

        Map<int, int> s;
        s.InsertKey(25, 25);
        s.InsertKey(15, 15);
        s.InsertKey(35, 35);
        s.InsertKey(5, 5);
        s.InsertKey(20, 20);
        s.InsertKey(30, 30);
        s.InsertKey(40, 40);

        assert(s.IndexOf(40) == 0);
        assert(s.IndexOf(35) == 1);
        assert(s.IndexOf(30) == 2);
        assert(s.IndexOf(25) == 3);
        assert(s.IndexOf(20) == 4);
        assert(s.IndexOf(15) == 5);
        assert(s.IndexOf(5) == 6);
        try {
            s.IndexOf(-1);
            assert(false);
        } catch (out_of_range &e) {}
        try {
            s.IndexOf(7);
            assert(false);
        } catch (out_of_range &e) {}

        Map<int, int> s2;

        try {
            s2.IndexOf(0);
            assert(false);
        } catch (out_of_range &e) {}

        cout << __func__ << " ->    OK" << '\n' << endl;
    }

    static void AVL_ShouldHaveRightDepthsAfterInsertTest() {
        cout << '\n' << __func__ << " -> START" << endl;

        Map<int, int> s;
        s.InsertKey(25, 25);
        assert(s.root_->height_ == 0);
        s.InsertKey(15, 15);
        assert(s.root_->height_ == 1);
        assert(s.root_->left_->height_ == 0);
        s.InsertKey(35, 35);
        assert(s.root_->height_ == 1);
        assert(s.root_->left_->height_ == 0);
        assert(s.root_->right_->height_ == 0);
        s.InsertKey(5, 5);
        assert(s.root_->height_ == 2);
        assert(s.root_->left_->height_ == 1);
        assert(s.root_->left_->left_->height_ == 0);
        assert(s.root_->right_->height_ == 0);
        s.InsertKey(20, 20);
        assert(s.root_->height_ == 2);
        assert(s.root_->left_->height_ == 1);
        assert(s.root_->left_->left_->height_ == 0);
        assert(s.root_->left_->right_->height_ == 0);
        assert(s.root_->right_->height_ == 0);
        s.InsertKey(30, 30);
        assert(s.root_->height_ == 2);
        assert(s.root_->left_->height_ == 1);
        assert(s.root_->left_->left_->height_ == 0);
        assert(s.root_->left_->right_->height_ == 0);
        assert(s.root_->right_->height_ == 1);
        assert(s.root_->right_->left_->height_ == 0);
        s.InsertKey(40, 40);
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
        Map<int, int> s;
        s.InsertKey(25, 25);
        s.InsertKey(15, 15);
        s.InsertKey(35, 35);
        s.InsertKey(5, 5);
        s.InsertKey(20, 20);
        s.InsertKey(30, 30);
        s.InsertKey(40, 40);

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

    static void AVL_SingleRotationTest1() {
        cout << '\n' << __func__ << " -> START" << endl;

        Map<int, int> s1;
        s1.InsertKey(10, 10);
        s1.InsertKey(15, 15);
        s1.InsertKey(20, 20);
        assert(s1.root_->key_ == 15);
        assert(s1.root_->parent_ == nullptr);
        assert(s1.root_->left_->key_ == 10);
        assert(s1.root_->left_->parent_ == s1.root_);
        assert(s1.root_->left_->isList());
        assert(s1.root_->right_->key_ == 20);
        assert(s1.root_->right_->parent_ == s1.root_);
        assert(s1.root_->right_->isList());
        s1.DeleteKey(20);
        s1.InsertKey(5, 5);
        assert(s1.root_->key_ == 10);
        assert(s1.root_->parent_ == nullptr);
        assert(s1.root_->left_->key_ == 5);
        assert(s1.root_->left_->parent_ == s1.root_);
        assert(s1.root_->left_->isList());
        assert(s1.root_->right_->key_ == 15);
        assert(s1.root_->right_->parent_ == s1.root_);
        assert(s1.root_->right_->isList());


        cout << __func__ << " ->    OK" << '\n' << endl;
    }

    static void AVL_SingleRotationTest2() {
        cout << '\n' << __func__ << " -> START" << endl;

        Map<int, int> s1;
        s1.InsertKey(2, 2);
        s1.InsertKey(1, 1);
        s1.InsertKey(4, 4);
        s1.InsertKey(3, 3);
        s1.InsertKey(5, 5);
        s1.InsertKey(6, 6);
        assert(s1.root_->key_ == 4);
        assert(s1.root_->parent_ == nullptr);
        assert(s1.root_->left_->key_ == 2);
        assert(s1.root_->left_->parent_ == s1.root_);
        assert(s1.root_->left_->right_->key_ == 3);
        assert(s1.root_->left_->right_->parent_ == s1.root_->left_);
        assert(s1.root_->left_->right_->isList());
        assert(s1.root_->left_->left_->key_ == 1);
        assert(s1.root_->left_->left_->parent_ == s1.root_->left_);
        assert(s1.root_->left_->left_->isList());

        assert(s1.root_->right_->key_ == 5);
        assert(s1.root_->right_->parent_ == s1.root_);
        assert(s1.root_->right_->right_->key_ == 6);
        assert(s1.root_->right_->right_->parent_ == s1.root_->right_);
        assert(s1.root_->right_->right_->isList());
        assert(s1.root_->right_->left_ == nullptr);
        s1.DeleteKey(6);
        s1.InsertKey(0, 0);
        assert(s1.root_->key_ == 2);
        assert(s1.root_->parent_ == nullptr);
        assert(s1.root_->left_->key_ == 1);
        assert(s1.root_->left_->parent_ == s1.root_);

        assert(s1.root_->left_->right_ == nullptr);
        assert(s1.root_->left_->left_->key_ == 0);
        assert(s1.root_->left_->left_->parent_ == s1.root_->left_);
        assert(s1.root_->left_->left_->isList());

        assert(s1.root_->right_->key_ == 4);
        assert(s1.root_->right_->parent_ == s1.root_);
        assert(s1.root_->right_->right_->key_ == 5);
        assert(s1.root_->right_->right_->parent_ == s1.root_->right_);
        assert(s1.root_->right_->right_->isList());
        assert(s1.root_->right_->left_->key_ == 3);
        assert(s1.root_->right_->left_->parent_ == s1.root_->right_);
        assert(s1.root_->right_->left_->isList());

        cout << __func__ << " ->    OK" << '\n' << endl;
    }

    static void AVL_DoubleRotationsTest() {
        cout << '\n' << __func__ << " -> START" << endl;

        Map<int, int> s;
        s.InsertKey(15, 15);
        s.InsertKey(5, 5);
        s.InsertKey(6, 6);

        assert(s.root_->key_ == 6);
        assert(s.root_->parent_ == nullptr);
        assert(s.root_->left_->key_ == 5);
        assert(s.root_->left_->parent_ == s.root_);
        assert(s.root_->left_->isList());
        assert(s.root_->right_->key_ == 15);
        assert(s.root_->right_->parent_ == s.root_);
        assert(s.root_->right_->isList());

        s.DeleteKey(5);
        s.InsertKey(14, 14);

        assert(s.root_->key_ == 14);
        assert(s.root_->parent_ == nullptr);
        assert(s.root_->left_->key_ == 6);
        assert(s.root_->left_->parent_ == s.root_);
        assert(s.root_->left_->isList());
        assert(s.root_->right_->key_ == 15);
        assert(s.root_->right_->parent_ == s.root_);
        assert(s.root_->right_->isList());

        cout << __func__ << " ->    OK" << '\n' << endl;
    }

    static void BVS_ShouldHaveCorrectTotalAmountTest() {
        cout << '\n' << __func__ << " -> START" << endl;

        Map<int, int> s;
        s.InsertKey(25, 25);
        assert(s.root_->subtreeSum_ == 25);
        s.InsertKey(10, 10);
        assert(s.root_->subtreeSum_ == 35);
        assert(s.root_->left_->subtreeSum_ == 10);
        s.InsertKey(5, 5);
        assert(s.root_->subtreeSum_ == 40);
        assert(s.root_->left_->subtreeSum_ == 5);
        assert(s.root_->right_->subtreeSum_ == 25);
        s.InsertKey(6, 6);
        assert(s.root_->subtreeSum_ == 46);
        assert(s.root_->left_->subtreeSum_ == 11);
        assert(s.root_->left_->right_->subtreeSum_ == 6);
        assert(s.root_->right_->subtreeSum_ == 25);

        cout << __func__ << " ->    OK" << '\n' << endl;
    }

    static void BVS_ShouldFindCorrectRangeSubTreeTest() {
        cout << '\n' << __func__ << " -> START" << endl;

        Map<int, int> s;
        s.InsertKey(25, 25);
        s.InsertKey(15, 15);
        s.InsertKey(35, 35);
        s.InsertKey(5, 5);
        s.InsertKey(20, 20);
        s.InsertKey(30, 30);
        s.InsertKey(40, 40);

        assert(s.FindRangeSubtreeRoot(s.root_, s.at(0)->key_, s.at(0)->key_)->key_ == 40);
        assert(s.FindRangeSubtreeRoot(s.root_, s.at(0)->key_, s.at(1)->key_)->key_ == 35);
        assert(s.FindRangeSubtreeRoot(s.root_, s.at(0)->key_, s.at(2)->key_)->key_ == 35);
        assert(s.FindRangeSubtreeRoot(s.root_, s.at(0)->key_, s.at(3)->key_)->key_ == 25);
        assert(s.FindRangeSubtreeRoot(s.root_, s.at(0)->key_, s.at(4)->key_)->key_ == 25);
        assert(s.FindRangeSubtreeRoot(s.root_, s.at(0)->key_, s.at(5)->key_)->key_ == 25);
        assert(s.FindRangeSubtreeRoot(s.root_, s.at(0)->key_, s.at(6)->key_)->key_ == 25);

        assert(s.FindRangeSubtreeRoot(s.root_, s.at(1)->key_, s.at(1)->key_)->key_ == 35);
        assert(s.FindRangeSubtreeRoot(s.root_, s.at(1)->key_, s.at(2)->key_)->key_ == 35);
        assert(s.FindRangeSubtreeRoot(s.root_, s.at(1)->key_, s.at(3)->key_)->key_ == 25);
        assert(s.FindRangeSubtreeRoot(s.root_, s.at(1)->key_, s.at(4)->key_)->key_ == 25);
        assert(s.FindRangeSubtreeRoot(s.root_, s.at(1)->key_, s.at(5)->key_)->key_ == 25);
        assert(s.FindRangeSubtreeRoot(s.root_, s.at(1)->key_, s.at(6)->key_)->key_ == 25);

        assert(s.FindRangeSubtreeRoot(s.root_, s.at(2)->key_, s.at(2)->key_)->key_ == 30);
        assert(s.FindRangeSubtreeRoot(s.root_, s.at(2)->key_, s.at(3)->key_)->key_ == 25);
        assert(s.FindRangeSubtreeRoot(s.root_, s.at(2)->key_, s.at(4)->key_)->key_ == 25);
        assert(s.FindRangeSubtreeRoot(s.root_, s.at(2)->key_, s.at(5)->key_)->key_ == 25);
        assert(s.FindRangeSubtreeRoot(s.root_, s.at(2)->key_, s.at(6)->key_)->key_ == 25);

        assert(s.FindRangeSubtreeRoot(s.root_, s.at(3)->key_, s.at(3)->key_)->key_ == 25);
        assert(s.FindRangeSubtreeRoot(s.root_, s.at(3)->key_, s.at(4)->key_)->key_ == 25);
        assert(s.FindRangeSubtreeRoot(s.root_, s.at(3)->key_, s.at(5)->key_)->key_ == 25);
        assert(s.FindRangeSubtreeRoot(s.root_, s.at(3)->key_, s.at(6)->key_)->key_ == 25);

        assert(s.FindRangeSubtreeRoot(s.root_, s.at(4)->key_, s.at(4)->key_)->key_ == 20);
        assert(s.FindRangeSubtreeRoot(s.root_, s.at(4)->key_, s.at(5)->key_)->key_ == 15);
        assert(s.FindRangeSubtreeRoot(s.root_, s.at(4)->key_, s.at(6)->key_)->key_ == 15);

        assert(s.FindRangeSubtreeRoot(s.root_, s.at(5)->key_, s.at(5)->key_)->key_ == 15);
        assert(s.FindRangeSubtreeRoot(s.root_, s.at(5)->key_, s.at(6)->key_)->key_ == 15);

        assert(s.FindRangeSubtreeRoot(s.root_, s.at(6)->key_, s.at(6)->key_)->key_ == 5);

        cout << __func__ << " ->    OK" << '\n' << endl;
    }

    static void BVS_ShouldReturnCorrectRangeSumTest() {
        cout << '\n' << __func__ << " -> START" << endl;

        Map<int, int> s;
        s.InsertKey(4, 4);
        s.InsertKey(2, 2);
        s.InsertKey(6, 6);
        s.InsertKey(1, 1);
        s.InsertKey(3, 3);
        s.InsertKey(5, 5);
        s.InsertKey(7, 7);

        assert(s.GetRangeSum(0, 6) == 28);
        assert(s.GetRangeSum(0, 5) == 27);
        assert(s.GetRangeSum(0, 4) == 25);
        assert(s.GetRangeSum(0, 3) == 22);
        assert(s.GetRangeSum(0, 2) == 18);
        assert(s.GetRangeSum(0, 1) == 13);
        assert(s.GetRangeSum(0, 0) == 7);

        assert(s.GetRangeSum(1, 6) == 21);
        assert(s.GetRangeSum(1, 5) == 20);
        assert(s.GetRangeSum(1, 4) == 18);
        assert(s.GetRangeSum(1, 3) == 15);
        assert(s.GetRangeSum(1, 2) == 11);
        assert(s.GetRangeSum(1, 1) == 6);

        assert(s.GetRangeSum(2, 6) == 15);
        assert(s.GetRangeSum(2, 5) == 14);
        assert(s.GetRangeSum(2, 4) == 12);
        assert(s.GetRangeSum(2, 3) == 9);
        assert(s.GetRangeSum(2, 2) == 5);

        assert(s.GetRangeSum(3, 6) == 10);
        assert(s.GetRangeSum(3, 5) == 9);
        assert(s.GetRangeSum(3, 4) == 7);
        assert(s.GetRangeSum(3, 3) == 4);

        assert(s.GetRangeSum(4, 6) == 6);
        assert(s.GetRangeSum(4, 5) == 5);
        assert(s.GetRangeSum(4, 4) == 3);

        assert(s.GetRangeSum(5, 6) == 3);
        assert(s.GetRangeSum(5, 5) == 2);

        assert(s.GetRangeSum(6, 6) == 1);


        cout << __func__ << " ->    OK" << '\n' << endl;
    }



};
