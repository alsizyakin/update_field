#include "airline_ticket.h"
#include "test_runner.h"
#include <istream>
#include <iostream>

using namespace std;

#define UPDATE_FIELD(ticket, field, values)  // Реализуйте этот макрос, а также необходимые операторы для классов Date и Time

bool operator < (Date lhs, Date rhs){
return 10000*lhs.year + 100*lhs.month + lhs.day < 10000*rhs.year + 100*rhs.month + rhs.day;
}

/*
std::istream& operator >> (std::istream& is, Date& date){
    is >> date.date;

    return is&;
}
*/

std::ostream& operator << (ostream& os, Date date){
    os << date.year << "-" << date.month << "-" << date.day << std::endl; 
}

std::ostream& operator << (ostream& os, Time time){
    os << time.hours << ":" << time.minutes << std::endl; 
}

bool operator == (Time lhs, Time rhs){
    return tie(lhs.hours, lhs.minutes) == tie(rhs.hours, rhs.minutes); 
}

bool operator == (Date lhs, Date rhs){
    return tie(lhs.year, lhs.month, lhs.day) == tie(rhs.year, rhs.month, rhs.day); 
}


void UpdateTicket(AirlineTicket& ticket, const map<string, string>& updates) {
  UPDATE_FIELD(ticket, to, updates);
  UPDATE_FIELD(ticket, from, updates);
  UPDATE_FIELD(ticket, price, updates);
  UPDATE_FIELD(ticket, airline, updates);

}

void TestUpdate() {
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

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestUpdate);
}
