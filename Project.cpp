#include <iostream>
#include <sstream>
#include <string>
#include "help.hpp"
using namespace std;

void loadCalculations(Revenue *Rev, Expenses *Exp)
{
  if (Rev == NULL && Exp == NULL)
  {
    cout << "There are currently no Revenue or Expense items." << endl;
  }
  else
  {
    float totalRevOneTime= 0.00;
    float totalRevMonthly= 0.00;
    float totalExpensesOneTime= 0.00;
    float totalExpensesMonthly= 0.00;
    Revenue *tempRev = Rev;
    Expenses *tempExp = Exp;
    int count1 = 1;
    int count2 = 1;
    cout << "             OneTime     Monthly" << endl;

    while(tempRev != NULL)
    {
      totalRevOneTime = totalRevOneTime + tempRev->oneTime;
      totalRevMonthly = totalRevMonthly + tempRev->monthly;
      cout << "Item " << count1 << ":" << "      $     " << tempRev->oneTime << "     $     " << tempRev->monthly << endl;
      count1++;
      tempRev=tempRev->next;
    }

    while(tempExp != NULL)
    {
      totalExpensesOneTime = totalExpensesOneTime + tempExp->oneTime;
      totalExpensesMonthly = totalExpensesMonthly + tempExp->monthly;
      cout << "Expense " << count2 << ":" << "   $     " << tempExp->oneTime << "     $     " << tempExp->monthly << endl;
      count2++;
      tempExp = tempExp->next;
    }
    float TotalRev = (totalRevMonthly*12)+totalRevOneTime;
    float TotalExpense= (totalExpensesMonthly*12)+totalExpensesOneTime;
    cout << "             OneTime     Monthly     Total" << endl;
    cout << "Revenue:     $     " <<totalRevOneTime<< "           " << totalRevMonthly <<"         " << TotalRev << endl;
    cout << "Expenses:    $     " <<totalExpensesOneTime<< "           " << totalExpensesMonthly <<"         " << TotalExpense << endl;

    float contribution= TotalRev - TotalExpense;
    float monthlyContribution = totalRevMonthly - totalExpensesMonthly;
    float contributionMargin = (contribution/TotalRev) * 100;
    float ROI = (totalExpensesOneTime - totalRevOneTime)/monthlyContribution;

    cout << "contribution:                  " << monthlyContribution << "         " << contribution << endl;
    cout << "contribution Margin: " << contributionMargin << "%" <<endl;
    cout << "Capital ROI: " << ROI << endl << endl << endl << endl;
  }
}

Revenue* addRevenue(Revenue *head)
{
  Revenue *temp = head;
  Revenue *newRev = new Revenue;
  newRev->oneTime = 0;
  newRev->monthly = 0;
  newRev->next = NULL;
  newRev->prev = NULL;

  string oneCost;
  string moCost;

  cout << "Please enter One-Time cost" << endl;
  cin >> oneCost;
  newRev->oneTime = stof(oneCost);

  cout << "Plesae enter Monthly cost" << endl;
  cin >> moCost;
  newRev->monthly = stof(moCost);
  if (head == NULL)
  {
    head = newRev;
    return head;
  }
  else
  {
    while(temp->next !=NULL)
    {
      temp = temp->next;
    }
    temp->next = newRev;
    temp->next->prev = temp;
    return head;
  }
}

Expenses* addExpense(Expenses *head)
{
  Expenses *temp = head;
  Expenses *newExp = new Expenses;
  newExp->oneTime = 0;
  newExp->monthly = 0;
  newExp->next = NULL;

  string oneCost;
  string moCost;
  cout << "Please enter One-Time cost" << endl;
  cin >> oneCost;
  newExp->oneTime = stof(oneCost);
  cout << "Plesae enter Monthly cost" << endl;
  cin >> moCost;
  newExp->monthly=stof(moCost);
  if(head == NULL)
  {
    head = newExp;
    return head;
  }
  else
  {
    while(temp->next != NULL)
    {
      temp = temp->next;
    }
    temp->next = newExp;
    temp->next->prev = temp;
    return head;
  }
}
Revenue* deleteRev(Revenue *head, int revTotal)
{
  string input;
  cout << "Select which Revenue item to delete" << endl;
  cin >> input;
  int in = stoi(input);

  if (in > revTotal)
  {
    cout << "Item does not exist" << endl;
    return NULL;
  }
  else
  {
    Revenue *delNode = head;
    int spot = 1;
    while(spot < in)
    {
      delNode = delNode->next;
      spot ++;
    }

    if(spot == 1)
    {
      head = delNode->next;
      delete delNode;
      delNode = NULL;
      return head;
    }
    else
    {
      Revenue *temp = delNode->prev;
      temp -> next = delNode->next;
      delete delNode;
      return head;
    }
  }
}

Expenses* deleteExp(Expenses *head, int expTotal)
{
  string input;
  cout << "Select which Expense item to delete" << endl;
  cin >> input;
  int in = stoi(input);

  if (in > expTotal)
  {
    cout << "Item does not exist" << endl;
    return NULL;
  }
  else
  {
    Expenses *delNode = head;
    int spot = 1;
    while(spot < in)
    {
      delNode = delNode->next;
      spot ++;
    }

    if(spot == 1)
    {
      head = delNode->next;
      delete delNode;
      delNode = NULL;
      return head;
    }
    else
    {
      Expenses *temp = delNode->prev;
      temp -> next = delNode->next;
      delete delNode;
      return head;
    }
  }
}


void helperfunction(Revenue *head)
{
  Revenue* temp = head;
  while (temp != NULL)
  {
    cout << temp->oneTime << " " << temp->monthly <<endl;
    temp = temp->next;
  }
}
int main()
{
  int totalRevItems = 0;
  int totalExpenseItems = 0;
  Revenue *Rev = NULL;
  Expenses *Exp = NULL;
  bool test = false;
  cout << "Welcome! Below are your options." << endl;
  cout << "-------------------------------" << endl;

  while(!test)
  {
    int choice;
    cout <<"1. Load Current Calculations" << endl;
    cout <<"2. Add Revenue Item" << endl;
    cout <<"3. Add Expense Item" << endl;
    cout << "4. Delete Revenue Item" << endl;
    cout << "5. Delete Expense Item" << endl;
    cout <<"6. Quit" << endl;
    cout << "Please select an option:" << endl;
    cin >> choice;

    switch(choice)
    {
      case 1:
      loadCalculations(Rev, Exp);
        break;

      case 2:
      Rev = addRevenue(Rev);
      totalRevItems++;
        break;

      case 3:
      Exp = addExpense(Exp);
      totalExpenseItems++;
        break;

      case 4:
      Rev = deleteRev(Rev, totalRevItems);
      totalRevItems --;
        break;

      case 5:
      Exp = deleteExp(Exp,totalExpenseItems);
      totalExpenseItems--;
        break;

      case 6:
        test = true;
        break;

      default:
      cout <<"Invalid Response" << endl;
        break;
    }
  }
  return 0;
}
