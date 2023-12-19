#include <iostream>
#include <vector

class Animal { //В данном примере создается базовый класс Animal с защищенными данными для имени и вида животного
protected:
    std::string name;
    std::string species;

public:
    Animal(const std::string& name, const std::string& species) : name(name), species(species) {}

    virtual void display() const {
        std::cout << "Имя: " << name << ", Вид: " << species << std::endl;
    }
};

class Bird : public Animal { //Затем создаются класс Bird, который наследуются от класса Animal и добавляют свои данные 
private:
    double wingspan;

public:
    Bird(const std::string& name, const std::string& species, double wingspan) : Animal(name, species), wingspan(wingspan) {}

    void display() const override {
        std::cout << "Имя: " << name << ", Вид: " << species << ", Размах крыльев: " << wingspan << std::endl;
    }
};

class Mammal : public Animal { //Затем создаются класс Mammal, который наследуются от класса Animal и добавляют свои специфичные данные 
private:
    std::string furType;

public:
    Mammal(const std::string& name, const std::string& species, const std::string& furType) : Animal(name, species), furType(furType) {}

    void display() const override {
        std::cout << "Имя: " << name << ", Вид: " << species << ", Длина меха: " << furType << std::endl;
    }
};

void modifyAnimal(Animal* animal) {
    animal->display(); // Отображает животное перед модификацией

    // изменение характеристики животного
    animal->display(); // Отображает животное после модификации
}

int main() {
    std::vector<Animal*> animals; //После этого создается std::vector для хранения указателей на объекты класса Animal

    Bird* bird1 = new Bird("Орел", "Птица", 2.5); //В него добавляются несколько объектов Bird и Mammal
    Bird* bird2 = new Bird("Ястреб", "Птица", 2.0);
    Mammal* mammal1 = new Mammal("Лев", "Млекопитающее", "Короткий");
    Mammal* mammal2 = new Mammal("Тигр", "Mлекопитающее", "Длинный");

    animals.push_back(bird1);
    animals.push_back(bird2);
    animals.push_back(mammal1);
    animals.push_back(mammal2);

    // Отображать информацию о каждом животном с помощью итераторов
    for (std::vector<Animal*>::iterator it = animals.begin(); it != animals.end(); ++it) { //Затем, используя итераторы std::vector, выводится информация о каждом животном в контейнере
        (*it)->display();
    }
 
    // Измените характеристики каждого животного с помощью функции modifyAnimal
    for (std::vector<Animal*>::iterator it = animals.begin(); it != animals.end(); ++it) {
        modifyAnimal(*it);
    }

    // Очистим память, удалив динамически выделяемые объекты
    for (std::vector<Animal*>::iterator it = animals.begin(); it != animals.end(); ++it) {
        delete (*it);
    }

    return 0;
}
