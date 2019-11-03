package trial1_2015;
import static org.junit.Assert.*;

import org.junit.Test;

public class TestCases {

	@Test
	public void testBuilding() throws Exception {
		Building b = new Building("B", -1, 4);
		assertEquals("B", b.getName());
		assertEquals(-1, b.getMinFloor());
		assertEquals(4, b.getMaxFloor());
	}

	@Test(expected=IllegalArgumentException.class)
	public void testBuildingArgs() throws Exception {
		Building b = new Building("B", 4, -1);
	}

	@Test
	public void testRoom() throws Exception {
		Building b = new Building("B", -1, 4);
		Room r = new Room(b, "104", 1);
		assertSame(b, r.getBuilding());
		assertEquals("104", r.getNumber());
		assertEquals("B104", r.getName());
		assertEquals(1, r.getFloor());
	}

	@Test(expected=IllegalArgumentException.class)
	public void testRoomArgs() throws Exception {
		Building b = new Building("B", -1, 4);
		Room r = new Room(b, "104", 5);
	}
	
	@Test
	public void testFacility() throws Exception {
		Facility b = new Building("B", -1, 4);
		Facility r = new Room((Building)b, "104", 1);
		assertEquals("B", b.getName());
		assertEquals("B104", r.getName());
	}
		
	@Test
	public void testUser() throws Exception {
		User u1 = new User("Rui");
		User u2 = new User("Maria");
		User u3 = new User("Rui");
		assertEquals("Rui", u1.getName());
		assertTrue(u1.equals(u3));
		assertFalse(u1.equals(u2));
	}
		
	@Test
	public void testToString() throws Exception {
		Building b = new Building("B", -1, 4);
		Room b104 = new Room(b, "104", 1);
		assertEquals("Building(B)", b + "");
		assertEquals("Room(B,104)", b104 + "");
	}
		
	@Test
	public void testCapacity() throws Exception {
		Building b = new Building("B", -1, 4);
		assertEquals(0, b.getCapacity());
		Room b104 = new Room(b, "104", 1, 69);
		assertEquals(69, b104.getCapacity());
		Room b208 = new Room(b, "208", 2, 52);
		Room b213 = new Room(b, "213", 2, 52);
		assertEquals(173, b.getCapacity());
	}
			
	@Test(expected = DuplicateRoomException.class)
	public void testDuplicateRooms() throws Exception {
		Building b = new Building("B", -1, 4);
		Room b1 = new Room(b, "104", 1);
		Room b2 = new Room(b, "104", 1);
	}

	@Test
	public void testUserAccess() throws Exception  {
		User u1 = new User("Rui");
		User u2 = new User("Maria");

		Facility b = new Building("B", -1, 4);
		Facility a = new Building("A", -1, 4);
		Room b104 = new Room((Building)b, "104", 1);
		Room a001 = new Room((Building)a, "001", 0);
	
		b104.authorize(u1);
		b104.authorize(u2);
		a001.authorize(u2);
		
		// A user is allowed to enter a room if he/she
		// was previously authorized
		assertTrue(b104.canEnter(u1) );
		assertTrue(b104.canEnter(u2) );
		assertFalse(a001.canEnter(u1) );
		assertTrue(a001.canEnter(u2) );

		// A user is allowed to enter a building if he/she
		// is authorized to enter a room in that building
		assertTrue(b.canEnter(u1));
		assertTrue(b.canEnter(u2));
		assertFalse(a.canEnter(u1));
		assertTrue(a.canEnter(u2));
		
		// All facilities have the "canEnter" method
		Facility f = b104;
		assertTrue(f.canEnter(u1));
	}
}
