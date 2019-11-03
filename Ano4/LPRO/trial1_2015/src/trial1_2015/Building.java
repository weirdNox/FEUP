package trial1_2015;

import java.util.HashMap;

public class Building extends Facility {
	int min, max;
	HashMap<String,Room> rooms = new HashMap<String, Room>();

	public Building(String string, int i, int j) {
		if(j < i) {
			throw new IllegalArgumentException();
		}
		name = string;
		min = i;
		max = j;
	}

	public void addRoom(Room r) throws DuplicateRoomException {
		if(rooms.containsKey(r.getNumber())) {
			throw new DuplicateRoomException();
		}
		else {
			rooms.put(r.getNumber(), r);
		}
	}
	
	public int getMinFloor() {
		return min;
	}

	public int getMaxFloor() {
		return max;
	}

	public String toString() {
		return "Building(" + name + ")";
	}

	public Object getCapacity() {
		int cap = 0;
		for(Room r : rooms.values()) {
			cap += r.getCapacity();
		}
		
		return cap;
	}

	@Override
	public boolean canEnter(User u1) {
		for(Room r : rooms.values()) {
			if(r.canEnter(u1)) {
				return true;
			}
		}
		return false;
	}

}
