#include "kkm.h"

int KKM::cmd_cancelcheck(json in, json & out) {
    kkm->ifptr->CancelCheck();
    CHECKERROR;
    return kkm->ErrorCode;
}

int KKM::cmd_closecheck(json in, json & out) {
    int typeClose = in[DS::fld_PAYMENT_TYPE];

    if (in.find(DS::fld_DISCOUNT) != in.end()) {
        int discountType = in[DS::fld_DISCOUNT][DS::fld_TYPE];
        double discountSumm = in[DS::fld_DISCOUNT][DS::fld_SUMM];
        kkm->ifptr->put_Summ(discountSumm);
        kkm->ifptr->put_DiscountType(discountType);
        kkm->ifptr->put_Destination(TED::Fptr::DestinationType::OnCheck);
        kkm->ifptr->Discount();
        CHECKERROR;
    }
    kkm->ifptr->put_TypeClose(typeClose);
    kkm->ifptr->CloseCheck();
    CHECKERROR;
    return kkm->ErrorCode;
}

int KKM::cmd_opencheck(json in, json & out) {
    int openType;
    std::wstring buyerContact;
    buyerContact.clear();
    if (in.find(DS::fld_BUYER_CONTACT) != in.end()) {
        buyerContact = KKM::utf8w(in[DS::fld_BUYER_CONTACT]);
    }

    openType = in[DS::fld_OPEN_TYPE];

    kkm->ifptr->put_Mode(TED::Fptr::ModeRegistration);
    kkm->ifptr->SetMode();
    CHECKERROR;


    kkm->ifptr->put_CheckType(openType);
    kkm->ifptr->put_PrintCheck(buyerContact.empty() ? 0 : 1);
    kkm->ifptr->OpenCheck();
    CHECKERROR;

    if (!buyerContact.empty()) {
        kkm->ifptr->put_FiscalPropertyNumber(1008);
        kkm->ifptr->put_FiscalPropertyType(TED::Fptr::FiscalPropertyTypeASCII);
        kkm->ifptr->put_FiscalPropertyValue(buyerContact.c_str());
        kkm->ifptr->WriteFiscalProperty();
        CHECKERROR;
    }
    return kkm->ErrorCode;
}

int KKM::cmd_registrationfz54(json in, json & out) {
    double discountSumm;
    int discountType;
    int taxNumber;
    double quantity;
    double price;
    std::wstring wname;
    std::wstring wclassifier;
    try {
        discountSumm = in[DS::fld_DISCOUNT][DS::fld_SUMM];
        discountType = in[DS::fld_DISCOUNT][DS::fld_TYPE];
        taxNumber = in[DS::fld_TAX_NUMBER];
        quantity = in[DS::fld_QUANTITY];
        price = in[DS::fld_PRICE];
        wname = KKM::utf8w(in[DS::fld_NAME]);
        if (in.find(DS::fld_CLASS) != in.end()) {
            wclassifier = KKM::utf8w(in[DS::fld_CLASS]);
        }

    } catch (std::exception &e) {
        kkm->errorDesc = e.what();
        kkm->ErrorCode = DS::code_ERROR;
        return kkm->ErrorCode;
    }
    kkm->ifptr->put_DiscountType(discountType);
    kkm->ifptr->put_Summ(discountSumm);
    kkm->ifptr->put_TaxNumber(taxNumber);
    kkm->ifptr->put_Quantity(quantity);
    kkm->ifptr->put_Price(price);
    kkm->ifptr->put_TextWrap(TED::Fptr::TextWrapWord);
    kkm->ifptr->put_Name(wname.c_str());
    
    if (!wclassifier.empty()) {
        kkm->ifptr->put_Classifier(wclassifier.data());
    }
    kkm->ifptr->Registration();
    CHECKERROR;
    return kkm->ErrorCode;
}

