#include "airline_ticket.h"
#include "test_runner.h"
#include <istream>
#include <iostream>

using namespace std;

bool operator<(Date lhs, Date rhs)
{
    return 10000 * lhs.year + 100 * lhs.month + lhs.day < 10000 * rhs.year + 100 * rhs.month + rhs.day;
}

istream &operator>>(istream &potok, Date &date)
{
    int year, month, day;
    char r1, r2;
    potok >> year >> r1 >> month >> r2 >> day;
    if (r1 != '-' || r2 != '-')
    {
        //throw invalid_argument("Wrong date format: " + potok.str());
    }
    date.year = year;
    date.month = month;
    date.day = day;
    return potok;
}

istream &operator>>(istream &potok, Time &time)
{
    int hours, minutes;
    char r1;
    potok >> hours >> r1 >> minutes;
    if (r1 != ':')
    {
        //throw invalid_argument("Wrong date format: " + potok.str());
    }
    time.hours = hours;
    time.minutes = minutes;
    return potok;
}

std::ostream &operator<<(ostream &os, Date date)
{
    os << date.year << "-" << date.month << "-" << date.day << std::endl;
    return os;
}


std::ostream &operator<<(ostream &os, Time time)
{
    os << time.hours << ":" << time.minutes << std::endl;
    return os;
}


bool operator==(Time lhs, Time rhs)
{
    return tie(lhs.hours, lhs.minutes) == tie(rhs.hours, rhs.minutes);
}

bool operator==(Date lhs, Date rhs)
{
    return tie(lhs.year, lhs.month, lhs.day) == tie(rhs.year, rhs.month, rhs.day);
}


#define UPDATE_FIELD(ticket, field, values) {\
                                                map<string, string>::const_iterator it;\
                                                it = values.find(#field);\
                                                if (it != values.end()) {\
                                                    istringstream is(it->second);\
                                                    is >> ticket.field;\
                                                }\
                                            }


void TestUpdate(){
    AirlineTicket t;
    t.price = 0;

    const map<string, string> updates1 = {
        {"departure_date", "2018-2-28"},
        {"departure_time", "17:40"},
    };

    UPDATE_FIELD(t, departure_date, updates1);
    UPDATE_FIELD(t, departure_time, updates1);
    UPDATE_FIELD(t, price, updates1);

    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
    ASSERT_EQUAL(t.price, 0);

    const map<string, string> updates2 = {
        {"price", "12550"},
        {"arrival_time", "20:33"},
    };
    UPDATE_FIELD(t, departure_date, updates2);
    UPDATE_FIELD(t, departure_time, updates2);
    UPDATE_FIELD(t, arrival_time, updates2);
    UPDATE_FIELD(t, price, updates2);

    // updates2 не содержит ключей "departure_date" и "departure_time", поэтому
    // значения этих полей не должны измениться
    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
    ASSERT_EQUAL(t.price, 12550);
    ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestUpdate);
}
