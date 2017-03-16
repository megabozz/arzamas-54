/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   kkm.h
 * Author: vgaltsev@OFFICE.INTERTORG
 *
 * Created on 6 февраля 2017 г., 15:32
 */

#ifndef KKM_H
#define KKM_H

#include <string>
#include <locale>
#include <codecvt>
#include <regex>
#include <iconv.h>
#include <sys/utsname.h>
#include <sys/time.h>
#include <time.h>

#include "include/idtobase.h"
#include "include/dto_errors.h"
#include "include/ifptr.h"
#include "json.h"
#include "token.h"
#include "datastrings.h"


#define CHECKERROR ;if(kkm->checkError() != EC_OK){return kkm->ErrorCode;}
#define CHECKERRORa(descr) ;if(kkm->checkError() != EC_OK){fprintf(stdout,"%s\n",descr);return kkm->ErrorCode;}
#define KKMEXEC(f) (kkm->execFunc(f, in, out) != EC_OK);
#define CHECKKKM kkm->ErrorCode == EC_OK &&

class KKM {
public:
    KKM();
    virtual ~KKM();

    int execFunc(std::string, json, json &);
    int set_settings(std::wstring);
    int enable();

    static std::string utf8s(std::wstring);
    static std::wstring s2ws(const std::string&);
    static std::wstring utf8w(std::string);

    static int getBarcodeType(const std::string&);
    
    int tokenInit(std::string path);
    int checkSessionOpened();
    

    int ErrorCode = EC_OK;
    std::string errorDesc = "";
    TED::Fptr::IFptr *ifptr = nullptr;

    int checkAuthToken(json, json &);

    int cmd_cancelcheck(json, json &);
    int cmd_closecheck(json, json &);
    int cmd_opencheck(json, json &);
    int cmd_registrationfz54(json, json &);
    int cmd_printtext(json, json &);
    
    int get_devicedescription(json, json &);
    int get_build(json , json &);
    int get_verlo(json in, json & out);
    int get_verhi(json in, json & out);
    int get_licenseexpireddate(json in, json & out);
    int get_license(json in, json & out);
    int get_licensevalid(json in, json & out);
    
    int get_checquestate(json in, json & out);
    int get_inn(json in, json & out);
    int get_serialnumber(json in, json & out);
    int get_machinenumber(json in, json & out);
    int get_systeminfo(json in, json & out);
    int get_systemtime(json in, json & out);

    int get_operator(json in, json & out);
    int get_logicalnumber(json in, json & out);
    int get_fiscal(json in, json & out) ;
    
    int get_kkmvalue( json in, json & out);
    int get_licensenumber( json in, json & out);
    int get_printeroverheaterror( json in, json & out);
    int get_printercutmechanismerror( json in, json & out);
    int get_printermechanismerror( json in, json & out);
    int get_printerconnectionfailed( json in, json & out);
    int get_outofpaper( json in, json & out);
    int get_summ( json in, json & out);
    int get_slotnumber( json in, json & out);
    int get_advancedmode( json in, json & out);
    int get_fnstate( json in, json & out);
    int get_fnerror( json in, json & out);
    int get_mode( json in, json & out);
    int get_model( json in, json & out);
    int get_controlpaperpresent( json in, json & out);
    int get_checkpaperpresent( json in, json & out);
    int get_coveropened( json in, json & out);
    int get_draweropened( json in, json & out);
    int get_slippixellinelength( json in, json & out);
    int get_slipcharlinelength( json in, json & out);
    int get_jrnpixellinelength( json in, json & out);
    int get_jrncharlinelength( json in, json & out);
    int get_rcppixellinelength( json in, json & out);
    int get_rcpcharlinelength( json in, json & out);
    int get_pixellinelength( json in, json & out);
    int get_charlinelength( json in, json & out);
    int get_summpointposition( json in, json & out);
    int get_checknumber( json in, json & out);
    int get_docnumber( json in, json & out);
    int get_session( json in, json & out);
    int get_sessionopened( json in, json & out);
    int get_date( json in, json & out);
    int set_date( json in, json & out);
    int get_systemdate( json in, json & out);
    int get_time( json in, json & out);
    int set_time( json in, json & out);
    
    //int set_systemtime( json in, json & out);
    //int set_systemdate( json in, json & out);
    int set_systemdate( json in, json & out);
    int set_systemtime( json in, json & out);
    int set_systemdatetime( json in, json & out);
    
    TOKEN *token = nullptr;
    struct function_t {
        const char *name;
        int(*fu) (KKM*, json, json &);
    };
    int checkError();

private:
    KKM* kkm;

    static function_t functions[];


};

#endif /* KKM_H */

