#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cstdio>
#include "Json.hpp"
using namespace std;

int base64Pre(const std::string & str64, char* des)
{
    int i = 0;
    for(std::string::const_iterator it = str64.begin(); it != str64.end(); ++it)
    {   
        if((*it >= 'A' && *it <= 'Z') || (*it >= 'a' && *it <= 'z') || (*it >= '0' && *it <= '9') || *it == '=' || *it == '/' || *it == '+')
        {   
            *(des + i++) = *it;
        }   
        if(*it == ' ')
        {
            *(des + i++) = '+';
        }
    }   
    return i;
}

int main()
{
        string post = " { \"cdata\" : \"AAAF9LtrAAAAgG6VODuK7HzQOdNqBRhsnXXI1rgMteJzCV0mWURazoFavWkqw7XLH7/QD5brEgvJprfwQa50GrFojvDwaYDhzTwGwLCyJ/vjNIgkwwQMGq7OrKIxFR OUHjpGeuEEzpJ8jhYYP3vQ4GGMHVZ0V66UmVPvaLavb7BS1Awztq3e7XM8YhVh13gJJVgC4wSxgwJUJoxWXZPnHiOvRfL79POIOGEGQL6xQyA/TFlC2/SkBnaLGDTDXVof4yl5mqxciNBTUcTHiUmRT16bScgO8HqDSUfWefIEhMis5x6F0E1ifn5PsvhPvlMEolJgX6unb7dC1bkYT7 HI6dmPQPXW/7EzcRfBSp9n2RDH2XDbKT4UsK16W93et PY3azBMfwGtBEXiD6xU/8e4TUf7jEWguPpbv5iykF9yUbAsav1vjwVX6R1sZ4jux0Tx01vjrp4mR8Iz42kxIj3cI2rf6aBYpiJeTL3KvpLWXojdWJ6JsJ56vCU9uP/YkDkdIqbaLznUCc0zzTNqHCNBxh/kRNovvM9h9QKgQ6Uqr6G4twYaWs CmrtCm0T68t23ChlC21xaDaNcSskFYxd510i3wekfOuAOJ2QAN66409Lzcz4N1k2WcOVHXm h/XvPuYPorDyN3glRdN4lM2J89xsr91nN2EBnQEn4EOOMNbmtE rc p5EwzP7a0yRPwF3Y5/xABTxANcY9t5SmhGsHcT4jEwiEGE96eKRa14Q9iJ2qu2zhoQn6gbt1NQlaZyLEjqGawkJNVg91u750n3bHWvRu0u/DH98I58J3bmHjlNxvr4x jG9UXs3NZmHUTInAc0WOH0aW0VQ/ywVYkAhc/lRuYzRckJO6EOnAlzpssnJaNg76mJOcxIHQxSwhmZoYCmEITgwZ1uFsi8P5zrgxKfGcDQ2fXgeyoVdHnmd7VJEhPuSnAz0jxmo9khrXxSeeAPQzzI9vYougd9fTPwHfyj4VJMgevVHXAf3o4t2er4hntfQVx0Dhk7o4ZACU6zbd6/L/7AyrxiEzuYToFQP6jdId/HjdjXDOsr5KGFkZ1VWHCCptGwcwrkqOqXrZ9s0w7FanySWRPnLn5F 5jDVmdhDYSkVqRgscpV0PL7P7CCJp3kA99AYxWCotf0BehBDoOqeoo12RUkZhbEa5ty/NsOWAMa5JgPWTUa3L8nwedGfsACvfhTJHb3rRctI1wL JrlQqP0kD/fucE/r83QzNVoTP1gH4p2giBlwT3WdbMKuI9SAEYZQ4xvoinppgJZQgcVbOdpyZE2LqQtbPQHgo749CwphI1/JTGjdwqJZ UN8fUbNCwqt08MDbfK39QDMmR Xl9Yc2yqGh2uJKEYRR/ePRe8L 4ohtlHQ8O44UQRwcBFdBTESHmIQv1Aes45oMCWTSBCDUPp6nywss/2rDP0VRhvFB DsElJ/slhrzPmOCzwW53RRX cZSq7VXHlxtG9oTVuDNroJAglpHlVLFMYaJ0mCxH2i862F/N4jn5JJCj/3HdnTVq14SGoB6LxKt3kcEfbmSAg0wm8kdE0hJTy9QKX8evc G0yuEfAjFFy8nsmPyrKHV/ujvh1NK8FeDdxM7KmYsVwlqP7CBQj3ZgrOD7N8rQYESlzXDZpNeysp8pVO xmeWpI8trohuDnccQUsjFFLchxAE4zITm4j mb7FO5M4qeC DkCEeYbxfGp13XMatD6HTyqdrD2A2/GqbMmi9yPGeXndSXC/VW1DvrEavEqIsvnn8mZniwuromcHZ66bPs9KA0g56eLJTmojxrcFn32oQnO0mVTeYVTznd1ZxG9WL pF1bhi9mbvEFqQLdjYZig1ILEv/bI7vxtfw2TLOXlgrFo3sjWesHIAu8UCEDnwrHJVxSRMqVRVsEi5ql8tXL4ZUyY3e7Rv B/wnDTy5sCrf7DmyJl4qb1dWLvLCN5NZrqDpFOa89vckQtOHbsu5zrJld0pT9MInK1h/08mX7n6MoFPmg1eXII/mn4eskCfAeTkivpc1Bc93biZDt56 lw \" } ";
        json::Value jsPara = json::Deserialize(post);
        cout<< "the para is:" << post << "#end" << endl;
        cout<< "the para is:" << json::Serialize(jsPara) << "#end" << endl;
}
