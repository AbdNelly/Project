#include <iostream>
#include <stdio.h>
#define max_lvl 5

using namespace std;

class Tree {
	private:
		Tree_node *root;
	public:
		Tree() {
			root = 0;
		}
		~Tree() {
			del(root);
			root = 0;
		}
    		int read_tree(FILE *IN) {
			root = new Tree_node();
			int r = root->read(IN);
    			if (r < 0) {
				return r;
			}
			root->left = NULL;
			root->right = NULL;
			while (1) {
        			Tree_node *tmp = new Tree_node();
        			if ((tmp->read(IN)) < 0) {
					if(!feof(IN)) {
					  delete tmp;
					  return -1;
					}
				    delete tmp;
				    return 0;
				}
				insert(root, tmp);
    			}
    			return 0;
		}
		void insert(Tree_node *root, Tree_node *add) {
    			if (*add < *root) {
        			if (!root->left) {
					root->left = add;
				} else { 
					insert(root->left, add);
    				}
			} else {
        			if (!root->right) { 
					root->right = add;
				} else {
					insert(root->right, add);
				}
   			}
		}
		Tree_node* get_root() const {
			return root;
		}
		void del(Tree_node *root) {
			if (root) {
			    del(root->left);
			    del(root->right);
			    delete root;
			    root = 0;
			}
		}
		void print_tree(Tree_node *root, int lvl) {
    			int i;
    			if(!root) {
				return;
			}
    			for (i = 0; i < lvl*2; i++) { 
				printf(" ");
			}
    			if (lvl == max_lvl) {
				return;
			}
    			root->print();
 			print_tree(root->left, lvl + 1);
    			print_tree(root->right, lvl + 1);
		}
		public:
		  int f1(Tree_node *);
		  int f2(Tree_node *);
		  int f3(Tree_node *);
		  int f4(Tree_node *);
		  int f5(Tree_node *);
		  int f6(Tree_node *, int);
 		  int diff(Tree_node *);
		  int kol(Tree_node *, int);
		  int f8(Tree_node *, int);
		  int f9(Tree_node *, int);
		  int f10(Tree_node *, int);
		  int kol_vertex(Tree_node *);
};
