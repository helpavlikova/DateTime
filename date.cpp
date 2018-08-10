#ifndef __PROGTEST__
#include <cstdio>
#include <ctime>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;
#endif /* __PROGTEST__ */

class InvalidDateException {};

ios_base & dummy_date_format_manipulator ( ios_base & x )
 {
   return x;
 }

ios_base & ( * ( date_format ( const char * fmt ) ) ) ( ios_base & x )
 {
   return dummy_date_format_manipulator;
 }
//=================================================================================================
class CDate
 {
   public:
    CDate ( int y, int m, int d );
    friend ostream& operator<<(ostream&, CDate);
    friend istream& operator>>(istream&, CDate&);
    friend ostringstream& operator<<(ostringstream&, CDate);
    friend istringstream& operator>>(istringstream &is , CDate&);
    friend CDate operator+ (int, CDate);
    friend CDate operator+ (CDate, int);
    friend CDate operator- (int, CDate);
    friend CDate operator- (CDate, int);
    friend int operator- (CDate, CDate);
    friend bool operator==(CDate a, CDate b);
    friend bool operator!=(CDate a, CDate b);
    friend bool operator>=(CDate a, CDate b);
    friend bool operator<=(CDate a, CDate b);
    friend bool operator>(CDate a, CDate b);
    friend bool operator<(CDate a, CDate b);
    CDate operator++ (void);
    CDate operator++ (int);
    CDate operator-- (int);
    CDate operator-- (void);
    int getYear(void);
    int getMonth(void);
    int getDay(void);
    bool Thirty(void);
    bool ThirtyOne(void);
    bool FebruaryEnd(void);
    bool EndOfTheYear(void);
    int NumberOfDays(CDate&);
    // operator - CDate
    // operators << and >>

   private:
    int year;
    int month;
    int day;
 };


CDate::CDate ( int y, int m, int d ){
InvalidDateException vyjimka;

if ( y < 2000 || y > 2030 || d < 1 || d > 31 || m < 1 || m > 12  ||
     ((m == 4 || m == 6 || m == 9 || m == 11 ) && d > 30) ||
     ( m == 2 && y%4!=0 && d > 28) || ( m == 2 && y%4==0 && d > 29) ){
    throw vyjimka;
}
year=y;
month=m;
day=d;
}
int CDate::getYear(void){
return year;
}
int CDate::getMonth(void){
return month;
}
int CDate::getDay(void){
return day;
}

bool CDate::Thirty(void){
return (month == 4 || month == 6 || month== 9 || month == 11 );
}

bool CDate::ThirtyOne(void){
return (month==1 || month==3 || month==5 || month==7 || month==8 || month==10);

}

bool CDate::FebruaryEnd(void){
return ((month==2 && year%4==0 && day==29) || (month==2 && year%4!=0 && day==28) );
}


bool CDate::EndOfTheYear(void){
return (month==12 && day==31);

}


CDate CDate::operator++ (void){
  if ((Thirty() && day == 30 )|| (ThirtyOne() && day == 31) || FebruaryEnd())
    {
        month++;
        day=1;
        return *this;
    }

  if(EndOfTheYear()){

    month=1;
    day=1;
    year++;
    return *this;
  }

 day++;
    return *this;

}

CDate CDate::operator++ (int){
CDate nove= *this;
  if ((Thirty() && day == 30 )|| (ThirtyOne() && day == 31) || FebruaryEnd())
    {
        month++;
        day=1;
        return nove;
    }

  if(EndOfTheYear()){

    month=1;
    day=1;
    year++;
    return nove;
  }

day++;
return nove;

}

CDate CDate::operator-- (int){
CDate nove= *this;

    if (month == 8 && day == 1 ){
    month--;
    day=31;
    return *this;
    }


if( Thirty() && day==1 ){

    day=31;
    month--;
    return nove;
}

if( day==1  && month==1 ){

    day=31;
    month=12;
    year--;
    return nove;
}

if( (ThirtyOne() && month!=3 && day==1) ||  ( month == 12 && day ==1 ) ){
    day=30;
    month--;
    return nove;
}

if( month==3 && day==1 && year%4 == 0){
    day=29;
    month--;
    return nove;
}

if(  month==3 && day==1 && year%4 != 0){
    day=28;
    month--;
    return nove;
}

if (month == 2 && day == 1 ){
    month--;
    day=31;
    return nove;
}

day--;
return nove;
}

