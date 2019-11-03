package atm;

import static org.junit.Assert.*;
import org.junit.Test;
import java.util.TreeSet;

public class TestATM {
	@Test
	public void testCard() {
		Card c = new Card(12345);
		assertEquals(12345, c.getNumber());
	}
	
	@Test
	public void testAccount() {
		Account a = new Account("Manuel", 500.00);
		assertEquals("Manuel", a.getName());
		assertEquals(500.00, a.getBalance(), 1e-10);
	}

	@Test
	public void testSession() {		
		ATM atm = new ATM(987, "Porto", "CGD");
		Session s = new Session(new ATM(987, "Porto", "CGD"));
		assertEquals(987, s.getATM().getID());
	}

	@Test
	public void testWithDrawal() {
		ATM atm = new ATM(987, "Porto", "CGD");
		Card c = new Card(12345);
		Session s = new Session(new ATM(987, "Porto", "CGD"));
		Withdrawal w = new Withdrawal(atm, s, c, 1234);
		w.setAmount(100.00);
		assertEquals(100.0, w.getAmount(), 1e-10);		
	}
	
	@Test
	public void testCountable() {
		ATM atm = new ATM(987, "Porto", "CGD");
		Card c = new Card(12345);
		Session s = new Session(new ATM(987, "Porto", "CGD"));
		Withdrawal w = new Withdrawal(atm, s, c, 1234);
		Deposit d = new Deposit(atm, s, c, 1234);
		s.addTransaction(w);
		s.addTransaction(d);
		Countable sessionCount = s;
		assertEquals(2, sessionCount.count());
	}

	@Test
	public void testAsText() {
		ATM atm = new ATM(987, "Porto", "CGD");
		Card c = new Card(12345);
		Session s = new Session(new ATM(987, "Porto", "CGD"));
		Withdrawal w = new Withdrawal(atm, s, c, 1234);
		w.setAmount(100.00);
		assertEquals("Withdrawal at ATM 987 (Porto, CGD) of 100.00", "" + w);
	}
	
	@Test
	public void testSessionEquals() {
		Session s = new Session(new ATM(987, "Porto", "CGD"));
		assertEquals(true, s.equals(new Session(new ATM(987, "Porto", "CGD"))));		
	}
}