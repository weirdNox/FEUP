package trial1_2015;

public class User {
	
	String name;

	public User(String string) {
		name = string;
	}

	public Object getName() {
		return name;
	}

	public boolean equals(Object o) {
		if(o instanceof User) {
			User ou = (User)o;
			return ou.name == name;
		}
		return false;
	}

}
