#include<iostream>
#include<fstream>
#include<string.h>
#include<stdio.h>
#include<conio.h>
using namespace std;
class Book
{
private:
    int bookid;
    char title[50];
    float price;
public:
    void setBook(int id,char t[],float p) { bookid=id; strcpy(title,t); price=p; }
    void showBook() { cout<<bookid<<" "<<title<<" "<<price<<endl; }
    void saveBook()
    {
        ofstream fout;
        fout.open("Bookfile.txt",ios::app);
        fout.write((char*)this, sizeof(*this));
        fout.close();
    }
    void showAllBooks()
    {
        ifstream fin;
        fin.open("Bookfile.txt",ios::in|ios::binary);
        if(!fin)
            cout<<"File not found"<<endl;
        else{
            fin.read((char*)this, sizeof(*this));
            while(!fin.eof()){
                this->showBook();
                fin.read((char*)this, sizeof(*this));
            }
            fin.close();
        }
    }
    void deleteBook(int id)
    {
        ofstream fout;
        fout.open("tempfile.txt",ios::out);
        ifstream fin;
        fin.open("Bookfile.txt",ios::in);
        Book temp;
        if(!fin)
            cout<<"File not found"<<endl;
        else{
            fin.read((char*)&temp, sizeof(temp));
            while(!fin.eof()){
                if(temp.bookid!=id)
                    fout.write((char*)&temp, sizeof(temp));
                fin.read((char*)&temp, sizeof(temp));
            }
            fin.close();
            fout.close();
            remove("Bookfile.txt");
            rename("tempfile.txt","Bookfile.txt");
        }
    }

};
int main()
{
    Book b1;
    /*b1.setBook(1,"Cpp Learner",550);
    b1.saveBook();

    b1.setBook(2,"C Learner",450);
    b1.saveBook();

    b1.setBook(3,"Java Learner",350);
    b1.saveBook();

    b1.setBook(4,"Python Learner",250);
    b1.saveBook();*/

    b1.showAllBooks();
    b1.deleteBook(3);
    cout<<endl<<endl<<"After deletion:\n";
    b1.showAllBooks();
    getch();
}