int KKM::cmd_registrationfz54return(json in, json & out) {
    double discountSumm;
    int discountType;
    int taxNumber;
    double quantity;
    double price;
    std::wstring wname;
    std::wstring wclassifier;
    try {
        discountSumm = in[DS::fld_DISCOUNT][DS::fld_SUMM];
        discountType = in[DS::fld_DISCOUNT][DS::fld_TYPE];
        taxNumber = in[DS::fld_TAX_NUMBER];
        quantity = in[DS::fld_QUANTITY];
        price = in[DS::fld_PRICE];
        wname = KKM::utf8w(in[DS::fld_NAME]);
        if (in.find(DS::fld_CLASS) != in.end()) {
            wclassifier = KKM::utf8w(in[DS::fld_CLASS]);
        }

    } catch (std::exception &e) {
        kkm->errorDesc = e.what();
        kkm->ErrorCode = DS::code_ERROR;
        return kkm->ErrorCode;
    }
    kkm->ifptr->put_DiscountType(discountType);
    kkm->ifptr->put_Summ(discountSumm);
    kkm->ifptr->put_TaxNumber(taxNumber);
    kkm->ifptr->put_Quantity(quantity);
    kkm->ifptr->put_Price(price);
    kkm->ifptr->put_TextWrap(TED::Fptr::TextWrapWord);
    kkm->ifptr->put_Name(wname.c_str());
    if (!wclassifier.empty()) {
        kkm->ifptr->put_Classifier(wclassifier.data());
    }
    kkm->ifptr->put_EnableCheckSumm(0);
    kkm->ifptr->Return();
    CHECKERROR;
    return kkm->ErrorCode;
}

int KKM::cmd_printtext(json in, json & out) {
    std::wstring text = KKM::utf8w(in[DS::fld_TEXT]);
    int wrap = TED::Fptr::TextWrap::TextWrapLine;
    int alignment = TED::Fptr::Alignment::AlignmentLeft;
    if (in.find(DS::fld_WRAP) != in.end()) {
        wrap = in[DS::fld_WRAP];
    }
    if (in.find(DS::fld_ALIGN) != in.end()) {
        alignment = in[DS::fld_ALIGN];
    }
    kkm->ifptr->put_Caption(text.c_str());
    kkm->ifptr->put_TextWrap(wrap);
    kkm->ifptr->put_Alignment(alignment);
    kkm->ifptr->PrintString();
    CHECKERROR;
    return kkm->ErrorCode;
}

int KKM::get_devicedescription(json in, json & out) {
    wchar_t v[64] = L"";
    kkm->ifptr->get_DeviceDescription(v, 63);

    out["DeviceDescription"] = KKM::utf8s(v);
    return EC_OK;
}

int KKM::get_build(json in, json & out) {
    wchar_t v[64] = L"";
    kkm->ifptr->get_Build(v, 63);

    out["Build"] = KKM::utf8s(v);
    return EC_OK;
}

int KKM::get_verlo(json in, json & out) {
    wchar_t v[64] = L"";
    kkm->ifptr->get_VerLo(v, 63);

    out["VerLo"] = KKM::utf8s(v);
    return EC_OK;
}

int KKM::get_verhi(json in, json & out) {
    wchar_t v[64] = L"";
    kkm->ifptr->get_VerHi(v, 63);

    out["VerHi"] = KKM::utf8s(v);
    return EC_OK;
}

int KKM::get_licenseexpireddate(json in, json & out) {
    wchar_t v[64] = L"";
    kkm->ifptr->get_LicenseExpiredDate(v, 63);

    out["LicenseExpiredDate"] = KKM::utf8s(v);
    return EC_OK;
}

int KKM::get_license(json in, json & out) {
    wchar_t v[64] = L"";
    kkm->ifptr->get_License(v, 63);

    out["License"] = KKM::utf8s(v);
    return EC_OK;
}

int KKM::get_licensevalid(json in, json & out) {
    int v;
    kkm->ifptr->get_LicenseValid(&v);

    out["LicenseValid"] = v;
    return EC_OK;
}

