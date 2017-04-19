/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   datastrings.h
 * Author: vgaltsev@OFFICE.INTERTORG
 *
 * Created on 15 марта 2017 г., 10:09
 */

#ifndef DATASTRINGS_H
#define DATASTRINGS_H

class DS {
public:
    
    enum cassier_codes{
        cassier_1 = 89,
    };
    enum cassier_passwords{
        cassier_password_1 = 6,
    };
    
    static constexpr const char* msg_NO_FUNCTION = "No function";
    static constexpr const char* msg_INVALID_INTERFACE = "Invalid interface";
    static constexpr const char* msg_AUTHTOKEN_REQUIRED = "Auth token required";
    static constexpr const char* msg_AUTHTOKEN_INCORRECT = "Auth token incorrect";
    static constexpr const char* msg_INCORRECT_REQUEST = "Incorrect request";
    static constexpr const char* msg_INCORRECT_FORMAT = "Incorrect format";
    
    enum error_codes{
        code_ERROR = -10000,
        code_NO_FUNCTION = -10001,
        code_INVALID_INTERFACE = -10002,
        code_INCORRECT_REQUEST = -10003,
        code_INCORRECT_FORMAT = -10004,
        
        
        code_AUTH_TOKEN_REQUIRED = -10998,
        code_AUTH_TOKEN_INCORRECT = -10999,
    };
    
    
    static constexpr const char* cmd_STATUS = "STATUS";
    static constexpr const char* cmd_SELL = "SELL";
    static constexpr const char* cmd_COMMANDS = "COMMANDS";
    static constexpr const char* cmd_SET_TIME = "SET_TIME";
    static constexpr const char* cmd_SET_DATE = "SET_DATE";
    static constexpr const char* cmd_SET_SYSTEMDATETIME = "SET_SYSTEMDATETIME";
    static constexpr const char* cmd_SET_SYSTEMTIME = "SET_SYSTEMTIME";
    static constexpr const char* cmd_SET_SYSTEMDATE = "SET_SYSTEMDATE";
    static constexpr const char* cmd_SET_KKMSYSTEMTIME = "SET_KKMSYSTEMTIME";
    
    
    static constexpr const char* fld_VALUE = "value";
    static constexpr const char* fld_DATETIME = "datetime";
    static constexpr const char* fld_TIME = "time";
    static constexpr const char* fld_DATE = "date";
    static constexpr const char* fld_ALIGN = "align";
    static constexpr const char* fld_WRAP = "wrap";
    static constexpr const char* fld_PARAMETERS = "parameters";
    static constexpr const char* fld_COMMAND = "command";
    static constexpr const char* fld_OPERATOR_POST = "operatorPost";
    static constexpr const char* fld_OPERATOR_NAME = "operatorName";
    static constexpr const char* fld_OPERATOR_ID = "operatorId";
    static constexpr const char* fld_OPERATOR_PASSWORD = "operatorPassword";
    static constexpr const char* fld_OPEN = "open";
    static constexpr const char* fld_OPEN_TYPE = "openType";
    static constexpr const char* fld_CLOSE = "close";
    static constexpr const char* fld_CLASS = "class";
    static constexpr const char* fld_NAME = "name";
    static constexpr const char* fld_PRICE = "price";
    static constexpr const char* fld_QUANTITY = "quantity";
    static constexpr const char* fld_DISCOUNT = "discount";
    static constexpr const char* fld_TAX_NUMBER = "taxNumber";
    static constexpr const char* fld_BARCODE = "barcode";
    static constexpr const char* fld_TYPE = "type";
    static constexpr const char* fld_TEXT = "text";
    static constexpr const char* fld_SCALE = "scale";
    static constexpr const char* fld_SUMM = "summ";
    static constexpr const char* fld_PAYMENT_TYPE = "paymentType";
    static constexpr const char* fld_BUYER_CONTACT = "buyerContact";
    static constexpr const char* fld_OPERATOR_CONTACT = "operatorContact";
    static constexpr const char* fld_AUTHTOKEN = "authToken";
    static constexpr const char* arr_BARCODES[] = {
        "EAN8", "EAN13", "UPCA", "Code39", "QR", "PDF417", "ITF14",
        "Interleaved2of5", "UPCE", "Codabar", "Code93", "Code128",
        0
    };
    
};

#endif /* DATASTRINGS_H */

