#include<iostream>
#include<fstream>
#include<ctype.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<process.h>
#include<math.h>
#include<conio.h>
#include<windows.h>


void hline()
{
	cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *";
}


void vline(int c)
{
	for (int i = 0; i < 25; i++)
	{
		gotoxy(c, i);
		cout << "*" << endl;
	}
}


void border()
{
	hline();
	vline(0);
	gotoxy(0, 25);
	hline();
	gotoxy(78, 25);
	cout << " *";
	vline(79);
}


class others
{
	public:
	  double transport, shop, transportcost, shopcost, netothers;

	others()
	{
		transportcost = 1000;
		shopcost = 1000;
		transport = shop = 1;
	}

	double calcothers()
	{
		netothers = (transport * transportcost) + (shop * shopcost);
		double b = netothers;
		return b;
	}
};

class facility
{
	public:
		double spa, spacost, drink, drinkcost, pool, poolcost, sauna, saunacost, netfac;

	facility()
	{
		spacost = 1000;
		drinkcost = 1000;
		poolcost = 1000;
		saunacost = 1000;
		spa=drink=pool=sauna=1;
	}

	double calcfac()
	{
		netfac = (spa * spacost) + (drink * drinkcost) + (pool * poolcost) + (sauna * saunacost);
		double a = netfac;
		return a;
	}
};

class amenities
{

	public:
		double wifi, wificost, refresh, refreshcost, netamen;

	amenities()
	{
		wificost = 1000;
		refreshcost = 1000;
		wifi = refresh = 1;
	}

	double calcamen()
	{
		netamen = (wifi * wificost) + (refresh * refreshcost);
		double a = netamen;
		return a;
	}
};

class guest: public facility, public amenities, public others
{
	public:
	int id;
	int rnum;
	char rtype[20];
	char gname[20];
	double nights;
	char stat;
	int rtaken;
	double nc;
	double tamt;

	guest() {
		id = 0;
		rnum = 0;
		strcpy(rtype, "Nill");
		strcpy(gname, "Nill");
		nights = 0;
		stat = 'n';
		rtaken = 0;
		nc = 0;
		tamt = 0;
	}

	void inputguest()
	{
		cout << "Enter Your Name:      ";
		gets(gname);
		cout << "Enter Guest ID:      ";
		cin >> id;
		cout << "Enter Duration of Stay:      ";
		cin >> nights;

	}

	int calcguest()
	{
		double a, b, c;
		a = calcfac();
		b = calcamen();
		c = calcothers();
		tamt = (nc * nights) + a + b + c;
		return tamt;
	}

	void outputguest(int r)
	{

		gotoxy(3, r);
		cout << id;
		gotoxy(17, r);
		cout << gname;
		gotoxy(35, r);
		cout << rnum;
		gotoxy(50, r);
		cout << nights;
		gotoxy(64, r);
		cout << tamt;

	}

	void bookroom();
	void readfile();
	void bill();
	void modguest();
	void delguest();

};

void roomfill()
{
	fstream f1, f2, f3;
	guest g1, g2, g3;

	f1.open("suitelist.dat", ios::out | ios::binary);
	f2.open("execlist.dat", ios::out | ios::binary);
	f3.open("buslist.dat", ios::out | ios::binary);

	for (int i = 0; i < 10; i++)
	{
		g1.rnum = 100 + i;
		g1.rtaken = 0;
		g1.nc = 4000;
		f1.write((char * ) & g1, sizeof(g1));
	}

	for (int j = 0; j < 10; j++)
	{
		g2.rnum = 200 + j;
		g2.rtaken = 0;
		g2.nc = 5000;
		f2.write((char * ) & g2, sizeof(g2));
	}

	for (int k = 0; k < 10; k++)
	{
		g3.rnum = 300 + k;
		g3.rtaken = 0;
		g3.nc = 2000;
		f3.write((char * ) & g3, sizeof(g3));
	}

	f1.close();
	f2.close();
	f3.close();
}

