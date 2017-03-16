#include "kkm.h"

int KKM::cmd_cancelcheck(json in, json & out) {
    CHECKKKM kkm->ifptr->CancelCheck();
    CHECKERROR;
    return kkm->ErrorCode;
}

int KKM::cmd_closecheck(json in, json & out) {
    int typeClose = in[DS::fld_PAYMENT_TYPE];

    if (in.find(DS::fld_DISCOUNT) != in.end()) {
        int discountType = in[DS::fld_DISCOUNT][DS::fld_TYPE];
        double discountSumm = in[DS::fld_DISCOUNT][DS::fld_SUMM];
        CHECKKKM kkm->ifptr->put_Summ(discountSumm);
        checkError();
        CHECKKKM kkm->ifptr->put_DiscountType(discountType);
        checkError();
        CHECKKKM kkm->ifptr->put_Destination(TED::Fptr::DestinationType::OnCheck);
        checkError();
        CHECKKKM kkm->ifptr->Discount();
        checkError();
    }
    CHECKKKM kkm->ifptr->put_TypeClose(typeClose);
    checkError();
    CHECKKKM kkm->ifptr->CloseCheck();
    checkError();
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
    CHECKKKM kkm->ifptr->put_Mode(TED::Fptr::ModeRegistration);
    checkError();
    CHECKKKM kkm->ifptr->SetMode();
    checkError();
    CHECKKKM kkm->ifptr->put_CheckType(openType);
    checkError();
    CHECKKKM kkm->ifptr->put_PrintCheck(buyerContact.empty() ? 0 : 1);
    checkError();
    CHECKKKM kkm->ifptr->OpenCheck();
    checkError();
    if (!buyerContact.empty()) {
        CHECKKKM kkm->ifptr->put_FiscalPropertyNumber(1008);
        checkError();
        CHECKKKM kkm->ifptr->put_FiscalPropertyType(TED::Fptr::FiscalPropertyTypeASCII);
        checkError();
        CHECKKKM kkm->ifptr->put_FiscalPropertyValue(buyerContact.c_str());
        checkError();
        CHECKKKM kkm->ifptr->WriteFiscalProperty();
        checkError();
    }
    CHECKERROR;
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
    CHECKKKM kkm->ifptr->put_DiscountType(discountType);
    checkError();
    CHECKKKM kkm->ifptr->put_Summ(discountSumm);
    checkError();
    CHECKKKM kkm->ifptr->put_TaxNumber(taxNumber);
    checkError();
    CHECKKKM kkm->ifptr->put_Quantity(quantity);
    checkError();
    CHECKKKM kkm->ifptr->put_Price(price);
    checkError();
    CHECKKKM kkm->ifptr->put_TextWrap(TED::Fptr::TextWrapWord);
    checkError();
    CHECKKKM kkm->ifptr->put_Name(wname.c_str());
    checkError();
    if (!wclassifier.empty()) {
        CHECKKKM kkm->ifptr->put_Classifier(wclassifier.data());
        checkError();
    }
    CHECKKKM kkm->ifptr->Registration();
    checkError();
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
    CHECKKKM kkm->ifptr->put_Caption(text.c_str());
    checkError();
    CHECKKKM kkm->ifptr->put_TextWrap(wrap);
    checkError();
    CHECKKKM kkm->ifptr->put_Alignment(alignment);
    checkError();
    CHECKKKM kkm->ifptr->PrintString();
    CHECKERROR;
    return kkm->ErrorCode;
}

int KKM::get_devicedescription(json in, json & out) {
    wchar_t v[64] = L"";
    CHECKKKM kkm->ifptr->get_DeviceDescription(v, 63);
    CHECKERROR;
    out["DeviceDescription"] = KKM::utf8s(v);
    return EC_OK;
}

int KKM::get_build(json in, json & out) {
    wchar_t v[64] = L"";
    CHECKKKM kkm->ifptr->get_Build(v, 63);
    CHECKERROR;
    out["Build"] = KKM::utf8s(v);
    return EC_OK;
}

int KKM::get_verlo(json in, json & out) {
    wchar_t v[64] = L"";
    CHECKKKM kkm->ifptr->get_VerLo(v, 63);
    CHECKERROR;
    out["VerLo"] = KKM::utf8s(v);
    return EC_OK;
}

int KKM::get_verhi(json in, json & out) {
    wchar_t v[64] = L"";
    CHECKKKM kkm->ifptr->get_VerHi(v, 63);
    CHECKERROR;
    out["VerHi"] = KKM::utf8s(v);
    return EC_OK;
}

int KKM::get_licenseexpireddate(json in, json & out) {
    wchar_t v[64] = L"";
    CHECKKKM kkm->ifptr->get_LicenseExpiredDate(v, 63);
    CHECKERROR;
    out["LicenseExpiredDate"] = KKM::utf8s(v);
    return EC_OK;
}

int KKM::get_license(json in, json & out) {
    wchar_t v[64] = L"";
    CHECKKKM kkm->ifptr->get_License(v, 63);
    CHECKERROR;
    out["License"] = KKM::utf8s(v);
    return EC_OK;
}

int KKM::get_licensevalid(json in, json & out) {
    int v;
    CHECKKKM kkm->ifptr->get_LicenseValid(&v);
    CHECKERROR;
    out["LicenseValid"] = v;
    return EC_OK;
}

int KKM::get_machinenumber(json in, json & out) {
    wchar_t b[64] = L"";
    CHECKKKM kkm->ifptr->get_MachineNumber(b, 63) CHECKERROR;
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
    CHECKKKM kkm->ifptr->get_Operator(&v);
    CHECKERROR;
    out["Operator"] = v;
    return EC_OK;
}

