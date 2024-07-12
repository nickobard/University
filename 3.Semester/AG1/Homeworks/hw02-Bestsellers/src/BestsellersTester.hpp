// #PRIOR_NO
// #EX_BEGIN
//
// Created by bardanik on 08/11/22.
//

#ifndef HW02_BESTSELLERS_BESTSELLERSTESTER_HPP
#define HW02_BESTSELLERS_BESTSELLERSTESTER_HPP

#endif //HW02_BESTSELLERS_BESTSELLERSTESTER_HPP

#include <iostream>
#include "Bestsellers.hpp"

using namespace std;

struct BestsellersTester{

    static void runAll(){
        test1();
        test2();
        SellsTest();
        FirstAndLastSameTest();
    }

    static void layout() {
        cout << '\n' << __func__ << " -> START" << endl;

        cout << __func__ << " ->    OK" << '\n' << endl;
    }

    static void test1() {
        cout << '\n' << __func__ << " -> START" << endl;

        Bestsellers<std::string> T;
        T.sell("coke", 32);
        T.sell("bread", 1);
        assert(T.products() == 2);
        T.sell("ham", 2);
        T.sell("mushrooms", 12);

        assert(T.products() == 4);
        assert(T.rank("ham") == 3);
        assert(T.rank("coke") == 1);
        assert(T.sold(1, 3) == 46);
        assert(T.product(2) == "mushrooms");

        T.sell("ham", 11);
        assert(T.products() == 4);
        assert(T.product(2) == "ham");
        assert(T.sold(2) == 13);
        assert(T.sold(2, 2) == 13);
        assert(T.sold(1, 2) == 45);

        cout << __func__ << " ->    OK" << '\n' << endl;
    }

    static void test2() {
        cout << '\n' << __func__ << " -> START" << endl;
# define CATCH(expr) \
        try { expr; assert(0); } catch (const std::out_of_range&) { assert(1); };

        Bestsellers<std::string> T;
        T.sell("coke", 32);
        T.sell("bread", 1);

        CATCH(T.rank("ham"));
        CATCH(T.product(3));
        CATCH(T.sold(0));
        CATCH(T.sold(9));
        CATCH(T.sold(0, 1));
        CATCH(T.sold(3, 2));
        CATCH(T.sold(1, 9));

#undef CATCH
        cout << __func__ << " ->    OK" << '\n' << endl;
    }

    static void SellsTest(){
        cout << '\n' << __func__ << " -> START" << endl;

        Bestsellers<std::string> T;
        T.sell("bread", 1);
        T.sell("bread", 1);
        T.sell("bread", 1);
        T.sell("bread", 1);
        T.sell("bread", 1);
        T.sell("bread", 1);
        T.sell("coke", 1);
        T.sell("test", 1);
        T.sell("coke", 1);
        T.sell("test", 1);

        cout << __func__ << " ->    OK" << '\n' << endl;
    }

    static void FirstAndLastSameTest(){
        cout << '\n' << __func__ << " -> START" << endl;
        Bestsellers<std::string> T;
        T.sell("1",1);
        T.sell("2",1);
        T.sell("3",1);
        T.sell("4",2);
        T.sell("5",2);
        T.sell("6",2);
        T.sell("7",3);
        T.sell("8",3);
        T.sell("9",3);

        size_t rank;
        rank = T.last_same(2);
        assert( rank == 3 );
        rank = T.first_same(2);
        assert( rank == 1 );

        rank = T.last_same(3);
        assert( rank == 3 );
        rank = T.first_same(3);
        assert( rank == 1 );

        rank = T.last_same(1);
        assert( rank == 3 );
        rank = T.first_same(1);
        assert( rank == 1 );



        rank = T.last_same(4);
        assert( rank == 6 );
        rank = T.first_same(4);
        assert( rank == 4 );
        rank = T.last_same(5);
        assert( rank == 6 );
        rank = T.first_same(5);
        assert( rank == 4 );
        rank = T.last_same(6);
        assert( rank == 6 );
        rank = T.first_same(6);
        assert( rank == 4 );


        rank = T.last_same(7);
        assert( rank == 9 );
        rank = T.first_same(7);
        assert( rank == 7 );
        rank = T.last_same(8);
        assert( rank == 9 );
        rank = T.first_same(8);
        assert( rank == 7 );
        rank = T.last_same(9);
        assert( rank == 9 );
        rank = T.first_same(9);
        assert( rank == 7 );

        cout << __func__ << " ->    OK" << '\n' << endl;
    }

};

// #EX_END
