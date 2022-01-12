#include <iostream>
#include <queue>
#include "set"
#include "list"

struct node;
struct arc;

struct node { // вершина графа

    int number{}; // номер вершины
    node *nextNode; // следующая вершина
    node *prevNode; //
    arc *arcs; // ссылка на список дуг
    int mark = 0;
    node *p = nullptr;

    node() {
        nextNode = nullptr;
        prevNode = nullptr;
        arcs = nullptr;
    }
};

struct arc { // дуга графа
    node *node_; // ссылка на вершину, в которую смотрит дуга
    arc *next; // ссылка на следующую вершину
    arc *prev;
    int mark = 0;

    arc() {
        node_ = nullptr;
        prev = nullptr;
        next = nullptr;
    }
};

class Graph {
    node *root;

public:

    Graph() {
        root = nullptr;
    }

    ~Graph() {
        node *help;
        while (root != nullptr) {
            help = root->nextNode;
            delNode(root->number);
            root = help;
        }
        root = nullptr;
    }

    int addNode(int a) {
        if (root == nullptr) {
            root = new node;
            root->number = a;
            return true;
        } else {
            // поиск ноды с таким же номером (вдруг уже существует)
            node *cur = root;

            while (cur != nullptr) {
                if (cur->number == a) {
                    return false;
                }
                cur = cur->nextNode;
            }

            // добавление новой ноды в начало
            cur = root;
            root = new node;
            root->number = a;
            root->nextNode = cur;
            cur->prevNode = root;
            return true;
        }
    }

    int addArc(int a, int b) { // а - откуда b - куда
        // ищем дугу

        node *nodeA = root;
        node *nodeB = root;

        if (a == b) {
            return false;
        }

        while (nodeA != nullptr && nodeA->number != a) {
            nodeA = nodeA->nextNode;
        }
        while (nodeB != nullptr && nodeB->number != b) {
            nodeB = nodeB->nextNode;
        }

        if (nodeA == nullptr) {
            std::cout << "node " << a << " not found" << std::endl;
            return false;
        }
        if (nodeB == nullptr) {
            std::cout << "node " << b << " not found" << std::endl;
            return false;
        }

        if (nodeA->number == a && nodeB->number == b) {
            // проверка на то что дуги нет
            // ищем куда добавить

            //---------------------------------

            if (nodeA->arcs == nullptr) { // не существует дуг
                nodeA->arcs = new arc;
                nodeA->arcs->node_ = nodeB;
                if (nodeB->arcs == nullptr) {
                    nodeB->arcs = new arc;
                    nodeB->arcs->node_ = nodeA;
                } else {
                    arc *carArc = nodeB->arcs;
                    nodeB->arcs = new arc;
                    nodeB->arcs->next = carArc;
                    carArc->prev = nodeB->arcs;
                    nodeB->arcs->node_ = nodeA;
                }
                return true;
            } else { // существует хотя бы одна дуга
                // поиск дуги с таким же номером (вдруг уже существует)
                arc *curArc = nodeA->arcs; // node *cur = root; (было)

                while (curArc != nullptr) {
                    if (curArc->node_ == nodeB) {
                        return false;
                    }
                    curArc = curArc->next;
                }

                curArc = nodeA->arcs;
                nodeA->arcs = new arc;
                nodeA->arcs->next = curArc;
                curArc->prev = nodeA->arcs;
                nodeA->arcs->node_ = nodeB;

                if (nodeB->arcs == nullptr) {
                    nodeB->arcs = new arc;
                    nodeB->arcs->node_ = nodeA;
                } else {
                    arc *carArc = nodeB->arcs;
                    nodeB->arcs = new arc;
                    nodeB->arcs->next = carArc;
                    carArc->prev = nodeB->arcs;
                    nodeB->arcs->node_ = nodeA;
                }

                return true;
            }
            //---------------------------------

            // создаём новую дугу

            // добавляем дугу
        }
        std::cout << "OMG";
        return false;
    }

