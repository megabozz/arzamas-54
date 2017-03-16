/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SESSION.cpp
 * Author: vgaltsev@OFFICE.INTERTORG
 * 
 * Created on 13 марта 2017 г., 16:27
 */

#include "token.h"

TOKEN::TOKEN(std::string &path) {
    char s[256] = "";
    tokenFilename = path;
    file.open(path.data(), std::fstream::binary | std::fstream::in | std::fstream::out);
    if (!file.is_open()) {
        file.open(path.data(), std::fstream::binary | std::fstream::out);
    }
    if (file.is_open()) {
        file.read(s, 255);
        number = s;
    }
}

TOKEN::~TOKEN() {
    if (file.is_open()) {
        file.close();
    }
}

void TOKEN::clear() {
    if (file.is_open()) {
        file.close();
        sleep(1);
        unlink(tokenFilename.data());
        number = "";
    }
}


void TOKEN::regenerate() {
    uuid_t uid;
    char s[64] = "";
    uuid_generate(uid);
    uuid_unparse(uid, s);
    number = s;
    if (file.is_open()) {
        file.clear();
        file.seekp(0, file.beg);
        file.write(number.data(), number.length());
    }
}