void guest::bookroom()
{
	guest g;
	fstream f1, f2, f3, f4, f5;

	char fname[20];
	int data;
	char type[30];
	int n;

	cout << "Enter number of records:" << endl;
	cin >> n;

	clrscr();

	f2.open("guestlist.dat", ios::app | ios::binary);

	for (int i = 0; i < n; i++)
	{
		gotoxy(35,0);
		cout << "Hello!" << endl << endl << endl;

		A:
		cout << "Enter the type of room you wish to book:" << endl;
		cout << "Enter Suite, Business or Executive:" << endl;
		gets(type);

		if (strcmpi(type, "suite") == 0)
		{
			strcpy(fname, "suitelist.dat");

		}

		else if (strcmpi(type, "business") == 0)
		{
			strcpy(fname, "buslist.dat");

		}

		else if (strcmpi(type, "executive") == 0)
		{
			strcpy(fname, "execlist.dat");

		}

		else
		{
			cout << "Invalid choice. Please enter a valid room type." << endl;
			goto A;
		}

		f1.open(fname, ios:: in | ios::binary);

		cout << "Available Room Numbers: " << endl;

		while (f1.read((char * ) & g, sizeof(g)))
		{
			if (g.rtaken == 0)
			{
				cout << g.rnum << "   ";
			}
		}

		cout<<endl;

		f1.close();
		f2.close();

		C:
		cout << "Enter the Desired Room Number:" << endl;
		cin >> data;

		int c = 0;
		int pos = -1 * sizeof(g);
		f1.open(fname, ios:: in | ios::out | ios::binary);
		f2.open("guestlist.dat", ios::app | ios::out | ios::binary);

		while (f1.read((char * ) & g, sizeof(g)))
		{

			if (g.rnum == data)
			{
				strcpy(g.rtype, type);

				if (g.rtaken == 1)
					cout << "Room not available. Please enter a valid room number." << endl;

				if (g.rtaken == 0)
				{
					g.rtaken = 1;

					f1.seekg(pos, ios::cur);

					cout << "Please enter your details:" << endl;

					g.inputguest();
					g.calcguest();

					f1.write((char * ) & g, sizeof(g));
					f2.write((char * ) & g, sizeof(g));

					cout << "Room " << data << " was chosen." << endl;
					c++;
				}
				break;
			}
		}

		f1.close();
		f2.close();

		if (c == 0)
		{
			cout << "Invalid choice." << endl;
			goto C;
		}
		getch();
		clrscr();
	}
}

void guest::readfile()
{
	fstream f;
	guest g;
	int r = 5;

	f.open("guestlist.dat", ios:: in | ios::out | ios::binary);

	clrscr();

	gotoxy(0, 2);
	hline();
	gotoxy(3, 3);
	cout << "ID";
	gotoxy(17, 3);
	cout << "Guest Name";
	gotoxy(35, 3);
	cout << "Room Number";
	gotoxy(50, 3);
	cout << "Duration(N)";
	gotoxy(64, 3);
	cout << "Grand Total";
	gotoxy(0, 4);
	hline();

	while (f.read((char * ) & g, sizeof(g)))
	{
		g.calcguest();
		g.outputguest(r);
		r = r + 2;
	}

	cout << endl;
   hline();
}

void guest::bill()
{
	fstream f;
	guest g;
	int data;

	f.open("guestlist.dat", ios:: in | ios::out | ios::binary);

	A:

	cout << "Enter Your Guest ID" << endl;
	cin >> data;

	int c = 0;

	while (f.read((char * ) & g, sizeof(g)))
	{

		if (g.id == data)
		{
			cout << "Enter any key to proceed to the bill" << endl;
			getch();
			clrscr();

			border();
			gotoxy(30, 3);
			cout << "GG Resorts & Spa";
			gotoxy(0, 5);
			hline();
			gotoxy(30, 7);
			cout << "Room Number       " << g.rnum;
			gotoxy(30, 8);
			cout << "Room Type         " << g.rtype;
			gotoxy(0, 10);
			hline();
			gotoxy(30, 12);
			cout << "Guest ID          " << g.id;
			gotoxy(30, 14);
			cout << "Room number       " << g.rnum;
			gotoxy(30, 16);
			cout << "Name              " << g.gname;
			gotoxy(30, 18);
			cout << "No. of Nights     " << g.nights;
			gotoxy(30, 20);
			cout << "Grand Total       " << g.calcguest();

			gotoxy(0, 22);
			hline();
			c++;

			getch();
			clrscr();
		}
	}

	if (c == 0)
	{
		cout << "Invalid entry. Please enter again." << endl;
		goto A;
	}
}

void guest::modguest()
{
	fstream f;
	guest g;
	int data;

	cout << "Enter Guest ID for modification:         ";
	cin >> data;

	f.open("guestlist.dat", ios::out | ios:: in | ios::binary);
	int i = -1 * sizeof(g);
	int pos = 0;

	while (f.read((char * ) & g, sizeof(g)))
	{
		if (data == g.id)
		{
			cout << "Records found. " << endl;

			f.seekg(i, ios::cur);
			g.stat = 'p';
			f.write((char * ) & g, sizeof(g));
			pos++;
		}
	}

	if (pos == 0)
		cout << "No such record was found. " << endl;

	else cout << "Data modified. " << endl;
}

