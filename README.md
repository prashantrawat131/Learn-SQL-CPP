# Learn-SQL-CPP

### SQLITE C++ Example
**Description**: In this repo I have used a simple example of student managment. We only only have one table named as "Student". Various operations are performed on the database like table creation, insetion, deletion and select query.

---------------------------------------

### SETUP FOR WINDOWS 10 (64 bit) and VS CODE
1. Download MSYS2 from https://www.msys2.org/

2. Install MSYS2

3. If you have installed msys2 in C drive then put the following in your PATH environment variable
   ```
   C:\msys64\ucrt64\bin
   ```

4. Add the following include path in the c_cpp_properties.json file inside the .vscode folder
    ```
    C:\\msys64\\ucrt64\\include\\**
    ```

5. Also add the -lsqlite3 flag in the tasks.json file inside the .vscode folder (This is for single file only)
    ```
    -lsqlite3
    ```

6. You can check my [c_cpp_properties.json](./.vscode/c_cpp_properties.json) and [tasks.json](./.vscode/tasks.json) file for reference.

------------------------------------------

### How to run the project

- Step 1: Open the terminal in the current directory

- Step 2: Run the following command
    ```
    g++ -o program main.cpp studentdb.cpp -lsqlite3
    ```

- Step 3: Run the program
    ```
    ./program.exe
    ```
