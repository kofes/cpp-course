# Ввод/вывод

# Стандартные потоки ввода/вывода данных

При написании кода на `C` для вывода/вывода данных в/из стандартного потока вывода/ввода в большинстве случаев* можно было воспользоваться функциями форматным ввода/вывода. В `C++` данными функциями также возможно воспользоваться, подключив заголовочный файл `cstdio`.
```cpp
#include <cstdio>

int main() {
    int some_value;
    // write some data
    printf("enter value: ");
    // read some data
    scanf_s("%d", &some_value);
    // write some data
    printf("value is %d", some_value);
    return 0;
}
```
Однако, в `C++` также существуют обертки для работы с вводом/выводом данных. Так, для работы со стандартнымии потоками ввода/вывода, возможно подключить заголовочный файл `iostream`.
```cpp
#include <iostream>

int main() {
    int some_value;
    // write some data
    std::cout << "enter value: ";
    // read some data
    std::cin >> some_value;
    // write some data
    std::cout << "value is " << some_value;
    return 0;
}
```
Для форматного ввода/вывода данных в/из файла используя функции, задекларированные в заголовочном файле `cstdio`, необходимо проделать, примерно, следующую последовательность действий.
```cpp
#include <cstdio>

int main() {
    // create file descriptor pointer variable
    std::FILE* file_descriptor = NULL;
    // attach file descriptor pointer to file stream from "input.txt" with read ("r") mode
    file_descriptor = fopen("input.txt", "r");
    // check is file descriptor attached
    if (file_descriptor == NULL) {
        return 1;
    }
    
    int val = 0;
    // format read value from file stream
    fscanf(file_descriptor, "%d", &val);

    // attach file descriptor pointer to file stream from "output.txt" with write ("w") mode
    file_descriptor = freopen("output.txt", "w", file_descriptor);
    // format write value to file stream
    fprintf(file_descriptor, "values: %d", val);
    // close file stream
    fclose(file_descriptor);

    return 0;
}
```
Также, как и для стандартного потока ввода/вывода данных, в стандартной библиотеки `C++` присутсвуют обертки для работы с файлами.
```cpp
#include <fstream>

int main() {
    // create file descriptor wrapper and attach it to file stream from "input.txt" with read (std::ios::in) mode
    std::fstream fd("input.txt", std::ios::in);
    // check is file opened
    if (!fd.is_open()) {
        return 1;
    }
    
    int val = 0;
    // read value from file stream
    fd >> val;

    // attach file descriptor to file stream from "input.txt" with write (std::ios::out) mode
    fd.open("output.txt", std::ios:out);
    // format write value to file stream
    fd << "values: " << val;

    // close file stream
    fd.close();

    return 0;
}
```
Вместо обертки `fstream` возможно явно воспользоваться обертками, явно предназначенными для считывания из файла (`ifstream`)/для записи в файл (`ofstream`). Подробнее в [cppreference/fstream](https://en.cppreference.com/w/cpp/header/fstream).