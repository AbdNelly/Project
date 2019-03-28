#include <iostream>
#include <stdio.h>

using namespace std;

class Tree_node: public Student {
	private:
		Tree_node *left; 
		Tree_node *right;
	public:
		Tree_node(const char *n = 0, int m = 0): Student(n, m) {
			left = 0;
			right = 0;
		}
		Tree_node(const Tree_node& x): Student(x) {
			left = 0;
			right = 0;
		}
		~Tree_node() {
        		left = 0;
			right = 0;
		}
		void print() {
		    cout << name << " " << mark << endl;	
		 }
		friend class Tree;
};
