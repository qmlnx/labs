#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
using namespace std;

const int MAX_WORDS = 50;
const int MAX_LEN = 25;

void clr(char* s) { int l=strlen(s); if(l>0&&s[l-1]=='\n') s[l-1]=0; }

void part1() {
    printf("\n ЧАСТЬ 1. ДЕМОНСТРАЦИЯ ФУНКЦИЙ \n\n");
    int n; char s[100];
    
    cout << "cin: Введите число: "; cin >> n; cout << "cout: " << n << "\n";
    printf("printf: Введите число: "); scanf("%d", &n); printf("scanf: %d\n", n); getchar();
    printf("gets: Введите строку: "); fgets(s,100,stdin); clr(s); printf("puts: "); puts(s);
    
    FILE* f = fopen("test.txt","w"); fprintf(f,"hello 42\nworld 123\n"); fclose(f);
    
    f = fopen("test.txt","r"); char w[50]; int x;
    while(fscanf(f,"%s %d",w,&x)!=EOF) printf("fscanf: %s %d\n",w,x);
    
    rewind(f); printf("feof/EOF: ");
    while(getc(f)!=EOF); 
    if(feof(f)) printf("достигнут конец файла (EOF)\n");
    fclose(f);
    
    f = fopen("binary.dat","wb+"); int d[]={1,2,3}, r[3];
    fwrite(d,4,3,f); rewind(f); fread(r,4,3,f); 
    printf("fread/fwrite: %d %d %d\n",r[0],r[1],r[2]); fclose(f);
    
    remove("test.txt"); remove("binary.dat");
}

void part2() {
    printf("\n ЧАСТЬ 2. КОРНЕВЫЕ СЛОВА \n");
    
    string base = "/Users/qmlnx/Desktop/labs/c++/lab11/";
    FILE* in = fopen((base + "test4.txt").c_str(), "r");
    if(!in) { printf("Файл не найден\n"); return; }
    
    vector<string> words;
    char line[256];
    while(fgets(line,256,in) && words.size()<MAX_WORDS) {
        clr(line);
        if(strlen(line)<2||strchr(line,'=')||strchr(line,'-')) continue;
        char* t=strtok(line," \t");
        while(t && words.size()<MAX_WORDS) {
            string s(t);
            if(s.length()<=MAX_LEN && s.length()>0) {
                bool found=false;
                for(auto& w:words) if(w==s) found=true;
                if(!found) words.push_back(s);
            }
            t=strtok(0," \t");
        }
    }
    fclose(in);
    
    int n=words.size();
    if(!n) {
        FILE* o1=fopen((base+"output_longest.txt").c_str(),"w");
        FILE* o2=fopen((base+"output_important.txt").c_str(),"w");
        fprintf(o1,"NO\n"); fprintf(o2,"NO\n");
        fclose(o1); fclose(o2);
        printf("Корневых слов нет\n"); return;
    }

    //ПОДГОТОВКА
    struct Word { char text[MAX_LEN+1]; int len; int cnt; vector<int> kids; } data[MAX_WORDS];
    for(int i=0;i<n;i++) {
        strcpy(data[i].text, words[i].c_str()); //положили
        data[i].len = words[i].length(); //измерили 
        data[i].cnt = 0; //пока не знаем корень или нет
    }
    
    //ПОИСК
    bool isRoot[MAX_WORDS]={0};
    for(int i=0;i<n;i++) { 
        for(int j=0;j<n;j++) {
            if(i!=j && data[i].len<=data[j].len && //проверяем является одно началом другого
               strncmp(data[i].text,data[j].text,data[i].len)==0) {
                isRoot[i]=true;
                data[i].cnt++; //запоминаем корень
                data[i].kids.push_back(j);
            }
        }
    }
    
    int li=-1, lmax=0, ii=-1, imax=0;
    for(int i=0;i<n;i++) if(isRoot[i]) {
        if(data[i].len>lmax) { lmax=data[i].len; li=i; }
        if(data[i].cnt>imax) { imax=data[i].cnt; ii=i; }
    }
    
    printf("\n ПОЛНЫЕ РЕЗУЛЬТАТЫ \n");
    if(li>=0) {
        printf("Самое длинное корневое: %s\n", data[li].text);
        printf("Слова-потомки: ");
        for(int k:data[li].kids) printf("%s ", data[k].text);
        printf("\n");
    } else printf("Самое длинное корневое: NO\n");
    
    if(ii>=0) {
        printf("Самое важное слово: %s\n", data[ii].text);
        printf("Количество потомков: %d\n", data[ii].cnt);
        printf("Список потомков: ");
        for(int k:data[ii].kids) printf("%s ", data[k].text);
        printf("\n");
    } else printf("Самое важное слово: NO\n");
    
    FILE* o1=fopen((base+"output_longest.txt").c_str(),"w");
    if(li>=0) {
        fprintf(o1,"%s\n",data[li].text);
        for(int k:data[li].kids) fprintf(o1,"%s\n",data[k].text);
    } else fprintf(o1,"NO\n");
    fclose(o1);
    
    FILE* o2=fopen((base+"output_important.txt").c_str(),"w");
    if(ii>=0) fprintf(o2,"%s %d\n",data[ii].text,data[ii].cnt);
    else fprintf(o2,"NO\n");
    fclose(o2);
}

int main() {
    part1();
    part2();
    return 0;
}