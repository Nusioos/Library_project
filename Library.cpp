#include <iostream>
#include <vector>
#include <cstdlib>
#include <unordered_map>
#include<string>
#include <fstream>
#include <sstream>

using namespace std;

class Library
{
private:
    struct Book
    {
        int number_of_pages;
        string title;
        string author;
    };

public:

    unordered_map<string, string> filter;
    vector<Book> books;
    int book_counter = 0;
    Book* book_pointer = nullptr;
    void add_book_from_data(const string& title, const string& author, int pages) //FUNC1
    {
        Book book;
        book.title = title;
        book.author = author;
        book.number_of_pages = pages;
        books.push_back(book);
        book_pointer = &books.back();
        filter.insert({book.title, book.author});
        book_counter++;
    }
    void add_book()
    {
        Book book;
         cin.ignore();
        cout << "Title: " << endl;
        getline(cin,book.title);
        cout << "Author: " << endl;
        getline(cin,book.author);
        cout << "Number of pages: " << endl;
        cin >> book.number_of_pages;
        books.push_back(book);
        book_pointer = &books.back();
        filter.insert({book.title, book.author});
    }
};

template<typename T>
void describe(T& book)
{
    cout << "Title: " << book.title << endl;
    cout << "Author: " << book.author << endl;
    cout << "Number of pages: " << book.number_of_pages << endl;
}


void Load_library(Library& library ,const string& filename_to_open)
{
ifstream file(filename_to_open);
if(!file.is_open()) 
{
cout << "corrupted file/file not found" << endl;
return;
}
string line;
while (getline(file,line))
{
  stringstream ss(line); // ss(line) ---> string->stream like cin
  string author;
  string title;
  string pages_amount;
  int pages;
    if (!getline(ss, title, ',')) continue;
    if (!getline(ss, author, ',')) continue;
    if (!getline(ss, pages_amount, ',')) continue;
  pages = stoi(pages_amount);
  library.add_book_from_data(title, author, pages); ///FUNC 1
}
file.close();
}
int main()
{
    Library* library = new Library();
    string filename="Books.txt";
    Load_library(*library,filename);
    int choice;
    string Find_via_author;
    string Find_via_name;
    while (1)
    {
        system("clear");
        cout << "Choose option:" << endl;
        cout << "1 - Add book" << endl;
        cout << "2 - Number of books" << endl;
        cout << "3 - Info about last added book" << endl;
        cout << "4 - List all books" << endl;
        cout << "5 - Filter / Find book" << endl;
        cin >> choice;
        system("clear");

        switch (choice)
        {
        case 1:
            library->add_book();
            library->book_counter++;
        break;

        case 2:
            cout << library->books.size() << " <- number of books" << endl;
        break;

        case 3:
            if (library->book_counter > 0)
            {
                describe(*library->book_pointer);
            }
            else
            {
                cout << "No books" << endl;
            }
        break;

        case 4:
            for (int i = 0; i < library->books.size(); i++)
            {
                describe(library->books[i]);
            }
        break;

        case 5:
        bool find_author;
        find_author=false;
        cout << "Name of the author:" << endl;
         cin >> Find_via_author;
      cout << "--------------------" << endl;
        for(const auto& element : library->filter)
        {
            if(Find_via_author == element.second)
            {
             find_author=true;
             cout << element.first << endl;
             cout << "--------------------" << endl;
            }
        }
        if(find_author==false) cout << "No books found with this author name" << endl;
        else cout << "All titles above" << endl;
        break;

        default:
            cout << "No such option" << endl;
            break;
        }
        cin.ignore();
        cin.ignore();
    }

    delete library;
}
