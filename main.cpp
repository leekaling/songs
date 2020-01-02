
#include "Song.h"
#include "BinarySearchTree.h"
#include "HashTable.h"
#include "StackADT.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

using namespace std;

// Constants for the menuc
const char  LIST_CHOICE = 'L',
            SEARCH_CHOICE = 'S',
            INSERT_CHOICE = 'I',
            DELETE_CHOICE = 'D',
            UNDO_DELETE_CHOICE = 'U',
            MENU_CHOICE = 'M',
            QUIT_CHOICE = 'Q';

//read data and get user input
void readData(string filename, BinarySearchTree<Song>*, BinarySearchTree<Song>*, HashTable<Song>*);
void performChoice(char, BinarySearchTree<Song>*, BinarySearchTree<Song>*, HashTable<Song>*, Stack<Song>);

//reused functions
bool validateID(string);
void printMenu();
void displaySong(Song&);
int compareId(Song&, Song&);
int compareTitle(Song&, Song&);

//list functions
void ListManager(BinarySearchTree<Song>*, BinarySearchTree<Song>*, HashTable<Song>*);
void ListUnsorted(HashTable<Song>* SongTable);
void ListById(BinarySearchTree<Song>* SongIdTreePtr);
void ListByTitle(BinarySearchTree<Song>* SongTitleTreePtr);
void ListAsIndentedTree(BinarySearchTree<Song>* SongIdTreePtr, BinarySearchTree<Song>* SongTitleTreePtr);

//search functions
void SearchManager(BinarySearchTree<Song>*, HashTable<Song>*);
void SearchById(HashTable<Song>* SongTable);
void SearchByTitle(BinarySearchTree<Song>* SongTitleTreePtr);

//insert and delete functions
void InsertManager(BinarySearchTree<Song>*, BinarySearchTree<Song>*, HashTable<Song>*);
void DeleteManager(BinarySearchTree<Song>*, BinarySearchTree<Song>*, HashTable<Song>*);
void UndoDelete(Stack<Song> &,BinarySearchTree<Song>*, BinarySearchTree<Song>*, HashTable<Song>* );

int main()
{
    char choice;
    const string FILENAME = "songs.txt";
    
    // 2 bst and 1 hash table
    BinarySearchTree<Song>* SongIdTreePtr = new BinarySearchTree<Song>() ;
    BinarySearchTree<Song>* SongTitleTreePtr = new BinarySearchTree<Song>() ;
    HashTable<Song>* SongTable = new HashTable<Song>();
    Stack<Song> deletedSongs;
    
    readData( FILENAME, SongIdTreePtr, SongTitleTreePtr, SongTable );
    
    printMenu();
    
    cout << "Enter your choice: " ;
    cin >> choice;
    choice = toupper(choice);
    
    while (choice != QUIT_CHOICE)
    {
        performChoice(choice, SongIdTreePtr, SongTitleTreePtr, SongTable, deletedSongs);
        cout << "Enter your choice: " ;
        cin >> choice;
        choice = toupper(choice);
    }
    
    delete SongIdTreePtr;
    delete SongTitleTreePtr;
    delete SongTable;
    
}



/**********************************************************************
 This function get the choice user choosen as parameter then perform  *
 the correspond BST operation it will return a bool value             *
 **********************************************************************/
void performChoice(char choice, BinarySearchTree<Song>* SongIdTreePtr, BinarySearchTree<Song>* SongTitleTreePtr, HashTable<Song>* SongTable, Stack<Song> deletedSongs)
{
    switch (choice)
    {
        case LIST_CHOICE:
            ListManager(SongIdTreePtr , SongTitleTreePtr, SongTable);
            break;
        case SEARCH_CHOICE:
            SearchManager(SongIdTreePtr, SongTable);
            break;
        case INSERT_CHOICE:
            InsertManager(SongIdTreePtr , SongTitleTreePtr, SongTable);
            break;
        case DELETE_CHOICE:
            DeleteManager(SongIdTreePtr , SongTitleTreePtr, SongTable);
            break;
        case UNDO_DELETE_CHOICE:
            UndoDelete(deletedSongs, SongIdTreePtr, SongTitleTreePtr, SongTable);
            break;
        case MENU_CHOICE:
            printMenu();
            break;
        default:
            cout << "Invalid option.\n" << endl;
            break;
    }
}

/************************************
 This function will print out       *
 the menu of all the BST operations *
 ************************************/
void printMenu()
{
    cout << "L - List all songs \n"
    << "S - Search a song \n"
    << "I - Insert a new song\n"
    << "D - Delete a song \n"
    << "U - Undo delete \n"
    << "Q - Write data to file and quit program \n\n";
}


