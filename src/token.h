/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SESSION.h
 * Author: vgaltsev@OFFICE.INTERTORG
 *
 * Created on 13 марта 2017 г., 16:27
 */

#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <uuid/uuid.h>
#include <unistd.h>

class TOKEN {
public:
    TOKEN(std::string &);
    virtual ~TOKEN();
    void regenerate();
    void clear();
    
    std::string number;
    
private:
    std::fstream file;
    std::string tokenFilename;

};

#endif /* SESSION_H */

