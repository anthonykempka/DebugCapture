# DebugCapture
Microsoft Windows debug output capture source code. 

This application is based on MFC and was ported to Visual Studio 2019. 

## Debug Output Win32 API

Windows applications can send debug output using the WIN32 API `OutputDebugString()`

See more about `OutputDebugString()` below:

ASCII version of the API: 
https://docs.microsoft.com/en-us/windows/win32/api/debugapi/nf-debugapi-outputdebugstringa 

UNICODE version of the API: 
https://docs.microsoft.com/en-us/windows/win32/api/debugapi/nf-debugapi-outputdebugstringw 

### Example Windows application code using the OutputDebugString() API
```cpp
int main()
{
    int i;
    WCHAR wStr[100] = { 0 };
    std::cout << "Hello World!\n";

    // This shows have to use the preprocessor macros to display compilation DATE and TIME
    ::printf("This was built on " __DATE__ " " __TIME__ "\r\n");

    for (i = 0; i < 100000; i++)
    {
        swprintf_s(wStr, L"Test application generating debug output using OutputDebugString()  loop count (%u)", i);
        ::OutputDebugString(wStr);
        ::printf("%S\r\n", wStr);
        Sleep(1000);
    }
    
}
```


## Example debug capture 
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