void ListManager(BinarySearchTree<Song>* SongIdTreePtr, BinarySearchTree<Song>* SongTitleTreePtr, HashTable<Song>* SongTable)
{
    cout << "========================================\n"
    << "List\n"
    << "========================================\n";
    
    cout << "U - Unsorted\n"
    << "P - Sorted by ID\n"
    << "S - Sorted by title\n"
    << "T - Print ID and title tree as an indented list\n";
    
    char choice;
    cout << "Enter your choice: " ;
    cin >> choice;
    choice = toupper(choice);
    
    while (choice != 'Q')
    {
        
        switch (choice)
        {
            case 'U':
                ListUnsorted(SongTable);
                break;
            case 'P':
                ListById(SongIdTreePtr);
                break;
            case 'S':
                ListByTitle(SongTitleTreePtr);
                break;
            case 'T':
                ListAsIndentedTree(SongIdTreePtr, SongTitleTreePtr);
                break;
            default: cout << "Invalid option!\n";
        }
        
        cout << "Enter a method ('Q' to stop searching): " ;
        cin >> choice;
        choice = toupper(choice);
        
    }
    
    cout << "==========END LIST SECTION==========";
}


/****************************************************************
 This function will allow the user to choose the search function *
 they want to perform, search using ID or title                  *
 ****************************************************************/
void SearchManager(BinarySearchTree<Song>* SongTitleTreePtr, HashTable<Song>* SongTable)
{
    cout << "========================================\n"
         << "Search\n"
         << "========================================\n";
    
    cout << "P - Search by ID \n"
         << "S - Search by title \n";
    
    char choice;
    cout << "Enter a method ('Q' to stop searching): " ;
    cin >> choice;
    choice = toupper(choice);
    
    while (choice != 'Q')
    {
        
        switch (choice)
        {
            case 'P':
                SearchById(SongTable);
                break;
            case 'S':
                SearchByTitle(SongTitleTreePtr);
                break;
            default: cout << "Invalid option!\n";
        }
        
        cout << "Enter a method ('Q' to stop searching): " ;
        cin >> choice;
        choice = toupper(choice);
    }
    
    cout << "==========END SEARCH SECTION==========";
}

void SearchById(HashTable<Song>* SongTable)
{
    
    cout << "----------------------------------------\n"
    << "Search by ID\n"
    << "----------------------------------------\n";
    
    string target;
    cout << "Enter the ID: ";
    cin >> target;
    
    if (validateID(target))
    { // if id is valid
        
        Song returnedSong;
        
        if (SongTable->searchHash(target, returnedSong))
        { // if song is found
            cout << "Found: \n";
            cout << returnedSong;
        }
        else
        { // if song is not in the table
            cout << "Not found!\n";
        }
    }
    else
    {
        // if id is not valid
        cout << "Invalid ID!\n";
    }
}

void SearchByTitle(BinarySearchTree<Song>* SongTitleTreePtr)
{
    cout << "----------------------------------------\n"
    << "Search by Title\n"
    << "----------------------------------------\n";
    
    string target;
    cout << "Enter the title: ";
    cin >> target;
    
    Song returnedSong;

    /***************/
    SongTitleTreePtr->search(returnedSong, compareTitle, displaySong);

}


void ListUnsorted(HashTable<Song>* SongTable)
{
    cout << "----------------------------------------\n"
        << "Unsorted\n"
    << "----------------------------------------\n";
    SongTable->printHash();
}

void ListById(BinarySearchTree<Song>* SongIdTreePtr) {
    cout << "----------------------------------------\n"
    << "Sorted by ID\n"
    << "----------------------------------------\n";
    SongIdTreePtr->inOrder(displaySong);
}

void ListByTitle(BinarySearchTree<Song>* SongTitleTreePtr) {
    cout << "----------------------------------------\n"
    << "Sorted by title\n"
    << "----------------------------------------\n";
    SongTitleTreePtr->inOrder(displaySong);
}

void ListAsIndentedTree(BinarySearchTree<Song>* SongIdTreePtr, BinarySearchTree<Song>* SongTitleTreePtr) {
    cout << "----------------------------------------\n"
    << "Print ID tree as an indented list \n"
    << "----------------------------------------\n";
    SongIdTreePtr->RightRootLeft(displaySong,0);
    
    cout << "----------------------------------------\n"
    << "Print title tree as an indented list \n"
    << "----------------------------------------\n";
    SongTitleTreePtr->RightRootLeft(displaySong,0);
}
/*****************************************************************************
 This function reads data about songs from a given file and inserts it
 into a Binary Search Tree.
 *****************************************************************************/
