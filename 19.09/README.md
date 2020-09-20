# Содержание
1. [Директивы](./DIRECTIVES.md)
2. [Ввод/вывод](./IO.md)
3. [Установка LLVM](./LLVM_INSTALLATION.md)
4. [Работа с адрес-санитайзером](./CLANG_SANITIZER.md)
5. [Указатели и ссылки](./REF_PTR.md)
6. [Модульное тестирование](./UNIT_TESTS.md)

# Невошедшее в отдельную категорию

- Большинство заголовочных файлов стандартной библиотеки C доступны в C++, однако для использования функционала поставляемого стандартной библиотекой C, необходимо пользоваться другими заголовочными файлами, название которых изменено изменено, аналогично тому, что показано в примере ниже:
```c
// C
#include <stdio.h>

int main() {
    printf("%d", 10);
    return 0;
}
```

```cpp
// C++
#include <cstdio>

int main() {
    printf("%d", 10);
    return 0;
}
```
С переченем доступных заголовчных файлов можно ознакомиться на [cppreference](https://en.cppreference.com/w/).

- Перечень базовых типов данных описан в [cppreference/fundamental-types](https://en.cppreference.com/w/cpp/language/types). Для точного определения веса типа/объекта следует воспользоваться функцией `sizeof`, для определения количества бит в объекте типа `char` существует макрос `CHAR_BIT` (определение макроса находится в `cstdint`) (в большинстве известных архитектурных решений, размер равен 8). Также, для точного определения различных границ объектов базового типа, существует заголовочный файл `limits`, в котором для них (базовых типов) определены специализации шаблонного класс `numeric_limits` с различными статичными методами (подробнее см. [cppreference/numeric_limits](https://en.cppreference.com/w/cpp/types/numeric_limits)).

- Также, как и в стандартной библиотеке `C`, стандартная библиотека `C++` также поставляет типы данных с четко заданными размерами. Их объявления возможно найти в заголовочном файле `cstdint` (подробнее см. [cppreference/cstdint](https://en.cppreference.com/w/cpp/types/integer)).

- Для подгонки файлов с исходным кодом под [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) возможно воспользоваться одной из утилит LLVM `clang-format`. Для этого необходимо вызвать данную утилиту с опцией `-style=Google`.<br/>
    Пример:<br/>
    `clang-format -style=Google source.cpp > output_source.cpp`<br/>
    Подробнее о различных вариантов форматирования исходного кода утилитой `clang-format` см. на [сайте LLVM](https://clang.llvm.org/docs/ClangFormatStyleOptions.html#:~:text=clang%2Dformat%20supports%20two%20ways,file%20in%20the%20project%20directory.).