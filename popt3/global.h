#pragma once
#ifndef Students
#define Students

#include <iostream>
#include <fstream>
#include <cstring>
#include <type_traits>

#define NAMESIZE_MAX 225
#define NAMESIZE 20

using namespace std;

int number_subj = 0;
int number_prep = 0;

class Information;
class MarksOnExam;
class Subjects;
class Prepods;
class Chelovek;
template <class T>
// Шаблон списка
class List
{
	friend class List<Information>;
	friend class List<MarksOnExam>;
	friend class List<Prepods>;
	friend class List<Chelovek>;
	friend class Information;
	friend class MarksOnExam;
	friend class Prepods;
	friend class Chelovek;
	List<T> *next;
	T data;
	// Конструктор
	List(T &v) { data = v; next = NULL; }
public:
	List<T> *get_next() { return next; }
	T get_data() { return data; }
	void AddExamens(string ch, int number, int mark, List<Subjects> *L);
	void AddExam(string ch, int number, int mark, List<Subjects> *&);
	void LoadInFile(const char *StudentsOut);
	void WriteExamens(std::ofstream &f);
	void LoadOnScreen();
	void WriteExamensOnScreen();
	int LoadFromFile(const char *StudentsIn, List<Subjects> *&);
	void Connect(List<Information> *S)
	{
		List<Chelovek> *q;
		for (q = this->next; q->next != NULL; q = q->next)
		{
		}
		q->next = (List<Chelovek>*)S;
	}
	//void Copy_Paste(List<Chelovek> *P);
	void Copy_Paste(List<Prepods> *P);
	int Add_Chto(string ch, List<T> *&)
	{
		int n = 0;//обнуляем счетчик студентов
		T a(ch);
		this->AddElements(a); n++;
		return n;
	}
	void deleteElement(List<T> *&pointer);
	int  ReadExamens(int Examens, std::ifstream &f, List<Subjects> *&);
	int LoadSmthFromFile(const char *SubjectsIn);
	void LoadSmthToFile(const char *SmthOut);
	void Delete(string s_name)
	{
		List<T> *res;
		List<T> *U = this->next;
		while (U != NULL)
		{
			if ((U->data).get_name() == s_name)
				break;
			U = U->next;
		}
		res = U;
		if (res == NULL)
		{
			cout << "404\n";
			return;
		}
		List<T> *a, *p;
		for (a = this; (a->next != NULL) && (a->next != res); a = a->next);
		if (a->next == NULL) return;
		p = a->next; a->next = p->next;
		p->next = NULL;
		p->data.DeleteExams();
		delete p;
	}
	float Average()
	{
		float  sum = 0;
		int n = 0;
		List<MarksOnExam> *q;
		for (q = this->next; q != NULL; q = q->next)
		{
			sum = sum + q->get_data().get_mark();
			n++;
		}
		sum = sum / n;
		return sum;
	}
	//Конструктор
	List()
	{
		next = NULL;
	};
	//Деструктор
	~List()
	{
		if (next != NULL) delete next;
	};
	//Функция добавления элемeнта в список
	void AddElements(T &c)
	{
		List *p, *q;
		p = new List(c);
		q = this;
		p->next = q->next;
		q->next = p;
	};
};
//Оценки за экзамены
class MarksOnExam
{
	int subject;
	List<Subjects> *Sub;
	int mark;
public:
	int get_subject() { return subject; }
	void set_subject(int subject) { this->subject = subject; }
	int get_mark() { return mark; }
	void set_mark(int mark) { this->mark = mark; }
	List<Subjects> *get_sub() { return Sub; }
	void set_sub(List<Subjects> *Sub) { this->Sub = Sub; }
	int  ReadExam(std::ifstream &f, List<Subjects> *&);
	void WriteExam(std::ofstream &f);
	void WriteExamOnScreen();
	MarksOnExam()
	{
		subject = 0;
		mark = 0;
	};
	~MarksOnExam()
	{
	};
};

