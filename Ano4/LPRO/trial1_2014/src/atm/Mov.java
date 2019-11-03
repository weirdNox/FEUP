package atm;

public class Mov {
	ATM a;
	Session s;
	Card c;
	int i;
	double d;
	String type;
	
	public Mov(ATM atm, Session s, Card c, int i) {
		this.a = atm;
		this.s = s;
		this.c = c;
		this.i = i;
	}
	
	public String toString() {
		return type + " at ATM " + a.getID() + " (" + a.loc + ", " + a.par + ") of " + String.format("%.2f", d);
	}
}
