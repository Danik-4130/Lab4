// OOP4_FinalEdition.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include<iostream>
#include<fstream>
#include<iomanip>
#include<string.h>
#include <Windows.h>
#pragma warning(disable : 4996)

using namespace std;

template <typename T1, typename T2>
struct Element {
	char firstName[40];
	char lastName[40];
	int otdel;
	int zarplata;
};

template <typename T1, typename T2>
class TextFile {
private:
	Element<T1, T2> object;
	char fileName[20] = "file.dat";
	int count = 0;
public:
	TextFile();
	void setData();
	void sortData(int);

	void showData();
	bool compare(Element<T1, T2> L, Element<T1, T2> R, int props);
};

template <typename T1, typename T2>
TextFile<T1, T2>::TextFile() {
	try {
		FILE* f = fopen(this->fileName, "rb");

		if (f == NULL)
			throw "Файл не найден";

		while (fread(&object, sizeof(Element<T1, T2>), 1, f)) {
			++count;
		}
	}
	catch (char* str) {
		cout << str << endl;
	}
}

template <typename T1, typename T2>
void TextFile<T1, T2>::setData() {
	try {
		int choice = 1;
		fstream file(this->fileName, ios::binary | ios::out);

		if (!file)
			throw "Файл не найден!!";

		this->count = 0;
		do
		{
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "\nИмя: ";
			cin.getline(object.firstName, 40);
			cout << "Фамилия: ";
			cin.clear();
			cin.getline(object.lastName, 40);
			cout << "Отдел: ";
			while (true)
			{
				cin >> object.otdel;
				if (!cin)
				{
					cout << "Не верно ввели, повторите ввод\n";
					cin.clear();
					while (cin.get() != '\n');
				}
				else break;
			}
			cout << "ЗП: ";
			while (true)
			{
				cin >> object.zarplata;
				if (!cin)
				{
					cout << "ne verno vveli, povtorite vvod\n";
					cin.clear();
					while (cin.get() != '\n');
				}
				else break;
			}
			file.write(reinterpret_cast<char*>(&object), sizeof(Element<T1, T2>));

			cout << "\nХотите добавить ещё? \n1 - Да, 0 - Нет: ";
			cin >> choice;
			cout << endl;
			++this->count;
		} while (choice == 1);

		file.close();
	}
	catch (char* str) {
		cout << str << endl;
	}
}

template <typename T1, typename T2>
void TextFile<T1, T2>::sortData(int props) {
	FILE* f = std::fopen(this->fileName, "r+");
	Element<T1, T2> left, right;
	for (int i = 0; i < count; i++)
	{
		std::fseek(f, i * (sizeof(Element<T1, T2>)), SEEK_SET);
		std::fread(&left, sizeof(Element<T1, T2>), 1, f);
		for (int j = count - 1; j > i; j--)
		{
			std::fseek(f, j * (sizeof(Element<T1, T2>)), SEEK_SET);
			std::fread(&right, sizeof(Element<T1, T2>), 1, f);
			if (compare(left, right, props))
			{
				std::fseek(f, j * (sizeof(Element<T1, T2>)), SEEK_SET);
				std::fwrite(&left, sizeof(Element<T1, T2>), 1, f);
				std::fseek(f, i * (sizeof(Element<T1, T2>)), SEEK_SET);
				std::fwrite(&right, sizeof(Element<T1, T2>), 1, f);
				left = right;
			}
		}
	}
	std::fclose(f);
}

template <typename T1, typename T2>
bool TextFile<T1, T2>::compare(Element<T1, T2> L, Element<T1, T2> R, int props)
{
	switch (props)
	{
	case 1: return L.firstName[0] > R.firstName[0] ? true : false;
	case 2: return L.lastName[0] > R.lastName[0] ? true : false;
	case 3: return L.otdel > R.otdel ? true : false;
	case 4: return L.zarplata > R.zarplata ? true : false;
	default: return L.zarplata < R.zarplata ? true : false;
	}
}

template <typename T1, typename T2>
void TextFile<T1, T2>::showData() {
	try {
		FILE* f;
		Element<T1, T2> object;
		f = fopen(this->fileName, "rb");

		if (f == NULL)
			throw "Файл не найден";

		for (int i = 0; i < count; i++) {
			fread(&object, sizeof(Element<T1, T2>), 1, f);
			cout << "Фамилия: " << object.lastName << endl << "Имя: " << object.firstName << endl << "Отдел: " << object.otdel << endl << "ЗП: " << object.zarplata << endl << endl;
		}

		cout << endl;
		std::fclose(f);
	}
	catch (char* str) {
		cout << str << endl;
	}
}

int main()
{
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода
	TextFile<int, char>* example = new TextFile<int, char>();
	int choice;

	cout << "1 - Добавить;\n2 - Показать всех;\n3 - Сорт по Имени; \n4 - Сорт по Фамилии;\n5 - Сорт по отделу; \n6 - Сорт по зп; \n7 - Выходим" << endl;
	cout << "\nВыбирайте там: ";
	cin >> choice;

	while (choice >= 1 & choice <= 6) {
		switch (choice)
		{
		case 1: {
			example->setData();
			break;
		}
		case 2: {
			cout << endl;
			example->showData();
			break;
		}
		case 3: {
			example->sortData(1);
			cout << "Сортнуто по Имени" << endl;
			cout << endl;
			example->showData();
			break;
		}
		case 4: {
			example->sortData(2);
			cout << "Сортнуто по Фамилии" << endl;
			cout << endl;
			example->showData();
			break;
		}
		case 5: {
			example->sortData(3);
			cout << "Сортнуто по Отделу" << endl;
			cout << endl;
			example->showData();
			break;
		}
		case 6:
			example->sortData(4);
			cout << "Сортнуто по зп" << endl;
			cout << endl;
			example->showData();
			break;
		}
		cout << "Выбирайте что делаем: ";
		cin >> choice;
	}

	system("pause");
}

