package trial1_2015;

import java.util.HashSet;

public class Room extends Facility {

	Building b;
	int floor;
	int capacity = 0;
	HashSet<User> set = new HashSet<User>();
	
	public Room(Building b, String string, int i) throws DuplicateRoomException {
		if(i > b.getMaxFloor() || i < b.getMinFloor()) {
			throw new IllegalArgumentException();
		}
		this.b = b;
		name = string;
		floor = i;
		b.addRoom(this);
	}

	public Room(Building b2, String string, int i, int j) throws DuplicateRoomException {
		this(b2, string, i);
		capacity = j;
	}

	public Object getBuilding() {
		return b;
	}

	public String getNumber() {
		return name;
	}

	public Object getName() {
		return b.getName() + name;
	}

	public Object getFloor() {
		// TODO Auto-generated method stub
		return floor;
	}

	public String toString() {
		return "Room(" + b.getName() + "," + name + ")";
	}

	public int getCapacity() {
		return capacity;
	}

	public void authorize(User u1) {
		set.add(u1);
	}

	public boolean canEnter(User u1) {
		return set.contains(u1);
	}
}
