package atm;

public class Account {
	
	String name;
	double bal;

	public Account(String string, double d) {
		name = string;
		bal = d;
	}

	public Object getName() {
		return name;
	}

	public double getBalance() {
		return bal;
	}

}