CDate CDate::operator-- (void){

    if (month == 8 && day == 1 ){
    month--;
    day=31;
    return *this;
    }


if( Thirty() && day==1 ){

    day=31;
    month--;
    return *this;
}

if( day==1  && month==1 ){

    day=31;
    month=12;
    year--;
    return *this;
}

if( (ThirtyOne() && month!=3  && day==1) || ( month == 12 && day ==1 ) ){
    day=30;
    month--;
    return *this;
}

if( month==3 && day==1 && year%4 == 0){
    day=29;
    month--;
    return *this;
}

if( month==3 && day==1 && year%4 != 0){
    day=28;
    month--;
    return *this;
}

if (month == 2 && day == 1 ){
    month--;
    day=31;
    return *this;
}

day--;
return *this;
}

ostream& operator<< (ostream &os, CDate date){
  os << date.year << "-";

  if( date.month < 10){
    os << 0;
  }

  os << date.month << "-";

  if( date.day < 10){
    os << 0;
  }
  os << date.day;
return os;
}


ostringstream& operator<<(ostringstream &os , CDate date){
  os << date.year << "-";

  if( date.month < 10){
    os << 0;
  }

  os << date.month << "-";

  if( date.day < 10){
    os << 0;
  }
  os << date.day;
return os;
}



istringstream& operator>>(istringstream &is , CDate &date){
    char c,d;

  CDate tmp(date.getYear(),date.getMonth(),date.getDay());

  is >> date.year >> c >> date.month >> d >> date.day;

  if( is.fail() || c != '-' || d != '-' ||  date.year < 2000 || date.year > 2030 || date.day < 1 || date.day > 31
     || date.month < 1 || date.month > 12  ||
      ((date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11 ) && date.day > 30) ||
     ( date.month == 2 && date.year%4!=0 && date.day > 28) || ( date.month == 2 && date.year%4==0 && date.day > 29) ){
    is.clear();
    is.setstate(std::ios::failbit);
    date.year=tmp.year;
    date.month=tmp.month;
    date.day=tmp.day;
  }

    return is;
}


istream& operator>>(istream &is , CDate &date){
    char c,d;

  CDate tmp(date.getYear(),date.getMonth(),date.getDay());

  is >> date.year >> c >> date.month >> d >> date.day;

  if( is.fail() || c != '-' || d != '-' ||  date.year < 2000 || date.year > 2030 || date.day < 1 || date.day > 31
     || date.month < 1 || date.month > 12  ||
      ((date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11 ) && date.day > 30) ||
     ( date.month == 2 && date.year%4!=0 && date.day > 28) || ( date.month == 2 && date.year%4==0 && date.day > 29) ){
    is.clear();
    is.setstate(std::ios::failbit);
    date.year=tmp.year;
    date.month=tmp.month;
    date.day=tmp.day;
  }

    return is;
}

 CDate operator+ (CDate datum, int n){
 if (n>0){
    for(int i=0; i<n; i++){
        datum++;
    }
    return datum;

 }

 for(int i=0;i<n;i++){
    datum--;
 }

return datum;
 }

 CDate operator+ (int n,CDate datum){
 if (n>0){
    for(int i=0; i<n; i++){
        datum++;
    }
    return datum;

 }

 for(int i=0;i<n;i++){
    datum--;
 }

 return datum;
 }

 CDate operator- (CDate datum, int n){

 if (n<0){
    for(int i=n; i<0; i++){
        datum++;
    }
    return datum;

 }

 for(int i=0;i<n;i++){
    datum--;
 }

 return datum;
 }

CDate operator- (int n, CDate datum){
 if (n<0){
    for(int i=0; i<n; i++){
        datum++;
    }
    return datum;

 }

 for(int i=0;i<n;i++){
    datum--;
 }

 return datum;
 }



bool operator==(CDate a, CDate b){
return (a.year==b.year && a.month == b.month && a.day == b.day);
}

bool operator!=(CDate a, CDate b){
return (a.year!=b.year || a.month != b.month || a.day != b.day);
}


bool operator>(CDate a, CDate b){
if (a.year > b. year){ return true;}
if (a.year < b. year){ return false;}
if (a.month > b.month) { return true;}
if (a.month < b.month) { return false;}
if (a.day > b. day) {return true;}
return false;
}

