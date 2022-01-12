#include <iostream>
#include "Graph.h"

int main() {
//    Graph g;
//
//    g.addNode(1);
//    g.addNode(6);
//    g.addNode(4);
//    g.addNode(9);
//    g.addArc(1, 6);
//    g.print();
//    std::cout << "1 ==========" << std::endl;
//    g.addArc(6, 1);
//    g.print();
//    std::cout << "2 ==========" << std::endl;
//    g.addArc(1, 4);
//    g.print();
//    std::cout << "3 ==========" << std::endl;
//    g.addArc(1, 9);
//    g.print();
//    std::cout << "4 ==========" << std::endl;
//    g.addArc(9, 4);
//    g.print();
//    std::cout << "5 ==========" << std::endl;
//    g.addArc(6, 4);
//    g.print();
//    std::cout << "6 ==========" << std::endl;
//    g.delArc(9, 4);
//    g.print();
//    std::cout << "7 ==========" << std::endl;
//    g.addArc(9, 4);
//    g.print();
//    std::cout << "8 ==========" << std::endl;
//    g.delArc(9, 4);
//    g.print();
//    std::cout << "9 ==========" << std::endl;
//    g.delArc(9, 4);
//    g.print();
//    std::cout << "10 ==========" << std::endl;
//    g.delArc(1, 9);
//    g.print();
//    std::cout << "11 ==========" << std::endl;
//    g.delArc(4, 6);
//    g.print();
//    std::cout << "12 ==========" << std::endl;
//    g.delArc(1, 4);
//    g.print();
//    std::cout << "13 ==========" << std::endl;
//    g.delArc(6, 1);
//    g.print();
//
//    std::cout << "14 ==========" << std::endl;
//    g.addNode(3);
//    g.addNode(7);
//    g.addNode(11);
//    g.addNode(13);
//    g.addArc(3, 7);
//    g.addArc(3, 11);
//    g.addArc(3, 13);
//    g.addArc(7, 11);
//    g.addArc(7, 13);
//    g.addArc(11, 13);
//    g.addArc(1, 13);
//    g.addArc(1, 6);
//    g.addArc(6, 7);
//    g.addArc(6, 9);
//    g.addArc(11, 4);
//
//    g.print();
//
//    std::cout << "Обход" << std::endl;
//    g.roundWidth(3); // 3 13 11 7 1 4 6 9
//
//    std::cout << "15 ==========" << std::endl;
//    g.delNode(3);
//    g.print();
//    std::cout << "16 ==========" << std::endl;
//    g.delNode(13);
//    g.print();
//    std::cout << "17 ==========" << std::endl;
//    g.delNode(11);
//    g.print();
//    std::cout << "18 ==========" << std::endl;
//    g.delNode(7);
//    g.print();

    Graph G1;

    for (int i = 0; i < 10; ++i) {
        G1.addNode(10 - i);
    }

////    -------
//    G1.addArc(1, 1);
//    G1.print();
//
////    -------

    for (int i = 1; i < 10; ++i) {
        //G1.addNode(i);
        for (int j = 1; j <= i; ++j) {
            G1.addArc(10-i, 10-j);
        }
    }

    G1.print();
    std::cout << std::endl;

    for (int i = -1; i < 12; ++i) {
     //   if (i%2 != 0)
            G1.delArc(i,i+1);
    }

    G1.print();
    std::cout<<"******************************************"<<std::endl;
    for (int i = 0; i < 10; ++i) {
        G1.addNode(10-i);
    }
    for (int i = 1; i < 10; ++i) {
        //G1.addNode(i);
        for (int j = 1; j <= i; ++j) {
            G1.addArc(i+1, i);
        }
    }
    std::cout << "+++++" << std::endl;
    G1.print();
    std::cout << std::endl;

    G1.roundWidth(1);


    return 0;
}
