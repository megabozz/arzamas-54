/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   kkm.cpp
 * Author: vgaltsev@OFFICE.INTERTORG
 * 
 * Created on 6 февраля 2017 г., 15:32
 */

#include "kkm.h"

//#define CHECKERROR ;if(kkm->checkError() != EC_OK){return kkm->ErrorCode;}
//#define KEXEC kkm->ErrorCode == EC_OK && kkm->ifptr

KKM::KKM() {
    kkm = this;
    ifptr = CreateFptrInterface(DTO_IFPTR_VER1);
    checkError();
}

KKM::~KKM() {
    if (ifptr) {
        ReleaseFptrInterface(&ifptr);
    }
//    if (token) {
//        delete token;
//        token = nullptr;
//    }
}

//int KKM::tokenInit(std::string path) {
//    token = new TOKEN(path);
//    return 0;
//}

//int KKM::checkAuthToken(json in, json& out) {
//    if (in.find(DS::fld_AUTHTOKEN) != in.end()) {
//        if (in[DS::fld_AUTHTOKEN] != kkm->token->number) {
//            kkm->ErrorCode = DS::code_AUTH_TOKEN_INCORRECT;
//            kkm->errorDesc = DS::msg_AUTHTOKEN_INCORRECT;
//        }
//    } else {
//        kkm->ErrorCode = DS::code_AUTH_TOKEN_REQUIRED;
//        kkm->errorDesc = DS::msg_AUTHTOKEN_REQUIRED;
//    }
//    return kkm->ErrorCode;
//}

int KKM::checkError() {
    errorDesc = "OK";
    ErrorCode = EC_OK;

    if (!ifptr) {
        errorDesc = DS::msg_INVALID_INTERFACE;
        ErrorCode = DS::code_INVALID_INTERFACE;
        return ErrorCode;
    }

    ifptr->get_ResultCode(&ErrorCode);
    if (ErrorCode != EC_OK) {
        std::wstring resultDescription, badParamDescription;
        std::vector<wchar_t> v(256);
        int size = ifptr->get_ResultDescription(&v[0], v.size());

        if (size <= 0) {
            errorDesc = DS::msg_INVALID_INTERFACE;
            return ErrorCode;
        }
        if (size > v.size()) {
            v.clear();
            v.resize(size + 1);
            ifptr->get_ResultDescription(&v[0], v.size());
        }
        resultDescription = std::wstring(v.begin(), v.end());

        if (ErrorCode == EC_INVALID_PARAM) {
            std::vector<wchar_t> v(256);
            int size = ifptr->get_BadParamDescription(&v[0], v.size());
            if (size <= 0) {
                errorDesc = "get_BadParamDescription error";
                return ErrorCode;
            }
            if (size > v.size()) {
                v.clear();
                v.resize(size + 1);
                ifptr->get_ResultDescription(&v[0], v.size());
            }
            badParamDescription = std::wstring(v.begin(), v.end());
        }

        if (badParamDescription.empty()) {
            errorDesc = utf8s(resultDescription);
            return ErrorCode;
        } else {
            errorDesc = utf8s(resultDescription + L" " + badParamDescription);
            return ErrorCode;
        }
    }
    return ErrorCode;
}

int KKM::getBarcodeType(const std::string& in) {
    for (size_t i = 0; *&DS::arr_BARCODES[i] != 0; i++) {
        if (std::string(DS::arr_BARCODES[i]) == in) {
            return i;
        }
    }
    return -1;
}

int KKM::checkSessionOpened() {
    int i;
    CHECKKKM kkm->ifptr->GetStatus();
    CHECKKKM kkm->ifptr->get_SessionOpened(&i) CHECKERROR;
    return i;
}


