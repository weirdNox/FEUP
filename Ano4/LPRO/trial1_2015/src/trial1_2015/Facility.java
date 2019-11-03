package trial1_2015;

public abstract class Facility {
	String name;

	public Object getName() {
		return name;
	}

	public abstract boolean canEnter(User u1);

}
