#include "utilities.h"

namespace utilities{
    // Verify date
    bool verifyDate(const QString &ver) {
        std::string stdVer = ver.toStdString();

        std::regex expr ("^[0-9]{4}-[0-9]{2}-[0-9]{2}$");

        // Check regex match
        if (std::regex_match(stdVer, expr)) {
            // Get month and day integers
           int month = stoi(stdVer.substr(5,2));
           int day = stoi(stdVer.substr(8,2));

           // Month between 1 and 12
           if(month > 12 || month < 1){
               return false;
           }
           // Day between 1 and 31
           else if(day > 31 || day < 1){
               return false;
           }
           else{
               return true;
           }
        }

        return false;
    }

    // Verify QString as number
    bool isNumber(const QString &str){
        for(int i = 0; i < str.length(); i++){
            if(!str[i].isDigit()){
                return false;
            }
        }

        return true;
    }

    // Convert 1's and 0's to yes and no
    QString boolYesNo(bool num) {
        QString yesNo = "";
        (num) ? yesNo = "yes" : yesNo = "no";
        return yesNo;
    }

    // Yes no to bool
    bool QStringBool(QString s){
        return (s == "y" || s == "yes") ? true : false;
    }

}