void readData(string filename, BinarySearchTree<Song>* SongIdTreePtr, BinarySearchTree<Song>* SongTitleTreePtr, HashTable<Song>* SongTable)
{
        ifstream inputFile;
        inputFile.open(filename);
        
        if (inputFile.fail())
        {
            cout << "\nThe file failed to open! Please try again...\n";
            exit(EXIT_FAILURE);
        }
        
        // use local variables to store data from file and use them
        // to build a Song object
        Song localSong;
        string id, title, artist, album, genre, duration, year;
        int durationInt, yearInt;
        
        while(getline(inputFile, id, ';'))
        {
            getline(inputFile, title, ';');
            getline(inputFile, artist, ';');
            getline(inputFile, album, ';');
            getline(inputFile, genre, ';');
            getline(inputFile, duration, ';');
            getline(inputFile,year);
            
            durationInt = stoi(duration);
            yearInt = stoi(year);
            
            localSong.setId(id);
            localSong.setTitle(title);
            localSong.setArtist(artist);
            localSong.setAlbum(album);
            localSong.setGenre(genre);
            localSong.setDuration(durationInt);
            localSong.setYear(yearInt);
            
            // insert the Song object into the Binary Search Tree
            SongIdTreePtr->insert(localSong, compareId);
            SongTitleTreePtr->insert(localSong, compareTitle);
            //insert into Hash
            SongTable->insertHash(id, localSong);
            
        }
        inputFile.close();
}

/*****************************************************************************
 This function allows the user to insert a new song into the two Binary      *
 Search Trees and the hash table.                                            *
 *****************************************************************************/
void InsertManager(BinarySearchTree<Song>* SongIdTreePtr, BinarySearchTree<Song>* SongTitleTreePtr, HashTable<Song>* SongTable)
{
    Song localSong;
    string id, title, artist, album, genre;
    int duration, year;
    bool inserted = false;
    
    cout << "Enter the ID of the song you want to add: ";
    getline (cin, id); // check?
    validateID(id);
    
    cout << "Enter the title of the song you want to add: ";
    getline (cin, title);
    
    cout << "Enter the artist of the song you want to add: ";
    getline (cin, artist);
    
    cout << "Enter the album of the song you want to add: ";
    getline (cin, album);
    
    cout << "Enter the genre of the song you want to add: ";
    getline (cin, genre);
    
    cout << "Enter the duration of the song you want to add: ";
    cin >> duration; // check?
    
    cout << "Enter the year of the song you want to add: ";
    cin >> year; // check?
    
    localSong.setId(id);
    localSong.setTitle(title);
    localSong.setArtist(artist);
    localSong.setAlbum(album);
    localSong.setGenre(genre);
    localSong.setDuration(duration);
    localSong.setYear(year);
    
    // insert the Song object into the data structures
    if ( SongIdTreePtr->insert(localSong,compareId) )
    {
        
        SongTitleTreePtr->insert(localSong,compareTitle);
        
        //insert into Hash
        SongTable->insertHash(id,localSong);
        
        cout << "The Song has been inserted!!\n";
    }
    else
    {
        cout << "The song cannot be inserted." << endl << endl;
    }
    
}
    
/*****************************************************************************
This function allows the user to delete a song from the two Binary          *
Search Trees and the hash table using the id of the song.                   *
*****************************************************************************/
void DeleteManager (BinarySearchTree<Song>* IdTree, BinarySearchTree<Song>* TitleTree, HashTable<Song>* songHash)
{
        string id;
        BinarySearchTree<Song>* searchIdPtr;
        BinarySearchTree<Song>*  searchTitlePtr;
        HashTable<Song>* hashPtr;
    
        Song Entry, returnedItem;
        
        cout << "Enter the ID of the song you want to delete: ";
        cin >> id;
        
        Entry.setId (id);
        
        bool removed = IdTree->remove(Entry);

        if ( removed ){
            removed = TitleTree->remove(Entry);
            removed = songHash->deleteHash(Entry.getId(), Entry);
            cout << "The song is deleted successfully!" << endl << endl;
        }
        else{
            cout << "The song is not found." << endl ;
        }
}
    

    
/*****************************************************************************
This function allows the user to delete a song from the two Binary          *
Search Trees and the hash table using the id of the song.                   *
*****************************************************************************/
    
void UndoDelete(Stack<Song>& deleted ,BinarySearchTree<Song>* IdTree, BinarySearchTree<Song>* TitleTree, HashTable<Song>* SongTable)
{
        Song temp;
        deleted.pop(temp);
        cout << "\n" << temp.getId() << "\t" << temp.getTitle() << "is being put back into the database!" << endl;
}
    
    
/*****************************************************************************
 This function will check if the ID given by the user is only number         *
 not alphabet.                                                               *
 *****************************************************************************/
bool validateID(string id_input)
{
    int i = 0;
    while( i < id_input.length())
    {
        if(isalpha(id_input[i]))
        {
            // cout << "INVALID INPUT! PLEASE ENTER NUMBER ONLY! PLEASE ENTER AGAIN!\n" << endl;
            return false;
        }
            i++;
    }
    return true;
}

void displaySong(Song& aSong)
{
    cout << aSong << endl;
}

int compareId(Song& left, Song& right )
{
    if ( left.getId() > right.getId())
        return 1;
    else if ( left.getId() < right.getId() )
        return -1;
    else
        return 0;
    
}

int compareTitle(Song& left, Song& right )
{
    if ( left.getTitle() > right.getTitle())
        return 1;
    else if (  left.getTitle() < right.getTitle() )
        return -1;
    else
        return 0;
    
}
