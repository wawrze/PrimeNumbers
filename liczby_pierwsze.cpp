#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <process.h>
#include <conio.h>
#include <string>
#include <fstream>
#pragma warning(disable : 4996)
using namespace std;

struct list {						//lista, w ktorej beda zapisywane znalezione liczby pierwsze
	unsigned long long int number;	//znaleziona liczba pierwsza
	list *next;						//wskaznik do nastepnego elementu listy
};

struct options {					//struktura zawierajaca wybrane opcje
	unsigned long long int min;		//wyszukiwanie od liczby (NA TE CHWILE ZAWSZE 2!!!)
	int max_type;					//wyszukiwanie do: 1-maksymalne liczby, 2-znalezienia okreslonej ilosci liczb pierwszych
	unsigned long long int max;		//wyszukiwanie do liczby
	int out_screen;					//czy wyswietlac wyniki na ekran: 1-tak, 2-nie
	int out_file;					//czy zapisywac wyniki do pliku: 1-tak, 2-nie
	string out_name;				//nazwa pliku wyjscia
	int out;						//czy do wynikow dodawac liczbe porzadkowa, 1-tak, 2-nie
	char sep;						//separator wynikow - nowa linia, spacja lub tabulator
	int cont_from_file;				//czy kontynuowac z pliku
	string in_name;					//nazwa pliku wejscia
};

int check(list *ltmp, unsigned long long int x);																				//funkcja sprawdzajaca podzielnosc liczby x przez liczby pierwsze ze wskazanej listy, zwraca: 1-jesli x jest liczba pierwsza, 0-jesli x nie jest liczba pierwsza
void seek(options *opt);																										//funkcja wyszukujaca liczby pierwsze, przekazujemy do niej wskaznik na wybrane opcje
void seek_file(list *start, unsigned long long int start_num, char sep, int max_type, int out, unsigned long long int min, unsigned long long int max, string file);			//wyszukiwanie z zapisem do pliku
void seek_screen(list *start, unsigned long long int start_num, char sep, int max_type, int out, unsigned long long int min, unsigned long long int max);						//wyszukiwanie z wyswietlaniem na ekran
void seek_file_screen(list *start, unsigned long long int start_num, char sep, int max_type, int out, unsigned long long int min, unsigned long long int max, string file);	//wyszukiwanie z wyswietlaniem na ekran i zapisem do pliku
options *menu();																												//funkcja wyswietlajaca menu wyboru opcji

int main()
{
	options *opt;
	opt = new options[1];
	opt = menu();
	system("CLS");
	seek(opt);
	cout << endl << endl;
	system("PAUSE");
	return 0;
}