int KKM::get_machinenumber(json in, json & out) {
    wchar_t b[64] = L"";
    kkm->ifptr->get_MachineNumber(b, 63);
    out["MachineNumber"] = KKM::utf8s(b);
    return kkm->ErrorCode;
}

int KKM::get_systeminfo(json in, json & out) {
    std::string key = "uname";
    utsname un;
    if (uname(&un) == 0) {
        out[key]["machine"] = un.machine;
        out[key]["nodename"] = un.nodename;
        out[key]["domainname"] = un.domainname;
        out[key]["release"] = un.release;
        out[key]["sysname"] = un.sysname;
        out[key]["version"] = un.version;
    }
    return EC_OK;
}

int KKM::get_systemtime(json in, json & out) {
    char b[16];
    int h, m, s;
    time_t t = time(0);
    struct tm * now = localtime(& t);
    h = now->tm_hour;
    m = now->tm_min;
    s = now->tm_sec;
    snprintf(b, 15, "%02d:%02d:%02d", h, m, s);
    out["Time"] = b;
    return EC_OK;
}

int KKM::get_operator(json in, json & out) {
    int v;
    kkm->ifptr->get_Operator(&v);
    out["Operator"] = v;
    return EC_OK;
}

int KKM::get_logicalnumber(json in, json & out) {
    int v = 0;
    kkm->ifptr->get_LogicalNumber(&v);
    out["LogicalNumber"] = v;
    return EC_OK;
}

int KKM::get_fiscal(json in, json & out) {
    int v = 0;
    kkm->ifptr->get_Fiscal(&v);

    out["Fiscal"] = bool(v);
    return EC_OK;
}

int KKM::get_kkmvalue(json in, json & out) {
    double v;
    const wchar_t *p = L"30";
    wchar_t s[64];
    int val = 0;
    val = in[DS::fld_VALUE];

    out["KKMValue"] = {};

    CHECKKKM kkm->ifptr->put_Mode(TED::Fptr::Mode::ModeProgramming);
    checkError();
    CHECKKKM kkm->ifptr->put_UserPassword(p);
    checkError();
    CHECKKKM kkm->ifptr->SetMode();
    checkError();

    //TED::Fptr::ModeProgramming;

    CHECKKKM kkm->ifptr->put_ValuePurpose(val);
    checkError();

    CHECKKKM kkm->ifptr->get_ValueIsSupported(&val);
    checkError();
    if (val == 1) {
        CHECKKKM kkm->ifptr->GetValue();
        checkError();
        CHECKKKM kkm->ifptr->get_ValueName(s, 64);
        checkError();
        CHECKKKM kkm->ifptr->get_Value(&v);
        checkError();
        CHECKERROR;
        out["KKMValue"]["id"] = in[DS::fld_VALUE];
        out["KKMValue"]["name"] = KKM::utf8s(s);
        out["KKMValue"]["value"] = v;
    }
    return EC_OK;
}

int KKM::get_licensenumber(json in, json & out) {
    int v;
    kkm->ifptr->get_LicenseNumber(&v);

    out["LicenseNumber"] = v;
    return EC_OK;
}

int KKM::get_printeroverheaterror(json in, json & out) {
    int v;
    kkm->ifptr->get_PrinterOverheatError(&v);

    out["PrinterOverheatError"] = (bool)v;
    return EC_OK;
}

int KKM::get_printercutmechanismerror(json in, json & out) {
    int v;
    kkm->ifptr->get_PrinterCutMechanismError(&v);

    out["PrinterCutMechanismError"] = (bool)v;
    return EC_OK;
}

int KKM::get_printermechanismerror(json in, json & out) {
    int v;
    kkm->ifptr->get_PrinterMechanismError(&v);

    out["PrinterMechanismError"] = (bool)v;
    return EC_OK;
}

int KKM::get_printerconnectionfailed(json in, json & out) {
    int v;
    kkm->ifptr->get_PrinterConnectionFailed(&v);

    out["PrinterConnectionFailed"] = (bool)v;
    return EC_OK;
}