void guest::delguest()
{
	fstream f1, f2, f3;
	guest g;
	int pos = 0;
	char fname[20];

	f1.open("guestlist.dat", ios:: in | ios::out | ios::binary);
	f2.open("sublist.dat", ios::out | ios::out | ios::binary);

	cout << "\nThis will delete records of guests who have paid. " << endl;

	while (f1.read((char * ) & g, sizeof(g)))
	{
		if (strcmpi(g.rtype, "suite") == 0)
		{
			strcpy(fname, "suitelist.dat");
		}

		else if (strcmpi(g.rtype, "business") == 0)
		{
			strcpy(fname, "buslist.dat");
		}

		else if (strcmpi(g.rtype, "executive") == 0)
		{
			strcpy(fname, "execlist.dat");
		}
	}

	f1.close();

	int i = -1 * sizeof(g);

	f1.open("guestlist.dat", ios:: in | ios::out | ios::binary);

	while (f1.read((char * ) & g, sizeof(g)))
	{
		if (g.stat == 'n' || g.stat == 'N')
		{
			f2.write((char * ) & g, sizeof(g));
		}
	}

	f1.close();

	int temp;

	f1.open("guestlist.dat", ios:: in | ios::out | ios::binary);

	while (f1.read((char * ) & g, sizeof(g)))
	{
		if (g.stat == 'p' || g.stat == 'P')
		{
			temp = g.rnum; pos++;

			f3.open(fname, ios:: in | ios::out | ios::binary);

			while (f3.read((char * ) & g, sizeof(g)))
			{
				if (g.rnum == temp)
				{
					g.rtaken = 0;

					int l = -1 * sizeof(g);
					f3.seekg(l, ios::cur);
					f3.write((char * ) & g, sizeof(g));
				}
			}

			f3.close();
		}
	}

	if (pos == 0)
		cout << "No such records were found." << endl;

	else
		cout << "Data Deleted" << endl;

	f1.close();
	f2.close();
	remove("guestlist.dat");
	rename("sublist.dat", "guestlist.dat");
}

char set_pwd[20] = "m-power.";

int pwd_chk(char A[])
{
	int i;

	for (i = 0;; i++)
	{
		A[i] = getch();
		if (A[i] != '\r')
		{
			if (A[i] == '\b')
			{
				cout << '\b';
				i--;
				i--;
			}

			else
				putch('*');
		}

		if (A[i] == '\r')
			break;
	}

	A[i] = '\0';

	if (strcmpi(A, set_pwd) == 0)
		return 1;

	else return 0;
}

int password()
{
	int i = 1, j = 1;

	char inp_pwd[20];

	cout << "Enter the password:" << endl;

	do
	{
		if (j > 1)
			cout << "\n Incorrect password, re-enter the password.\n";

		pwd_chk(inp_pwd);

		if (j == 4 && strcmp(set_pwd, inp_pwd) != 0)
		{
			cout << "\nNot more than 4 attempts " << endl;
			break;
		}

		j++;

	} while (strcmp(set_pwd, inp_pwd) != 0);

	if (strcmp(set_pwd, inp_pwd) == 0)
	{
		cout << "\nAccess Granted"<<endl;
		return 1;
	}

	else
	{
		cout << "\nAccess Denied"<<endl;
		return 0;
	}
}

void welcome()
{
	clrscr();
	border();
	gotoxy(25, 9);
	cout << "Passerelle vers le paradis!";
	cout << endl << endl;

	cout << "                        Welcome To GG Resorts & Spa" << endl;
	cout << endl;

	cout << endl;

	cout << "             We aim to provide our customers with the best service!" << endl;
	cout << endl;

	getch();
	clrscr();
}

int main()
{
	guest g;
	int c;
	char x;

	roomfill();

	do
	{
		clrscr();
		cout << "Main Menu" << endl;
		cout << "1. Book a room" << endl;
		cout << "2. Display details of all guests" << endl;
		cout << "3. Display details of any guest" << endl;
		cout << "4. Modify bill status of guest" << endl;
		cout << "5. Delete guest records" << endl;

		cout << "Enter your choice " << endl;
		cin >> c;

		int chk = 0;

		switch (c)
		{

			case 1:
						welcome();
						g.bookroom();
						break;

			case 2:
						if (password() == 1)
						{
							g.readfile();
							break;
						}

			case 3:
						g.bill();
						break;

			case 4:
						if (password() == 1)
						{
							g.modguest();
							break;
						}

			case 5:
						if (password() == 1)
						{
							g.delguest();
							break;
						}

			default:
						cout << "Invalid choice." << endl;
		}

		gotoxy(30, 24);
		cout << "Press key to continue. " << endl;

		x = getch();
	} while (1);
}
