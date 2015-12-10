#ifndef UTILITIES_H
#define UTILITIES_H

#include "person.h"
#include "machine.h"
#include "personmachine.h"
#include <regex>
#include <string>

// = UTILITY FUNCTIONS =

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

    // Largest size_t value
    size_t largestValue(const QVector<size_t> &v){
        size_t largest = 0;

        for(int i = 0; i < v.size(); i++){
            if(v[i] > largest){
                largest = v[i];
            }
        }

        return largest;
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

    // Get person index by ID
    int getPIndexByID(QVector<Person> p, int id){
        int start = 0;
        int end = (int)p.size() - 1;
        int middle = -1;
        int currentID;

        while(start <= end){
            // Get middle element index
            middle = start + ((end - start)/2);

            // Get middle element's ID
            currentID = p[middle].getId();

            // Found
            if(currentID == id){
                return middle;
            }
            // Higher
            else if(currentID < id){
                start = middle + 1;
            }
            // Lower
            else{
                end = middle - 1;
            }
        }

        // Not found
        if(end < start){
            middle = -1;
        }

        return middle;
    }

    // Get machine index by ID
    int getMIndexByID(QVector<Machine> m, int id){
        int start = 0;
        int end = (int)m.size() - 1;
        int middle = -1;
        int currentID;

        while(start <= end){
            // Get middle element index
            middle = start + ((end - start)/2);

            // Get middle element's ID
            currentID = m[middle].getId();

            // Found
            if(currentID == id){
                return middle;
            }
            // Higher
            else if(currentID < id){
                start = middle + 1;
            }
            // Lower
            else{
                end = middle - 1;
            }
        }

        // Not found
        if(end < start){
            middle = -1;
        }

        return middle;
    }

    // Verify gender input
    QString verifyGender(QString g){
        g = g[0].toLower();

        if(g == ""){
            g = "Please enter a gender.";
        }
        else if(g[0] != 'm' && g[0] != 'f'){
            g = "Invalid gender input";
        }
        else{
            g = (g[0] == 'm') ? g = "male" : g = "female";
        }

        return g;
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

#endif // UTILITIES_H
