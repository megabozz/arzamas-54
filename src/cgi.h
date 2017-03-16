/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   http_request.h
 * Author: vgaltsev@OFFICE.INTERTORG
 *
 * Created on 6 февраля 2017 г., 15:39
 */

#ifndef CGI_H
#define CGI_H

#include <string>

    

class CGI {
public:
    CGI();
    virtual ~CGI();
    
    static std::string getENV(std::string env, std::string in = "");
    static long int getContentLength();
    static std::string getPostData();
    static void sendResponse(std::string in);
    
    static constexpr const char *ENVIRONMENT = "environment";
    static constexpr const char *CONTENT_LENGTH = "CONTENT_LENGTH";
    static constexpr const char *REQUEST_METHOD = "REQUEST_METHOD";
    static constexpr const char *REQUEST_METHOD_POST = "POST";
    
private:
};

#endif /* CGI_H */