KKM::function_t KKM::functions[] = {
    {
        DS::cmd_STATUS, [](KKM* kkm, json in, json & out_t) -> int {
            json out = {};
            wchar_t w[64];
            int i;
            double d;

            int b_ec = kkm->ErrorCode;
            std::string b_ed = kkm->errorDesc;
            kkm->ErrorCode = EC_OK;

            if (kkm->enable() == 0) {
                CHECKKKM kkm->ifptr->GetStatus();

//                out[DS::fld_AUTHTOKEN] = kkm->token->number;

                CHECKKKM kkm->ifptr->get_INN(w, 63);
                out["INN"] = KKM::utf8s(w);
                CHECKKKM kkm->ifptr->get_SummPointPosition(&i);
                out["SummPointPosition"] = i;
                CHECKKKM kkm->ifptr->get_CheckState(&i);
                out["CheckState"] = i;
                CHECKKKM kkm->ifptr->get_CheckNumber(&i);
                out["CheckNumber"] = i;
                CHECKKKM kkm->ifptr->get_DocNumber(&i);
                out["DocNumber"] = i;
                CHECKKKM kkm->ifptr->get_CharLineLength(&i);
                out["CharLineLength"] = i;
                CHECKKKM kkm->ifptr->get_PixelLineLength(&i);
                out["PixelLineLength"] = i;
                CHECKKKM kkm->ifptr->get_RcpCharLineLength(&i);
                out["RcpCharLineLength"] = i;
                CHECKKKM kkm->ifptr->get_RcpPixelLineLength(&i);
                out["RcpPixelLineLength"] = i;
                CHECKKKM kkm->ifptr->get_JrnCharLineLength(&i);
                out["JrnCharLineLength"] = i;
                CHECKKKM kkm->ifptr->get_JrnPixelLineLength(&i);
                out["JrnPixelLineLength"] = i;
                CHECKKKM kkm->ifptr->get_SlipCharLineLength(&i);
                out["SlipCharLineLength"] = i;
                CHECKKKM kkm->ifptr->get_SlipPixelLineLength(&i);
                out["SlipPixelLineLength"] = i;
                CHECKKKM kkm->ifptr->get_SerialNumber(w, 63);
                out["SerialNumber"] = KKM::utf8s(w);
                kkm->get_date(in, out);
                kkm->get_time(in, out);
                kkm->get_operator(in, out);
                kkm->get_logicalnumber(in, out);
                kkm->get_session(in, out);
                kkm->get_sessionopened(in, out);
                kkm->get_fiscal(in, out);
                kkm->get_draweropened(in, out);
                kkm->get_coveropened(in, out);
                kkm->get_checkpaperpresent(in, out);
                kkm->get_controlpaperpresent(in, out);
                kkm->get_model(in, out);
                kkm->get_mode(in, out);
                kkm->get_advancedmode(in, out);
                kkm->get_slotnumber(in, out);
                kkm->get_summ(in, out);
                kkm->get_outofpaper(in, out);
                kkm->get_printerconnectionfailed(in, out);
                kkm->get_printermechanismerror(in, out);
                kkm->get_printercutmechanismerror(in, out);
                kkm->get_printeroverheaterror(in, out);
                kkm->get_verhi(in, out);
                kkm->get_verlo(in, out);
                kkm->get_build(in, out);
                kkm->get_devicedescription(in, out);
                kkm->get_license(in, out);
                kkm->get_licensenumber(in, out);
                kkm->get_licensevalid(in, out);
                kkm->get_licenseexpireddate(in, out);
                kkm->get_fnstate(in, out);
                kkm->get_fnerror(in, out);
                kkm->get_machinenumber(in, out);
            } else {

            }
            out_t["status"]["kkm"] = out;
            out = {};
            kkm->get_systemdate(in, out);
            kkm->get_systemtime(in, out);
            kkm->get_systeminfo(in, out);
            out_t["status"]["system"] = out;

            kkm->ErrorCode = b_ec;
            kkm->errorDesc = b_ed;

            return kkm->ErrorCode;
        }
    },
    {
        "SETTINGS", [](KKM* kkm, json in, json & out) -> int {
            wchar_t *b;
            b = new wchar_t[4096];
            CHECKKKM kkm->ifptr->get_DeviceSettings(b, 4096);
            out["Settings"] = KKM::utf8s(std::wstring(b));
            delete []b;
            CHECKERROR;
            return kkm->ErrorCode;
        }
    },
    {
        "PRINT_TEXT", [](KKM* kkm, json in, json & out) -> int {

            kkm->enable() CHECKERROR;

            kkm->cmd_printtext(in, out);
            return kkm->ErrorCode;
        }
    },

    {
        "REPORT_X", [](KKM* kkm, json in, json & out) -> int {

            kkm->enable() CHECKERROR;

            CHECKKKM kkm->ifptr->put_Mode(TED::Fptr::ModeReportNoClear); kkm->checkError();
            CHECKKKM kkm->ifptr->SetMode(); kkm->checkError();
            CHECKKKM kkm->ifptr->put_ReportType(TED::Fptr::ReportX); kkm->checkError();
            CHECKKKM kkm->ifptr->Report(); kkm->checkError();

            KKMEXEC(DS::cmd_STATUS);
            
            

            return kkm->ErrorCode;
        }
    },
    {
        "REPORT_Z", [](KKM* kkm, json in, json & out) -> int {

            kkm->enable() CHECKERROR;

            CHECKKKM kkm->ifptr->put_Mode(TED::Fptr::ModeReportClear); kkm->checkError();
            CHECKKKM kkm->ifptr->SetMode(); kkm->checkError();
            CHECKKKM kkm->ifptr->put_ReportType(TED::Fptr::ReportZ); kkm->checkError();
            CHECKKKM kkm->ifptr->Report(); kkm->checkError();

//            kkm->token->clear();
            
            KKMEXEC(DS::cmd_STATUS);
            
            CHECKERROR;

            return kkm->ErrorCode;
        }
    },
    {
        "SELL", [](KKM* kkm, json in, json & out) -> int {
            kkm->enable() CHECKERROR;
            int s_opened = kkm->checkSessionOpened() CHECKERROR;
//            if (s_opened == 1) {
//                if (kkm->checkAuthToken(in, out) < 0) {
//                    return kkm->ErrorCode;
//                }
//            } else {
//                kkm->token->regenerate();
//            }
//            if (kkm->token->number.empty()) {
//                kkm->token->regenerate();
//                out[DS::fld_AUTHTOKEN] = kkm->token->number;
//            }
            json cheque = in["cheque"];
            json positions = cheque["positions"];
            json cp = {};

            int i;
            double d;
            std::string s;
            
            
            for (auto &p : positions) {
                json op = {};
                s = p[DS::fld_NAME];
                op[DS::fld_NAME] = s;
                
                if (p.find(DS::fld_DISCOUNT) != p.end()) {
                    i = p[DS::fld_DISCOUNT][DS::fld_TYPE];
                    op[DS::fld_DISCOUNT][DS::fld_TYPE] = i;
                    d = p[DS::fld_DISCOUNT][DS::fld_SUMM];
                    op[DS::fld_DISCOUNT][DS::fld_SUMM] = d;
                } else {
                    op[DS::fld_DISCOUNT] = {
                        {DS::fld_TYPE, 0},
                        {DS::fld_SUMM, 0}
                    };
                }
                
                i = p[DS::fld_TAX_NUMBER];
                op[DS::fld_TAX_NUMBER] = i;
                d = p[DS::fld_PRICE];
                op[DS::fld_PRICE] = d;
                d = p[DS::fld_QUANTITY];
                op[DS::fld_QUANTITY] = d;
                cp.push_back(op);
            }

            cheque[DS::fld_OPEN_TYPE] = TED::Fptr::ChequeSell;
            i = cheque[DS::fld_PAYMENT_TYPE];
            cheque[DS::fld_PAYMENT_TYPE] = i;

            if (cheque.find(DS::fld_DISCOUNT) != cheque.end()) {
                i = cheque[DS::fld_DISCOUNT][DS::fld_TYPE];
                cheque[DS::fld_DISCOUNT][DS::fld_TYPE] = i;
                d = cheque[DS::fld_DISCOUNT][DS::fld_SUMM];
                cheque[DS::fld_DISCOUNT][DS::fld_SUMM] = d;
            }
            
            bool cancelled = false;

            kkm->cmd_opencheck(cheque, out);
            if (kkm->ErrorCode == EC_OK) {

                if (cheque.find(DS::fld_OPERATOR_POST) != cheque.end() &&
                        cheque.find(DS::fld_OPERATOR_NAME) != cheque.end()) {
                    json text;
                    std::string opPost = cheque[DS::fld_OPERATOR_POST];
                    std::string opName = cheque[DS::fld_OPERATOR_NAME];
                    text[DS::fld_TEXT] = opPost + ": " + opName;
                    CHECKKKM kkm->cmd_printtext(text, out);
                }
                if (cheque.find(DS::fld_OPERATOR_CONTACT) != cheque.end()) {
                    json text;
                    std::string opContact = cheque[DS::fld_OPERATOR_CONTACT];
                    text[DS::fld_TEXT] = "Адрес продавца: " + opContact;
                    CHECKKKM kkm->cmd_printtext(text, out);
                }

                for (auto &p : cp) {
                    CHECKKKM kkm->cmd_registrationfz54(p, out);
                    if(kkm->ErrorCode != EC_OK){
                        cancelled = true;
                        break;
                    }
                }

                if(!cancelled){
                    kkm->cmd_closecheck(cheque, out);
                }
                
                if (kkm->ErrorCode != EC_OK) {
                    int b_ec = kkm->ErrorCode;
                    std::string b_ed = kkm->errorDesc;
                    sleep(1);
                    kkm->ErrorCode = EC_OK;
                    KKMEXEC("ROLL");
                    kkm->cmd_printtext({
                        {DS::fld_TEXT, "Ошибка: " + b_ed}
                    }, out);
                    kkm->cmd_cancelcheck(in, out);
                    kkm->ErrorCode = b_ec;
                    kkm->errorDesc = b_ed;
                }
            }


            KKMEXEC(DS::cmd_STATUS);

            return kkm->ErrorCode;
        }
    },
    {
        "BARCODES", [](KKM* kkm, json in, json & out) -> int {
            for (size_t i = 0; *&DS::arr_BARCODES[i] != 0; i++) {
                out["barcodes"].push_back(DS::arr_BARCODES[i]);
            }
            return EC_OK;
        }
    },
    {
        "PRINT_BARCODE", [](KKM* kkm, json in, json & out) -> int {
            kkm->enable() CHECKERROR;
            int type = TED::Fptr::BarcodeType::BarcodeEAN8;
            std::wstring wbarcode;
            double scale = 100;
            //            try {
            wbarcode = KKM::utf8w(in[DS::fld_TEXT]);
            if (in.find(DS::fld_TYPE) != in.end()) {
                type = KKM::getBarcodeType(in[DS::fld_TYPE]);
            }
            if (in.find(DS::fld_SCALE) != in.end()) {
                scale = in[DS::fld_SCALE];
            };
            CHECKKKM kkm->ifptr->put_Alignment(TED::Fptr::AlignmentCenter);
            CHECKKKM kkm->ifptr->put_BarcodeType(type);
            CHECKKKM kkm->ifptr->put_Barcode(wbarcode.c_str());
            CHECKKKM kkm->ifptr->put_Height(20);
            CHECKKKM kkm->ifptr->put_BarcodeVersion(0);
            CHECKKKM kkm->ifptr->put_BarcodePrintType(TED::Fptr::BarcodeAuto);
            CHECKKKM kkm->ifptr->put_PrintBarcodeText(1);
            CHECKKKM kkm->ifptr->put_BarcodeControlCode(1);
            CHECKKKM kkm->ifptr->put_Scale(scale);
            CHECKKKM kkm->ifptr->put_BarcodeCorrection(0);
            CHECKKKM kkm->ifptr->put_BarcodeColumns(3);
            CHECKKKM kkm->ifptr->put_BarcodeRows(1);
            CHECKKKM kkm->ifptr->put_BarcodeProportions(50);
            CHECKKKM kkm->ifptr->put_BarcodeUseProportions(1);
            CHECKKKM kkm->ifptr->put_BarcodePackingMode(TED::Fptr::BarcodePDF417PackingModeDefault);
            CHECKKKM kkm->ifptr->put_BarcodePixelProportions(300);
            CHECKKKM kkm->ifptr->PrintBarcode();
            CHECKERROR;
            return kkm->ErrorCode;
        }
    },
    {
        "CUT_PARTIAL", [](KKM* kkm, json in, json & out) -> int {
            kkm->enable() CHECKERROR;
            CHECKKKM kkm->ifptr->PartialCut() CHECKERROR;
            return kkm->ErrorCode;
        }
    },
    {
        "CUT_FULL", [](KKM* kkm, json in, json & out) -> int {
            kkm->enable() CHECKERROR;
            CHECKKKM kkm->ifptr->FullCut() CHECKERROR;
            return kkm->ErrorCode;
        }
    },
    {
        "CANCEL_CHECK", [](KKM* kkm, json in, json & out) -> int {
            kkm->enable() CHECKERROR;
            kkm->cmd_cancelcheck(in, out);
            KKMEXEC(DS::cmd_STATUS);
            return kkm->ErrorCode;
        }
    },
    {
        "ROLL", [](KKM* kkm, json in, json & out) -> int {
            kkm->enable() CHECKERROR;
            CHECKKKM kkm->ifptr->put_Caption(L"");
            CHECKKKM kkm->ifptr->put_Alignment(TED::Fptr::Alignment::AlignmentCenter);
            CHECKKKM kkm->ifptr->put_TextWrap(TED::Fptr::TextWrap::TextWrapNone);
            CHECKKKM kkm->ifptr->PrintString();
            CHECKERROR;
            return kkm->ErrorCode;
        }
    },
    {
        DS::cmd_SET_SYSTEMDATE, [](KKM* kkm, json in, json & out) -> int {
            kkm->set_systemdate(in, out);
            return kkm->ErrorCode;
        }
    },
    {
        DS::cmd_SET_SYSTEMTIME, [](KKM* kkm, json in, json & out) -> int {
            kkm->set_systemtime(in, out);
            return kkm->ErrorCode;
        }
    },
    {
        DS::cmd_SET_SYSTEMDATETIME, [](KKM* kkm, json in, json & out) -> int {
            kkm->set_systemdatetime(in, out);
            return kkm->ErrorCode;
        }
    },
    {
        DS::cmd_SET_DATE, [](KKM* kkm, json in, json & out) -> int {
            kkm->enable() CHECKERROR;
            kkm->set_date(in, out);
            KKMEXEC(DS::cmd_STATUS);
            return kkm->ErrorCode;
        }
    },
    {
        DS::cmd_SET_TIME, [](KKM* kkm, json in, json & out) -> int {
            kkm->enable() CHECKERROR;
            kkm->set_time(in, out);
            KKMEXEC(DS::cmd_STATUS);
            return kkm->ErrorCode;
        }
    },
    {
        DS::cmd_COMMANDS, [](KKM* kkm, json in, json & out) -> int {
            KKM::function_t *f = functions;
            while (std::string(f->name) != DS::cmd_COMMANDS) {
                std::string name = f->name;
                out["functions"].push_back(name);
                f++;
            }
            return kkm->ErrorCode;
        }
    },


};