int KKM::get_outofpaper(json in, json & out) {
    int v;
    kkm->ifptr->get_OutOfPaper(&v);

    out["OutOfPaper"] = (bool)v;
    return EC_OK;
}

int KKM::get_summ(json in, json & out) {
    double v;
    kkm->ifptr->get_Summ(&v);

    out["Summ"] = v;
    return EC_OK;
}

int KKM::get_slotnumber(json in, json & out) {
    int v;
    kkm->ifptr->get_SlotNumber(&v);

    out["SlotNumber"] = v;
    return EC_OK;
}

int KKM::get_advancedmode(json in, json & out) {
    int v;
    kkm->ifptr->get_AdvancedMode(&v);
    out["AdvancedMode"] = v;
    return kkm->ErrorCode;
}

int KKM::get_fnstate(json in, json & out) {
    int v;
    kkm->ifptr->get_FNState(&v);
    out["FNstate"] = v;
    return kkm->ErrorCode;
}

int KKM::get_fnerror(json in, json & out) {
    int v;
    kkm->ifptr->get_FNError(&v);
    out["FNerror"] = v;
    return kkm->ErrorCode;
}

int KKM::get_mode(json in, json & out) {
    int v;
    kkm->ifptr->get_Mode(&v);

    out["Mode"] = v;
    return kkm->ErrorCode;
}

int KKM::get_model(json in, json & out) {
    int v;
    kkm->ifptr->get_Model(&v);

    out["Model"] = v;
    return kkm->ErrorCode;
}

int KKM::get_controlpaperpresent(json in, json & out) {
    int v;
    kkm->ifptr->get_ControlPaperPresent(&v);

    out["ControlPaperPresent"] = (bool)v;
    return kkm->ErrorCode;
}

int KKM::get_checkpaperpresent(json in, json & out) {
    int v;
    kkm->ifptr->get_CheckPaperPresent(&v);
    out["CheckPaperPresent"] = (bool)v;
    return kkm->ErrorCode;
}

int KKM::get_coveropened(json in, json & out) {
    int v;
    kkm->ifptr->get_CoverOpened(&v);
    out["CoverOpened"] = (bool)v;
    return kkm->ErrorCode;
}

int KKM::get_draweropened(json in, json & out) {
    int v;
    kkm->ifptr->get_DrawerOpened(&v);
    out["DrawerOpened"] = (bool)v;
    return kkm->ErrorCode;
}

int KKM::get_session(json in, json & out) {
    int v;
    kkm->ifptr->get_Session(&v);
    out["Session"] = v;
    return kkm->ErrorCode;
}

int KKM::get_sessionopened(json in, json & out) {
    int v;
    kkm->ifptr->get_SessionOpened(&v);
    out["SessionOpened"] = (bool)v;
    return kkm->ErrorCode;
}

int KKM::get_date(json in, json & out) {
    char b[16];
    int d, m, y;
    kkm->ifptr->get_Date(&d, &m, &y);
    snprintf(b, 15, "%04d-%02d-%02d", y, m, d);
    out["Date"] = b;
    return kkm->ErrorCode;
}

int KKM::set_date(json in, json & out) {
    int y, m, d;
    std::regex regex("^(\\d\\d\\d\\d)-(\\d\\d)-(\\d\\d)$");
    std::smatch match;
    std::string str = in["date"];
    std::regex_match(str, match, regex);
    std::string::size_type sz;
    if (match.size() == 4) {
        y = std::stoi(match[1].str(), &sz);
        m = std::stoi(match[2].str(), &sz);
        d = std::stoi(match[3].str(), &sz);

        for (int i = 0; i < 2; i++) {
            kkm->ifptr->put_Date(d, m, y);
            kkm->ifptr->SetDate();
            checkError();
            if (kkm->ErrorCode != EC_3893) {
                break;
            }
            kkm->ifptr->ResetMode();
        }

    } else {
        kkm->errorDesc = DS::msg_INCORRECT_FORMAT;
        kkm->ErrorCode = DS::code_INCORRECT_FORMAT;
    }
    return kkm->ErrorCode;
}

