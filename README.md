# Debug Capture
This code is an example of how to capture debug output generated using the Win32 API `OutputDebugString()`

There are two Visual Studio 2019 solutions in this example:
1. [DebugCaptureCode](https://github.com/anthonykempka/DebugCapture/tree/main/DebugCaptureCode) is an MFC dialog application that captures debug output from a running process
2. [DebugOutputConsoleApp](https://github.com/anthonykempka/DebugCapture/tree/main/DebugOutputConsoleApp) is a C++ console application that generates test debug output using OutputDebugString()


## Debug Output Win32 API

Windows applications can send debug output using the WIN32 API `OutputDebugString()` and later capture the debug string using a combination of `DebugActiveProcess()` and `ReadProcessMemory()`

## WIN32 Debug Functions
Here is the link to the official Microsoft reference for Windows debugging functions.  

https://docs.microsoft.com/en-us/windows/win32/debug/debugging-functions  


### OutputDebugString() ASCII and UNICODE
Win32 `OutputDebugString()` comes in two variations supporting either ASCII or UNICODE strings.

#### OutputDebugStringA("ASCII debug text here")  
https://docs.microsoft.com/en-us/windows/win32/api/debugapi/nf-debugapi-outputdebugstringa  
 
 
#### OutputDebugStringW(L"UNICODE debug text here")  
https://docs.microsoft.com/en-us/windows/win32/api/debugapi/nf-debugapi-outputdebugstringw  
 
 
### Example Windows application code using the OutputDebugString() API
In the example below, the project was built with UNICODE flag, therefore `OutputDebugString()` function is defined as `OutputDebugStringW()` and the source code is in [DebugCaptureCode](https://github.com/anthonykempka/DebugCapture/tree/main/DebugCaptureCode)

The code builds a UNICODE string, then outputs to the debug system and the console. The loop continues for a count of 100000, or until the user hits the ESC key.
```cpp
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
```


## Debug capture UI
Here is what the UI looks like as various steps in usage.

### Dialog before selecting process
Right after launching DebugCapture.exe

![image](https://user-images.githubusercontent.com/16089554/160298432-64158cfb-3c6e-4d32-9456-1dfc1a462a7b.png)

### Selecting process

In this case, the process SimpleConsoleCPP.exe with process ID 12364 is selected. 

![image](https://user-images.githubusercontent.com/16089554/160298492-a8223038-ba98-422e-ab34-bcc6bd18845d.png)

### Process selected

See in field "Process Id"

![image](https://user-images.githubusercontent.com/16089554/160298518-573104c2-a3b5-4787-8e23-56c477db1387.png)

### Click Start Capture


![image](https://user-images.githubusercontent.com/16089554/160298529-04039ecf-16ff-4d5b-af68-c9655eb4770d.png)


### Click Stop Capture

See what happens

![image](https://user-images.githubusercontent.com/16089554/160298565-25b0c771-b5ba-4697-8004-eed3600b25a8.png)

### Simple console test application

![image](https://user-images.githubusercontent.com/16089554/160298744-7ab11170-0048-43f2-96b7-78d67c2d3950.png)




