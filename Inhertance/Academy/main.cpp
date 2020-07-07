#include<iostream>
#include<string>
using namespace std;

//#define DEBUG
//Polymorphism (����������������)

class Human
{
	string name;
	string surname;
	unsigned int age;
public:
	const string& get_name()const
	{
		return name;
	}
	const string& get_surname()const
	{
		return surname;
	}
	unsigned int get_age()const
	{
		return age;
	}
	string& set_name(const string& name)
	{
		return this->name = name;
	}
	string& set_surname(const string& surname)
	{
		return this->surname = surname;
	}
	unsigned int set_age(unsigned int age)
	{
		return this->age = age;
	}
	//			Constructors:
	Human(const string& name, const string& surname, unsigned int age)
	{
		set_name(name);
		set_surname(surname);
		set_age(age);
#ifdef DEBUG
		cout << "HConstructor:\t" << this << endl;
#endif // DEBUG

	}
	~Human()
	{
#ifdef DEBUG
		cout << "HDestructor:\t" << this << endl;
#endif // DEBUG

	}

	//		Methods:
	void print()const
	{
		cout << name << " " << surname << " " << age << " ���.\t";
	}
};

class Student :public Human
{
	string group;
	unsigned int rating;
	unsigned int attendence;
public:
	const string& get_group()const
	{
		return group;
	}
	unsigned int get_rating()const
	{
		return rating;
	}
	unsigned int get_attendence()const
	{
		return attendence;
	}
	string& set_group(const string& group)
	{
		return this->group = group;
	}
	unsigned int set_rating(unsigned int rating)
	{
		return this->rating = rating;
	}
	unsigned int set_attendence(unsigned int attendence)
	{
		return this->attendence = attendence;
	}
	//			Constructors:
	Student
	(
		const string& name, const string& surname, unsigned int age,
		const string& group, unsigned int rating, unsigned int attendence
	):Human(name, surname, age)
	{
		set_group(group);
		set_rating(rating);
		set_attendence(attendence);
#ifdef DEBUG
		cout << "SConstructor:\t" << this << endl;
#endif // DEBUG

	}
	~Student()
	{
#ifdef DEBUG
		cout << "SDestructor:\t" << this << endl;
#endif // DEBUG

	}

	//			Methods
	void print()const
	{
		Human::print();
		cout << group << " ������������:" << rating << " ������������:" << attendence << endl;
	}
};

class Teacher :public Human
{
	string spec;
	unsigned int xp;
public:
	const string& get_spec()const
	{
		return spec;
	}
	unsigned int get_experienxe()const
	{
		return xp;
	}
	string& set_spec(const string& spec)
	{
		return this->spec = spec;
	}
	unsigned int set_experienxe(unsigned int xp)
	{
		return this->xp=xp;
	}

	//			Constructors:
	Teacher
	(
		const string& name, const string& surname, unsigned int age,
		const string& spec, unsigned int xp
	) :Human(name, surname, age)
	{
		set_spec(spec);
		set_experienxe(xp);
#ifdef DEBUG
		cout << "TConstructor:\t" << this << endl;
#endif // DEBUG

	}
	~Teacher()
	{
#ifdef DEBUG
		cout << "TDestructor:\t" << this << endl;
#endif // DEBUG

	}

	//			Methods:
	void print()const
	{
		Human::print();
		cout << spec << " ���� ������������:" << xp << " ���.\n";
	}
};

class Graduate :public Student
{
	string diploma_theme;
public:
	const string& get_diploma_theme()const
	{
		return diploma_theme;
	}
	string& set_diploma_theme(const string& diploma_theme)
	{
		return this->diploma_theme = diploma_theme;
	}
	//			Constructors:
	Graduate
	(
		const string& name, const string& surname, unsigned int age,
		const string& group, unsigned int rating, unsigned int attendence,
		const string& diploma_theme
	) :Student(name, surname, age, group, rating, attendence)
	{
		set_diploma_theme(diploma_theme);
#ifdef DEBUG
		cout << "GConstructor:\t" << this << endl;
#endif // DEBUG

	}
	Graduate(const Student& stud, const string& diploma_theme) :Student(stud)
	{
		set_diploma_theme(diploma_theme);
#ifdef DEBUG
		cout << "GCConstructor:\t" << this << endl;
#endif // DEBUG

	}
	~Graduate()
	{
#ifdef DEBUG
		cout << "GDestructor:\t" << this << endl;
#endif // DEBUG

	}

	void print()const
	{
		Student::print();
		cout << "���� ���������� �������: " << diploma_theme << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	/*Human h( "�������", "��������",18);
	h.print();*/

	/*Student stud("�������", "��������", 18, "PV_911", 20, 30);
	stud.print();

	Teacher Albert("Albert", "Einstein", 141, "Theory of relativity", 120);
	Albert.print();

	Graduate pink("Jessie", "Pinkman", 25, "n/a", 70, 100, "Methamphitamin development");
	pink.print();

	Graduate petr(stud, "��������� �������");
	petr.print();*/

	Human group[] = 
	{
		Student("����", "��������", 17, "PV_911", 100,100),
		Student("�������", "�������", 16, "PV_911", 100, 99),
		Teacher("������", "�����������", 40, "HardwarePC", 20),
		Student("����", "��������", 16, "PV_911", 98, 95),
		Teacher("�����", "�������", 30, "Web development", 5),
		Graduate("����", "�����������", 19, "PV_911", 100, 100, "���������� ����������� ������������� � �������� � ����� OCaml"),
	};
	cout << sizeof(group) << endl;
	cout << size(group) << endl;
	for (int i = 0; i < size(group); i++)
	{
		group[i].print();
		cout << endl;
	}
}