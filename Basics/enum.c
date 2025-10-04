#include "../Common/BasicTypes.h"
#include <stdio.h>
typedef enum Months {
  Jan = 0,
  Feb,
  Mar,
  Apr,
  May,
  Jun,
  Jul,
  Aug,
  Sep,
  Oct,
  Nov,
  Dec
} Months;

const String toStringMonth(const Months month) {
  switch (month) {
  case Jan:
    return "January";
  case Feb:
    return "February";
  case Mar:
    return "March";
  case Apr:
    return "April";
  case May:
    return "May";
  case Jun:
    return "June";
  case Jul:
    return "July";
  case Aug:
    return "August";
  case Sep:
    return "September";
  case Oct:
    return "October";
  case Nov:
    return "November";
  case Dec:
    return "December";
  default:
    return "Invalid Month";
  }
}

int main() {
  Months month = 0;
  if (month == Jan) {
    printf("Response for month is %s", toStringMonth(month));
  }

  newline
}