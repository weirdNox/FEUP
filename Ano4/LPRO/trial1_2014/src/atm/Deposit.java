package atm;

public class Deposit extends Mov {

	ATM a;
	Session s;
	Card c;
	int i;
	
	public Deposit(ATM atm, Session s, Card c, int i) {
		super(atm,s,c,i);
		type = "Deposit";
	}

}