int KKM::execFunc(std::string fname, json in, json& out) {
    uint16_t fsize = sizeof (KKM::functions) / sizeof (KKM::function_t);
    for (uint16_t i = 0; i < fsize; i++) {
        function_t * f = &functions[i];
        if (std::string(f->name) == fname) {
            return f->fu(this, in, out);
        }
    }
    ErrorCode = DS::code_NO_FUNCTION;
    errorDesc = std::string(DS::msg_NO_FUNCTION) + " <" + fname + ">";
    return ErrorCode;
}

int KKM::set_settings(std::wstring config) {
    if (ErrorCode == EC_OK && ifptr->put_DeviceSettings(config.data()) != EC_OK) checkError();
    return ErrorCode;
}

int KKM::enable() {
    if (ErrorCode == EC_OK && ifptr->put_DeviceEnabled(1) != EC_OK) checkError();
    return ErrorCode;
}

std::wstring KKM::s2ws(const std::string& s) {
    return std::wstring(s.begin(), s.end());
}

std::string KKM::utf8s(std::wstring in) {
    return utf_to_utf<char>(in.c_str(), in.c_str() + in.size());
//    std::wstring_convert < std::codecvt_utf8<wchar_t>, wchar_t> conv;
//    return conv.to_bytes(in).data();
}

std::wstring KKM::utf8w(std::string in) {
    return utf_to_utf<wchar_t>(in.c_str(), in.c_str() + in.size());
//    std::wstring_convert < std::codecvt_utf8<wchar_t>, wchar_t> conv;
//    return conv.from_bytes(in).data();
}
