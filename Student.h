#include <iostream>
#include <string.h>
#include <stdio.h>
#define len 1234

using namespace std;

class Student {
	protected:
		char *name;
		int mark;
	private:
		int init(const char *n, int m) {
			mark = m;
			if (n != 0) {
        			if (!(name = new char[strlen(n) + 1])) {
					return -3;
				}
        			strcpy(name, n);
			} else {
				name = 0;
			}
    			return 0;
		}
	public:
		Student(const char *n = 0, int m = 0) {
			init(n, m);
		}
                Student(const Student& x) {
			init(x.name, x.mark);
		}
		~Student() {
			if (name != 0) {
        			delete[] name;
        			name = 0;
    			}
    			mark = 0;
		}
		Student& operator = (const Student& x) {
    			init(x.name, x.mark);
    			return *this;
		}
		int operator < (const Student& b) {
			int k = strcmp(name, b.name);
			if (k == 0) {
			  return mark < b.mark;
			}
			if (k < 0) {
			  return 1;
			}
			return 0;
		}
		int operator > (const Student& b) {
			int k = strcmp(name, b.name);
			if (k == 0) {
			  return mark > b.mark;
			}
			if (k > 0) {
			  return 1;
			}
			return 0;
		}
		int operator <= (const Student& b) {
			int k = strcmp(name, b.name);
			if (k == 0) {
			  return mark <= b.mark;
			}
			if (k <= 0) {
			  return 1;
			}
			return 0;
		}
		int operator >= (const Student& b) {
			int k = strcmp(name, b.name);
			if (k == 0) {
			  return mark >= b.mark;
			}
			if (k >= 0) {
			  return 1;
			}
			return 0;
		}
		int operator == (const Student& b) {
			int k = strcmp(name, b.name);
			if (k == 0) {
			    return mark == b.mark;
			}
			return 0;
		}
		int operator != (const Student& b) {
			int k = strcmp(name, b.name);
			if (k == 0) {
			    return mark != b.mark;
			}
			return 1;
		}
		int read(FILE *IN) {
    			char s[len];
    			if (fscanf(IN, "%s %d", s, &mark) != 2) {
				if(!feof(IN)) { 
					return -1;
				}
        			return -2;
			}
    			return init(s, mark);
		}		
		char* st_name() const {
			return (char*) name;
		}
		int st_mark() const {
			return mark;
		}
};
