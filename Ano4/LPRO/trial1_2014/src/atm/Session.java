package atm;

import java.util.ArrayList;

public class Session implements Countable {

	ATM a;
	ArrayList<Mov> movs = new ArrayList<Mov>();
	public Session(ATM atm) {
		a = atm;
	}

	public ATM getATM() {
		return a;
	}

	public void addTransaction(Mov m) {
		movs.add(m);
	}

	@Override
	public int count() {
		return movs.size();
	}

	public boolean equals(Object o) {
		if(o instanceof Session) {
			Session s = (Session)o;
			return s.a.equals(a);
		}
		return false;
	}

}
