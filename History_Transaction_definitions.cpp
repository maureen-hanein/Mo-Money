#include <cassert>
#include <iomanip>
#include <iostream>

#include "project4.hpp"
#include "History.hpp"
#include "Transaction.hpp"

////////////////////////////////////////////////////////////////////////////////
// Definitions for Transaction class
////////////////////////////////////////////////////////////////////////////////
//
///

// Constructor
// TASK 1
Transaction::Transaction ( std::string ticker_symbol, unsigned int day_date, unsigned int month_date,
unsigned year_date, bool buy_sell_trans, unsigned int number_shares, double trans_amount)
{
  symbol= ticker_symbol;
  day= day_date;
  month= month_date;
  year= year_date;
 
 //std::string set buy and set sell to a variable 
 if (buy_sell_trans){

 trans_type= "Buy";
 }
 else{
  trans_type = "Sell";
 }


 shares= number_shares;
 amount= trans_amount;
 trans_id= assigned_trans_id;
 assigned_trans_id++;
 
    acb=0;
    acb_per_share=0;
    share_balance=0;
    cgl=0;
p_next = nullptr;

}




// Destructor
// TASK 1
//
Transaction::~Transaction(){
p_next = nullptr;
}

// Overloaded < operator.
// TASK 2
//

bool Transaction::operator<( Transaction const &other ){
  if (this->year <other.year){
    return true; 
  }
  if(this->year== other.year){
    if(this->month< other.month){
      return true;
    }
    else if(this->month== other.month){
      if(this->day< other.day){
        return true;
      }

    else if(this->day== other.day){
      if(this->trans_id > other.trans_id){
        return true;
      }
    }
  }
}
return false;
}

// GIVEN
// Member functions to get values.
//
std::string Transaction::get_symbol() const { return symbol; }
unsigned int Transaction::get_day() const { return day; }
unsigned int Transaction::get_month() const { return month; }
unsigned int Transaction::get_year() const { return year; }
unsigned int Transaction::get_shares() const { return shares; }
double Transaction::get_amount() const { return amount; }
double Transaction::get_acb() const { return acb; }
double Transaction::get_acb_per_share() const { return acb_per_share; }
unsigned int Transaction::get_share_balance() const { return share_balance; }
double Transaction::get_cgl() const { return cgl; }
bool Transaction::get_trans_type() const { return (trans_type == "Buy") ? true: false ; }
unsigned int Transaction::get_trans_id() const { return trans_id; }
Transaction *Transaction::get_next() { return p_next; }

// GIVEN
// Member functions to set values.
//
void Transaction::set_acb( double acb_value ) { acb = acb_value; }
void Transaction::set_acb_per_share( double acb_share_value ) { acb_per_share = acb_share_value; }
void Transaction::set_share_balance( unsigned int bal ) { share_balance = bal ; }
void Transaction::set_cgl( double value ) { cgl = value; }
void Transaction::set_next( Transaction *p_new_next ) { p_next = p_new_next; }

// GIVEN
// Print the transaction.
//
void Transaction::print() {
  std::cout << std::fixed << std::setprecision(2);
  std::cout << std::setw(4) << get_trans_id() << " "
    << std::setw(4) << get_symbol() << " "
    << std::setw(4) << get_day() << " "
    << std::setw(4) << get_month() << " "
    << std::setw(4) << get_year() << " ";


  if ( get_trans_type() ) {
    std::cout << "  Buy  ";
  } else { std::cout << "  Sell "; }

  std::cout << std::setw(4) << get_shares() << " "
    << std::setw(10) << get_amount() << " "
    << std::setw(10) << get_acb() << " " << std::setw(4) << get_share_balance() << " "
    << std::setw(10) << std::setprecision(3) << get_acb_per_share() << " "
    << std::setw(10) << std::setprecision(3) << get_cgl()
    << std::endl;
}


////////////////////////////////////////////////////////////////////////////////
// Definitions for the History class
////////////////////////////////////////////////////////////////////////////////
//
//


// Constructor
// TASK 3
//
History::History(){
p_head= nullptr;
}



// Destructor
// TASK 3
//
History::~History(){
Transaction*x = nullptr;
while(p_head != nullptr){
  x= p_head;
  p_head= p_head-> get_next();
  delete x;
}
x=nullptr;
}





//check if the list is only one node 
//if it is just return;
//classes dont return anything 
//if theres more than one node you want to go through all of them and delete all of them 
//while loop to go through each one and delete it 
//tempx-> will give you whats inside the node
//after u put tempx-> u need to put specifically what ur looking for 
//get_next
//temp: will give u the address 
//}


