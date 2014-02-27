#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <cctype>
#include <cstdio>
#include <csignal>
#include <dirent.h>

void print_usage( std::ostream& out )
{
	out << "Usage: fuckyou <process name> \n";
	out << "fuckyou -h prints this text\n";
	exit(1);
}

void die( std::string message )
{
    using std::cerr;
    using std::cout;
    if( cerr )
    {
        cerr << message << "\n";
    }
    else
    {
        cout << message << "\n";
    }
    exit(1);    
}

bool check_if_number( std::string str )
{
    using std::string;
    for ( string::iterator i = str.begin(); i != str.end(); ++i )
    {
        if ( !isdigit( *i ) )
        {
            return false;
        }
    }
    return true;
}

std::string flip_char( char );

std::vector<int> get_pids( std::string pname );

int main(int argc, char const *argv[])
{
	using std::cout;
    using std::string;
    using std::vector;

	if( argc < 2 )
	{
		print_usage( std::cerr );
	}

    if( string( argv[1] ) == "-h" )
    {
        print_usage( cout );
    }

    string proc_name( argv[1] );    
    vector<int> pids = get_pids( proc_name );
    if( pids.size() > 0 )
    {
        for (int i = 0; i < pids.size(); ++i)
        {
            kill( pids[i] , SIGTERM );
        }
        cout << "\n";
        cout << "(\u1D0A\u00B0\u25FD\u00B0)\u1D0A\u25E0 ";
        for ( string::reverse_iterator it = proc_name.rbegin(); it != proc_name.rend(); ++it )
        {
            cout << flip_char( *it );
        }
        cout << std::endl;
        cout << "\n";
    }
    else
    {
        cout << "There's no 'fuckable' process running with that name\n";
    }
	return 0;
}

/*
 Code borrowed from here http://phoxis.org/2013/09/13/find-process-ids-of-a-running-process-by-name/
 (Although it's a little different)
*/
std::vector<int> get_pids( std::string pname )
{
    using std::vector;
    using std::ifstream;
    using std::string;
    
    vector<int> pidlist;

    ifstream fin;

    DIR *dirp;
    dirent *entry;
    
    dirp = opendir ("/proc/");
    if (dirp == NULL)
    {
        die( "Can't open the dir" );
    }

    while ( ( entry = readdir (dirp) ) != NULL )
    {
        string dname( entry->d_name );
        // with this check we avoid . and .. dirs too
        if ( check_if_number ( dname ) )
        {
            /* A file may not exist, it may have been removed.
            * dut to termination of the process. Actually we need to
            * make sure the error is actually file does not exist to
            * be accurate.
            */
            fin.open( string( "/proc/" +  dname + "/comm" ).c_str() );
            if ( fin )
            {
                string cmm;
                fin >> cmm;
                if ( cmm == pname )
                {
                    int pid;
                    sscanf( dname.c_str(), "%i", &pid );
                    pidlist.push_back( pid );
                }
                fin.close();
            }
        }
    }
    closedir (dirp);
    return pidlist;
}

//code extracted from http://pastebin.ca/599880
std::string flip_char( const char c ) 
{
    if (c == 'a') 
    {
        return "\u0250";
    }
    else if (c == 'b') 
    {
        return "q";
    }
    else if (c == 'c') 
    {
        return "\u0254"; //Open o -- copied from pne
    }
    else if (c == 'd') 
    {
        return "p";
    }
    else if (c == 'e') 
    {
        return "\u01DD";
    }
    else if (c == 'f') 
    {
        return "\u025F"; //Copied from pne --
        //LATIN SMALL LETTER DOTLESS J WITH STROKE
    }
    else if (c == 'g') 
    {
        return "b";
    }
    else if (c == 'h') 
    {
        return "\u0265";
    }
    else if (c == 'i') 
    {
        return "\u0131";//'\u0131\u0323' //copied from pne
    }
    else if (c == 'j') 
    {
        return "\u0638";
    }
    else if (c == 'k') 
    {
        return "\u029E";
    }
    else if (c == 'l') 
    {
        return "1";
    }
    else if (c == 'm') 
    {
        return "\u026F";
    }
    else if (c == 'n') 
    {
        return "u";
    }
    else if (c == 'o') 
    {
        return "o";
    }
    else if (c == 'p') 
    {
        return "d";
    }
    else if (c == 'q') 
    {
        return "b";
    }
    else if (c == 'r') 
    {
        return "\u0279";
    }
    else if (c == 's') 
    {
        return "s";
    }
    else if (c == 't') 
    {
        return "\u0287";
    }
    else if (c == 'u') 
    {
        return "n";
    }
    else if (c == 'v') 
    {
        return "\u028C";
    }
    else if (c == 'w') 
    {
        return "\u028D";
    }
    else if (c == 'x') 
    {
        return "x";
    }
    else if (c == 'y') 
    {
        return "\u028E";
    }
    else if (c == 'z') 
    {
        return "z";
    }
    else if (c == '[') 
    {
        return "]";
    }
    else if (c == ']') 
    {
        return "[";
    }
    else if (c == '(') 
    {
        return ")";
    }
    else if (c == ')') 
    {
        return "(";
    }
    else if (c == '{') 
    {
        return "}";
    }
    else if (c == '}') 
    {
        return "{";
    }
    else if (c == '?') 
    {
        return "\u00BF"; //From pne
    }
    else if (c == '¿') 
    {
        return "?";
    }
    else if (c == '!') 
    {
        return "\u00A1";
    }
    else if (c == '\'') 
    {
        return ",";
    }
    else if (c == ',') 
    {
        return "\'";
    }
    return std::string(1,c);
}