class Chelovek
{
protected:
	string Name;
	List<MarksOnExam> *pass;
	int subjcount;
public:
	string get_name() { return Name; }
	void set_name(string name) { Name = name; }
	List<MarksOnExam> *get_pass() { return pass; }
	void set_pass(List<MarksOnExam> *pass) { this->pass = pass; }
	void DeleteExams() { pass->~List(); }
	int Read(Chelovek *a, std::ifstream &f, List<Subjects> *&R);
	void   WriteOnScreen();
	Chelovek()
	{
		Name = "NONAME";
		pass = NULL;
		subjcount = 0;
	}
	Chelovek(string ch)
	{
		Name = ch;
		pass = NULL;
		subjcount = 0;
	}
	~Chelovek() {};
};
//Информация о студенте: оценки и средний балл
class Information: public Chelovek
{
	float Avg;
public:
	void set_avg(float avg) { Avg = avg; }
	float get_avg() { return Avg; }
	void Write(std::ofstream &f);
	void WriteOnScreen();
	int  Read(Information *a, std::ifstream &f, List<Subjects> *&);
	Information()
	{
		Avg = 0;
	};
	Information(string ch) : Chelovek(ch)
	{
		Avg = 0;
	};
	~Information() {};
};

class Prepods: public Chelovek
{
public:
	Prepods(){};
	Prepods(string ch): Chelovek(ch){};
	//Деструктор
	~Prepods(){};
	int  Read(Prepods *a, std::ifstream &f, List<Subjects> *&);
	void Write(std::ofstream &f);
	void WriteOnScreen();
	friend class Information;
	friend class List<Information>;
	friend int List<Information>::LoadFromFile(const char *StudentsIn, List<Subjects> *&R);
	friend int Information::Read(Information *a, std::ifstream &f, List<Subjects> *&R);
};

//Информация о предмете: номер и название
class Subjects
{
	
