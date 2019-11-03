package atm;

public class ATM {
	int id;
	String loc;
	String par;
	public ATM(int i, String string, String string2) {
		id = i;
		loc = string;
		par = string2;
	}

	public Object getID() {
		return id;
	}

	public boolean equals(Object o) {
		if(o instanceof ATM) {
			ATM a = (ATM)o;
			return a.id == id && a.loc == loc && a.par == par;
		}
		return false;
	}


}
