// DebugOutputConsoleApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*
BSD 3-Clause License

Copyright (c) 2022, Anthony Kempka
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <iostream>
#include <windows.h>
#include <conio.h>
// Do not need to explicitly include debugapi.h since it's referenced in windows.h
//#include <debugapi.h>

using namespace std;

int main()
{
    int i, ch;
    WCHAR wStr[100] = { 0 };

    // This shows have to use the preprocessor macros to display compilation DATE and TIME
    cout << "This application was built on " __DATE__ " " __TIME__ "\n";
    cout << "Hit Esc key to exit ... \n";

    for (i = 0; i < 100000; i++)
    {
        swprintf_s(wStr, L"Test application generating debug output using OutputDebugString()  loop count (%u)", i);
        // Output to debug system
        ::OutputDebugString(wStr);
        // Output to console
        wcout << wStr << endl;

        ::Sleep(1000);
        // Check for keyboard input
        if (::_kbhit())
        {
            ch = ::_getch();
            if (ch == 27)   // ESC key
                break;
        }
    }
    return (0);
}