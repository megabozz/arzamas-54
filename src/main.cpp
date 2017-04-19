/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: VGaltsev@OFFICE.INTERTORG
 *
 * Created on 24 января 2017 г., 11:38
 */

//#include <cstdlib>
//#include <unistd.h>
#include <exception>
#include <string>

#include "json.h"
#include "cgi.h"
#include "kkm.h"
#include "datastrings.h"
//#include "token.h"



int EC;
std::string ED;

int main(int argc, char** argv, char **envp) {
    char** envi;
    json result = {};
    //result = result.unflatten();
    json in;
    json out;
    json pd;
    json env = {};

    for (envi = envp; *envi != 0; envi++) {
        std::string thisEnv = *envi;
        int p = thisEnv.find_first_of("=");
        if (p != thisEnv.npos) {
            std::string key = thisEnv.substr(0, p);
            std::string val = thisEnv.substr(p + 1);
            env[key] = val;
        }
    }

    std::string postdata = CGI::getPostData();

    if(argc == 2){
        postdata = argv[1];
//        postdata = "{\"command\":\"SET_DATE\",\"parameters\":{\"date\":\"2017-04-20\"}}";
        env[CGI::REQUEST_METHOD] = CGI::REQUEST_METHOD_POST;
        
    }
    
    
    if (env[CGI::REQUEST_METHOD] == CGI::REQUEST_METHOD_POST) {
        try {
            pd = json::parse(postdata);
            if (pd.value(CGI::ENVIRONMENT, false) == true) {
                result[CGI::ENVIRONMENT] = env;
            }
            std::string currentDir = get_current_dir_name();

            std::string sessionPath = currentDir + std::string("/config/session.txt");

            auto fn = pd[DS::fld_COMMAND];
            if (!pd[DS::fld_COMMAND].empty()) {
                in = pd[DS::fld_PARAMETERS];
                std::string fname = pd[DS::fld_COMMAND];
                std::string config;
                std::string config_name = currentDir + "/config/config.xml";
                FILE *f = fopen(config_name.data(), "rb");
                if (f) {
                    fwide(f, 0);
                    char b[256] = "";
                    while (fgets(b, 256, f)) {
                        config += b;
                    }
                    fclose(f);
                }

                KKM kkm;
                
//                kkm.tokenInit(sessionPath);

                if (!config.empty()) {
                    kkm.set_settings(KKM::utf8w(config));
                }
//                if (kkm.enable() == 0) {
                    kkm.execFunc(fname, in, out);
//                }
                EC = kkm.ErrorCode;
                ED = kkm.errorDesc;
            } else {
                EC = DS::code_INCORRECT_REQUEST;
                ED = DS::msg_INCORRECT_REQUEST;
            }
        } catch (std::exception &e) {
            EC = DS::code_ERROR;
            ED = e.what();
        }
    } else {
        EC = DS::code_INCORRECT_REQUEST;
        ED = DS::msg_INCORRECT_REQUEST;
    }
    result["errorCode"] = EC;
    result["errorDescription"] = ED;
    result["responseData"] = out;
    
    postdata = result.dump(4);
    CGI::sendResponse(postdata);
    return 0;
}

