#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

template<typename ...Ts> class Observer;

template<typename ...Ts>
class Subject 
{
protected:

    std::vector<Observer<Ts...>*> observers;

public:
    void pushback(Observer<Ts...> *observer)
    {
        observers.emplace_back(observer);
    }

    void remove(Observer<Ts...> *observer)
    {
        observers.erase(std::remove(observers.begin(),observers.end(),observer),observers.end());
    }

    virtual void notify() = 0;
};

template<typename ...Ts>
class Observer
{
public:
    virtual void update(const Ts&...) = 0;
};



class Weather:public Subject<float, float, float>
{
public:
    float temprature_m,humidity_m, pressure_m;
    void notify() override
    {
        for(auto &observer:observers)
            observer->update(temprature_m,humidity_m,pressure_m);
    }

    void setState(float temp, float humid, float pressure)
    {
        temprature_m = temp;
        humidity_m = humid;
        pressure_m = pressure;
        notify();
    }
};

class Client:public Observer<float, float, float>
{
public:
    std::string client_name;
    float temprature_m, humidity_m, pressure_m;
    Client(const std::string &str, float temp , float humid , float pressure):
    client_name(str),temprature_m(temp),humidity_m(humid),pressure_m(pressure){}
    void update(const float &temp,const float &humid, const float &pressure)
    {
        temprature_m = temp;
        humidity_m = humid;
        pressure_m = pressure;
    }
};

int main()
{
    Client client1{"CLIENT01",24.0f,86.0f,200.0f};
    Client client2{"CLIENT02",26.0f,80.0f,100.0f};
    Client client3{"CLIENT01",21.0f,70.0f,160.0f};
    Weather weather{};
    weather.pushback(&client1);
    weather.pushback(&client2);
    weather.pushback(&client3);
    std::cout<<client1.temprature_m<<"\n";   
    std::cout<<weather.temprature_m<<"\n";   
    std::cout<<client1.temprature_m<<"\n";   
    std::cout<<client2.temprature_m<<"\n";   
    std::cout<<client3.temprature_m<<"\n";   
    std::cout<<"After Set State\n";
    weather.setState(35.0f,40.0f,5000.45);
    std::cout<<weather.temprature_m<<"\n";   
    std::cout<<client1.temprature_m<<"\n";   
    std::cout<<client2.temprature_m<<"\n";   
    std::cout<<client3.temprature_m<<"\n";   


    std::cin.get();
    return 0;
}