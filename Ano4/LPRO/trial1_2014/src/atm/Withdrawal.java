package atm;

public class Withdrawal extends Mov {

	public Withdrawal(ATM atm, Session s, Card c, int i) {
		super(atm,s,c,i);
		type = "Withdrawal";
	}

	public void setAmount(double d) {
		this.d = d;
		
	}

	public double getAmount() {
		return d;
	}

}
