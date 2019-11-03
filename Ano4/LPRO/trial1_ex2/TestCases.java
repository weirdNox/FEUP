import static org.junit.Assert.*;

import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.util.ArrayList;
import java.util.Random;
import java.util.TreeSet;

import org.junit.Test;

public class TestCases {
	// ---- auxiliary methods : THESE ARE NOT TEST METHODS -----
	private void fieldsArentPublic(Class<?> ... classes) {
		for (Class<?> c: classes)
			for (Field f : c.getDeclaredFields())
				assertFalse(Modifier.isPublic(f.getModifiers()));
	}

	private void isAbstract(Class<?> c) {
		assertTrue(Modifier.isAbstract(c.getModifiers()));
	}
	private void hasNoSuchMethod(Class<?> c, String methodName) {
		Method[] ms = c.getMethods();
		for (Method m : ms) {
			assertFalse("Class '"+c.getName()+"' must not have a method called '"+methodName+"'",m.getName().equals(methodName));
		}
	}
	private String generateRandomString() {
    	String alfabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    	StringBuffer sb = new StringBuffer();
    	Random r = new Random();
    	int l = 0;
    	do {
    		l = r.nextInt(20);
    	} while (l < 3);
    	for (int i = 0; i < l; i++) {
    		sb.append(alfabet.charAt(r.nextInt(alfabet.length())));
    	}
    	return sb.toString();
    }
	// -----------------------------


	@Test
	public void testMessageConstructorAndAccessors() {
		String s = generateRandomString();
		Message m = new Message(s);
		assertEquals(s, m.getMessage());

		s = generateRandomString();
		m.setMessage(s);
		assertEquals(s, m.getMessage());

		fieldsArentPublic(Message.class);

	}

	@Test
	public void testIdentifiedMessageConstructorAndAccessors() {
		Message m = new IdentifiedMessage("Nuno", "Greetings!");
		assertEquals("[Nuno]: Greetings!",m.getMessage());

		IdentifiedMessage idm = (IdentifiedMessage)m;
		idm.setUser("Flores");
		assertEquals("[Flores]: Greetings!",m.getMessage());
		assertEquals("Flores", idm.getUser());

		hasNoSuchMethod(Message.class, "setUser");
		fieldsArentPublic(IdentifiedMessage.class);
	}

	@Test
	public void testMessageFormattingStrategy() {
		Message m1 = new IdentifiedMessage("Nuno", "hello world!");
		Message m2 = new IdentifiedMessage("Honorio", "hi there, people!");
		Message m3 = new IdentifiedMessage("Flores", "greetings, dear students!");

		MessageFormatter mf = new Post(); // Normal message
		m1.setFormattingStrategy(mf);
		m2.setFormattingStrategy(mf);
		m3.setFormattingStrategy(mf);

		assertEquals("[Nuno]: hello world!", m1.getMessage());
		assertEquals("[Flores]: greetings, dear students!", m3.getMessage());
		assertEquals("[Honorio]: hi there, people!", m2.getMessage());

		mf = new Shout(); // All message letters UPPERCASE.
		m1.setFormattingStrategy(mf);
		m2.setFormattingStrategy(mf);
		m3.setFormattingStrategy(mf);

		assertEquals("[Honorio]: HI THERE, PEOPLE!", m2.getMessage());
		assertEquals("[Flores]: GREETINGS, DEAR STUDENTS!", m3.getMessage());
		assertEquals("[Nuno]: HELLO WORLD!", m1.getMessage());

		mf = new Capitalize(); // All First Letters Of Words UPPERCASE.
		m1.setFormattingStrategy(mf);
		m2.setFormattingStrategy(mf);
		m3.setFormattingStrategy(mf);

		assertEquals("[Flores]: Greetings, Dear Students!", m3.getMessage());
		assertEquals("[Nuno]: Hello World!", m1.getMessage());
		assertEquals("[Honorio]: Hi There, People!", m2.getMessage());


		isAbstract(MessageFormatter.class);
	}

    @Test
    public void testConversation() {
    	Conversation c = new Conversation(3);
    	assertEquals(3, c.getMaxNumberOfUsers());
    	assertEquals(0, c.getUserCount());

    	c.addUser("Luis");
    	c.addUser("Luis");
    	c.addUser("Pedro");
    	c.addUser("Joaquim");

    	assertEquals(3, c.getUserCount());

    	c.addUser("João");

    	assertEquals(3, c.getUserCount());

    	c.addMessage(new IdentifiedMessage("Pedro", "Hi there!"));
    	c.addMessage(new IdentifiedMessage("Luis", "Hello!"));

    	assertEquals(2,c.getMessageCount());

    	c.addMessage(new IdentifiedMessage("Sergio", "How are you?"));

    	assertEquals(2,c.getMessageCount());

    	c.addMessage(new IdentifiedMessage("Joaquim", "Where have you been?"));

    	assertEquals(3,c.getMessageCount());
    }

