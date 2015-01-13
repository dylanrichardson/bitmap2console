#include <iostream>
#include <fstream>
#include <windows.h>
#include "bitmap2console.h"
#include <dirent.h>
#include <string.h>
#include <iomanip>

using namespace std;

static void show_usage(std::string name)
{
    cerr << "Usage: " << name << " <option(s)> SOURCE DESTINATION\n"
              << "Options:\n"
              << "\t-h,--help\t\tShow this help message\n"
              << "\t-s,--single SINGLE\tSpecify the only bitmap file\n"
              << "\t-f,--folder FOLDER\tSpecify the folder containing multiple bitmaps\n"
              << endl;
}

void createCPIC (char *path, char *dest)
{
	CPIC *cpic = bitmap2console(path);
	if (cpic!=NULL)
	{
		ofstream outfile;
		outfile.open(dest, ios::binary | ios::out);
		cpic->save(outfile);
	}
}

bool hasEnding (string const &fullString, string const &ending)
{
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

int main(int argc, char** argv) {
	char *path, *dest;
	if (argc==1)
	{
		path = new char [50];
		dest = new char [50];
		cout<<"Path: ";
		cin>>path;
		cout<<"Destination: ";
		cin>>dest;
		createCPIC(path,dest);
	}
	else if (argc == 2 || argc > 4)
	{
        show_usage(argv[0]);
        return 1;
    }
    else if (!strcmp(argv[1],"-f")||!strcmp(argv[1],"--folder"))
    {
    	if (argc!=4)
    	{
    		show_usage(argv[0]);
	        return 1;
	    }
    	//folder
    	DIR *dir;
		struct dirent *ent;
		if ((dir = opendir (argv[2])) != NULL) {
			/* print all the files and directories within directory */
			cout<<"Files converted:    0";
			int i = 0;
			while ((ent = readdir (dir)) != NULL) {
				if (ent->d_name[0]!='.'&&hasEnding(ent->d_name,".bmp"))
				{
					int len = strlen(ent->d_name);
					char *path = new char [strlen(argv[2])+len+2];
					strncpy(path,argv[2],strlen(argv[2])+1);
					strcat(path,"/");
					strcat(path,ent->d_name);
					strcat(path,"\0");
					char *dest = new char [strlen(argv[3])+len+2];
					strncpy(dest,argv[3],strlen(argv[3])+1);
					strcat(dest,"/");
					strncat(dest,ent->d_name,strlen(argv[3])+len-4);
					dest[strlen(argv[3])+len-3] = '\0';
					strcat(dest,".cpic\0");
					createCPIC(path,dest);
					i++;
					cout<<"\b\b\b\b    \b\b\b\b"<<setw(4)<<i;
				}
			}
			closedir (dir);
		} else {
			/* could not open directory */
			perror ("");
			return 1;
		}
    }
    else
    {
		createCPIC(argv[1],argv[2]);
    }
	
	return 0;
}




