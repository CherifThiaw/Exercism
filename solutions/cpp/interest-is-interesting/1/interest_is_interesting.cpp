// interest_rate returns the interest rate for the provided balance.
double interest_rate(double balance) {
    // TODO: Implement the interest_rate function
    if (balance < 0){
        return 3.213;
    }
     else if (balance >= 0 && balance < 1000){
        return 0.5;
    }
     else if (balance >= 1000 && balance < 5000){
        return 1.621;
    }
    else if(balance >= 5000){
        return 2.475;
        
    }
    return 0.0;
}

// yearly_interest calculates the yearly interest for the provided balance.
double yearly_interest(double balance) {
    // TODO: Implement the yearly_interest function
    if (balance < 0){
        return (balance * 3.213) / 100;
    }
     else if (balance >= 0 && balance < 1000){
        return (balance * 0.5) / 100;
    }
     else if (balance >= 1000 && balance < 5000){
        return (balance * 1.621) / 100;
    }
    else if (balance >= 5000){
        return (balance * 2.475) / 100;
        
    }
    return 0.0;
}

// annual_balance_update calculates the annual balance update, taking into
// account the interest rate.
double annual_balance_update(double balance) {
    // TODO: Implement the annual_balance_update function
     if (balance < 0){
        return balance + (balance * 3.213) / 100;
    }
     else if (balance >= 0 && balance < 1000){
        return balance + (balance * 0.5) / 100;
    }
     else if (balance >= 1000 && balance < 5000){
        return balance + (balance * 1.621) / 100;
    }
    else if (balance >= 5000){
        return balance + (balance * 2.475) / 100;
        
    }
    
    return 0.0;
}

// years_until_desired_balance calculates the minimum number of years required
// to reach the desired balance.
int years_until_desired_balance(double balance, double target_balance) {
    // TODO: Implement the years_until_desired_balance function
    int i = 0;
    for (; target_balance > balance; ++i){
     balance = annual_balance_update(balance);
     
 }

    return i;
}
