#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

// Функция для добавления данных о продукте в файл "products.txt"
void addProductToFile() {
    ofstream file("products.txt", ios::app);

    string name;
    double price;
    int quantity;

    cout << "Введите название продукта (или нажмите Enter для завершения ввода): ";
    getline(cin, name);
    if (name.empty()) {
        return;
    }

    cout << "Введите цену продукта: ";
    cin >> price;

    cout << "Введите количество продукта: ";
    cin >> quantity;

    file << name << "," << price << "," << quantity << "\n";
    file.close();
}

// Функция для поиска продукта по названию в файле "products.txt"
void searchProductByName(const string& productName) {
    ifstream file("products.txt");
    string line;
    while (getline(file, line)) {
        size_t found = line.find(productName);
        if (found != string::npos) {
            cout << line << endl;
            return;
        }
    }

    cout << "Продукт не найден." << endl;
    file.close();
}

// Функция для сортировки продуктов по цене или количеству
void sortProducts(bool byPrice) {
    ifstream file("products.txt");

    vector<string> productLines;
    string line;

    while (getline(file, line)) {
        productLines.push_back(line);
    }

    file.close();

    if (byPrice) {
        sort(productLines.begin(), productLines.end(),
             [](const string& a, const string& b) {
                 double priceA = stod(a.substr(a.find(',') + 1));
                 double priceB = stod(b.substr(b.find(',') + 1));
                 return priceA < priceB;
             });
    } else {
        sort(productLines.begin(), productLines.end(),
             [](const string& a, const string& b) {
                 int quantityA = stoi(a.substr(a.rfind(',') + 1));
                 int quantityB = stoi(b.substr(b.rfind(',') + 1));
                 return quantityA < quantityB;
             });
    }

    ofstream sortedFile("products_sorted.txt");
    for (const string& line : productLines) {
        sortedFile << line << endl;
    }
    sortedFile.close();
    cout << "Продукты отсортированы и сохранены в 'products_sorted.txt'." << endl;
}

// Функция для вывода продуктов в соответствии с условием пользователя
void ProductsByCondition(double conditionValue, bool byPrice) {
    ifstream file("products.txt");

    cout << "Продукты ";
    if (byPrice) {
        cout << "с ценой не более ";
    } else {
        cout << "с количеством не более ";
    }
    cout << conditionValue << ":\n";

    string line;
    while (getline(file, line)) {
        double price = stod(line.substr(line.find(',') + 1));
        int quantity = stoi(line.substr(line.rfind(',') + 1));

        if ((byPrice && price <= conditionValue) || (!byPrice && quantity <= conditionValue)) {
            cout << line << endl;
        }
    }

    file.close();
}

int main() {
    while (true) {
        cout << "Меню:\n";
        cout << "1. Добавить данные о продукте\n";
        cout << "2. Поиск продукта по названию\n";
        cout << "3. Сортировать продукты по цене\n";
        cout << "4. Сортировать продукты по количеству\n";
        cout << "5. Вывести продукты по условию цены\n";
        cout << "6. Вывести продукты по условию количества\n";
        cout << "0. Выйти\n";

        int choice;
        cin >> choice;
        cin.ignore(); // Очистить символ новой строки из буфера

        switch (choice) {
            case 1:
                addProductToFile();
                break;
            case 2:
                string searchName;
                cout << "Введите название продукта для поиска: ";
                getline(cin, searchName);
                searchProductByName(searchName);
                break;
            case 3:
                sortProducts(true);
                break;
            case 4:
                sortProducts(false);
                break;
            case 5:
                double priceCondition;
                cout << "Введите условие цены: ";
                cin >> priceCondition;
                ProductsByCondition(priceCondition, true);
                break;
            case 6:
                double quantityCondition;
                cout << "Введите условие количества: ";
                cin >> quantityCondition;
                ProductsByCondition(quantityCondition, false);
                break;
            case 7:
                cout << "Программан завершена\n";
                return 0;
            default:
                cout << "Некорректный выбор. Пожалуйста, выберите правильную опцию.\n";
                break;
        }
    }
}
