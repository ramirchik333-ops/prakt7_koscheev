#define DEBUG_MODE
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

struct session
{
    string movietitle;
    int hallnumber;
    string starttime;
    int totatmest;
    int soldtickets;
    int pricetickets;
};

session ses[50];
int counts ;

void load()
{
  
    ifstream file("cinema.txt");
    if (!file.is_open()) {
        cout << "ошибка, не удалось найти файл!" << endl;
        return;
    }
    string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue;
        session s;
        int pos = line.find(';');
        s.movietitle = line.substr(0, pos);
        line = line.substr(pos + 1);

        pos = line.find(';');
        s.hallnumber = stoi(line.substr(0, pos));
        line = line.substr(pos + 1);

        pos = line.find(';');
        s.starttime = line.substr(0, pos);
        line = line.substr(pos + 1);

        pos = line.find(';');
        s.totatmest = stoi(line.substr(0, pos));
        line = line.substr(pos + 1);

        pos = line.find(';');
        s.soldtickets = stoi(line.substr(0, pos));
        line = line.substr(pos + 1);

        s.pricetickets = stoi(line);
        if (s.soldtickets > s.totatmest)
        {
            cout << "количество проданых билетов не может быть больше мест в зале" << endl;
            break;
        }
        ses[counts] = s;
        counts++;
    }
    file.close();
#ifdef DEBUG_MODE
    cout << "загружено записей: " << counts << endl;
#endif
}

void save()
{
    ofstream file("cinema.txt");
    if (!file.is_open())
    { 
        cout << "ошибка, не удалось найти файл!" << endl;
        return;
    }
    for (int i = 0; i < counts; i++)
    {
        file << ses[i].movietitle << ";" << ses[i].hallnumber << ";" << ses[i].starttime << ";" << ses[i].totatmest << ";" << ses[i].soldtickets << ";" << ses[i].pricetickets << "\n" << endl;
    }
    file.close();
#ifdef DEBUG_MODE
    cout << "сохранено записей: " << counts << endl;
#endif 
}
void showAll()
{
    cout << "все сеансы" << endl;
    for (int i = 0; i < counts; i++)
    {
        cout << ses[i].movietitle << " | зал - " << ses[i].hallnumber << " | начало в: " << ses[i].starttime << " | кол-во свободных мест: " << (ses[i].totatmest - ses[i].soldtickets) << " | цена - " << ses[i].pricetickets << endl;
        break;
    }
}

void sellTickets()
{
    string name;
    int tickets;
    cout << "фильм: " << endl;
    cin >> name;
    cout << "кол-во билетов: " << endl;
    cin >> tickets;
    for (int i = 0; i < counts; i++)
    {
        if (ses[i].movietitle == name) {
            int frees = ses[i].totatmest - ses[i].soldtickets;
            if (tickets > frees) {
                cout << "мало мест, свободно: " << frees << endl;
                return;
            }
            ses[i].soldtickets += tickets;
            cout << "продано" << endl;
            return;
        }
    }
    cout << "не найдено" << endl;
    return;
}

int main()
{
    
    setlocale(LC_ALL, "Russian");
    int choice;
    load(); 
    try {
        do {
        cout << "1. показать все сеансы" << endl;
        cout << "2. купить билеты(-ы)" << endl;
        cout << "3. сохранить и выйти" << endl;
        cin >> choice;
        
            if (choice == 1) showAll();
            else if (choice == 2) sellTickets();
            else save();
        } while (choice != 3);
    }
    catch(exception e)
    {
        cout << "ошибка: " << e.what() << endl;
    }
    return 0;
}