#include<iostream>
using namespace std;
static double health = 300; // остаток травы, после её поедания
static int h = 1;//Счетчик Итераций
static float recovery = 1.2;// коэффицент восстановления травы
static int TheEnd; //количество животных в игре
static int Killer = -1;
struct herbivores {
    int x, y; //начальные координаты животного
    int age;
    int death_age;
    int minRep; //минимальный репродуктивный возраст
    int maxRep; // максимальный репродуктивный возраст
    int foodh; // количество поедания травы
    bool dmark;
};
struct predator {
    int x, y; //начальные координаты животного
    int age;
    int death_age;
    int minRep; // Возрасты
    int maxRep;
    int foodp;//количество пищи нужный животным для поддержания жизни
    bool dmark;
};
class Herbivores {
private:
    herbivores herb;
public:
    Herbivores() {
        herb = { 0,0,-1000,0,0,0,1 };
    }
    Herbivores(int X, int Y, int Age, int Death_age, int MinRep, int MaxRep, int Foodh, bool Dmark) {
        herb.x = X;
        herb.y = Y;
        herb.age = Age;
        herb.death_age = Death_age;
        herb.minRep = MinRep;
        herb.maxRep = MaxRep;
        herb.foodh = Foodh;
        herb.dmark = Dmark;
    }
    void EatingP() { //поедание травы для травоядных животных и проверка на смертность
        if (health > 30)
        {
            herb.foodh += 20;
            health -= 20;
        }
    }
    void EatingM() {
        herb.foodh -= 20;
        if (herb.foodh < 0)
        {
            herb.foodh = 0;
            if (herb.dmark == true) TheEnd--;
            herb.dmark = false;
        }
    }
    void PlusAge() { // прибавка к возрасту,выставление dmark при возрасте смерти
        herb.age += 1;
        if (herb.age == herb.death_age) {
            if (herb.dmark == true) TheEnd--;
            herb.dmark = false;
        }
    }
    void movement(int h) {// перемещение
        switch (h) {
            case 0:herb.x += 5; herb.y += 5; break;
            case 1:herb.x -= 5; herb.y += 5; break;
            case 2:herb.x += 5; herb.y -= 5; break;
            case 3:herb.x -= 5; herb.y -= 5; break;
            case 4:herb.x += 5; break;
            case 5:herb.x -= 5; break;
            case 6:herb.y += 5; break;
            case 7:herb.y -= 5; break;
            default: 10; break;
        }
        if (herb.x > 100) {
            herb.x -= 10;
        }
        else if (herb.x < 0)
        {
            herb.x += 10;
        }
        if (herb.y > 100) {
            herb.y -= 10;
        }
        else if (herb.y < 0)
        {
            herb.y += 10;
        }
    }
    void transfer() { // передача координат для функции проверки убийства травоядных и рождения всех животных
        int Xp, Yp;
        Xp = herb.x;
        Yp = herb.y;
    }
    void SetDmarkh() {
        if (herb.dmark == true) TheEnd--;
        herb.dmark = false;
    }
    int GetDmarkh() {
        return herb.dmark;
    }
    int GetX() { // передача координат для функции смертности животных
        return(herb.x);
    }
    int GetY() { // передача координат для функции смертности животных
        return(herb.y);
    }
    int GetFoodh() {
        return herb.foodh;
    }
    int GetAge() {
        return herb.age;
    }
    bool CheckRepAge() {
        bool r = false;
        if ((herb.minRep <= herb.age) && (herb.maxRep >= herb.age)) {
            r = true;
        }
        return r;
    }
    void Outh(int k, int h) { // вывод значений за итерацию травоядного
        cout << "Для " << k << " травоядного:" << endl;
        cout << "Координата X: " << herb.x << " и Y: " << herb.y << endl;
        cout << "Возраст: " << herb.age << endl;
        cout << "Уроень еды: " << herb.foodh << endl;
        cout << "Уровень травы: " << health << endl;
        if (herb.dmark == true)
        {
            cout << "Жив" << endl;
        }
        else {
            cout << "Мёртв" << endl;
            if (Killer != -1) cout << " Убил " << h << " хищник" << endl;
            else if (herb.age==herb.death_age)
            {
                cout << "Умер от старости" << endl;
            }
            else
            {
                cout <<"Умер голодной смертью " << endl;
            }
        }
        cout << "-----------------------------------------------------------------" << endl;
    }

};
class Predator {
private:
    predator pred;
public:
    Predator() {
        pred = { 0,0,-1000,0,0,0,1 };
    }
    Predator(int X, int Y, int Age, int Death_age, int MinRep, int MaxRep, int Foodp, bool Dmark) {
        pred.x = X;
        pred.y = Y;
        pred.age = Age;
        pred.death_age = Death_age;
        pred.minRep = MinRep;
        pred.maxRep = MaxRep;
        pred.foodp = Foodp;
        pred.dmark = Dmark;
    }
    void SetFood() {//уменьшает сытость хищников
        if (pred.foodp >= 1)
        {
            pred.foodp--;
        }
        else
        {
            if (pred.dmark == true) TheEnd--;
            pred.dmark = false;
        }
    }
    void PlusAge() {//возраст и dmark
        pred.age += 1;
        if (pred.age == pred.death_age) { // умрёт от старости
            if (pred.dmark == true) TheEnd--;
            pred.dmark = false;
        }
    }
    void movement(int h) {//перемещение
        switch (h) {
            case 0:pred.x += 5; pred.y += 5; break;
            case 1:pred.x -= 5; pred.y += 5; break;
            case 2:pred.x += 5; pred.y -= 5; break;
            case 3:pred.x -= 5; pred.y -= 5; break;
            case 4:pred.x += 5; break;
            case 5:pred.x -= 5; break;
            case 6:pred.y += 5; break;
            case 7:pred.y -= 5; break;
            default: 10; break;
        }
        if (pred.x > 100) {
            pred.x -= 10;
        }
        else if (pred.x < 0)
        {
            pred.x += 10;
        }
        if (pred.y > 100) {
            pred.y -= 10;
        }
        else if (pred.y < 0)
        {
            pred.y += 10;
        }
    }
    int GetX() { // передача координат для функции смертности животных
        return pred.x;
    }
    int GetY() { // передача координат для функции смертности животных
        return pred.y;
    }
    int GetDmarkp() {
        return pred.dmark;
    }
    int GetFoodp() {
        return pred.foodp;
    }
    void SetFoodp(int k) {
        pred.foodp = k;
    }
    void SetDmarkp() {
        if (pred.dmark == true)
            TheEnd--;
        pred.dmark = false;
        Killer = -1;
    }
    bool CheckRepAge() {
        bool r = false;
        if ((pred.minRep <= pred.age) && (pred.maxRep >= pred.age)) {
            r = true;
        }
        return r;
    }
    int GetAge() {
        return pred.age;
    }
    void Outp(int k) { // вывод значений за итерацию хищника
        cout << "Для " << k << " xищника:" << endl;
        cout << "Координата X: " << pred.x << " и Y: " << pred.y << endl;
        cout << "Возраст: " << pred.age << endl;
        cout << "Уроень еды: " << pred.foodp << endl;
        if (pred.dmark == true)
        {
            cout << "Жив" << endl;
        }
        else {
            cout << "Мёртв" << endl;
            if (pred.age==pred.death_age) cout << "Умер от старости" << endl;
            else cout <<"Умер голодной смертью " << endl;
        }
        cout << "-----------------------------------------------------------------" << endl;

    }
};
bool deathHerb(int Xp, int Yp, int Xh, int Yh, int Foodp, bool Dmark, int K) { //функция,которая проверяет, убьёт ли хищник травоядного
    bool a = false;
    if (abs(Xp - Xh) * (abs(Yp - Yh) <= 6) && Dmark == true)
    {
        a = true;
        Killer = K;
    }
    return a;
}
bool Born(int Xh1, int Yh1, int Xh2, int Yh2, bool Dmark1, bool Dmark2, bool y, bool u) { //функция для рождения новых животных (встретились или нет)
    bool a = false;
    if (abs(Xh1 - Xh2) * abs(Yh1 - Yh2) <= 16 && (Dmark1 == 1 && Dmark2 == 1) && (y == true && u == true))
    {
        a = true;
    }
    return a;
}
int main() {
    setlocale(0, "");
    const int  lenghBase = 5;// количество животных каждого вида
    const int lengh = 60;
    Herbivores herb[lengh];
    Predator pred[lengh];
    Herbivores herbH[lengh];// массив детей травоядных
    Predator predP[lengh];// массив детей хищников
    herb[0] = Herbivores(rand() % 101, rand() % 101, 0, rand() % 7 + 5, 1, 8, 50, 1);
    herb[1] = Herbivores(rand() % 101, rand() % 101, 0, rand() % 7 + 5, 1, 8, 50, 1);
    herb[2] = Herbivores(rand() % 101, rand() % 101, 0, rand() % 7 + 5, 1, 8, 50, 1);
    herb[3] = Herbivores(rand() % 101, 13, 0, rand() % 7 + 5, 1, 8, 50, 1);
    herb[4] = Herbivores(rand() % 101, rand() % 101, 0, rand() % 7 + 5, 1, 8, 50, 1);
    pred[0] = Predator(rand() % 101, rand() % 101, 0, rand() % 7 + 5, 1, 8, 5, 1);
    pred[1] = Predator(rand() % 101, rand() % 101, 0, rand() % 7 + 5, 1, 8, 5, 1);
    pred[2] = Predator(rand() % 101, rand() % 101, 0, rand() % 7 + 5, 1, 8, 5, 1);
    pred[3] = Predator(rand() % 101, rand() % 101, 0, rand() % 7 + 5, 1, 8, 5, 1);
    pred[4] = Predator(rand() % 101, rand() % 101, 0, rand() % 7 + 5, 1, 8, 5, 1);
    int t = 0; // счётчик для добавления детей травоядных
    int u = 0; // счётчик для добавление детей хищников
    int max = 0;
    TheEnd = 10;//количество животных в игре
    bool Chekingh[lengh];//Проверка на вывод уже мертвых существ
    bool Chekingp[lengh];
    for (int i = 0; i < lengh; i++) {
        Chekingh[i] = true;
        Chekingp[i] = true;
    }
    ///////
    while (TheEnd > 0) { //отслеживает конец игры
        //cout << TheEnd << " животных оставшхся в живых" << endl;
        cout << h << " ИТЕРАЦИЯ: " << endl;
        cout << "---------------------------------------------------------------------" << endl;
        cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        cout << "---------------------------------------------------------------------" << endl;
        for (int i = 0; i < lenghBase + max; i++) { //перемещение животных+возраст
            if (pred[i].GetAge() >= 0) pred[i].SetFood();
            herb[i].EatingM();
            if (herb[i].GetDmarkh() == true && herb[i].GetAge() >= 0) herb[i].EatingP();
            herb[i].PlusAge();
            pred[i].PlusAge();
            if (herb[i].GetDmarkh() == true)  herb[i].movement(rand() % 8);
            if (pred[i].GetDmarkp() == true) pred[i].movement(rand() % 8);
            if (herb[i].GetAge() >= 0 && pred[i].GetAge() >= 0) {
                for (int j = 0; j < lenghBase + max; j++) { // проверка на близость хищника и травоядного
                    if (pred[j].GetDmarkp() == true) {
                        if (deathHerb(pred[j].GetX(), pred[j].GetY(), herb[i].GetX(), herb[i].GetY(), pred[j].GetFoodp(), herb[i].GetDmarkh(), j))
                        {
                            pred[j].SetFoodp(pred[j].GetFoodp() + 1);
                            herb[i].SetDmarkh();
                        }
                    }
                    if (Born(herb[i].GetX(), herb[i].GetY(), herb[j].GetX(), herb[j].GetY(), herb[i].GetDmarkh(), herb[j].GetDmarkh(), herb[i].CheckRepAge(), herb[j].CheckRepAge()) && (i != j)) {// Процесс рождения:CheckAge проверяет,может ли давать потомство каждый из травоядных,BornHerb-рядом они или нет

                        herb[lenghBase + t] = Herbivores(herb[i].GetX(), herb[i].GetY(), 0, rand() % 7 + 5, 3, 11, 50, 1);
                        t++;
                        TheEnd++;
                    }
                    if (Born(pred[i].GetX(), pred[i].GetY(), pred[j].GetX(), pred[j].GetY(), pred[i].GetDmarkp(), pred[j].GetDmarkp(), pred[i].CheckRepAge(), pred[j].CheckRepAge()) && (i != j)) // Процесс рождения:CheckAge проверяет,может ли давать потомство каждый из травоядных,BornHerb-рядом они или нет
                    {
                        pred[lenghBase + u] = Predator(pred[i].GetX(), pred[i].GetY(), 0, rand() % 7 + 5, 3, 11, 5, 1);
                        u++;
                        TheEnd++;
                    }
                }
            }
            if (t >= u)
            {
                max = t;
            }
            else {
                max = u;
            }
            if (herb[i].GetAge() >= 0) {
                if (herb[i].GetDmarkh() == true) {
                    herb[i].Outh(i, Killer);
                }
                else {
                    if (Chekingh[i] == true) {
                        herb[i].Outh(i, Killer);
                        Chekingh[i] = false;
                    }

                }
            }
            if (pred[i].GetAge() >= 0) {
                if (pred[i].GetDmarkp() == true)
                    pred[i].Outp(i);
                if (pred[i].GetDmarkp() == false) {
                    if (Chekingp[i] == true) {
                        pred[i].Outp(i);
                        Chekingp[i] = false;
                    }
                }
            }
        }
        health *= recovery;
        cout << endl;
        h++;
        cout << TheEnd << " животных оставшхся в живых" << endl;
        Killer = -1;
    }
    cout << " КОНЕЦ: все животные мертвы" << endl;
    return 0;
}
