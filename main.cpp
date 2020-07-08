#include "mainwindow.h"
#include <QApplication>
#include <stdexcept>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    try{w.show();}
    catch(runtime_error &e)
    {
        cerr <<  "Err:  runtime_error: " << e.what() << "\n\n";
    }
    catch(out_of_range &e)
    {
        cerr <<  "Err:  out_of_range: " << e.what() << "\n\n";
    }
    catch(logic_error &e)
    {
        cerr <<  "Err:  logic_error : " << e.what() << "\n\n";
    }
    catch(exception &e)
    {
        cerr <<  "Err:  exception: " << e.what() << "\n\n";
    }
    catch(...)
    {
        cerr <<  "Err: Unknown error cause the program to terminate. \n\n";
    }

    return a.exec();
}
