//
// Created by LENOVO on 7/16/2024.
//

#ifndef DS1_PAIR_H
#define DS1_PAIR_H
template<class T>
class pair {
public:
    int key;
    T value;
    pair(int key, T value);
    pair() = default;

};
template<class T>
pair<T>::pair(int key, T value) {
    this->key=key;
    this->value=value;
}


#endif //DS1_PAIR_H