options *menu()
{
	options *opt;
	opt = new options[1];
	opt->min = 2;
	opt->max_type = 1;
	opt->max = 18446744073709551615;
	opt->out_screen = 1;
	opt->out_file = 1;
	opt->out_name = "prime_numbers.txt";
	opt->out = 1;
	opt->sep = '\n';
	opt->cont_from_file = 1;
	opt->in_name = "prime_numbers.txt";
	char c = 'p';
	char o = 'p';
	int error = 0;
	while (c != 's')
	{
		system("CLS");
		cout << "Obliczanie liczb pierwszych, wybierz opcje:" << endl << endl;
		cout << "(1) Wyszukiwanie od liczby: " << opt->min << endl;
		cout << "(2) Wyszukiwanie do: ";
		if (opt->max_type == 1)
			cout << "maksymalnej liczby" << endl;
		else
			cout << "okreslonej ilosci liczb pierwszych" << endl;
		cout << "    (3) ";
		if (opt->max_type == 1)
			cout << "Maksymalna liczba: " << opt->max << endl;
		else
			cout << "Ilosc liczb pierwszych: " << opt->max << endl;
		cout << "(4) Wyjscie na ekran: ";
		if (opt->out_screen == 1)
			cout << "tak" << endl;
		else
			cout << "nie" << endl;
		cout << "(5) Wyjscie do pliku: ";
		if (opt->out_file == 1)
			cout << "tak" << endl;
		else
			cout << "nie" << endl;
		cout << "    (6) Nazwa pliku wyjscia: ";
		if (opt->out_file == 1)
			cout << (opt->out_name);
		cout << endl;
		cout << "(7) Sposob reprezentacji wynikow: ";
		if (opt->out == 1)
			cout << "tylko znalezione liczby" << endl;
		else
			cout << "znalezione liczby wraz z liczba porzadkowa" << endl;
		cout << "(8) Separator: ";
		if (opt->sep == '\n')
			cout << "nowa linia" << endl;
		else if (opt->sep == ' ')
			cout << "spacja" << endl;
		else
			cout << "tabulator" << endl;
		cout << "(9) Kontynuacja z pliku: ";
		if (opt->cont_from_file == 1)
			cout << "tak" << endl;
		else
			cout << "nie" << endl;
		cout << "    (0) Nazwa pliku wejscia: ";
		if(opt->cont_from_file == 1)
			cout << (opt->in_name);
		cout << endl;
		cout << "(s) Rozpocznij wyszukiwanie liczb pierwszych.";
		if (error == 1)
			cout << endl << endl << "Blad w zmianie opcji!!!";
		error = 0;
		c = _getch();
		switch (c)
		{
		case '1':
		{
			cout << endl << endl << "Nie mozna zmienic minimalnej liczby. Wcisnij dowolny klawisz.";
			o = _getch();
			break;
		}
		case '2':
		{
			cout << endl << endl << "Wybierz opcje: (m)aksymalna liczba  /  (i)losc liczb pierwszych";
			o = _getch();
			if (o == 'm')
				opt->max_type = 1;
			else if (o == 'i')
			{
				opt->max_type = 2;
				opt->out = 2;
			}
			else
				error = 1;
			break;
		}
		case '3':
		{
			unsigned long long int max;
			cout << endl << endl << "Podaj ";
			if (opt->max_type == 1)
				cout << "maksymalna liczbe (od 3 do 18446744073709551615): ";
			else
				cout << "ilosc liczb pierwszych do znalezienia: ";
			cin >> max;
			if (max >= 3 && max <= 18446744073709551615)
			{
				opt->max = max;
				break;
			}
			else
				error = 1;
			break;
		}
		case '4':
			cout << endl << endl << "Wyjscie na ekran: (t)ak  /  (n)ie";
			o = _getch();
			if (o == 't')
				opt->out_screen = 1;
			else if (o == 'n')
				if (opt->out_file == 2)
				{
					opt->out_file = 1;
					opt->out_screen = 2;
				}
				else
					opt->out_screen = 2;
			else
				error = 1;
			break;
		case '5':
		{
			cout << endl << endl << "Wyjscie do pliku: (t)ak  /  (n)ie";
			o = _getch();
			if (o == 't')
				opt->out_file = 1;
			else if (o == 'n')
				if (opt->out_screen == 2)
				{
					opt->out_screen = 1;
					opt->out_file = 2;
				}
				else
					opt->out_file = 2;
			else
				error = 1;
			break;
		}
		case '6':
		{
			cout << endl << endl << "Jesli plik nie istnieje, zostanie utworzony. Jesli plik istnieje, jego zawartosc zostanie zastapiona" << endl << "Podaj nazwe pliku wyjscia: ";
			cin >> opt->out_name;
			break;
		}
		case '7':
			cout << endl << endl << "Sposob reprezentacji wynikow: (t)ylko znalezione liczby (opcja \"Wyszukiwanie do\" musi byc ustawione na \"maksymalna liczba\") " << endl << "znalezione liczby wraz z liczba (p)orzadkowa";
			o = _getch();
			if (o == 't')
			{
				if (opt->max_type == 2)
					error = 1;
				else
					opt->out = 1;
			}
			else if (o == 'p')
				opt->out = 2;
			else
				error = 1;
			break;
		case '8':
		{
			cout << endl << endl << "Podaj typ separatora: (n)owa linia  /  (s)pacja  /  (t)abulator";
			o = _getch();
			if (o == 'n')
				opt->sep = '\n';
			else if (o == 's')
				opt->sep = ' ';
			else if (o == 't')
				opt->sep = '\t';
			else
				error = 1;
			break;
		}
		case '9':
		{
			cout << endl << endl << "Czy kontynuowac z pliku: (t)ak  /  (n)ie";
			o = _getch();
			if (o == 't')
				opt->cont_from_file = 1;
			else if (o == 'n')
				opt->cont_from_file = 2;
			else
				error = 1;
			break;
		}
		case '0':
		{
			cout << endl << endl << "Program nie bedzie dzialal poprawnie, jesli wybrany plik bedzie nieprawidlowy!" << endl << "Podaj nazwe pliku wejscia: ";
			cin >> opt->in_name;
			break;
		}
		default:
			break;
		}
	}
	return opt;
}

