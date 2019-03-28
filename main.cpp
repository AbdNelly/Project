#include <iostream>
#include "Student.h"
#include "tree_node.h"
#include "tree.h"
#include <math.h>
#include <stdlib.h>

using namespace std;

int main() {
    int k;
    setlocale(LC_ALL, "rus");
    FILE *IN;
    Tree *T = new Tree();
    cout << "k = ";
    cin >> k;
    IN = fopen("in1.txt", "r");
    int key = T->read_tree(IN);
    if (key < 0) {
        delete T;
        fclose(IN);
        if (key == -2) {
            cout << "Empty tree! \n";
            return -2;
        }
        cout << "Can't read tree! \n";
        return -1;
    }
    Tree_node *T1 = T->get_root();
    cout << "Кол-во концевых эл-в: " << T->f1(T1) << endl;
    cout << "Длина наибольшей ветви дерева: " << T->f2(T1) << endl;
    cout << "Макс. кол-во эл-в в одном уровне: " << T->f3(T1) << endl;
    cout << "Макс. разность между глубинами левого и правого поддеревьев: " << T->f4(T1) << endl;
    cout << "Кол-во элементов, имеющих 1 потомка: " << T->f5(T1) << endl;
    cout << "Кол-во поддеревьев, имеющих не более k вершин: " << T->f6(T1, k) << endl;
    cout << "Кол-во поддеревьев, имеющих не более k уровней: " << T->f8(T1, k) << endl;
    cout << "Кол-во поддеревьев, имеющих не более k эл-в в любом уровне: " << T->f9(T1, k) << endl;
    cout << "Кол-во эл-в в k-м уровне: " << T->f10(T1, k) << endl;
    //cout << T->kol_vertex(T1) << endl;
    T->print_tree(T1, 0);
    delete T;
    fclose(IN);
    return 0;
}

int Tree::f1(Tree_node *root) {
    if (!root) {
        return 0;
    }
    if(!root->left && !root->right) {
        return 1;
    }
    return f1(root->left) + f1(root->right);
}

int Tree::f2(Tree_node *root) {
    if(!root) {
        return 0;
    }
    return max(f2(root->left), f2(root->right)) + 1;
}

int Tree::f3(Tree_node *root) {
    int maxi = 0, k, i = 0;
    if(!root) {
        return 0;
    }
    int maxlvl = f2(root);
    while(i < maxlvl) {
        k = kol(root, i);
        //cout << " " << k << endl;
        if(k > maxi) {
            maxi = k;
        }
        i++;
    }
    return maxi;
}

int Tree::kol(Tree_node *root, int lvl) {
    if(!root) {
        return 0;
    }
    if(lvl == 0) {
        return 1;
    }
    return kol(root->left, lvl - 1) + kol(root->right, lvl - 1);
}

int Tree::f4(Tree_node *root) {
    if(!root) {
        return 0;
    }
    if(!root->left) {
        if(!root->right) {
            return 0;
        }
        return max(f4(root->left), diff(root));
    }
    if(!root->right) {
        return max(f4(root->left), diff(root));
    }
    return max(max(f4(root->left), f4(root->right)), diff(root));
}

int Tree::diff(Tree_node *root) {
    if(!root) {
        return 0;
    }
    return abs(f2(root->left)-f2(root->right));
}

int max(int a, int b) {
    if(a > b) {
        return a;
    }
    return b;
}

int Tree::f5(Tree_node *root) {
    int kol = 0;
    if(!root) {
        return 0;
    }
    if((root->left && !root->right) || (!root->left && root->right)) {
        kol = 1;
    }
    return f5(root->left) + f5(root->right) + kol;
}

int Tree::f6(Tree_node *root, int k) {
    int kol = 0;
    if(!root) {
        return 0;
    }
    if(kol_vertex(root->left) + kol_vertex(root->right) <= k) {
        kol = 1;
    }
    return f6(root->left, k) + f6(root->right, k) + kol;
}

int Tree::kol_vertex(Tree_node *root) {
    int kol = 0;
    if(!root) {
        return 0;
    }
    kol = 1;
    return kol_vertex(root->left) + kol_vertex(root->right) + kol;
}

int Tree::f8(Tree_node *root, int k) {
    int kol = 0;
    if(!root) {
        return 0;
    }
    if (f2(root->left) <= k && f2(root->right) <= k) {
        kol = 1;
    }
    return f8(root->left, k) + f8(root->right, k) + kol;
}

int Tree::f9(Tree_node *root, int k) {
    int ans = 0, i = 0, t = 0;
    if(!root) {
        return 0;
    }
    while(i < f2(root)) {
        if(kol(root, i) > k) {
            t = 1;
            break;
        }
        i++;
    }
    if(t == 0) {
        ans = 1;
    }
    return f9(root->left, k) + f9(root->right, k) + ans;
}

int Tree::f10(Tree_node *root, int k) {
    if(!root) {
        return 0;
    }
    if(!root->left && !root->right) {
        return 1;
    }
    return kol(root, k);
}
