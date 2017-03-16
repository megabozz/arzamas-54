/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   http_request.cpp
 * Author: vgaltsev@OFFICE.INTERTORG
 * 
 * Created on 6 февраля 2017 г., 15:39
 */

#include "cgi.h"

CGI::CGI() {
}

CGI::~CGI() {
}

std::string CGI::getENV(std::string env, std::string in) {
    std::string result = "";
    char * e = getenv(env.data());
    if (e) {
        result = e;
    } else {
        result = in;
    }
    return result;
}

long int CGI::getContentLength() {
    return strtol(getENV(CGI::CONTENT_LENGTH, "0").data(), 0, 10);
}

std::string CGI::getPostData() {
    std::string result = "";
    long int cl = getContentLength();
    if (cl > 0) {
        char * pd = new char[cl + 1];
        fgets(pd, cl + 1, stdin);
        result = pd;
        delete []pd;
    }
    return result;
}

void CGI::sendResponse(std::string data) {
    fprintf(stdout, "Content-type: application/json\r\n\r\n");
    fprintf(stdout, "%s\r\n", data.data());
}

