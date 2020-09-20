# Указатели и ссылки

# Указатели

Также, как и в `C`, в `C++` работа с указателями построена аналогичным образом.
```cpp
#include <cstddef>
#include <iostream>

int main() {
    int val = 5;
    /*
    ** 'int*' - тип указателя на объект типа int
    ** '&' - оператор взятия указателя на объект.
    */
    int* ptr = &val;

    // * - оператор разыменования
    *ptr = 12312; // меняем значение переменной, на которую указывает указатель ptr

    std::cout << val << std::endl; // Вывод: 12312

    int val2 = 10;
    int* ptr2;
    ptr2 = &val2;

    std::ptrdiff_t ptr_diff = ptr2 - ptr; // берем разницу между адресами, хранящимеся в переменных типа указатель

    std::cout << ptr_diff << std::endl;

    return 0;
}
```
**[Упоминание]**: Подробнее про тип `std::ptrdiff_t` можно узнать из [cppreference](https://en.cppreference.com/w/cpp/language/operator_arithmetic#Additive_operators)

Аналогичным образом построена работа с указателями типа `void*`.
```cpp
#include <cstddef>
#include <iostream>

int main() {
    int val = 5;
    /*
    ** 'int*' - тип указателя на объект типа int
    ** '&' - оператор взятия указателя на объект.
    */
    void* ptr = &val;

    // * - оператор разыменования
    // *ptr = 12312; // compile-time error: необходимо привести тип (void*)
    *(int*)ptr = 12312;

    std::cout << val << std::endl; // Вывод: 12312

    int val2 = 10;
    void* ptr2;
    ptr2 = &val2;

    // std::ptrdiff_t ptr_diff = ptr2 - ptr; // compile-time error: арифметические операции с указателями типа `void*` запрещены 

    return 0;
}
```

Однако, помимо макроса `NULL`, в `C++` определено ключевое слово `nullptr` для обозначения нулевого указателя. Типом `nullptr` является `std::nullptr_t`. 

*[ВАЖНО]*: Не пользуйтесь в `C++` макросом `NULL` для обозначения нулевого указателя, - для этого лучше воспользоваться опредленным `nullptr`.
```cpp
#include <iostream>

void func(int*) {
    std::cout << "int*" << std::endl;
}

void func(int) {
    std::cout << "int" << std::endl;
}

void func1(int*) {
    std::cout << "int*" << std::endl;
}

void func1(std::nullptr_t) {
    std::cout << "nullptr_t" << std::endl;
}

int main() {
    func(nullptr); // Вызовется функция `func(int*)`
    func(NULL); // Вызовется функция `func(int)`

    func1(nullptr); // Вызовется функция `func(std::nullptr_t)`
    return 0;
}
```

## Элементы const propagation для указателей

При работе с указателями может возникнуть необходимость взятия указателя на константный тип.
В таком случае работают следующие правила:
```cpp
int main() {
    const int val = 5;

    // int* ptr = &val; // compile-time error: объект типа `int*` не может взять указатель на переменную типа const int
    const int* ptr = &val; // success
    int const* ptr1 = &val; // success

    // *ptr = 10; // compile-time error: нельзя поменять значение по указателю типа `const type*`

    int mutable_val = 10;

    ptr = &mutable_val; // указатель на объекты константного типа может взять указатель на переменную изменяемого типа
    // *ptr = 123; // compile-time error: но поменять значение по указателю также не удастся

    /* Если мы не хотим, чтобы нельзя было поменять значение объекта типа указатель,
    ** то возможно воспользоваться конструкцией, представленной ниже
    */
   int* const nonmutable_ptr = &mutable_val;
   *nonmutable_ptr = 23; // success
    // nonmutable_ptr = &mutable_val; // compile-time error: нельзя поменять значение объекта типа указатель

    return 0;
}
```

# Ссылки

Также в `C++` присутсвует ссылочный тип, представленный в виде `type&`.
```cpp
#include <cstddef>
#include <iostream>

int main() {
    int val = 5;
    /*
    ** 'int&' - тип ссылки на объект типа int
    */
    int& ref = val;

    ref = 12312; // меняем значение переменной, на которую ссылается ссылка ref

    std::cout << val << std::endl; // Вывод: 12312

    int val2 = 10;
    // int& ref2; // compile-time error: ссылка должна на что-то ссылаться
    int& ref2 = val2;

    int diff = ref2 - ref; // берем разницу между значениями объектов, на которые ссылаются ref2 и ref

    std::cout << diff << std::endl;

    return 0;
}
```

## Элементы const propagation для ссылок

Также, как и при работе с указателями, при работе с ссылками может возникнуть необходимость взятия ссылки на константный объект.
```cpp
int main() {
    const int val = 5;

    // int& ref = val; // compile-time error: объект типа `int&` не может взять ссылку на переменную типа const int
    const int& ref = val; // success
    int const& ref1 = val; // success

    // ref = 10; // compile-time error: нельзя поменять значение по ссылке типа `const type&`

    int mutable_val = 10;

    const int& ref2 = mutable_val; // объекты ссылочного типа на объекты константного типа могут ссылаться на переменные изменяемого типа
    // ref2 = 123; // compile-time error: но поменять значение по таким ссылкам также не удастся

    /*
    ** Возможно создать "неизменяемую ссылку", однако в этом нет смысла,
    ** т.к. ссылка сама по себе имеет "неизменяемый" тип:
    ** нельзя просто так взять, и сделать так, чтобы ссылка ссылалась на другой объект, если она уже ссылается на что-то.
    */
    int& const nonmutable_ref = mutable_val;
    nonmutable_ref = 23; // success, but why?

    return 0;
}
```

# Указатель this

Переменная `this`, определенная в методах объектов класса, представляет из себя указатель на объект данного класса, метод которого был вызван. Более того, внутри методов класса нельзя поменять значение перменной `this`.
```cpp
class Dummy {
public:
    Dummy(int val): val(val) {
        Dummy tmp(val);
        // this = &tmp; // compile-time error
    }

    void doSmth() {
        Dummy tmp(val);
        // this = &tmp; // compile-time error
    }

private:
    int val;
};

int main() {
    Dummy(10).doSmth();

    return 0;
}
```

Ввиду того, что `this` является объектом типа указатель, то он обладает некоторым специфическим свойством, связанным
с `const propagation`. Дело в том, что в константных методах, `this` становится указателем на объект константного типа, но это не гарантирует, что мы не можем менять значения по внутренним указателям.  
Пример:
```cpp
#include <iostream>

class Dummy {
public:
    Dummy(int* ptr): ptr(ptr) {}

    void doSmth() const {
        int val2 = 123;
        // ptr = &val2; // compile-time error: нельзя поменять значение полей объекта константного типа
        // однако возможно поменять значение по указателю
        *ptr = 123; // Am I a joke to you?
    }
private:
    int* ptr;
};

int main() {
    int val = 10;
    const Dummy dummy(&val);

    dummy.doSmth(); // success
    std::cout << val << std::endl; // Вывод: 123

    return 0;
}
```
**[ВАЖНО]**: Старайтесь не менять значения данных внутренних структур без явного на то повода.