    int delNode(int a) {
        // существует ли вершина?
        node *nodeA = root;
        node *nodeHelp = nullptr;

        while (nodeA != nullptr && nodeA->number != a) {
            nodeHelp = nodeA;
            nodeA = nodeA->nextNode;
        }

        if (nodeA == nullptr) {
            std::cout << "node " << a << " not found" << std::endl;
            return false;
        }

        // идём по всем вершинам и ищем вхождение вершины в дугах. Удаляем эти дуги
        node *curNode = root;
        arc *curArc;
        arc *helpArc;

        while (curNode != nullptr) {
            curArc = curNode->arcs;

            if (curArc != nullptr) {
                while (curArc != nullptr) {
                    helpArc = curArc;
                    curArc = curArc->next;
                    if (helpArc->node_ == nodeA) {
                        delArc(curNode->number, a); // храни господь эту строчку
                    }
                }
            }

            curNode = curNode->nextNode;
        }

        // удаляем все дуги выходящие из вершины А
        curArc = nodeA->arcs;
        arc *curArcHelp;

        while (curArc != nullptr) {
            curArcHelp = curArc;
            curArc = curArc->next;
            delete curArcHelp;
        }

        // удаляем вершину A
        if (nodeHelp == nullptr) { // А - первая вершина списка
            if (root->nextNode == nullptr && root->prevNode == nullptr) {
                root = nodeA->nextNode;
                return false;
            }
            root = nodeA->nextNode;
            root->prevNode = nullptr;
        } else if (nodeA->nextNode == nullptr) { // А - последняя вершина списка
            nodeHelp->nextNode = nullptr;
        } else { // А - вершина в середине
            nodeHelp->nextNode = nodeA->nextNode;
            nodeA->nextNode->prevNode = nodeHelp;
        }
        delete nodeA;
        return true;
    }

    int delArc(int a, int b) {
        node *nodeA = root;
        node *nodeB = root;

        while (nodeA != nullptr && nodeA->number != a) {
            nodeA = nodeA->nextNode;
        }
        while (nodeB != nullptr && nodeB->number != b) {
            nodeB = nodeB->nextNode;
        }

        if (nodeA == nullptr) {
            std::cout << "node " << a << " not found" << std::endl;
            return false;
        }
        if (nodeB == nullptr) {
            std::cout << "node " << b << " not found" << std::endl;
            return false;
        }

        arc *curArc = nodeA->arcs;
        arc *lastArc = nullptr;

        while (curArc != nullptr && curArc->node_ != nodeB) { // ищем дугу
            lastArc = curArc;
            curArc = curArc->next;
        }

        if (curArc == nullptr) {
            return false;
        }

        if (curArc->node_ == nodeB) {
            if (lastArc == nullptr) { // АB - первая дуга
                lastArc = curArc->next;
                nodeA->arcs = lastArc;
            } else if (curArc->next == nullptr) { // АB - последняя дуга списка
                lastArc->next = nullptr;

            } else { // А - вершина в середине
                lastArc->next = curArc->next;
                curArc->next->prev = lastArc;
            }
            delete curArc;

            curArc = nodeB->arcs;
            lastArc = nullptr;

            while (curArc != nullptr && curArc->node_ != nodeA) { // ищем дугу
                lastArc = curArc;
                curArc = curArc->next;
            }

            if (curArc->node_ == nodeA) {
                if (lastArc == nullptr) { // АB - первая дуга
                    lastArc = curArc->next;
                    nodeB->arcs = lastArc;
                } else if (curArc->next == nullptr) { // АB - последняя дуга списка
                    lastArc->next = nullptr;
                } else { // А - вершина в середине
                    lastArc->next = curArc->next;
                    curArc->next->prev = lastArc;
                }
                delete curArc;

            } else { return false; }

        } else { return false; }

    }

    int searchNode(int a) {
        node *nodeA = root;

        while (nodeA != nullptr && nodeA->number != a) {
            nodeA = nodeA->nextNode;
        }

        if (nodeA == nullptr) {
            std::cout << "node " << a << " not found" << std::endl;
            return false;
        } else return true;
    }