	@Test
	public void testEqualMessage() {
		Message m1 = new Message("This is a new message.");
		Message m2 = new Message("This is a new message.");
		Message m3 = new Message("This is another new message.");

		assertNotSame(m1,m2);
		assertEquals(m1,m2);
		assertTrue(m1.equals((Object)m2));
		assertNotEquals(m1,m3);
		assertFalse(m1.equals((Object)m3));

		m1 = new IdentifiedMessage("Henrique", "This is a new message.");
		m2 = new IdentifiedMessage("Alvaro", "This is a new message.");
		m3 = new IdentifiedMessage("Alvaro", "This is a new message.");

		assertNotEquals(m1,m2);
		assertNotSame(m2,m3);
		assertEquals(m2,m3);
		assertTrue(m2.equals((Object)m3));
		assertFalse(m1.equals((Object)m2));
 	}

	@Test
	public void testRemoveUser() {
		Conversation c = new Conversation(3);

    	c.addUser("Nuno");
    	c.addUser("Rodrigues");
    	c.addUser("Flores");

    	c.removeUser("Honorio");

    	assertEquals(3,c.getUserCount());

    	c.removeUser("Flores");

    	assertEquals(2,c.getUserCount());
	}

	@Test
	public void testToString() {
		Message m = new Message("A printed message.");
		assertEquals("msg:[A printed message.]", ""+m);

		m = new Message("Another printed message.");
		assertEquals("msg:[Another printed message.]", ""+m);

		m = new IdentifiedMessage("Nuno", "A printed message.");
		assertEquals("user:[Nuno], msg:[A printed message.]", ""+m);

		m = new IdentifiedMessage("Flores", "Another printed message.");
		assertEquals("user:[Flores], msg:[Another printed message.]", ""+m);
	}

	@Test
	public void testCopyConstructor() {
		Message m = new Message("This is an original message");
		m.setFormattingStrategy(new Shout());

		Message m1 = new Message(m);

		assertNotSame(m, m1);
		assertEquals(m,m1);
		assertEquals("THIS IS AN ORIGINAL MESSAGE", m.getMessage());
		assertEquals("THIS IS AN ORIGINAL MESSAGE", m1.getMessage());
		assertEquals(m.getMessage(), m1.getMessage());

		m.setFormattingStrategy(new Capitalize());

		assertNotEquals(m.getMessage(), m1.getMessage());
	}

	@Test
	public void testCompareTo() {
		TreeSet<Message> messages = new TreeSet<Message>();

		messages.add(new Message("Xander is back!"));
		messages.add(new Message("Follow him!"));
		messages.add(new Message("All is well."));
		messages.add(new Message("Hope is near."));

		Message[] a = messages.toArray(new Message[4]);
		assertEquals(a[0].getMessage(),"All is well.");
		assertEquals(a[1].getMessage(),"Follow him!");
		assertEquals(a[2].getMessage(),"Hope is near.");
		assertEquals(a[3].getMessage(),"Xander is back!");

	}

	@Test
	public void testUserMessages() {
		Conversation c = new Conversation(2);

    	c.addUser("Nuno");
    	c.addUser("Flores");

    	c.addMessage(new IdentifiedMessage("Nuno","Hello!"));
    	c.addMessage(new IdentifiedMessage("Flores","Hi there!"));
    	c.addMessage(new IdentifiedMessage("Nuno","How is everything?"));
    	c.addMessage(new IdentifiedMessage("Flores","Fine! And you?"));
    	c.addMessage(new IdentifiedMessage("Nuno","All is well."));
    	c.addMessage(new IdentifiedMessage("Flores","Great!"));
    	c.addMessage(new IdentifiedMessage("Flores","See ya!"));

    	ArrayList<Message> messagesFromNuno = c.getUserMessages("Nuno");
    	ArrayList<Message> messagesFromFlores = c.getUserMessages("Flores");

    	ArrayList<Message> messagesFromNoOne = c.getUserMessages("Honorio");

    	assertEquals(3,messagesFromNuno.size());
    	assertEquals(4,messagesFromFlores.size());
    	assertEquals(0,messagesFromNoOne.size());

    	assertTrue(messagesFromNuno.contains(new Message("Hello!")));
    	assertTrue(messagesFromNuno.contains(new Message("How is everything?")));
    	assertTrue(messagesFromNuno.contains(new Message("All is well.")));

    	assertTrue(messagesFromFlores.contains(new Message("Hi there!")));
    	assertTrue(messagesFromFlores.contains(new Message("Fine! And you?")));
    	assertTrue(messagesFromFlores.contains(new Message("Great!")));
    	assertTrue(messagesFromFlores.contains(new Message("See ya!")));

	}

}
