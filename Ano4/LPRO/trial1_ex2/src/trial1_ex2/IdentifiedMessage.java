package trial1_ex2;

public class IdentifiedMessage extends Message {
	String user;

	public IdentifiedMessage(String user, String message) {
		super(message);
		this.user = user;  
	}


	public Object getMessage() {
		return "[" + user + "]: " + super.getMessage();
	}


	public void setUser(String string) {
		this.user = string;
	}

	public String getUser() {
		return user;
	}
	
	public boolean equals(Object o) {
		if(o instanceof IdentifiedMessage) {
			IdentifiedMessage om = (IdentifiedMessage)o;
			return om.message.equals(this.message) && om.user == this.user;
		}
		return false; 
	}
	
	public String toString() {
		return "user:[" + user + "], msg:[" + message + "]";
	}

}