	friend class List<Information>;
	friend class List<MarksOnExam>;
	friend class List<Prepods>;
	friend class List<Chelovek>;
	friend class Information;
	friend class MarksOnExam;
	friend class Prepods;
	friend class Chelovek;
	friend int List<Information>::LoadFromFile(const char *StudentsIn, List<Subjects> *&R);
	friend int Information::Read(Information *a, std::ifstream &f, List<Subjects> *&R);
	friend int List<MarksOnExam>::ReadExamens(int nExams, std::ifstream &f, List<Subjects> *&R);
	friend int  MarksOnExam::ReadExam(std::ifstream &f, List<Subjects> *&R);
public:
	static int s_number_subj;
	int NumberOfSubject;
	string NameOfSubject;
	//Конструктор
	Subjects()
	{
		//static int s_number_subj = 0;
		NumberOfSubject = number_subj;
		NameOfSubject = "NONAME";
		//number_subj++;
	};
	Subjects(string ch)
	{
		
		NumberOfSubject = s_number_subj;
		NameOfSubject = ch;
		number_subj++;
	};
	//Деструктор
	~Subjects()
	{
	};
	int ReadSubject(std::ifstream &f);
	void  Write(std::ofstream &f);
	void WriteOnScreen()
	{
		if (NameOfSubject != "NONAME")
		{
			cout << "Название - " << this->NameOfSubject << " ";
			cout << "Номер - " << this->NumberOfSubject << "\n";
			cout << "\n";
		}
	}
};
template<>
void List<Information>::AddExamens(string ch, int number, int mark, List<Subjects> *E)
{
	List<Information> *q;
	for (q = this->next; q != NULL; q = q->next)
	{
		if (ch == (q->data).get_name())
		{
			List<MarksOnExam> *b;
			b = q->data.get_pass();
			int flag = 0;
			if (b != NULL)
			{
				while (b != NULL)
				{
					if (number == b->data.get_subject()) { b->data.set_mark(mark); flag++; };
					b = b->next;
				}
				if (flag == 0)
				{
					q->data.get_pass()->AddExam(ch, number, mark, *&E);
				}
				q->data.set_avg(q->data.get_pass()->Average());
			}
			else
			{
				b = new List<MarksOnExam>();
				b->AddExam(ch, number, mark, *&E);
				q->data.set_pass(b);
				q->data.set_avg(q->data.get_pass()->Average());
			}
		}
	}
}
template<>
void List<Prepods>::AddExamens(string ch, int number, int mark, List<Subjects> *E)
{
	List<Prepods> *q;
	for (q = this->next; q != NULL; q = q->next)
	{
		if (ch == (q->data).get_name())
		{
			List<MarksOnExam> *b;
			b = q->data.get_pass();
			int flag = 0;
			if (b != NULL)
			{
				while (b != NULL)
				{
					if (number == b->data.get_subject()) { b->data.set_mark(mark); flag++; };
					b = b->next;
				}
				if (flag == 0)
				{
					q->data.get_pass()->AddExam(ch, number, mark, *&E);
				}
			}
			else
			{
				b = new List<MarksOnExam>();
				b->AddExam(ch, number, mark, *&E);
				q->data.set_pass(b);
			}
		}
	}
}
template<>
void List<Chelovek>::AddExamens(string ch, int number, int mark, List<Subjects> *E)
{
	List<Chelovek> *q;
	for (q = this->next; q != NULL; q = q->next)
	{
		if (ch == (q->data).get_name())
		{
			List<MarksOnExam> *b;
			b = q->data.get_pass();
			int flag = 0;
			if (b != NULL)
			{
				while (b != NULL)
				{
					if (number == b->data.get_subject()) { b->data.set_mark(mark); flag++; };
					b = b->next;
				}
				if (flag == 0)
				{
					q->data.get_pass()->AddExam(ch, number, mark, *&E);
				}
			}
			else
			{
				b = new List<MarksOnExam>();
				b->AddExam(ch, number, mark, *&E);
				q->data.set_pass(b);
			}
		}
	}
}
//Функция загрузки списка из файла
template<class T>
int List<T>::LoadFromFile(const char *In, List<Subjects> *&E)
{
	std::ifstream f_in(In);
	int n = 0;//обнуляем счетчик студентов
	while (f_in)//пока файл существует
	{
		T a;
		int flag = this->data.Read(&a, f_in, *&E); //вызов функции для ввода очередного студента из файла
		if (!flag) // проверить флаг на успешный ввод при flag == 0
		{
			this->AddElements(a); n++;
		}
		else break;
	}
	f_in.close();
	return n;
}
//функция для ввода очередного студента из файла
int Information::Read(Information *a, std::ifstream &f, List<Subjects> *&E)
{
	int flag = 1; //нет считывания из файла
	try
	{
		f >> a->Name;
		if (a->get_name().length() == 0) return 1; // if (strlen(a->StudentName) == 0) return 1; //проверяем пустую строку
		f >> (a->subjcount);
		float n = a->subjcount;
		List<MarksOnExam> *b = new List<MarksOnExam>();
		a->Avg = b->ReadExamens(a->subjcount, f, *&E) / n;
		a->pass = b;
		return 0;
	}
	catch (...)
	{
		return 1;
	}
}
//функция для ввода очередного студента из файла
int Prepods::Read(Prepods *a, std::ifstream &f, List<Subjects> *&E)
{
	int flag = 1; //нет считывания из файла
	try
	{
		f >> a->Name;
		if (a->get_name().length() == 0) return 1;
		f >> (a->subjcount);
		float n = a->subjcount;
		List<MarksOnExam> *b = new List<MarksOnExam>();
		b->ReadExamens(a->subjcount, f, *&E);
		a->pass = b;
		return 0;
	}
	catch (...)
	{
		return 1;
	}
}
int Chelovek::Read(Chelovek *a, std::ifstream &f, List<Subjects> *&E)
{
	int flag = 1; //нет считывания из файла
	try
	{
		f >> a->Name;
		if (a->get_name().length() == 0) return 1;
		f >> (a->subjcount);
		float n = a->subjcount;
		List<MarksOnExam> *b = new List<MarksOnExam>();
		b->ReadExamens(a->subjcount, f, *&E);
		a->pass = b;
		return 0;
	}
	catch (...)
	{
		return 1;
	}
}
template<class T>
inline void List<T>::deleteElement(List<T> *&pointer)
{
	List<T> *p;
	if (pointer != NULL)
	{
		p = pointer;
		pointer = pointer->get_next();
		delete(p);
	}
}
template<>
//Функция считывания n экзаменов и добавление их список оценок
int List<MarksOnExam>::ReadExamens(int nExams, std::ifstream &f, List<Subjects> *&E)
{
	int n = 0;
	for (int i = 0; i < nExams; i++)
	{
		MarksOnExam a;
		int flag = a.ReadExam(f, *&E); //вызов функции для ввода в переменную (а) очередного экзамена из файла (f)
		if (flag) {
			AddElements(a);
			n += flag;
		}
		else break;
	}
	return n;
}
//Функция считывания одного экзамена
int  MarksOnExam::ReadExam(std::ifstream &f, List<Subjects> *&E)
{
	f >> (this->subject);//прочитать из файла f номер предмета
	f >> (this->mark);//прочитать из файла f оценку
	int n = this->mark;
	List<Subjects> *q = E;
	for (q = E->next; q != NULL; q = q->next)
	{
		//Сравниваем номер предмета из списка предметов с номером предмета из списка экзаменов для данного студента
		if (this->subject == (q->data).NumberOfSubject)
		{
			this->Sub = q;
		}
	}
	return n;
}
//Функция загрузки списка в файл
template<class T>
void List<T>::LoadInFile(const char *Out)
{
	std::ofstream f_out;
	if (typeid(T) == typeid(Information))
	{
		f_out.open(Out, std::ios::app);
		f_out << "	Список студентов\n\nНачало:\n\n";
	}
	if (typeid(T) == typeid(Prepods))
	{
		f_out.open(Out, std::ios::app);
		f_out << "	Список преподавателей\n\nНачало:\n\n";
	}
	if (typeid(T) == typeid(Subjects))
	{
		f_out.open(Out, std::ios::app);
		f_out << "	Список предметов\n\nНачало:\n\n";
	}
	
	List<T> *q;
	for (q = this->next; q != NULL; q = q->next)
	{
		q->data.Write(f_out);
	}
	f_out << "\nКонец\n\n";
}
//Функция записи в файл информации о студенте
void   Information::Write(std::ofstream &f)
{
	if (this->Name != "NONAME")
	{
		f << "Имя - " << this->Name << "\n";
		f << "Средний балл - " << this->Avg << "\n";
		if (this->pass != NULL)
		{
			this->pass->WriteExamens(f);
			f << "\n";
		}
	}
}
//Функция записи в файл информации о студенте
void   Prepods::Write(std::ofstream &f)
{
	if (this->Name != "NONAME")
	{
		f << "Имя - " << this->Name << "\n";
		if (this->pass != NULL)
		{
			this->pass->WriteExamens(f);
			f << "\n";
		}
	}
}
//Функция записи в файл спсика экзаменов для одного студента
template<>
void List<MarksOnExam>::WriteExamens(std::ofstream &f)
{
	List<MarksOnExam> *q;
	for (q = this->next; q != NULL; q = q->next)
	{
		q->data.WriteExam(f);
	}
}
//Функция записи информации об экзамене
void MarksOnExam::WriteExam(std::ofstream &f)
{
	Subjects subj;
	subj = (this->Sub)->data;
	f << this->subject << " {" << subj.NameOfSubject << "}(" << this->mark << ");";
}
//Функция загрузки списка предметов из файла
template<>
int List<Subjects>::LoadSmthFromFile(const char *SmthIn)
{
	std::ifstream fin(SmthIn);
	while (fin)
	{
		Subjects subject;
		int flag = subject.ReadSubject(fin);
		if (!flag)
		{
			AddElements(subject);
			::number_subj++;
		}
		else break;
	}
	return number_subj;
}
//Функция загрузки информации об одном предмете 
int  Subjects::ReadSubject(std::ifstream &f)
{
	try
	{
		//f >> (NumberOfSubject);
		f >> (NameOfSubject);
		if (NameOfSubject.length() == 0) return 1;
		
		return 0;
	}
	catch (...)
	{
		return 1;
	}
}
//Функция загрузки списка предметов в файл
template<>
void List<Subjects>::LoadSmthToFile(const char *SmthOut)
{
	std::ofstream f_out;
	f_out.open(SmthOut, std::ios::app);
	f_out << "	Список предметов\n\nНачало:\n\n";
	List<Subjects> *q;
	for (q = this->next; q != NULL; q = q->next)
	{
		q->data.Write(f_out);
	}
	f_out << "\nКонец\n\n";
}
//Функция загрузки информации об одном предмете 
void   Subjects::Write(std::ofstream &f)
{
	f << "Номер - " << this->NumberOfSubject << "\n";
	f << "Идентификация - " << this->NameOfSubject << "\n";
	f << "\n";
}
//Функции вывода списков на экран
void   Information::WriteOnScreen()
{
	if (this->Name != "NONAME")
	{
		cout << "Имя - " << this->Name << "\n";
		cout << "Средний балл - " << this->Avg << "\n";
		if (this->pass != NULL)
		{
			this->pass->WriteExamensOnScreen();
			cout << "\n";
		}
	}
}
void   Prepods::WriteOnScreen()
{
	if (this->Name != "NONAME")
	{
		cout << "Имя - " << this->Name << "\n";
		if (this->pass != NULL)
		{
			this->pass->WriteExamensOnScreen();
			cout << "\n";
		}
	}
}
void   Chelovek::WriteOnScreen()
{
	if (this->Name != "NONAME")
	{
		cout << "Имя - " << this->Name << "\n";
		//cout << "Средний балл - " << this->Avg << "\n";
		if (this->pass != NULL)
		{
			this->pass->WriteExamensOnScreen();
			cout << "\n";
		}
	}
}
template<>
void List<MarksOnExam>::WriteExamensOnScreen()
{
	List<MarksOnExam> *q;
	for (q = this->next; q != NULL; q = q->next)
	{
		q->data.WriteExamOnScreen();
	}
}
void MarksOnExam::WriteExamOnScreen()
{
	if (this->mark == 91939)
	{
		cout << this->subject << " " << Sub->data.NameOfSubject << "; " ;
	}
	else
	{
		cout << this->subject << " " << Sub->data.NameOfSubject << " " << "(" << this->mark << ");";
	}
}
template<class T>
void List<T>::LoadOnScreen()
{
	if (typeid(T) == typeid(Subjects))
	{
		cout << "	Список экзаменов\n\nНачало:\n\n";
	}
	if (typeid(T) == typeid(Information))
	{
		cout << "	Список студентов\n\nНачало:\n\n";
	}
	if (typeid(T) == typeid(Prepods))
	{
		cout << "	Список преподавателей\n\nНачало:\n\n";
	}
	if (typeid(T) == typeid(Chelovek))
	{
		cout << "	Список людей\n\nНачало:\n\n";
	}
	List<T> *q;
	for (q = this->next; q != NULL; q = q->next)
	{
		q->data.WriteOnScreen();
	}
	cout << "\nКонец\n\n";
}
template<>
void List<MarksOnExam>::AddExam(string ch, int number, int mark, List<Subjects> *&E)
{
	MarksOnExam M;
	M.set_subject(number);
	M.set_mark(mark);
	List<Subjects> *q = E;
	for (q = E->next; q != NULL; q = q->next)
	{
		//Сравниваем номер предмета из списка предметов с номером предмета из списка экзаменов для данного студента
		if (number == (q->data).NumberOfSubject)
		{
			M.set_sub(q);
			AddElements(M);
		}
	}
}
template <>
void List<Prepods>::Copy_Paste(List<Prepods> *P)
{
	List<Prepods> *q;
	for (q = this->next; q != NULL; q = q->next)
	{
		P->AddElements(q->data);
	}
}
#endif