    int searchArc(int a, int b) {
        node *nodeA = root;
        node *nodeB = root;

        while (nodeA != nullptr && nodeA->number != a) {
            nodeA = nodeA->nextNode;
        }
        while (nodeB != nullptr && nodeB->number != b) {
            nodeB = nodeB->nextNode;
        }

        if (nodeA == nullptr) {
            std::cout << "node " << a << " not found" << std::endl;
            return false;
        }
        if (nodeB == nullptr) {
            std::cout << "node " << b << " not found" << std::endl;
            return false;
        }

        arc *curArc = nodeA->arcs;

        while (curArc != nullptr && curArc->node_ != nodeB) { // ищем дугу
            curArc = curArc->next;
        }

        if (curArc != nullptr && curArc->node_ == nodeB) {
            return true;
        } else return false;
    }

    void print() {
        node *thisNode = root;
        arc *thisArc;

        if (thisNode == nullptr) {
            std::cout << "Graph is empty" << std::endl;
        } else {
            while (thisNode != nullptr) {
                std::cout << "|" << thisNode->number;
                if (thisNode->p != nullptr) std::cout << thisNode->p->number;
                std::cout << "| --> ";
                thisArc = thisNode->arcs;

                while (thisArc != nullptr) {
                    std::cout << thisArc->node_->number << " --> ";
                    thisArc = thisArc->next;
                }
                std::cout << " \\ " << std::endl;
                thisNode = thisNode->nextNode;
            }
        }
    }

    bool roundWidth(int a) {
        node *nodeA = root;

        while (nodeA != nullptr && nodeA->number != a) {
            nodeA = nodeA->nextNode;
        }

        if (nodeA == nullptr) {
            std::cout << "Start node " << a << " not found!" << std::endl;
            return false;
        }

        std::queue<node *> Q;
        Q.push(nodeA);
        nodeA->mark = 1;
        arc *w = nullptr;
        std::cout << "Обход в ширину(вершины): ";

        while (!Q.empty()) {
            arc *q = Q.front()->arcs;
            w = Q.front()->arcs;

            while (w != nullptr) {
                w->mark = true;

                node *p = w->node_;
                if (p->mark == 0) {
                    p->mark = 1;
                    Q.push(p);
                }

                w = w->next;
            }

            if (q != nullptr) {
                if (q->node_->mark == 1) {
                    q->node_->mark = 2;
                }
            }

            if (q != nullptr)
                q = q->next;
            if (q == nullptr || q->mark) {
                std::cout << Q.front()->number << ' ';
                Q.pop();
            }
        }

        std::cout << std::endl;
    }

//     std::list <std::set<int>> kerbosh(int **&a) {
//        int SIZE =
//        std::set<int> M, G, K, P;
//        std::list <std::set<int>> REZULT;
//        for (int i = 0; i < SIZE; i++) {
//            K.insert(i);
//        }
//        int v, Count = 0, cnt = 0;
//        int Stack1[100];
//        std::set<int> Stack2[100];
//        std::set<int>::iterator theIterator;
//        theIterator = K.begin();
//        while ((K.size() != 0) || (M.size() != 0)) {
//            if (K.size() != 0) {
//                theIterator = K.begin();
//                v = *theIterator;
//                Stack2[++Count] = M;
//                Stack2[++Count] = K;
//                Stack2[++Count] = P;
//                Stack1[++cnt] = v;
//                M.insert(v);
//                for (int i = 0; i < SIZE; i++) {
//                    if (a[v][i]) {
//                        theIterator = K.find(i);
//                        if (theIterator != K.end()) {
//                            K.erase(theIterator);
//                        }
//                        theIterator = P.find(i);
//                        if (theIterator != P.end()) {
//                            P.erase(theIterator);
//                        }
//                    }
//                }
//                theIterator = K.find(v);
//                if (theIterator != K.end()) {
//                    K.erase(theIterator);
//                }
//            } else {
//                if (P.size() == 0) {
//                    REZULT.push_back(M);
//                }
//                v = Stack1[cnt--];
//                P = Stack2[Count--];
//                K = Stack2[Count--];
//                M = Stack2[Count--];
//                theIterator = K.find(v);
//                if (theIterator != K.end()) {
//                    K.erase(theIterator);
//                }
//                P.insert(v);
//            }
//        }
//        return REZULT;
//    }
//
//    void bronKerbosh() {
//        std::list <std::set<int>> res;
//        res = kerbosh()
//    }
};