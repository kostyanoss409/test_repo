#pragma once
#include "pch.h"
#include <iostream>
#include<string>
#include"global.h"
using namespace std;
//прием Земля
int Subjects::s_number_subj = 0;
int main()
{

	setlocale(LC_ALL, "Russian");
	char command = -1;
	cout << "1. Загрузить список студентов из файла" << endl;
	cout << "2. Выгрузить список студентов в файл" << endl;
	cout << "3. Вывести список студентов на экран" << endl;
	cout << "4. Загрузить список предметов из файла" << endl;
	cout << "5. Загрузить список предметов в файл" << endl;
	cout << "6. Вывести список экзаменов на экран" << endl;
	cout << "7. Загрузить список преподавателей из файла" << endl;
	cout << "8. Выгрузить список преподавателей в файл" << endl;
	cout << "9. Вывести список преподавателей на экран" << endl;
	cout << "0. Вывести список людей на экран" << endl;
	cout << "e. Редактировать" << endl;
	//cout << "o. Открыть файл StudentOut" << endl;
	cout << "q. Выйти" << endl;
	cin >> command;
	
	List<Information> *S = NULL;
	List<Prepods> *P = NULL;
	List<Subjects> *E = NULL;
	List<Chelovek> *C = NULL;
	List<Prepods> *O = NULL;// = new List<Prepods>;
	while (command != 'q')
	{
		switch (command)
		{
		case '1':
			if (S == NULL)
			{
				if (E == NULL)
				{
					cout << "Пэйн, я список предметов не чувствую" << endl;
				}
				else
				{
					S = new List<Information>;
					S->LoadFromFile("StudentsIn.txt", *&E);
					cout << "Cписок студентов загружен из файла" << endl;
				}
			}
			else { cout << "Модератор, тут баян" << endl; }
			break;
		case '2':
		{
			S->LoadInFile("StudentsOut.txt");
			cout << "Cписок студентов загружен в файл" << endl;
		}
			break;
		case '3':
		{
			if (S == NULL) { cout << "Список еще пуст" << endl; }
			else { S->LoadOnScreen(); }
		}
			break;
		case '4':
		{
			if (E == NULL)
			{
				E = new List<Subjects>;
				E->LoadSmthFromFile("SubjectsIn.txt");
				cout << "Cписок экзаменов загружен из файла" << endl;
			}
			else { cout << "Модератор, тут баян" << endl; }
		}
			break;
		case '5':
		{
			E->LoadSmthToFile("SubjectsOut.txt");
		}
			break;
		case '6':
		{
			if (E == NULL) { cout << "Мой глаз видит пустоту" << endl; }
			else { E->LoadOnScreen(); }
		}
			break;
		case '7':
		{
			if (E == NULL)
			{
				cout << "Пэйн, я список предметов не чувствую" << endl;
			}
			else
			{
				P = new List<Prepods>;
				P->LoadFromFile("PrepodsIn.txt", *&E);
				cout << "Cписок преподавателей загружен из файла" << endl;
			}
		}
			break;
		case '8':
		{
			P->LoadInFile("PrepodsOut.txt");
		}
			break;
		case '9':
		{
			if (P == NULL) { cout << "Мой глаз видит пустоту" << endl; }
			else { P->LoadOnScreen(); }
		}
			break;
		case 'e':
		{
			if (S == NULL || P== NULL)
			{
				cout << "Пустота неизменна" << endl;
			}
			else
			{
				char vab = -1;
				cout << "Выберите функцию" << endl;
				cout << "1. Добавить нового студента" << endl;
				cout << "2. Добавить/изменить оценку" << endl;
				cout << "3. Добавить экзамен в список экзаменов" << endl;
				cout << "4. Добавить преподавателя в список преподавателей" << endl;
				cout << "5. Добавить учителю предмет" << endl;
				cout << "6. Удалить студента" << endl;
				cout << "7. Удалить преподавателя" << endl;
				cout << "b. Назад" << endl;
				cin >> vab;
				while (vab != 'b')
				{
					switch (vab)
					{
					case '1':
					{
						cout << "Введите фамилию студента" << endl;
						string ch;
						cin >> ch;
						S->Add_Chto(ch, *&S);
					}
						break;
					case '2':
					{
						cout << "Введите фамилию студента" << endl;
						string ch;
						cin >> ch;
						cout << "Введите номер предмета" << endl;
						int number = 0;
						cin >> number;
						cout << "Введите оценку" << endl;
						int mark = 0;
						cin >> mark;
						if (mark >= 0 && mark <= 6)
						{
							S->AddExamens(ch, number, mark, E);
						}
						else { cout << "Эти баллы похожи на надувательство." << endl; }
					}
						break;
					case '3':
					{
						cout << "Введите Название экзамена" << endl;
						string ch;
						cin >> ch;
						E->Add_Chto(ch, *&E);
					}
						break;
					case '4':
					{
						cout << "Введите фамилию преподавателя" << endl;
						string ch;
						cin >> ch;
						P->Add_Chto(ch, *&P);
					}
						break;
					case '5':
					{
						cout << "Введите фамилию преподавателя" << endl;
						string ch;
						cin >> ch;
						cout << "Введите номер предмета" << endl;
						int number = 0;
						cin >> number;
						int mark = 91939;
						P->AddExamens(ch, number, mark, E);
					}
						break;
					case '6':
					{
						string s_name;
						cout << "Введите студента " << endl;
						cin >> s_name;
						S->Delete(s_name);
					}
					break;
					case '7':
					{
						string s_name;
						cout << "Введите преподавателя " << endl;
						cin >> s_name;
						P->Delete(s_name);
					}
					break;
					default:
					{
						cout << "1. Добавить нового студента" << endl;
						cout << "2. Изменить оценку" << endl;
						cout << "3. Добавить экзамен в список экзаменов" << endl;
						cout << "4. Добавить преподавателя в список преподавателей" << endl;
						cout << "5. Добавить учителю предмет" << endl;
						cout << "6. Удалить студента" << endl;
						cout << "7. Удалить преподавателя" << endl;
						cout << "b. Назад" << endl;
						cin >> vab;
					}
						break;
					}
					cout << "Выберите функцию" << endl;
					cin >> vab;
				}
			}
		}
			break;
		case 'o':
			system("notepad C:\\Users\\kosty\\source\\repos\\4_4_Ozenki+Prepody\\popt3\\StudentsOut.txt");
				break;
			break;
		case '0':
		{
			if (S == NULL || P == NULL)
			{
				cout << "Истина в вине, но не здесь" << endl;
			}
			else
			{
				/*List<Prepods>* O = new List<Prepods>();
				C = new List<Chelovek>;
				P->Copy_Paste(C);
				S->Copy_Paste(C);
				//C = (List<Chelovek>*)O;
				//C->Connect(S);
				C->LoadOnScreen();*/
				List<Prepods>*O = new List<Prepods>();
				P->Copy_Paste(O);
				C = (List<Chelovek>*)O;
				C->Connect(S);
				C->LoadOnScreen();
			}
		}
			break;
		default:
			cout << "Введите команду" << endl;
			cin >> command;
			break;
		}
		cout << "Введите команду" << endl;
		cin >> command;
	}
	system("pause");
	return 0;
}