int KKM::get_systemdate(json in, json & out) {
    char b[16];
    int y, m, d;
    time_t t = time(0);
    struct tm * now = localtime(& t);
    y = (now->tm_year + 1900);
    m = (now->tm_mon + 1);
    d = now->tm_mday;
    snprintf(b, 15, "%04d-%02d-%02d", y, m, d);
    out["Date"] = b;
    return EC_OK;
}

int KKM::get_time(json in, json & out) {
    char b[16];
    int h, m, s;
    kkm->ifptr->get_Time(&h, &m, &s);
    snprintf(b, 15, "%02d:%02d:%02d", h, m, s);
    out["Time"] = b;
    return kkm->ErrorCode;
}

int KKM::set_time(json in, json & out) {
    int h, m, s;
    std::regex regex("^(\\d\\d):(\\d\\d):(\\d\\d)$");
    std::smatch match;
    std::string str = in["time"];
    std::regex_match(str, match, regex);
    std::string::size_type sz;
    if (match.size() == 4) {
        h = std::stoi(match[1].str(), &sz);
        m = std::stoi(match[2].str(), &sz);
        s = std::stoi(match[3].str(), &sz);
        CHECKKKM kkm->ifptr->put_Time(h, m, s);
        checkError();
        CHECKKKM kkm->ifptr->SetTime() CHECKERROR;
    } else {
        kkm->errorDesc = DS::msg_INCORRECT_FORMAT;
        kkm->ErrorCode = DS::code_INCORRECT_FORMAT;
    }
    return kkm->ErrorCode;
}

int KKM::set_systemdate(json in, json& out) {
    int Y, M, D, h, m, s;
    std::regex regex("^(\\d\\d\\d\\d)-(\\d\\d)-(\\d\\d)$");
    std::smatch match;
    std::string str = in[DS::fld_DATE];
    std::regex_match(str, match, regex);
    std::string::size_type sz;
    if (match.size() == 4) {
        std::string cmd = "sudo date --set=\"" + str + " $(date +%H:%M:%S)\"";
        FILE *f = popen(cmd.data(), "r");
        if (f) {
            char buffer[1024];
            fgets(buffer, sizeof (buffer), f);
            pclose(f);
        }
    } else {
        kkm->errorDesc = DS::msg_INCORRECT_FORMAT;
        kkm->ErrorCode = DS::code_INCORRECT_FORMAT;
        return kkm->ErrorCode;
    }
    KKMEXEC(DS::cmd_STATUS);
    return kkm->ErrorCode;
}

int KKM::set_systemtime(json in, json& out) {
    int Y, M, D, h, m, s;
    std::regex regex("^(\\d\\d):(\\d\\d):(\\d\\d)$");
    std::smatch match;
    std::string str = in[DS::fld_TIME];
    std::regex_match(str, match, regex);
    std::string::size_type sz;
    if (match.size() == 4) {
        std::string cmd = "sudo date --set=\"" + str + "\"";
        FILE *f = popen(cmd.data(), "r");
        if (f) {
            char buffer[1024];
            fgets(buffer, sizeof (buffer), f);
            pclose(f);
        }
    } else {
        kkm->errorDesc = DS::msg_INCORRECT_FORMAT;
        kkm->ErrorCode = DS::code_INCORRECT_FORMAT;
        return kkm->ErrorCode;
    }
    KKMEXEC(DS::cmd_STATUS);
    return kkm->ErrorCode;
}

