# Перпроцессор: директивы препроцессора
Базовые директивы, которые возможно встретить при написании кода на C/C++

## #include
Для подключения заголовочных файлов в C/C++ существует директива `#include`, который на этапе препроцесса кода компилятором, копирует содержимое указанного файла в файл, где происходила попытка подключения файла.
**[Упоминание]**: Подключать возможно любые файлы! Однако проверка на корректность кода будет проводится уже после подстановки содержимого подключаемого файла.
```cpp
#include <iostream> // copy-paste from `iostream` header here!

int main() {
    return 0;
}
```

## #define/#undef
Для создания и удаления макроса существуют директивы `#define` и `#undef`.
**[ВАЖНО]**: Если определить в качестве макро подстановки выражение, то данное выражение будет проверено на корректность только после работы препроцессора (подстановки).
```cpp
#include <iostream>

#define MY_MACRO (10 + s)

int main() {
    int s = 5;
    std::cout << MY_MACRO << std::endl; // will be processed to `std::cout << (10 + s) << std::endl`
    return 0;
}
```

## #if/#ifdef/#ifndef/#elif/#else/#endif
Возможна ситуация, когда мы хотим, чтобы при определенных параметрах компиляции/окружения в код программы подставлялся только определенный код. К примеру, если мы хотим, чтобы код из заголовочных файлов не подставлялся дважды в файл (исходник), из которого он подключается. 
Для подобных случаев стандартом определены директивы "условной компиляции".
Пример:
```cpp
// header.h
// `Include guard`
#ifndef __FOO_HEADER__
#define __FOO_HEADER__

static int static_value = 10;

#endif // __FOO_HEADER__
``` 
```cpp
// source.cpp
#include <iostream>

#include "header.h"
#include "header.h" // no error about twice defined `static_value` variable

int main() {
    std::cout << static_value << std::endl;
    return 0;
}
```
**[УПОМИНАНИЕ]**: В большинстве известных компиляторов (gcc/clang/msvc) определен макрос `#pragma` с параметром `once`, которые позволяют не писать "`include guard`" для защиты от повторяющегося кода.
Пример:
```cpp
// header.h
#pragma once
static int static_value = 10;
``` 
```cpp
// source.cpp
#include <iostream>

#include "header.h"
#include "header.h" // no error about twice defined `static_value` variable

int main() {
    std::cout << static_value << std::endl;
    return 0;
}
```

Подробнее о различных директивах компилятора(-ов) и предопреределенных макросах возможно узнать из [cppreference](https://en.cppreference.com/w/) / спецификации определенных компиляторов / стандарта