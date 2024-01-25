#pragma once

template <class T>
class Actuator
{
private:
    T oldValue;
public:
    bool isChanged=false;
    Actuator(T startValue) {
        oldValue=startValue;
    };
    ~Actuator() {

    };
    void Set(T value) {
        isChanged=(value!=oldValue);
        oldValue=value;
    };
};