int KKM::set_systemdatetime(json in, json& out) {
    int Y, M, D, h, m, s;
    std::regex regex("^(\\d\\d\\d\\d)-(\\d\\d)-(\\d\\d) (\\d\\d):(\\d\\d):(\\d\\d)$");
    std::smatch match;
    std::string str = in[DS::fld_DATETIME];
    std::regex_match(str, match, regex);
    std::string::size_type sz;
    if (match.size() == 7) {
        std::string cmd = "sudo date --set=\"" + str + "\"";
        FILE *f = popen(cmd.data(), "r");
        if (f) {
            char buffer[1024];
            fgets(buffer, sizeof (buffer), f);
            pclose(f);
        }
    } else {
        kkm->errorDesc = DS::msg_INCORRECT_FORMAT;
        kkm->ErrorCode = DS::code_INCORRECT_FORMAT;
        return kkm->ErrorCode;
    }
    KKMEXEC(DS::cmd_STATUS);
    return kkm->ErrorCode;
}

int KKM::get_cassierInfo(json in, json& out) {
    int i;
    wchar_t w[64];
    int c = in["id"].get<int>();
    kkm->ifptr->put_CaptionPurpose(c + DS::cassier_codes::cassier_1 - 1);
    kkm->ifptr->get_CaptionIsSupported(&i);
    if (i == 1) {
        kkm->ifptr->GetCaption();
        kkm->checkError();
        if (kkm->ErrorCode == EC_OK) {
            kkm->ifptr->get_Caption(w, 64);
            out["id"] = c;
            out["name"] = KKM::utf8s(w);
        }
    }
    kkm->ifptr->put_CaptionPurpose(c + DS::cassier_passwords::cassier_password_1 - 1);
    kkm->ifptr->get_CaptionIsSupported(&i);
    if (i == 1) {
        kkm->ifptr->GetCaption();
        kkm->checkError();
        if (kkm->ErrorCode == EC_OK) {
            kkm->ifptr->get_Caption(w, 64);
            out["password"] = KKM::utf8s(w);
        }
    }
    return kkm->ErrorCode;
}

int KKM::cheque(json in, json& out) {
    kkm->enable();
    CHECKERROR;
    kkm->ifptr->ResetMode();
    CHECKERROR;
    //    int s_opened = kkm->checkSessionOpened() CHECKERROR;
    json cheque = in["cheque"];
    json positions = cheque["positions"];
    json cp = {};

    int i;
    double d;
    std::string s;

    if (cheque.find(DS::fld_OPERATOR_ID) != cheque.end() && cheque.find(DS::fld_OPERATOR_PASSWORD) != cheque.end()) {
        kkm->ifptr->put_UserPassword(KKM::s2ws(cheque[DS::fld_OPERATOR_PASSWORD]).c_str());
        kkm->ifptr->put_Operator(cheque[DS::fld_OPERATOR_ID]);
    }

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

    //            cheque[DS::fld_OPEN_TYPE] = TED::Fptr::ChequeSell;
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

        //        if (cheque.find(DS::fld_OPERATOR_POST) != cheque.end() &&
        //                cheque.find(DS::fld_OPERATOR_NAME) != cheque.end()) {
        //            json text;
        //            std::string opPost = cheque[DS::fld_OPERATOR_POST];
        //
        //            text[DS::fld_TEXT] = opPost + ": " + opName;
        //            CHECKKKM kkm->cmd_printtext(text, out);
        //
        //        }
        if (cheque.find(DS::fld_OPERATOR_CONTACT) != cheque.end()) {
            json text;
            std::string opContact = cheque[DS::fld_OPERATOR_CONTACT];
            text[DS::fld_TEXT] = "Адрес продавца: " + opContact;
//            CHECKKKM kkm->cmd_printtext(text, out);
        }

        for (auto &p : cp) {
            switch (cheque[DS::fld_OPEN_TYPE].get<int>()) {
                case TED::Fptr::ChequeSell:
                    CHECKKKM kkm->cmd_registrationfz54(p, out);
                    break;
                case TED::Fptr::ChequeSellReturn:
                    CHECKKKM kkm->cmd_registrationfz54return(p, out);
                    break;
                default:
                    break;
            }

            if (kkm->ErrorCode != EC_OK) {
                cancelled = true;
                break;
            }
        }

        if (!cancelled) {
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

}