void seek(options *opt)
{
	list *listtmp;
	listtmp = new list[1];
	listtmp->number = 2;
	listtmp->next = NULL;
	list *start;
	start = listtmp;
	unsigned long long int num = 0;
	if (opt->cont_from_file == 1)
	{
		system("CLS");
		cout << "Trwa wczytywanie danych z pliku..." << endl << endl;
		string temp;
		char *buf;
		ifstream in_file;
		in_file.open(opt->in_name);
		if (!in_file.good())
		{
			cout << endl << endl << "Nie udalo sie otworzyc pliku " << opt->in_name << ", dzialanie programu przerwane!";
			return;
		}
		while (!in_file.eof())
		{
			in_file >> temp;
			buf = strtok(&temp[0], "-");
			num = stoull(buf, NULL, 10);
			while (buf != NULL)
			{
				temp = buf;
				buf = strtok(NULL, "-");
			}
			listtmp->number = stoull(temp, NULL, 10);
			if (!in_file.eof())
			{
				listtmp->next = new list[1];
				listtmp = listtmp->next;
			}
			else
				listtmp->next = NULL;
			opt->min = ((listtmp->number)++);
		}
		in_file.close();
		num--;
	}
	system("CLS");
	cout << "Wyszukiwanie rozpoczete." << endl;		//DODAC CZAS!!!!!
	if (opt->out_screen == 1 && opt->out_file == 1)
		seek_file_screen(start, num, opt->sep, opt->max_type, opt->out, opt->min, opt->max, opt->out_name);	//wyswietlanie na ekran + zapis do pliku
	else if (opt->out_screen == 2 && opt->out_file == 1)
		seek_file(start, num, opt->sep, opt->max_type, opt->out, opt->min, opt->max, opt->out_name);		//tylko zapis do pliku
	else if (opt->out_screen == 1 && opt->out_file == 2)
		seek_screen(start, num, opt->sep, opt->max_type, opt->out, opt->min, opt->max);						//tylko wyswietlanie na ekran
	cout << endl << "Wyszukiwanie zakonczone." << endl;	//DODAC CZAS!!!!!
	return;
}

