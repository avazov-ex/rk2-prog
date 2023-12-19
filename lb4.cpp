#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

// Шаблонный класс Pair для хранения пары характеристик книги
template <typename T1, typename T2>
class Pair {
public:
    Pair(const T1& first, const T2& second) : first(first), second(second) {}

    T1 getFirst() const { return first; }
    T2 getSecond() const { return second; }

private:
    T1 first;
    T2 second;
};

// Базовый класс Book представляет общие характеристики для всех книг
class Book {
public:
    Book(const std::string& title, const std::string& author, const std::string& genre)
        : title(title), author(author), genre(genre) {}

    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    std::string getGenre() const { return genre; }

    virtual void displayInfo() const {
        std::cout << "Заглавие: " << title << std::endl;
        std::cout << "Автор: " << author << std::endl;
        std::cout << "Жанр: " << genre << std::endl;
    }

private:
    std::string title;
    std::string author;
    std::string genre;
};

// Класс Fiction, наследуется от Book и представляют собой конкретные типы книг, есть свой метод displayInfo(), которые выводят информацию о книгах.
class Fiction : public Book {
public:
    Fiction(const std::string& title, const std::string& author)
        : Book(title, author, "Функции") {}

    void displayInfo() const override {
        std::cout << "Функции книги" << std::endl;
        std::cout << "Заглавие: " << getTitle() << std::endl;
        std::cout << "Автор: " << getAuthor() << std::endl;
    }
};

// Класс NonFiction, наследуется от Book, есть свой метод displayInfo(), которые выводят информацию о книгах.
class NonFiction : public Book {
public:
    NonFiction(const std::string& title, const std::string& author)
        : Book(title, author, "Не функция") {}

    void displayInfo() const override {
        std::cout << "Нефункционировання книга" << std::endl;
        std::cout << "Заглавие: " << getTitle() << std::endl;
        std::cout << "Aвтор: " << getAuthor() << std::endl;
    }
};

// Класс Library для управления каталогом библиотеки. Он содержит вектор объектов типа Book, в котором хранятся все добавленные книги. В этом классе определены методы для добавления книги, поиска книги по заглавию, сортировки книг по автору и сохранения информации о книгах в файл.
class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void searchBook(const std::string& title) {
        for (const auto& book : books) {
            if (book.getTitle() == title) {
                book.displayInfo();
                return;
            }
        }
        std::cout << "Книга не найдена!" << std::endl;
    }

    void sortBooksByAuthor() {
        std::sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
            return a.getAuthor() < b.getAuthor();
        });
    }

    void saveToFile(const std::string& filename) {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto& book : books) {
                file << "Заглавие: " << book.getTitle() << std::endl;
                file << "Aвтор: " << book.getAuthor() << std::endl;
                file << "Жанр: " << book.getGenre() << std::endl;
                file << "-------------------------------------" << std::endl;
            }
            file.close();
            std::cout << "Данные сохраенные в файл: " << filename << std::endl;
        } else {
            std::cerr << "Не удалось открыть файл " << filename << std::endl;
        }
    }

private:
    std::vector<Book> books;
};

// Текстовое меню для пользователя это текстовое меню для пользователя, которое выводит на экран доступные опции.
void showMenu() {
    std::cout << "********** Меню библиотеки **********" << std::endl;
    std::cout << "1. Добавить книгу" << std::endl;
    std::cout << "2. Найти кригу" << std::endl;
    std::cout << "3. Сортировать книги по авторам" << std::endl;
    std::cout << "4. Сохранить файл" << std::endl;
    std::cout << "5. Выйти" << std::endl;
    std::cout << "**********************************" << std::endl;
    std::cout << "Введите свой выбор: ";
}

int main() { //Функция main() представляет собой основной цикл программы. Она создает объект класса Library и выполняет действия в зависимости от выбора пользователя, вводимого с помощью меню. При выборе опции "break" цикл завершается и программа заканчивает выполнение.
    Library library;
    std::string filename = "output.txt";

    int choice;
    do {
        showMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string title, author, genre;
                std::cout << "Ввидите заглавие: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                std::cout << "Ввидите автора: ";
                std::getline(std::cin, author);

                std::cout << "Ввидите жанр: ";
                std::getline(std::cin, genre);

                Book book(title, author, genre);
                library.addBook(book);
                break;
            }
            case 2: {
                std::string title;
                std::cout << "Введите заглавие для поиска: ";
                std::cin.ignore();
                std::getline(std::cin, title);

                library.searchBook(title);
                break;
            }
            case 3:
                library.sortBooksByAuthor();
                std::cout << "Поиск книги по автору." << std::endl;
                break;
            case 4:
                library.saveToFile(filename);
                break;
            case 5:
                std::cout << "Выходящий" << std::endl;
                break;
            default:
                std::cout << "Неверынй выбор. Попробуйте снова" << std::endl;
                break;
        }

    } while (choice != 5);

    return 0;
}
