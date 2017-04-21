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
#include <exception>
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
        resultDescription = std::wstring(v.begin(), v.end()).c_str();

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
            badParamDescription = std::wstring(v.begin(), v.end()).c_str();
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


                kkm->ifptr->GetStatus();

                //                out[DS::fld_AUTHTOKEN] = kkm->token->number;

                kkm->ifptr->get_INN(w, 63);
                out["INN"] = KKM::utf8s(w);
                kkm->ifptr->get_SummPointPosition(&i);
                out["SummPointPosition"] = i;
                kkm->ifptr->get_CheckState(&i);
                out["CheckState"] = i;
                kkm->ifptr->get_CheckNumber(&i);
                out["CheckNumber"] = i;
                kkm->ifptr->get_DocNumber(&i);
                out["DocNumber"] = i;
                kkm->ifptr->get_CharLineLength(&i);
                out["CharLineLength"] = i;
                kkm->ifptr->get_PixelLineLength(&i);
                out["PixelLineLength"] = i;
                kkm->ifptr->get_RcpCharLineLength(&i);
                out["RcpCharLineLength"] = i;
                kkm->ifptr->get_RcpPixelLineLength(&i);
                out["RcpPixelLineLength"] = i;
                kkm->ifptr->get_JrnCharLineLength(&i);
                out["JrnCharLineLength"] = i;
                kkm->ifptr->get_JrnPixelLineLength(&i);
                out["JrnPixelLineLength"] = i;
                kkm->ifptr->get_SlipCharLineLength(&i);
                out["SlipCharLineLength"] = i;
                kkm->ifptr->get_SlipPixelLineLength(&i);
                out["SlipPixelLineLength"] = i;
                kkm->ifptr->get_SerialNumber(w, 63);
                out["SerialNumber"] = KKM::utf8s(w);

                kkm->get_operator(in, out);
                kkm->get_date(in, out);
                kkm->get_time(in, out);
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
        "CASSIERS", [](KKM* kkm, json in, json & out) -> int {
            int i;
            wchar_t w[64];
            std::string key = "cassiers";
            kkm->enable();
            CHECKERROR;
            kkm->ifptr->put_Mode(TED::Fptr::ModeProgramming);
            kkm->ifptr->SetMode();
            CHECKERROR;
            for (int c = 0; c < 30; c++) {
                kkm->ifptr->put_CaptionPurpose(c + DS::cassier_codes::cassier_1);
                kkm->ifptr->get_CaptionIsSupported(&i);
                if (i == 1) {
                    kkm->ifptr->GetCaption();
                    kkm->checkError();
                    if (kkm->ErrorCode == EC_OK) {
                        kkm->ifptr->get_Caption(w, 64);
                        out[key][c]["id"] = c + 1;
                        out[key][c]["name"] = KKM::utf8s(w);
                    }
                }
                kkm->ifptr->put_CaptionPurpose(c + DS::cassier_passwords::cassier_password_1);
                kkm->ifptr->get_CaptionIsSupported(&i);
                if (i == 1) {
                    kkm->ifptr->GetCaption();
                    kkm->checkError();
                    if (kkm->ErrorCode == EC_OK) {
                        kkm->ifptr->get_Caption(w, 64);
                        out[key][c]["password"] = KKM::utf8s(w);
                    }
                }
            }
            return kkm->ErrorCode;
        }
    },
    {
        "SET_CASSIERS", [](KKM* kkm, json in, json & out) -> int {
            int i;
            wchar_t w[64];
            kkm->enable();
            CHECKERROR;
            kkm->ifptr->put_Mode(TED::Fptr::ModeProgramming);
            kkm->ifptr->SetMode();
            CHECKERROR;

            json cassiers = in["cassiers"];

            int x = 0;
            for (auto it = cassiers.begin(); it != cassiers.end(); it++) {
                json cassier = it.value();
                int id = cassier["id"];
                std::string name = cassier["name"];
                std::string password = cassier["password"];

                int e = 0;

                if (id >= 1 && id < 30) {
                    kkm->ifptr->put_CaptionPurpose(DS::cassier_codes::cassier_1 + id - 1);
                    kkm->ifptr->get_CaptionIsSupported(&i);
                    if (i == 1) {
                        kkm->ifptr->put_Caption(KKM::utf8w(name).c_str());
                        kkm->ifptr->SetCaption();
                        e |= kkm->checkError();
                    }
                    if (e == EC_OK) {
                        kkm->ifptr->put_CaptionPurpose(DS::cassier_passwords::cassier_password_1 + id - 1);
                        kkm->ifptr->get_CaptionIsSupported(&i);
                        if (i == 1) {
                            kkm->ifptr->put_Caption(KKM::utf8w(password).c_str());
                            kkm->ifptr->SetCaption();
                            e |= kkm->checkError();
                        }
                    }
                    if (e == EC_OK) {
                        out["set"]["cassiers"].push_back(cassier);
                    } else {
                        cassier["errorCode"] = kkm->ErrorCode;
                        cassier["errorDescription"] = kkm->errorDesc;
                        out["not_set"]["cassiers"][x++] = cassier;
                    }
                } else {
                    cassier["errorDescription"] = "incorrect id";
                    out["not_set"]["cassiers"].push_back(cassier);
                }
            }
            return kkm->ErrorCode;
        }
    },
    {
        "SETTINGS", [](KKM* kkm, json in, json & out) -> int {
            wchar_t *b;
            b = new wchar_t[4096];
            kkm->ifptr->get_DeviceSettings(b, 4096);
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

            if (in.find(DS::fld_OPERATOR_ID) != in.end() && in.find(DS::fld_OPERATOR_PASSWORD) != in.end()) {
                kkm->ifptr->put_UserPassword(KKM::s2ws(in[DS::fld_OPERATOR_PASSWORD]).c_str());
                kkm->ifptr->put_Operator(in[DS::fld_OPERATOR_ID]);
            }

            kkm->ifptr->put_Mode(TED::Fptr::ModeReportNoClear);
            kkm->ifptr->SetMode();
            kkm->checkError();
            if (kkm->ErrorCode == EC_OK) {
                kkm->ifptr->put_ReportType(TED::Fptr::ReportX);
                kkm->ifptr->Report();
                kkm->checkError();
            }
            KKMEXEC(DS::cmd_STATUS);
            return kkm->ErrorCode;
        }
    },
    {
        "REPORT_Z", [](KKM* kkm, json in, json & out) -> int {

            kkm->enable() CHECKERROR;
            if (in.find(DS::fld_OPERATOR_ID) != in.end() && in.find(DS::fld_OPERATOR_PASSWORD) != in.end()) {
                kkm->ifptr->put_UserPassword(KKM::s2ws(in[DS::fld_OPERATOR_PASSWORD]).c_str());
                kkm->ifptr->put_Operator(in[DS::fld_OPERATOR_ID]);
            }
            kkm->ifptr->put_Mode(TED::Fptr::ModeReportClear);
            kkm->ifptr->SetMode();
            kkm->checkError();
            if (kkm->ErrorCode == EC_OK) {
                kkm->ifptr->put_ReportType(TED::Fptr::ReportZ);
                kkm->ifptr->Report();
                kkm->checkError();
            }
            KKMEXEC(DS::cmd_STATUS);
            return kkm->ErrorCode;
        }
    },

    {
        "SELL", [](KKM* kkm, json in, json & out) -> int {
            in["cheque"][DS::fld_OPEN_TYPE] = TED::Fptr::ChequeSell;
            kkm->cheque(in, out);
            KKMEXEC(DS::cmd_STATUS);
            return kkm->ErrorCode;
        }
    },
    {
        "SELL_RETURN", [](KKM* kkm, json in, json & out) -> int {

            in["cheque"][DS::fld_OPEN_TYPE] = TED::Fptr::ChequeSellReturn;
            kkm->cheque(in, out);
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
        DS::cmd_SET_KKMDATE, [](KKM* kkm, json in, json & out) -> int {
            kkm->enable() CHECKERROR;
            kkm->set_date(in, out);
            KKMEXEC(DS::cmd_STATUS);
            return kkm->ErrorCode;
        }
    },
    {
        DS::cmd_SET_KKMTIME, [](KKM* kkm, json in, json & out) -> int {
            kkm->enable() CHECKERROR;
            kkm->set_time(in, out);
            KKMEXEC(DS::cmd_STATUS);
            return kkm->ErrorCode;
        }
    },
    {
        DS::cmd_SET_KKMSYSTEMTIME, [](KKM* kkm, json in, json & out) -> int {
            json t;
            kkm->get_systemdate({}, t);
            kkm->get_systemtime({}, t);
            t["date"] = t["Date"];
            t["time"] = t["Time"];
            kkm->enable() CHECKERROR;
            kkm->set_date(t, out);
            kkm->set_time(t, out);
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
    kkm->ifptr->put_DeviceEnabled(1);
    CHECKERROR;
    kkm->enabled = true;
    return kkm->ErrorCode;
}

int KKM::disable() {
    if (kkm->enabled) {
        kkm->ifptr->ResetMode();
        kkm->ifptr->put_DeviceEnabled(0);
        kkm->enabled = false;
    }
    return kkm->ErrorCode;
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
