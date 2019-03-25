
/*#include "pch.h"

#include "Global.h"
#include <iostream>
#include "HeaderLink.h"

using namespace std;

// добавление студента в список
void push(ListOfStudents *&ptr, information c)	// *& - это ссылка на указатель, Использвется как альтернатива двойному указателю **
{
	ListOfStudents *p = new ListOfStudents;
	p->data = c;								// a -> b равнозначно (*a).b вызов члена структуры 
	p->next = ptr;
	ptr = p;
}

// добавление оценки в список
void push(ListOfExam *&ptr, MarksOnExam c)
{
	ListOfExam *p = new ListOfExam;
	p->data = c;
	p->next = ptr;
	ptr = p;
}

// Функция удаления внутреннего списка ( списка студентов ) 
void Del_El_Stek(ListOfStudents *&ptr)
{
	ListOfStudents *p;
	if (ptr != NULL)
	{
		p = ptr;
		ptr = ptr->next;
		delete(p);
	}
}

// Функция удаления внутреннего списка ( списка экзаменов ) 
void Del_El_Stek(ListOfExam *&ptr)
{
	ListOfExam *p;
	if (ptr != NULL)
	{
		p = ptr;
		ptr = ptr->next;
		delete(p);
	}
}

// Функция очистки внешнего стека ( список студентов ) 
void DelStek(ListOfStudents *&S)
{
	while (S != NULL)
	{
		DelStek(S->data.pass);
		Del_El_Stek(S);
	}
	S = NULL;
}

// Функция очистки внешнего стека ( списко экзаменов )
void DelStek(ListOfExam *&S)
{
	while (S != NULL)
		Del_El_Stek(S);
	S = NULL;
}


// Функция очистки структуры предметов
void DelStekSubject(ListSubjects *&ptr)
{
	while (ptr != NULL)
	{
		ListSubjects *p;
		if (ptr != NULL)
		{
			p = ptr;
			ptr = ptr->next;
			delete(p);
		};
	}
	ptr = NULL;
}

// Заполнение файла из списка предметов 
void LoadSubjectToFile(ListSubjects *&ptr, char *OutputSub)
{
	std::ofstream f_out;
	f_out.open(OutputSub, std::ios::app);
	f_out << "\nПредметы \nНачало:\n\n";									// обозначаем начало записи предметов в файле 
	while (ptr != NULL)														// пока список не пуст добавляем предметы в файл
	{
		f_out << ptr->data.subject << "(" << ptr->data.number << ")\n";		// заполняем файл: Предмет(номер предмета) 
		ptr = ptr->next;													// переходим к следующему элементу
	}
	f_out << "\n\nКонец \n";												// обозначаем конец записи предметов в файле 
}

// заполнение списка предметов из файла
int LoadSubjectFromFile(ListSubjects *&ptr, char *InputSub)
{
	std::ifstream f_in(InputSub);
	int n = 0;											// обнуляем счетчик предметов
	while (f_in)										// пока список не пуст добавляем предметы в файл
	{
		Subject a;										// Создаем "информационный" элемент списка предметов
		try
		{
			f_in >> a.subject;
			if (strlen(a.subject) == 0) return n;		// проверяем пустую строку
			f_in >> (a.number);
		}
		catch (...)
		{
		}
		// Добавляем сформированный элеент в список предметов 
		ListSubjects *p = new ListSubjects;
		p->data = a;
		p->next = ptr;
		ptr = p;
		n++;
	}
	f_in.close();
	return n;
}

// заполнение списка из файла
int LoadFromFile(ListOfStudents *&ptr, char *Input)
{
	std::ifstream f_in(Input);
	int n = 0;						// обнуляем счетчик студентов
	while (f_in)					// пока файл существует
	{
		information a;
		int flag = Read(&a, f_in);	// вызов функции для ввода очередного студента из файла
		if (!flag)					// проверить флаг на успешный ввод при flag == 0
		{
			push(ptr, a); 
			n++;
		}
		else break;
	}
	f_in.close();
	return n;
}


// Функция для ввода очередного студента из файла
int Read(information *a, std::ifstream &f)
{
	int flag = 1; // нет считывания из файла 
	try
	{
		f >> a->name; if (strlen(a->name) == 0) return 1; // проверяем пустую строку
		f >> (a->group);
		f >> (a->size);
		float n = a->size;
		a->avg = ReadExamens(a->size, a->pass, f) / n;	//average присваивается значение всех оценок, 
														//поделенных на число экзаменов - получается средний балл
		return 0;
	}
	catch (...)
	{
		return 1;
	}
}

// считывание n экзаменов и добавление их в списко оценок
int  ReadExamens(int nExam, ListOfExam *&ptr, std::ifstream &f)
{
	int n = 0;
	for (int i = 0; i<nExam; i++)
	{
		MarksOnExam a;
		int flag = ReadExam(&a, f);						// вызов функциидля ввода в переменную (а) очередного значения из файла (f)
		if (flag) {
			push(ptr, a);
			n += flag;
		}
		else break;
	}
	return n;
}

// считывание одного элемента из файла 
int  ReadExam(MarksOnExam *a, std::ifstream &f)
{
	f >> (a->subject);									//прочитать из файла f номер предмета в поле (subj) переменной (a)
	f >> (a->mark);										//прочитать из файла f оценку в поле (mark) переменной (a)
	int n = a->mark;
	return n;
}




//Вывод списка в файл
void LoadToFile(ListOfStudents *s, const char *Output)
{
	std::ofstream f_out;
	f_out.open(Output, std::ios::app);
	f_out << "\n Begin stek\n\n";
	while (s != NULL)
	{
		Write(s->data, f_out);
		s = s->next;
	}
	f_out << "\n End stek\n";
}

// вывод строки списка
void  Write(information a, std::ofstream &f)
{
	f << "Name - " << a.name << "\n";
	f << "Group - " << a.group << "\n";
	f << "Averange - " << a.avg << "\n";
	WriteExamens(a.pass, f);
	f << "\n";
}

 // занос всех эказменов в файл
void WriteExamens(ListOfExam *s, std::ofstream &f)
{
	while (s != NULL)
	{
		WriteExam(s->data, f);
		s = s->next;
	}
}

// предмет и оцена в опреедленном виде заносится в файл 
void WriteExam(MarksOnExam a, std::ofstream &f)
{
	f << a.subject << "(" << a.mark << ");";
}*/