#include <iostream>
#include <uio.h>
#include <fcntl.h>

using namespace std;

int main()
{
    wchar_t message_korean[] = L"반갑다! 세계야!";

    cout << "Hello, World!" << endl;

    _setmode(_fileno(stdout), _0_U16TEXT);

    wcout << message_korean << endl;

}