// read_history(...): Read the transaction history from file.
// TASK 4
//
void History::read_history(){
  ece150:: open_file();
while(ece150::next_trans_entry()){


 Transaction *w = new Transaction(ece150::get_trans_symbol(), ece150::get_trans_day(), ece150::get_trans_month(), ece150::get_trans_year(), ece150::get_trans_type(), ece150::get_trans_shares(), ece150::get_trans_amount());
insert(w);
}

ece150:: close_file();
}

//Transaction::Transaction ( std::string ticker_symbol, unsigned int day_date, unsigned int month_date,
//unsigned year_date, bool buy_sell_trans, unsigned int number_shares, double trans_amount)



// insert(...): Insert transaction into linked list.
// TASK 5
//
void History:: insert(Transaction *p_new_trans){
if(p_head== nullptr){
  p_head= p_new_trans;
}
else{
  Transaction*w =p_head;
  while(w->get_next()!= nullptr){
    w= w-> get_next();
  }
  w-> set_next(p_new_trans);
}


}


// sort_by_date(): Sort the linked list by trade date.
// TASK 6
//
void History::sort_by_date(){
  if( p_head == nullptr){
    return;
  }

  Transaction *p_sorted_head{p_head};
  Transaction *index;
  Transaction *p_head_old{p_head->get_next()};
  p_sorted_head->set_next(nullptr);

  while(p_head_old !=nullptr){
    if(*p_head_old < *p_sorted_head){
      //insert as head      
      Transaction * temp = p_head_old -> get_next();
      p_head_old->set_next(p_sorted_head);
      p_sorted_head = p_head_old;
      p_head_old = temp;
    } else {
      //insert in the middle
      index = p_sorted_head;
      while(index != nullptr){
        if((index-> get_next() != nullptr) && (*p_head_old < *(index-> get_next()))){
          //insert here
          Transaction * temp = index -> get_next();
          Transaction * temp2 = p_head_old -> get_next();
          index->set_next(p_head_old);
          p_head_old->set_next(temp);
          p_head_old = temp2;
          break;
        } else if (index-> get_next() == nullptr){
          //insert at the end
          Transaction * temp = p_head_old->get_next();
          index->set_next(p_head_old);
          p_head_old->set_next(nullptr);
          p_head_old = temp;
          break;
        }
        index = index->get_next();
      }
    }
  }
  p_head = p_sorted_head;
}


// update_acb_cgl(): Updates the ACB and CGL values.
// TASK 7
//
void History:: update_acb_cgl(){
Transaction *x= p_head;
Transaction *w= p_head; //points to previous node of current liked list 
double value_acb= 0;
int value_shares=0;
double value_cgl= 0;
double value_acb_p_share =0;

while( x!= nullptr){
 //if buy 
if(x-> get_trans_type()){// if it's true
value_acb += x-> get_amount();
value_shares += x-> get_shares();
value_acb_p_share = value_acb/value_shares; 
x-> set_acb(value_acb);
x-> set_share_balance(value_shares);
x-> set_acb_per_share(value_acb_p_share);
}
else{
 //if sell
 value_acb_p_share= value_acb/value_shares; 
 value_acb= (w-> get_acb()) - (x-> get_shares())*(w-> get_acb_per_share());
 value_shares -= x-> get_shares();
 value_cgl= (x-> get_amount())- (x->get_shares())*(w->get_acb_per_share());
x-> set_acb(value_acb);
x-> set_share_balance(value_shares);
x-> set_acb_per_share(value_acb_p_share);
x-> set_cgl(value_cgl);  
}
  w= x;
  x= x-> get_next();


}
}

// compute_cgl(): )Compute the ACB, and CGL.
// TASK 8
double History::compute_cgl(unsigned int year){

Transaction* x = p_head;
double sum = 0;// initializing the sum with zero
while((x != nullptr)){ //while the next after x isn't null 
    if(x->get_year()== year){
    sum= sum + x-> get_cgl(); //sum+ gcl of x 
    }
  x= x->get_next();
  
}
return sum; // returns number for a specific year 
}



// print() Print the transaction history.
//TASK 9
//
void History::print(){
std::cout <<"========== BEGIN TRANSACTION HISTORY ============"<< std::endl;
Transaction *T = p_head;
while( T != nullptr){
  T-> print();
  T = T-> get_next();
}
std::cout << "========== END TRANSACTION HISTORY ============"<< std::endl;

}


// GIVEN
// get_p_head(): Full access to the linked list.
//
Transaction *History::get_p_head() { return p_head; }
