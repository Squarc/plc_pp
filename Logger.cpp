#include "Logger.h"


Logger::Logger(std::string path,std::string filename,bool timeDep):timeDep{timeDep} {
    this->filename=filename;
    if(path.back()!='/') path.push_back('/');
    this->path=path;
    system((std::string("mkdir -p ")+path).c_str());
}
Logger::~Logger() { }

void Logger::SetFileName(std::string filename) {
    this->filename=filename;
    timeDep=false;
}
void Logger::SetTimeDepFileName(std::string path,std::string filename) {
    this->filename=filename;
    if(path.back()!='/') path.push_back('/');
    this->path=path;
    system((std::string("mkdir -p ")+path).c_str());
    timeDep=true;
    //std::cout<<"Set file name: "<<path<<"%%TIME%%_"<<filename<<std::endl;
}

void Logger::Message(std::string message) {
    if(filename.empty()) {
        std::cout<<"Filename is empty"<<std::endl;
        return;
    }
    std::ofstream outfile;
    T = time(NULL);
    struct tm *u;
    u = localtime(&T);
    if(timeDep) {
        strftime(s, 80, "%Y%m%d",u);
        outfile.open(path+s+"_"+filename,std::ofstream::out|std::ios_base::app);
    }
    else outfile.open(filename, std::ofstream::out|std::ios_base::app);
    strftime(s, 80, "%d.%m.%Y %H:%M:%S",u);
    outfile<<s<<" "<<message<<std::endl;
    outfile.close();
}
/// @brief Запись информации в файл через шаблонные записи
/// @param msg Текстовый шаблон
/// @param  Параметры
void Logger::WriteLog(const char *msg, ...) {
    if(filename.empty()) {
        std::cout<<"Filename is empty"<<std::endl;
        return;
    }
    FILE* f;
    time_t T = time(NULL);
    struct tm *u;
    char s[80] = { 0 };
    //time(&T);
    u = localtime(&T);
    if(timeDep) {
        strftime(s, 80, "%Y%m%d",u);
        f=fopen((path+s+"_"+filename).c_str(), "a+");
    } 
    else
        f=fopen(filename.c_str(), "a+");
    if (f) {
        va_list args;
        va_start(args, msg);
        strftime(s, 80, "%d.%m.%Y %H:%M:%S ",u);
        fprintf(f,"%s ",s); // запись в файл
        vfprintf(f, msg, args);
        fprintf(f,"\n");
        fclose(f);
        va_end(args);
    }
}
/// @brief Запись информации в файл и консоль через шаблонные записи
/// @param msg Текстовый шаблон
/// @param  Параметры
void Logger::WriteConLog(const char *msg, ...) {
    if(filename.empty()) {
        std::cout<<"Filename is empty"<<std::endl;
        return;
    }
    FILE* f;
    time_t T = time(NULL);
    struct tm *u;
    char s[80] = { 0 };
    time(&T);
    u = localtime(&T);
    if(timeDep) {
        strftime(s, 80, "%Y%m%d",u);
        f=fopen((path+s+"_"+filename).c_str(), "a+");
    } 
    else
        f=fopen(filename.c_str(), "a+");
    if (f) {
        va_list args;
        va_start(args, msg);
        strftime(s, 80, "%d.%m.%Y %H:%M:%S ",u);
        fprintf(f,"%s ",s); // запись в файл
        vfprintf(f, msg, args);
        fprintf(f,"\n");
        printf("%s ",s); // запись в консоль
        vprintf(msg, args);
        printf("\n");
        fclose(f);
        va_end(args);
    }
}