bool operator<(CDate a, CDate b){
if (a.year < b. year){ return true;}
if (a.year > b. year){ return false;}
if (a.month < b.month) { return true;}
if (a.month > b.month) { return false;}
if (a.day < b. day) {return true;}
return false;
}

bool operator>=(CDate a, CDate b){
return ( a > b || a==b );
}


bool operator<=(CDate a, CDate b){
return ( a < b || a==b );
}

int NumberOfDays(CDate &date){
 int days=date.getDay();

  for (int i = 0; i < date.getYear()-2000; i++){
    if(i%4==0) {days+=366;}
    else {days+=365;}
  }

  for ( int i = 1; i < date.getMonth(); i++){
    if ( i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12){
        days+=31;
    }
    if ( i == 4 || i == 6 || i == 9 || i == 11){
        days+=30;
    }
    if (i == 2 && date.getYear()%4 == 0){
        days+=29;
    }
    if (i == 2 && date.getYear()%4 != 0){
        days+=28;
    }

  }


  return days;
}


int operator- (CDate a, CDate b){
int vysledek;

vysledek = NumberOfDays(a) - NumberOfDays(b);

if(vysledek<0){
    return -1 * vysledek;
}
return vysledek;
}

#ifndef __PROGTEST__
int main()
{

ostringstream oss;
istringstream iss;

CDate a ( 2000, 1, 2 );
CDate b ( 2010, 2, 3 );
CDate c ( 2004, 2, 10 );
oss . str ("");
oss << a;
assert ( oss . str () == "2000-01-02" );
oss . str ("");
oss << b;
assert ( oss . str () == "2010-02-03" );
oss . str ("");
oss << c;
assert ( oss . str () == "2004-02-10" );
a = a + 1500;
oss . str ("");
oss << a;
assert ( oss . str () == "2004-02-10" );
b = b - 2000;
oss . str ("");
oss << b;
//cout << oss.str() << endl;


assert ( oss . str () == "2004-08-13" );
assert ( b - a == 185 );
assert ( ( b == a ) == false );
assert ( ( b != a ) == true );
assert ( ( b <= a ) == false );
assert ( ( b < a ) == false );
assert ( ( b >= a ) == true );
assert ( ( b > a ) == true );
assert ( ( c == a ) == true );
assert ( ( c != a ) == false );
assert ( ( c <= a ) == true );
assert ( ( c < a ) == false );
assert ( ( c >= a ) == true );
assert ( ( c > a ) == false );
a = ++c;
oss . str ( "" );
oss << a << " " << c;


assert ( oss . str () == "2004-02-11 2004-02-11" );
a = --c;
oss . str ( "" );
oss << a << " " << c;
assert ( oss . str () == "2004-02-10 2004-02-10" );
a = c++;
oss . str ( "" );
oss << a << " " << c;
assert ( oss . str () == "2004-02-10 2004-02-11" );
a = c--;
oss . str ( "" );
oss << a << " " << c;
assert ( oss . str () == "2004-02-11 2004-02-10" );
iss . clear ();
iss . str ( "2015-09-03" );
assert ( ( iss >> a ) );
oss . str ("");
oss << a;
assert ( oss . str () == "2015-09-03" );
a = a + 70;
oss . str ("");
oss << a;
assert ( oss . str () == "2015-11-12" );

CDate d ( 2000, 1, 1 );
try
 {
    CDate e ( 2000, 32, 1 );
    assert ( "No exception thrown!" == NULL );
 }
catch ( ... ) { }
iss . clear ();
iss . str ( "2000-12-33" );
assert ( ! ( iss >> d ) );
oss . str ("");
oss << d;
assert ( oss . str () == "2000-01-01" );
iss . clear ();
iss . str ( "2000-11-31" );
assert ( ! ( iss >> d ) );
oss . str ("");
oss << d;
assert ( oss . str () == "2000-01-01" );
iss . clear ();
iss . str ( "2000-02-29" );
assert ( ( iss >> d ) );
oss . str ("");
oss << d;
assert ( oss . str () == "2000-02-29" );
iss . clear ();
iss . str ( "2001-02-29" );
assert ( ! ( iss >> d ) );
oss . str ("");
oss << d;
assert ( oss . str () == "2000-02-29" );

    return 0;
}

#endif /* __PROGTEST__ */
