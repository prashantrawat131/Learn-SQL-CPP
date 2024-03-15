# SQLITE C++ Example

## SETUP FOR WINDOWS 10 (64 bit) and VS CODE
1. Download MSYS2 from https://www.msys2.org/

2. Install MSYS2

3. If you have installed msys2 in C drive then put the following in your environment variable
   ```
   C:\msys64\ucrt64\bin
   ```

4. Add the following include path in the c_cpp_properties.json file inside the .vscode folder
    ```
    C:\\msys64\\ucrt64\\include\\**
    ```

5. Also add the -lsqlite3 flag in the tasks.json file inside the .vscode folder
    ```
    -lsqlite3
    ```

6. You can check my [c_cpp_properties.json](./.vscode/c_cpp_properties.json) and [tasks.json](./.vscode/tasks.json) file for reference.

7. Now you can run the code like you usually do in VS code.