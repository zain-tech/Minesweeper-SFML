#include<iostream>
#include<iomanip>
#include<time.h>
#include<Windows.h>
#include<fstream>
#include<string>

using namespace std;
const char t = 30, k = 30;
bool cell_isopen = true;
bool islose = false;                                             //true for open and false for close....
bool iswin = false;
char tabLE[k][k];                                                //declared global array for table
//char _mines[k][k];
char copy_tabLE[k][k];                                          //copy of the original table containing mines to remove flag
int high_scores = 0, mine_num = 17, _col = 12, _row = 12, c_flag = 0, c_open = 0, que = 0;
string name;                                                     //name of the player ...
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void keep_window_open(){ char ch; cout << "\nplease enter a character to exit : "; cin >> ch; };
void show_menu();                                                //this will show the initial menu to the user.... first function
void oper_menu();                                                //operation on menu input... second function
void insTrucTions();                                            //this will show instructions (how to play ) to the user...3rd function
void highScores();                                              //shows high score menu -------------<<<<<<<<i will cover this later 4th function
void deve_lopers();                                             //it will just shows our names .5th function
void score();                                                   //to print the user score and check if user's score are in the list of high score or not.....
void game();                                                    // function which will handle most of the game functions....  6th fun
void print_board(char tabLE[][k], char copy[][k]);              //print table that is shown as output............7th fun
void set_mines(char tabLE[][k], char copy[][k], int c, int v);    //it will set mines............fun 8th
void cell_open_close(char check, bool& cell_isopen);            //............fun 9th
void checking_input(char _array[][k], int, int);                //.................fun 10
void count_mines(char _array[][k], int, int);                   //...............fun11
void reveal_mines(char _array[][k], int, int, char);            //................fun 12
void check_flag(char _array[][k], int, int, char copy[][k],char);    //fun 13 to put and remove flag 
void simple_error(){ cerr << "Error: please give correct input" << endl; system("pause"); }//fun 14
void game_win(char tabLE[][k], char copy[][k]);                                 //fun 15..check game state............
void print_board(char tabLE[][k]);                              //in order to print update table
void initialize(); void clr(int&); time_t time_since_epoch = time(0);
void input(char&,int&,int&);
time_t game_time;
//===========================================================================================
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
int main()
{
	system("title Minesweeper"); system("Color 7c"); 
	cout << "\n\n\n\t\t WELCOME \n\n\t\t\tTO\n\n\t\t\t  MINESWEEPER"; 
	Sleep(1100);
	cout << "\n\n\t\tLOADING"; Sleep(1500); cout << " .."; Sleep(1000); cout << "..."; Sleep(1000); cout << "...\r"; system("pause");
	show_menu();                                                //function call -->show initial menu to the user
	//..................................game...................................................................................
	keep_window_open();                                         //keep window open until user enter a chaaracter
	return 0;
}
///////////////////////////////////////////////////////////////functions///////////////////////////////////////////////////////
void show_menu()//first
{
	system("CLS"); 
	system("color 7c");
	time_since_epoch = time(0);//if user wanted to play again time should be reset
	string h; 
	ifstream fin("menu.txt");
	while (!fin.eof())
	{ 
		getline(fin, h);
	
	cout << h << endl;
	}               
	fin.close();
	oper_menu();                                               //function call  -->operation on menu get appropriate input and proceed
}
//=====================================================
void oper_menu()//second
{
	cout << "please enter the character to proceed : " << endl;
	char m_input; cin >> m_input;         //initialize menu_input in order to get input from user to proceed on menu..

	if (m_input == 'A' || m_input == 'a')               { game(); }
	else    if (m_input == 'B' || m_input == 'b')       { insTrucTions(); }
	else    if (m_input == 'C' || m_input == 'c')	    { system("cls"); highScores(); }
	else    if (m_input == 'D' || m_input == 'd')     	{ deve_lopers(); }
	else   	if (m_input == 'E' || m_input == 'e')	    { return; }
	else    { cout << "invalid entery" << endl << endl;	oper_menu(); }
}
//==========================================================
void insTrucTions()//3rd
{
	system("CLS");   ifstream fin("instructions.txt");              string h;
	while (!fin.eof()){ getline(fin, h); cout << h << endl; }       fin.close();
	char pl;	cin >> pl;
	if (pl == 'P' || pl == 'p' || pl == 'E' || pl == 'e')//for bad input
	{
		if (pl == 'P' || pl == 'p')       show_menu();
		if (pl == 'E' || pl == 'e')       return;
	}
	else        cout << "invalid input"; insTrucTions();
}
//========================================================
void highScores()//4th
{
	 system("Color 7C");   string a;
	cout	<< "  \n \nHigh Scores";
	ifstream fin("Scores.txt");          while (!fin.eof()){ getline(fin, a); cout << a << endl; } fin.close();
	cout << "enter R to go  to menu.";   char r;                                   cin >> r;
	while (r != 'R' && r != 'r')    { simple_error();	   cout << "\n enter R to go  to menu.";   	cin >> r; }
	show_menu();
}
//==================================================================
void deve_lopers()//5th
{
	system("CLS"); system("Color 4f"); Sleep(500);
	string h;
	ifstream fin("developers.txt"); 
	while (!fin.eof())
	{ getline(fin, h); cout << h << endl; Sleep(500); } 
	fin.close();
	char r;            cin >> r;
	while (r != 'R' && r != 'r') { simple_error(); cout << "\n  enter R to go back to menu.";	cin >> r; }show_menu();
}
//=========================================================================
void score()
{
	int b = 3, scr[3] = { 0 }, c;   char ch;        string nam[3], d; bool cond = true;      //bool to check if users score is > then any previous scores then 
	ifstream fin("Scores.txt");                                                             //next conditions executes
	for (int n = 0; n < b; ++n)                                                             //and update score file
		if (fin.get(ch))
		{
		fin >> nam[n];
		fin >> scr[n];
		}
	else	{ break; }        fin.close();

	for (int n = 0; n < b; ++n)
	if (high_scores>scr[n]) 
	{ cond = false;   scr[2] = high_scores;   nam[2] = name;   break; }

	if (!cond){//if score > previous one then this loop will execute
		for (int n = 0; n < b - 1; ++n)
		for (int r = n + 1; r < b; ++r)
		if (scr[r] > scr[n])	
		{ c = scr[r]; scr[r] = scr[n]; scr[n] = c;
		d = nam[r]; nam[r] = nam[n]; nam[n] = d; }//swap
		ofstream fout("Scores.txt");   fout << endl;    
		for (int y = 0; y < 3; ++y)       // input names and scores in file Score.txt
		{
			fout << nam[y] << " " << scr[y] << endl;
		}        fout.close();
	}
}
//===========================================================
void game()                    //6th fun         
{
	islose = false; iswin = false; c_flag = 0;   high_scores = 0;	bool mine_q = true; mine_num = 20; _row = 12; _col = 12; c_open = 0;  //to set mines once after user open first cell
	initialize();     print_board(tabLE, copy_tabLE);//fun 7 to set table equals to asterik
	int c = ' ', v = ' ';	char f = 'f';
	while (!islose&&!iswin)
	{
		game_time = time(0);
		system("cls");
		system("Color 0C"); 	
		cout << "Time:" << game_time - time_since_epoch << endl;
		print_board(tabLE);     //print table on the screen
		cout << "\nTotal   num  of  cells = " << _row*_col 
			 << "\nNum   of  opened  Cell = " << c_open << "\nNumber    of   Flags   = " << c_flag
			 << "\nNumber of question mark= " << que << "\nTotal   num  of  mines = " << mine_num;
		if (c >= 0 && c < _row&&v >= 0 && v < _col)           //if user enter bad input in first entery previous input option will not show
			cout << "\nprevious selected row col: " << c << "-" << v;                                        //---->conditi //if user enter bad input after first entery than previous no of row col will be shown...                                                                                         
		    cout << "\nselect a row col to open or flag a cell press enter after each entery: " << endl
		         << "open(Q) , flag(F) ,unknown(U): ";
		input(f, c, v);
		if (f == 'q' || f == 'Q')
		while (mine_q){ set_mines(tabLE, copy_tabLE, c, v); mine_q = false; }   //setting mines once after first execution condition false
		cell_open_close(tabLE[c][v], cell_isopen);                              //calling fun 3 to check that cell is already openor not
		if (cell_isopen)            { continue; } 
		if (f == 'f' || f == 'F'||f=='u'||f=='U')	check_flag(tabLE, c, v, copy_tabLE,f);       //if user want to put or remove flag
		if (f == 'q' || f == 'Q')   checking_input(tabLE, c, v);               //calling fun 10  to check input lose or cell open               
		game_win(tabLE, copy_tabLE);                                           //to check all the cell are open if yes then iswin = true
	}
	if (islose)
	{
		system("CLS");   
		print_board(tabLE);
		cout << endl << "ooh! you lose...";   
		score();
		cout << endl << "you select :" << c << "-" << v << endl;  
		system("pause"); 
		system("cls");
		cout << "Your Score " << high_scores << " Time to complete:" << game_time - time_since_epoch;
		highScores();
	}
	if (iswin)
	{
		score(); system("cls");  print_board(tabLE); cout << '\n'; cout << "congratulations you win..";  system("pause");
		system("cls");	cout << "Your Score " << high_scores << " Time to complete:" << game_time - time_since_epoch;
		highScores();
	}
}
//===============================================================
void input(char& f, int& c , int& v)
{
	 bool in_put = true;
	while (in_put){
		cin >> f;
		if (f != 'Q' && f != 'F' && f != 'q' && f != 'f'&&f != 'u'&&f != 'U')     //::::::::::if f is equanl to any of these //condition will false ... //if condition executes error message will be shown   //and  program will prompt for input again
		{
			cout << "Please give correct input:\nopen(Q) , flag(F) ,unknown(U):";
				cin.clear(); cin.ignore();  /*c = k + 10; v = k + 10;	*/	continue;
		}
		//I give c(row) & v(col) some values because if user give bad input   //--- i.e w 1 2 the message for previous selected row //and col will be shown..k+10 condition 1 can't be true
		cout << "row no : ";  	cin >> c;                                     //if user inter bad value for row and col condition  //will execute...
		if (!cin || (c < 0 || c >= _row))                                        //if condition executes error message will be shown   //and program will prompt for input again
		{
			cout << "Please give correct input:\nopen(Q) , flag(F) ,unknown(U):";
			cin.clear(); cin.ignore(); 		continue;
		}       // check for bad input and prompt input again                                               
		cout << "col no : ";   cin >> v;
		if (!cin || (v < 0 || v >= _col))
		{
			cout << "Please give correct input:\nopen(Q) , flag(F) ,unknown(U):";
			cin.clear(); cin.ignore();	continue;
		}in_put = false;
	}
}
//==================================================================
void initialize()
{
	bool intial = true;
	while (intial){
		_row = 12; _col = 12;
		system("cls");	cout << "\n\nEnter your name : "; cin >> name;
		cout << "\n\nFor customization press S:\n\nPress D to for default setting:\n";
		char ch; cin >> ch;
		if (ch == 'd' || ch == 'D' || ch == 's' || ch == 'S')
		{
			if (ch == 's' || ch == 'S'){
				cout << "Enter number of rows :"; cin >> _row;        if (!cin || _row > 30){ simple_error();	continue; }
				cout << "\nEnter number of columns :"; cin >> _col;   if (!cin || _col > 30){ simple_error();	continue; }
				cout << "\nEnter number of mines :"; cin >> mine_num; if (!cin || mine_num > _row*_col){ cin.ignore(); simple_error();	continue; }
			}     //loop will execute only once and its purpose is to handle errors and all bad inputs
		}
		else { cout << "\nPlease give correct input"; Sleep(1000); initialize(); }intial = false;
	}
}
//============================================================
void print_board(char tabLE[][k])
{
	int c = 1;
	int j = 0, f = 0, q = 0;     cout << endl << "\n\n\n\t\t\t  ";  cout << "_";  //j for counting open cells and f for flags
	for (int t = 0; t < _col; t++)	    
	{ clr(c);  cout << "_";  cout << t << "_"; }

	for (int i = 0; i < _row; i++)	   
	{
		clr(c); 	cout << "\n\t\t\t" << i; if (i < 10)cout << " |"; else cout << "|";
		for (int y = 0; y < _col; y++)
		if (tabLE[i][y] == 'M'&&!iswin&&!islose)
		{
			if (y >9)cout << " "; clr(c); c++; if (i == _row - 1){ cout << "_*_"; c--; }
			else{ cout << " * "; }
		}
		else{
	clr(c); c++;	if (y > 9)cout << " "; if (i == _row - 1) cout << "_" << tabLE[i][y] << "_";
	else { clr(c);  cout << " " << tabLE[i][y] << " "; }
	if (tabLE[i][y] == 'F')f++; if (tabLE[i][y] == '?')q++;
	else if (tabLE[i][y] == ' ' || tabLE[i][y] == '1' || tabLE[i][y] == '2' || tabLE[i][y] == '3' || tabLE[i][y] == '4' || tabLE[i][y] == '5' || tabLE[i][y] == '6' || tabLE[i][y] == '7' || tabLE[i][y] == '8') j++;
		}                              //c_flag will count number of flags placed
		cout << "|";
	} 
	c = 6; clr(c); c_open = j; c_flag = f; high_scores = j * 2; que = q; cout << "\nScore                  = " << high_scores;
}
void clr(int& c)
{
	c++; HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, c % 10 | FOREGROUND_INTENSITY);
	if (c % 10 == 0)SetConsoleTextAttribute(h, 3 | FOREGROUND_INTENSITY);
}
//=========================================================
void game_win(char tabLE[][k], char copy[][k])//.............fun 15
{
	bool state = true;
	for (int a = 0; a < _row; ++a)
	for (int j = 0; j < _col; ++j)
	{
		if (tabLE[a][j] == '*' || (tabLE[a][j] == 'F'&&copy[a][j] == '*' || tabLE[a][j] == '?'&&copy[a][j] == '*'))  { state = false;	break; }
	}
	if (state)                                                    { iswin = true; }
}
//===============================================
void check_flag(char _array[][k], int c, int v, char copy[][k],char f)//..............fun 13
{
	if (_array[c][v] == ' ' || _array[c][v] == '1' || _array[c][v] == '2' || _array[c][v] == '3' || _array[c][v] == '4' || _array[c][v] == '5' || _array[c][v] == '6' || _array[c][v] == '7' || _array[c][v] == '8')return;
	if ((f=='u'||f=='U')&&_array[c][v] != '?')                 { _array[c][v] = '?';	  return; }
	if ((f == 'f'||f == 'F')&&_array[c][v] != 'F' )            { _array[c][v] = 'F';return; }
	if ((f == 'f' || f == 'F')&&_array[c][v] == 'F')           { _array[c][v] = copy[c][v];  return; }
	if ((f == 'u' || f == 'U')&&_array[c][v] == '?')           { _array[c][v] = copy[c][v]; }
}
//===============================================
void print_board(char tabLE[][k], char copy[][k])                    //7th fun
{
	for (int n = 0; n < _row; n++)
	for (int j = 0; j < _col; j++)
	{
		tabLE[n][j] = '*';         copy[n][j] = '*';
	}
}
//======================================================
void set_mines(char tabLE[][k], char copy[][k], int c, int v)// ...........................fun 8
{
	srand(time(0));      char x = '0', y = '0';
	for (int i = 0; i < mine_num; ++i)
	{
		x = rand() % _row;   y = rand() % _col; 
		if (y == v&&x == c){ --i; continue; }//for first entery mine should not placed at user's first entery
		if (tabLE[x][y] == 'M'){ --i; continue; }	tabLE[x][y] = 'M'; 			copy[x][y] = 'M';
	}
}
//=======================================================
void cell_open_close(char check, bool& cell_isopen)//fun 9
{
	if (check != 'M' || check != '*' || check != 'F' || check != '?')	    cell_isopen = false;
	else                                                	cell_isopen = true;
}
//=========================================================
void checking_input(char _array[][k], int c, int v)// fun 10
{
	if (_array[c][v] == 'M')        { islose = true;     return; }
	if (_array[c][v] == 'F' || _array[c][v] == '?')//:::::::::::::::::::::::::::::
	{
		cout << "please remove flag first then open cell ." << endl;
		system("pause");          return;
	}         
	count_mines(_array, c, v);
}
//==================================================================================================
void count_mines(char _array[][k], int c, int v)// fun 11
{
	char n = '0'; 
	for (int new_r = c - 1; new_r <= c + 1; new_r++)
	{
		for (int new_c = v - 1; new_c <= v + 1; new_c++)
		{
			if (new_r<0 || new_r>_row || new_c<0 || new_c>_col) 
				continue;
			if (_array[new_r][new_c] == 'M')n++;
		}
	}
	if (n != '0')       	{ _array[c][v] = n;  return;   }
	if (n == '0')           { _array[c][v] = ' ';    reveal_mines(_array, c, v, n); } 
}
//=====================================================================================================
void reveal_mines(char _array[][k], int c, int v, char n)//..............fun 12
{
	for (int new_r = c - 1; new_r <= c + 1; new_r++)
	{

		for (int new_c = v - 1; new_c <= v + 1; new_c++)
		{	_array[new_r][new_c] == ' ';
			if ((new_r<0 || new_r>_row || new_c<0 || new_c>_col)||_array[new_r][new_c]!='*'||_array[new_r][new_c]==n)
				continue;		
			count_mines(_array, new_r, new_c);
		}
	}
}
//=================================================================