void seek_file(list *start, unsigned long long int start_num, char sep, int max_type, int out, unsigned long long int min, unsigned long long int max, string file)
{
	cout << "Zapisywanie wynikow do pliku " << file;
	list *listtmp = NULL;
	ofstream out_file;
	out_file.open(file);
	if (!out_file.good())
	{
		cout << endl << endl << "Nie udalo sie otworzyc pliku " << file << ", dzialanie programu przerwane!";
	}
	if (out == 2)
	{
		unsigned long long int i, j = start_num;
		if (max_type == 2)		//wyszukiwanie z liczba porzadkowa do znalezienia okreslonej ilosci liczb pierwszych
		{
			for (i = min; j < max; i++)
			{
				listtmp = start;
				if (check(listtmp, i) == 1)
				{
					j++;
					out_file << sep << j << "-" << i;
				}
			}
		}
		else						//wyszukiwanie z liczba porzadkowa do maksymalnej liczby
		{
			for (i = min; i <= max; i++)
			{
				listtmp = start;
				if (check(listtmp, i) == 1)
				{
					j++;
					out_file << sep << j << "-" << i;
				}
			}

		}
	}
	else							//wyszukiwanie bez liczby porzadkowej
	{
		unsigned long long i;
		for (i = min; i <= max; i++)
		{
			listtmp = start;
			if (check(listtmp, i) == 1)
				out_file << sep << i;
		}
	}
	out_file.close();
	while (start->next != NULL)
	{
		listtmp = start->next;
		delete start;
		start = listtmp;
	}
}
void seek_screen(list *start, unsigned long long int start_num, char sep, int max_type, int out, unsigned long long int min, unsigned long long int max)
{
	list *listtmp = NULL;
	if (out == 2)
	{
		unsigned long long int i, j = start_num;
		if (max_type == 2)		//wyszukiwanie z liczba porzadkowa do znalezienia okreslonej ilosci liczb pierwszych
		{
			for (i = min; j < max; i++)
			{
				listtmp = start;
				if (check(listtmp, i) == 1)
				{
					j++;
					cout << sep << j << "-" << i;
				}
			}
		}
		else						//wyszukiwanie z liczba porzadkowa do maksymalnej liczby
		{
			for (i = min; i <= max; i++)
			{
				listtmp = start;
				if (check(listtmp, i) == 1)
				{
					j++;
					cout << sep << j << "-" << i;
				}
			}

		}
	}
	else							//wyszukiwanie bez liczby porzadkowej
	{
		unsigned long long i;
		for (i = min; i <= max; i++)
		{
			listtmp = start;
			if (check(listtmp, i) == 1)
				cout << sep << i;
		}
	}
	while (start->next != NULL)
	{
		listtmp = start->next;
		delete start;
		start = listtmp;
	}
}
void seek_file_screen(list *start, unsigned long long int start_num, char sep, int max_type, int out, unsigned long long int min, unsigned long long int max, string file)
{
	list *listtmp = NULL;
	ofstream out_file;
	out_file.open(file);
	if (!out_file.good())
	{
		cout << endl << endl << "Nie udalo sie otworzyc pliku " << file << ", dzialanie programu przerwane!";
	}
	if (out == 2)
	{
		unsigned long long int i, j = start_num;
		if (max_type == 2)		//wyszukiwanie z liczba porzadkowa do znalezienia okreslonej ilosci liczb pierwszych
		{
			for (i = min; j < max; i++)
			{
				listtmp = start;
				if (check(listtmp, i) == 1)
				{
					j++;
					cout << sep << j << "-" << i;
					out_file << sep << j << "-" << i;
				}
			}
		}
		else						//wyszukiwanie z liczba porzadkowa do maksymalnej liczby
		{
			for (i = min; i <= max; i++)
			{
				listtmp = start;
				if (check(listtmp, i) == 1)
				{
					j++;
					cout << sep << j << "-" << i;
					out_file << sep << j << "-" << i;
				}
			}

		}
	}
	else							//wyszukiwanie bez liczby porzadkowej
	{
		unsigned long long i;
		for (i = min; i <= max; i++)
		{
			listtmp = start;
			if (check(listtmp, i) == 1)
			{
				cout << sep << i;
				out_file << sep << i;
			}
		}
	}
	out_file.close();
	while (start->next != NULL)
	{
		listtmp = start->next;
		delete start;
		start = listtmp;
	}
}

int check(list *ltmp, unsigned long long int x)
{
	while ((ltmp->next) != NULL)
	{
		if ((x % (ltmp->number)) != 0)
			ltmp = ltmp->next;
		else
			break;
	}
	if ((ltmp->next) == NULL)
	{
		ltmp->next = new list[1];
		ltmp->next->number = x;
		ltmp->next->next = NULL;
		return 1;
	}
	return 0;
}