int KKM::get_logicalnumber(json in, json & out) {
    int v = 0;
    CHECKKKM kkm->ifptr->get_LogicalNumber(&v);
    CHECKERROR;
    out["LogicalNumber"] = v;
    return EC_OK;
}

int KKM::get_fiscal(json in, json & out) {
    int v = 0;
    CHECKKKM kkm->ifptr->get_Fiscal(&v);
    CHECKERROR;
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
    CHECKKKM kkm->ifptr->get_LicenseNumber(&v);
    CHECKERROR;
    out["LicenseNumber"] = v;
    return EC_OK;
}

int KKM::get_printeroverheaterror(json in, json & out) {
    int v;
    CHECKKKM kkm->ifptr->get_PrinterOverheatError(&v);
    CHECKERROR;
    out["PrinterOverheatError"] = (bool)v;
    return EC_OK;
}

int KKM::get_printercutmechanismerror(json in, json & out) {
    int v;
    CHECKKKM kkm->ifptr->get_PrinterCutMechanismError(&v);
    CHECKERROR;
    out["PrinterCutMechanismError"] = (bool)v;
    return EC_OK;
}

int KKM::get_printermechanismerror(json in, json & out) {
    int v;
    CHECKKKM kkm->ifptr->get_PrinterMechanismError(&v);
    CHECKERROR;
    out["PrinterMechanismError"] = (bool)v;
    return EC_OK;
}

int KKM::get_printerconnectionfailed(json in, json & out) {
    int v;
    CHECKKKM kkm->ifptr->get_PrinterConnectionFailed(&v);
    CHECKERROR;
    out["PrinterConnectionFailed"] = (bool)v;
    return EC_OK;
}

int KKM::get_outofpaper(json in, json & out) {
    int v;
    CHECKKKM kkm->ifptr->get_OutOfPaper(&v);
    CHECKERROR;
    out["OutOfPaper"] = (bool)v;
    return EC_OK;
}

int KKM::get_summ(json in, json & out) {
    double v;
    CHECKKKM kkm->ifptr->get_Summ(&v);
    CHECKERROR;
    out["Summ"] = v;
    return EC_OK;
}

int KKM::get_slotnumber(json in, json & out) {
    int v;
    CHECKKKM kkm->ifptr->get_SlotNumber(&v);
    CHECKERROR;
    out["SlotNumber"] = v;
    return EC_OK;
}

int KKM::get_advancedmode(json in, json & out) {
    int v;
    CHECKKKM kkm->ifptr->get_AdvancedMode(&v);
    CHECKERROR;
    out["AdvancedMode"] = v;
    return kkm->ErrorCode;
}

int KKM::get_fnstate(json in, json & out) {
    int v;
    CHECKKKM kkm->ifptr->get_FNState(&v) CHECKERROR;
    out["FNstate"] = v;
    return kkm->ErrorCode;
}

int KKM::get_fnerror(json in, json & out) {
    int v;
    CHECKKKM kkm->ifptr->get_FNError(&v) CHECKERROR;
    out["FNerror"] = v;
    return kkm->ErrorCode;
}

int KKM::get_mode(json in, json & out) {
    int v;
    CHECKKKM kkm->ifptr->get_Mode(&v);
    CHECKERROR;
    out["Mode"] = v;
    return kkm->ErrorCode;
}

int KKM::get_model(json in, json & out) {
    int v;
    CHECKKKM kkm->ifptr->get_Model(&v);
    CHECKERROR;
    out["Model"] = v;
    return kkm->ErrorCode;
}

int KKM::get_controlpaperpresent(json in, json & out) {
    int v;
    CHECKKKM kkm->ifptr->get_ControlPaperPresent(&v);
    CHECKERROR;
    out["ControlPaperPresent"] = (bool)v;
    return kkm->ErrorCode;
}

int KKM::get_checkpaperpresent(json in, json & out) {
    int v;
    CHECKKKM kkm->ifptr->get_CheckPaperPresent(&v) CHECKERROR;
    out["CheckPaperPresent"] = (bool)v;
    return kkm->ErrorCode;
}

int KKM::get_coveropened(json in, json & out) {
    int v;
    CHECKKKM kkm->ifptr->get_CoverOpened(&v) CHECKERROR;
    out["CoverOpened"] = (bool)v;
    return kkm->ErrorCode;
}

int KKM::get_draweropened(json in, json & out) {
    int v;
    CHECKKKM kkm->ifptr->get_DrawerOpened(&v) CHECKERROR;
    out["DrawerOpened"] = (bool)v;
    return kkm->ErrorCode;
}

int KKM::get_session(json in, json & out) {
    int v;
    CHECKKKM kkm->ifptr->get_Session(&v) CHECKERROR;
    out["Session"] = v;
    return kkm->ErrorCode;
}

int KKM::get_sessionopened(json in, json & out) {
    int v;
    CHECKKKM kkm->ifptr->get_SessionOpened(&v) CHECKERROR;
    out["SessionOpened"] = (bool)v;
    return kkm->ErrorCode;
}

int KKM::get_date(json in, json & out) {
    char b[16];
    int d, m, y;
    CHECKKKM kkm->ifptr->get_Date(&d, &m, &y) CHECKERROR;
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
        CHECKKKM kkm->ifptr->put_Date(d, m, y);
        checkError();
        CHECKKKM kkm->ifptr->SetDate();
        CHECKERROR;
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
    CHECKKKM kkm->ifptr->get_Time(&h, &m, &s) CHECKERROR;
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

