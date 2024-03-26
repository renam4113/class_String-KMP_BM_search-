#include <iostream>
#include <string.h>

using namespace std;

class String {
  char *line;
  int len;
  public:
    String(int l = 0); // fierce unluck
    String(const char *); 
    String(const String &); 
    String operator()(int , int ); // выделяет подстроку из исходной строки с i-ого по j-ый символы.
    ~String() { if(line) delete []line; line = NULL; }
    int getLen();
    char & Index(int); // кринж
    String & operator = (String &);
    char &operator [](int);
    bool operator == (String &);
    bool operator != (String &);
    String operator + (const String &);
    String & operator += (const String &);
    String & operator ++ ();
    operator int ();
    int BMH_search(const String &);
    operator char* (); 
    friend istream & operator >> (istream &, String &);
    friend ostream & operator << (ostream &, const String &);
    int KMP_search(const String &);
};

String String:: operator()(int i, int j){
    
    String a(abs(i - j) + 2);
    int m = 0;
    for(int k = i; k <= j && line[k] != '\0'; k++){
      a.line[m] = line[k];
      m++;
    }
    a[m] = '\0';
    return a;
}



int String:: BMH_search(const String& s1){
    int Tab[256] = {0};
    for (int i = 0; i < 256; i++) Tab[i] = s1.len; 
    for(int i = 0; i < s1.len - 1; i++) Tab[(unsigned char)s1.line[i]] = s1.len - 1 - i;
    
    int i = s1.len - 1;
    int j = s1.len - 1;

    while( i < len - s1.len - 1){
        if (j == 0) return i - s1.len + 1;
        j = s1.len - 1;
        int k = i;
         while(j > 0 && i < len - s1.len - 1){
            
            if(s1.line[j] == line[k]){
                k--;
                j--;
            }
            else{ 
                i = i + Tab[(unsigned char)line[k]];
                k = i;
                j = s1.len - 1;
            }
        }
    }
    return -1;
}

String:: String(int i){
  if(i >= 1) line = new char[i + 1]; 
  len = i;
  line[i] = '\0';
}


ostream& operator << (ostream& out, const String& s) {
  out << s.line;
  return out;
}

String:: String(const char* a){
  line = new char[strlen(a) + 1];
  strcpy(line, a);
  len  = strlen(a);
}


String:: String(const String &s2){
   line  = new char[s2.len + 1];
   len  = s2.len;
   strcpy(line, s2.line);
}

int String:: getLen() {
  return len;
}

char& String::Index(int i) {
  if(i < 0 || i >= len){
    cout << "\n Индекс за пределами строки»";
    return line[0];
  }
  return line[i];
}

bool String:: operator == (String& other) {
  if(len != other.len) return false;
  if(strcmp(line, other.line) == 0) return true;
  return false;
}


 
istream & operator >> (istream & in, String & s){
  char S[128];
  in >> S;
  strcpy(s.line, S);
  s.len = strlen(s.line);
  return in;
}



String String:: operator + (const String &s) { 
  String z(len+s.len+1);
  strcpy(z.line, line);   
  strcat(z.line, s.line);  
  z.len = strlen(z.line); 
  return z;                  
                              
}

bool String:: operator != (String &s){
  if(len != s.len || strcmp(line, s.line) != 0) return true;
  else return false;
}

String& String:: operator = (String &s){
  if(this != &s){
  delete []line;
  line = new char[s.len + 1];
  len = s.len;
  strcpy(line, s.line);
  }
  return *this;
}

String &  String:: operator += (const String &S){
  String z = *this;
  delete []line;
  line = new char[S.len + len + 1];
  len = len + S.len;
  strcpy(line,S.line);   
  strcat(line,z.line);
  return *this;
}

char & String::operator [](int i) {
  if(i < 0 || i >= len) {
    cout << "\n Индекс за пределами строки";
    return line[0];
  }
  return line[i];
}

String& String:: operator ++(){
  for(int i = 0; i < len; i++) line[i]++;
  return *this;
}

 String:: operator char*(){
   char* a = new char[len + 1];
   for( int i = 0; i < len ; i++) a[i] = line[i];
   return a;
 }

String ::operator int() {
  int k = 0, i;
  for(i = 0; i < len; i++)
  k = k * 10 + line[i] - '0';
  
   return k;
}

int String:: KMP_search(const String & s1){
    //cout << s1;
    int j = 0;
    int k = -1;
    int NewJ[s1.len] = {0};
    NewJ[0] = -1;
    while(j < s1.len - 1){
        if(k >= 0){
            if(s1.line[j] != s1.line[k]){
                k = NewJ[k];
            }
            else{
                k++;
                j++;
                if(s1.line[j] == s1.line[k]){
                    NewJ[j] = NewJ[k];
                }
                else{ 
                    NewJ[j] = k;
                    cout << k << ":" << j << ":" << NewJ[j] << "\n";
                }
            }
        }
        else{
        k++;
        j++;
        if(s1.line[j] == s1.line[k]) NewJ[j] = NewJ[k];
        else NewJ[j] = k;
        }
    }
    
    j = 0;
    int i = 0;

    while ( j < s1.len){
        if(i >= len) return -1;

        while (j >= 0){
            if(line[i] != s1.line[j]) j = NewJ[j];
            else break;
        }
    i++;
    j++;
        
    }

    if(j >= s1.len) return i - s1.len;
    return -1;
}




int main(){

  String s("grass on the ground, firewood on the grass");
  String S("firewood");
  int k = s.BMH_search(S);
  cout << k << endl;

  return 0;
}