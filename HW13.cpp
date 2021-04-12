#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class DealerShip {
private:
    string model;
    int year;
    float engine;
    float price;
public:
    static vector<DealerShip> arr;
    DealerShip() {
        model = "";
        year = -1;
        engine = -1;
        price = -1;
    }
    DealerShip(string _model, int _year, float _engine, float _price) {
        model = _model;
        year = _year;
        engine = _engine;
        price = _price;
    }
    void Put() {
        cout << "Enter the model of car: "; cin >> model;
        cout << "Enter the year: "; cin >> year;
        cout << "Enter the volume of engine: "; cin >> engine;
        cout << "Enter the price: "; cin >> price;
    }
    void SaveToFile() {
        int size;
        fstream file("cars.txt", ios::out | ios::binary | ios::app);
        if (!file) {
            cout << "File is not open for write" << endl;
            exit(1);
        }

        size = model.length();
        file.write((char*)&size, sizeof(size));
        file.write(model.c_str(), size * sizeof(char));

        file.write((char*)&year, sizeof(year));
        file.write((char*)&engine, sizeof(engine));
        file.write((char*)&price, sizeof(price));

        file.close();
    }
    static void ShowFromFile() {
        fstream file("cars.txt", ios::in | ios::binary);
        if (!file)
        {
            cout << "File is not open for read" << endl;
            exit(1);
        }
        char* m;
        int y;
        float e;
        float p;

        int temp;

        while (file.read((char*)&temp, sizeof(int)))
        {
            cout << "Model: ";
            m = new char[temp + 1];
            if (!m)
            {
                cout << "Memory allocation error" << endl;
                exit(1);
            }
            file.read(m, temp * sizeof(char));
            m[temp] = '\0';
            cout << m << endl;

            cout << "Year: ";
            file.read((char*)&y, sizeof(y));
            cout << y << endl;

            cout << "Engine: ";
            file.read((char*)&e, sizeof(e));
            cout << e << endl;

            cout << "Price: ";
            file.read((char*)&p, sizeof(p));
            cout << p << endl;

            delete[] m;
        }
    }
    static void GetFromFile() {
        if (arr.size()) arr.clear();
        fstream file("cars.txt", ios::in | ios::binary);
        if (!file)
        {
            cout << "File is not open for read" << endl;
            exit(1);
        }
        char* m;
        int y;
        float e;
        float p;

        int temp;
        while (file.read((char*)&temp, sizeof(int)))
        {
            DealerShip tmp;

            m = new char[temp + 1];
            if (!m)
            {
                cout << "Memory allocation error" << endl;
                exit(1);
            }
            file.read(m, temp * sizeof(char));
            m[temp] = '\0';
            tmp.model = m;

            file.read((char*)&y, sizeof(y));
            tmp.year = y;

            file.read((char*)&e, sizeof(e));
            tmp.engine = e;

            file.read((char*)&p, sizeof(p));
            tmp.price = p;

            arr.push_back(tmp);

            delete[] m;
        }
    }
    static void FindByModel(string model) {
        GetFromFile();
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i].model == model) {
                arr[i].Display();
            }
        }
    }
    static void FindByYear(int year) {
        GetFromFile();
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i].year == year) {
                arr[i].Display();
            }
        }
    }
    static void FindByEngine(float engine) {
        GetFromFile();
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i].engine == engine) {
                arr[i].Display();
            }
        }
    }
    static void FindByPrice(float price) {
        GetFromFile();
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i].price == price) {
                arr[i].Display();
            }
        }
    }
    static void SortYear() {
        GetFromFile();
        sort(arr.begin(), arr.end(), [](DealerShip a, DealerShip b) {return a.year > b.year; });
    }
    static void SortEngine() {
        GetFromFile();
        sort(arr.begin(), arr.end(), [](DealerShip a, DealerShip b) {return a.engine > b.engine; });
    }
    static void SortPrice() {
        GetFromFile();
        sort(arr.begin(), arr.end(), [](DealerShip a, DealerShip b) {return a.price > b.price; });
    }
    static void PrintArr() {
        for (int i = 0; i < arr.size(); i++) {
            arr[i].Display();
        }
    }
    void Display()
    {
        cout << "Model: " << model << endl;
        cout << "Year: " << year << endl;
        cout << "Engine: " << engine << endl;
        cout << "Price: " << price << endl;
    }
};
vector<DealerShip> DealerShip::arr;

int main(void) {
    int ch;
    DealerShip* u;
    string model;
    int year;
    float engine;
    float price;
    do
    {
        system("cls");
        cout << "1 - Add struct" << endl;
        cout << "2 - Show structs" << endl;
        cout << "3 - Find by Model" << endl;
        cout << "4 - Find by Year" << endl;
        cout << "5 - Find by Engine" << endl;
        cout << "6 - Find by Price" << endl;
        cout << "7 - Sort by Year and Show" << endl;
        cout << "8 - Sort by Engine and Show" << endl;
        cout << "9 - Sort by Price and Show" << endl;
        cout << "10 - Exit" << endl;
        cout << "Enter option: "; cin >> ch;
        switch (ch)
        {
        case 1:
            system("cls");
            u = new DealerShip;
            u->Put();
            u->SaveToFile();
            delete u;
            system("pause");
            break;
        case 2:
            system("cls");
            DealerShip::ShowFromFile();
            system("pause");
            break;
        case 3:
            system("cls");
            cout << "Enter model: "; cin >> model;
            DealerShip::FindByModel(model);
            system("pause");
            break;
        case 4:
            system("cls");
            cout << "Enter year: "; cin >> year;
            DealerShip::FindByYear(year);
            system("pause");
            break;
        case 5:
            system("cls");
            cout << "Enter engine: "; cin >> engine;
            DealerShip::FindByEngine(engine);
            system("pause");
            break;
        case 6:
            system("cls");
            cout << "Enter price: "; cin >> price;
            DealerShip::FindByPrice(price);
            system("pause");
            break;
        case 7:
            system("cls");
            DealerShip::SortYear();
            DealerShip::PrintArr();
            system("pause");
            break;
        case 8:
            system("cls");
            DealerShip::SortEngine();
            DealerShip::PrintArr();
            system("pause");
            break;
        case 9:
            system("cls");
            DealerShip::SortPrice();
            DealerShip::PrintArr();
            system("pause");
            break;
        case 10:
            system("cls");
            cout << "See You Later" << endl;
            break;
        default:
            system("cls");
            cout << "Not correct input" << endl;
            system("pause");
            break;
        }
    } while (ch != 10);

    return 0;
}
