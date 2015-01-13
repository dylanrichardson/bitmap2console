#ifndef BITMAP2CONSOLE_H
#define BITMAP2CONSOLE_H

using namespace std;

class CPIC
{
	private:
		unsigned char *colors;
		int width;
		int height;
	public:
		CPIC (int w, int h); 
	    void save(ofstream& of); 
	    void load(ifstream& inf);
	    void setColors (unsigned char *c);
		void display (void); 
};

CPIC* bitmap2console (char*);

#endif
