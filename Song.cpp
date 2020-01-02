//
//  Song.cpp
//

#include "Song.h"
#include <iostream>
#include <iomanip>
using namespace std;


ostream & operator <<(ostream & strm, const Song & obj)
{
    strm << setw(8) << left << obj.getId()
    << setw(24) << left << obj.getTitle()
    << setw(23) << left << obj.getArtist()
    << setw(31) << left << obj.getAlbum()
    << setw(7) << left << obj.getGenre()
    << setw(10) << left << obj.getDuration()
    << setw(5) << left << obj.getYear() << endl;
    return strm;
}


//overload operator
bool Song :: operator > (const Song & right)
{
    return id > right.id;
}

bool Song :: operator < (const Song & right)
{
    
    return id < right.id;
}

bool Song :: operator == (const Song & right)
{
    return id == right.id;
}

